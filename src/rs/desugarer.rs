// Desugarer phase: Desugars ForIn loops to while loops with get() calls,
// and Switch statements to if/else chains.
// This phase runs after typer, before precomp.

use crate::rs::init::{Context, get_value_type, SymbolInfo, ScopeType};
use crate::rs::parser::{
    Expr, NodeType, ValueType, SStructDef, SNamespaceDef, SFuncDef, Literal,
    Declaration, str_to_value_type, transform_continue_with_step,
};

// ============================================================================
// AST Construction Helpers
// These reduce verbosity when building AST nodes during desugaring
// ============================================================================

/// Create an identifier expression
fn make_id(name: &str, line: usize, col: usize) -> Expr {
    Expr::new_explicit(NodeType::Identifier(name.to_string()), vec![], line, col)
}

/// Create a function call: name(args...)
fn make_call(name: &str, args: Vec<Expr>, line: usize, col: usize) -> Expr {
    let mut params = vec![make_id(name, line, col)];
    params.extend(args);
    Expr::new_explicit(NodeType::FCall(false), params, line, col)
}

/// Create a string literal
fn make_str(s: &str, line: usize, col: usize) -> Expr {
    Expr::new_explicit(NodeType::LLiteral(Literal::Str(s.to_string())), vec![], line, col)
}

/// Create a number literal
fn make_num(n: &str, line: usize, col: usize) -> Expr {
    Expr::new_explicit(NodeType::LLiteral(Literal::Number(n.to_string())), vec![], line, col)
}

/// Create a body block
fn make_body(stmts: Vec<Expr>, line: usize, col: usize) -> Expr {
    Expr::new_explicit(NodeType::Body, stmts, line, col)
}

/// Create an if expression (with optional else)
fn make_if(cond: Expr, then_body: Expr, else_body: Option<Expr>, line: usize, col: usize) -> Expr {
    match else_body {
        Some(else_b) => Expr::new_explicit(NodeType::If, vec![cond, then_body, else_b], line, col),
        None => Expr::new_explicit(NodeType::If, vec![cond, then_body], line, col),
    }
}

/// Create a variable declaration with initializer
fn make_decl(name: &str, value_type: ValueType, is_mut: bool, init: Expr, line: usize, col: usize) -> Expr {
    let decl = Declaration {
        name: name.to_string(),
        value_type,
        is_mut,
        is_copy: false,
        is_own: false,
        default_value: None,
    };
    Expr::new_explicit(NodeType::Declaration(decl), vec![init], line, col)
}

/// Create an assignment statement
fn make_assign(name: &str, value: Expr, line: usize, col: usize) -> Expr {
    Expr::new_explicit(NodeType::Assignment(name.to_string()), vec![value], line, col)
}

/// Create an identifier with nested field access: name.field1.field2...
fn make_field_access(name: &str, fields: Vec<&str>, line: usize, col: usize) -> Expr {
    let field_params: Vec<Expr> = fields.iter().map(|f| make_id(f, line, col)).collect();
    Expr::new_explicit(NodeType::Identifier(name.to_string()), field_params, line, col)
}

/// Generate a unique temp variable name with optional function prefix
fn make_temp_name(prefix: &str, func_name: &str, id: usize) -> String {
    if !func_name.is_empty() {
        format!("{}_{}_{}", prefix, func_name, id)
    } else {
        format!("{}_{}", prefix, id)
    }
}

/// Build: eq(var_name, enum_to_str(case_pattern))
fn build_enum_eq_condition(var_name: &str, case_pattern: &Expr, line: usize, col: usize) -> Expr {
    let case_val_str = make_call("enum_to_str", vec![case_pattern.clone()], line, col);
    make_call("eq", vec![make_id(var_name, line, col), case_val_str], line, col)
}

/// Build: eq(var_name, case_pattern)
fn build_eq_condition(var_name: &str, case_pattern: &Expr, line: usize, col: usize) -> Expr {
    make_call("eq", vec![make_id(var_name, line, col), case_pattern.clone()], line, col)
}

/// Build a default value expression for a given ValueType.
/// Used when generating placeholder values for enum variant payloads in for-in loops.
/// Bug #33: for-in loops don't work with enum collections
/// Bug #86: Handle enum payload types recursively
fn build_default_value(context: &Context, vt: &ValueType, line: usize, col: usize) -> Expr {
    match vt {
        ValueType::TCustom(type_name) => {
            match type_name.as_str() {
                "I64" | "U8" => make_num("0", line, col),
                "Bool" => make_id("false", line, col),
                "Str" => make_str("", line, col),
                // For other types (structs, other enums), check if it's an enum
                _ => {
                    // Bug #86: Check if this type is an enum - enums need special constructor syntax
                    if let Some(enum_def) = context.scope_stack.lookup_enum(type_name) {
                        // Build proper enum constructor: EnumType.FirstVariant or EnumType.FirstVariant(payload)
                        if let Some(first_v) = enum_def.variants.first() {
                            let first_variant = &first_v.name;
                            let payload_type = &first_v.payload_type;
                            // Build Type.Variant as Identifier with nested Identifier
                            let enum_id = Expr::new_explicit(
                                NodeType::Identifier(type_name.clone()),
                                vec![make_id(first_variant, line, col)],
                                line, col,
                            );
                            if let Some(payload_vt) = payload_type {
                                // Variant has a payload - need FCall with default value (recursive)
                                let default_arg = build_default_value(context, payload_vt, line, col);
                                Expr::new_explicit(NodeType::FCall(false), vec![enum_id, default_arg], line, col)
                            } else {
                                // Variant has no payload - just the identifier chain
                                enum_id
                            }
                        } else {
                            // Empty enum - fall back to struct-like constructor (shouldn't happen)
                            Expr::new_explicit(NodeType::FCall(false), vec![make_id(type_name, line, col)], line, col)
                        }
                    } else {
                        // Not an enum - use struct-like constructor: TYPE()
                        Expr::new_explicit(NodeType::FCall(false), vec![make_id(type_name, line, col)], line, col)
                    }
                }
            }
        }
        // For function types and other types, use a placeholder (shouldn't typically happen)
        _ => make_num("0", line, col),
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
    let line = e.line;
    let col = e.col;

    // Build: mut _for_i := 0
    let index_decl_expr = make_decl(&index_var_name, str_to_value_type("I64"), true, make_num("0", line, col), line, col);

    // Build: lt(_for_i, len(collection))
    let len_call = make_call("len", vec![collection_expr.clone()], line, col);
    let cond_expr = make_call("lt", vec![make_id(&index_var_name, line, col), len_call], line, col);

    // Build: catch (_err_forin_N: IndexOutOfBoundsError) { panic(loc(), _err_forin_N.msg) }
    // Bug #97: Use unique name to avoid shadowing loop variable if it's also named "err"
    let catch_err_var = format!("_err_forin_{}", forin_id);
    let panic_call = make_call("panic", vec![
        make_call("loc", vec![], line, col),
        make_field_access(&catch_err_var, vec!["msg"], line, col),
    ], line, col);
    let catch_expr = Expr::new_explicit(
        NodeType::Catch,
        vec![make_id(&catch_err_var, line, col), make_id("IndexOutOfBoundsError", line, col), make_body(vec![panic_call], line, col)],
        line, col,
    );

    // Build: _for_i = add(_for_i, 1)
    let inc_stmt = make_assign(&index_var_name, make_call("add", vec![make_id(&index_var_name, line, col), make_num("1", line, col)], line, col), line, col);

    // Bug #144: All types use get_by_ref + cast (zero-copy for all types)
    // Build: _ref_forin_N := get_by_ref(collection, _for_i)
    let ref_var_name = make_temp_name("_ref_forin", func_name, forin_id);
    let get_by_ref_call = make_call("get_by_ref", vec![
        collection_expr.clone(),
        make_id(&index_var_name, line, col),
    ], line, col);
    let ref_decl = make_decl(&ref_var_name, ValueType::TCustom("Ptr".to_string()), false, get_by_ref_call, line, col);

    // Build: item := cast(Type, _ref_forin_N)
    let cast_call = make_call("cast", vec![
        make_id(var_type_name, line, col),
        make_id(&ref_var_name, line, col),
    ], line, col);
    let cast_decl = make_decl(&var_name, ValueType::TCustom(var_type_name.to_string()), false, cast_call, line, col);

    let mut while_body_params = vec![ref_decl, catch_expr, cast_decl];

    // Bug #57 fix: Transform continue statements to include increment before continue
    let transformed_body = transform_continue_with_step(&body_expr, &inc_stmt);
    match &transformed_body.node_type {
        NodeType::Body => while_body_params.extend(transformed_body.params.clone()),
        _ => while_body_params.push(transformed_body),
    }
    while_body_params.push(inc_stmt.clone());

    // Build: while cond { body }
    let while_expr = Expr::new_explicit(NodeType::While, vec![cond_expr, make_body(while_body_params, line, col)], line, col);

    // Build outer body: index_decl, while
    Ok(make_body(vec![index_decl_expr, while_expr], line, col))
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
fn get_case_variant_info(expr: &Expr) -> Result<VariantInfo, String> {
    match &expr.node_type {
        NodeType::FCall(_) => {
            // FCall for Type.Variant (without payload extraction)
            if !expr.params.is_empty() {
                let first = expr.get(0)?;
                if let NodeType::Identifier(type_name) = &first.node_type {
                    if !first.params.is_empty() {
                        if let NodeType::Identifier(variant_name) = &first.get(0)?.node_type {
                            return Ok(VariantInfo {
                                type_name: type_name.clone(),
                                variant_name: variant_name.clone(),
                            });
                        }
                    }
                }
            }
            Ok(VariantInfo { type_name: String::new(), variant_name: String::new() })
        },
        NodeType::Identifier(name) => {
            // Identifier with nested params: Type.Variant
            if !expr.params.is_empty() {
                if let NodeType::Identifier(variant_name) = &expr.get(0)?.node_type {
                    return Ok(VariantInfo {
                        type_name: name.clone(),
                        variant_name: variant_name.clone(),
                    });
                }
            }
            // Plain identifier without nested params - NOT an enum variant pattern
            Ok(VariantInfo { type_name: String::new(), variant_name: String::new() })
        },
        _ => Ok(VariantInfo { type_name: String::new(), variant_name: String::new() }),
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
/// Rename all occurrences of an identifier in an expression tree
/// Used to rename payload binding variables to unique names to avoid conflicts
/// Stops at shadowing constructs (inner Patterns, Declarations with same name)
/// IMPORTANT: Does NOT rename inside an Identifier's params - those are field names, not variable refs
fn rename_identifier_in_expr(e: &Expr, old_name: &str, new_name: &str) -> Result<Expr, String> {
    match &e.node_type {
        NodeType::Identifier(name) if name == old_name => {
            // Identifier reference - rename it but DON'T recurse into params
            // Params of an Identifier are field names (e.g., x.field) or method calls,
            // NOT variable references. Renaming them would break field access.
            Ok(Expr::new_clone(
                NodeType::Identifier(new_name.to_string()),
                e,
                e.params.clone(), // Keep params unchanged - they're field names
            ))
        },
        NodeType::Identifier(_) => {
            // Different identifier - recurse into params to find nested expressions
            // But be careful: direct children that are Identifiers are likely field names
            // We need to check if params contain expressions that use the old_name
            if e.params.is_empty() {
                Ok(e.clone())
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
                            Ok(p.clone())
                        } else {
                            rename_identifier_in_expr(p, old_name, new_name)
                        }
                    })
                    .collect::<Result<Vec<_>, _>>()?;
                Ok(Expr::new_clone(e.node_type.clone(), e, new_params))
            }
        },
        NodeType::Assignment(name) if name == old_name => {
            // Assignment to the variable - rename it
            let assign_new_params: Vec<Expr> = e.params.iter()
                .map(|p| rename_identifier_in_expr(p, old_name, new_name))
                .collect::<Result<Vec<_>, _>>()?;
            Ok(Expr::new_clone(
                NodeType::Assignment(new_name.to_string()),
                e,
                assign_new_params,
            ))
        },
        NodeType::Pattern(pattern_info) if pattern_info.binding_var == old_name => {
            // Inner Pattern with same binding name - this shadows our variable
            // Don't rename anything inside (the body after this Pattern will use the new binding)
            Ok(e.clone())
        },
        NodeType::Declaration(decl) if decl.name == old_name => {
            // Declaration shadows our variable - stop renaming in this scope
            // But we still need to rename in the initializer (params[0]) since it runs
            // BEFORE the declaration takes effect
            if e.params.is_empty() {
                Ok(e.clone())
            } else {
                // Only rename in the initializer (first param), not in nested bodies
                let mut decl_new_params = Vec::new();
                if !e.params.is_empty() {
                    // The initializer is evaluated before the declaration, so rename in it
                    decl_new_params.push(rename_identifier_in_expr(e.get(0)?, old_name, new_name)?);
                    // Any remaining params (shouldn't exist for Declaration) - don't rename
                    for p in e.params.iter().skip(1) {
                        decl_new_params.push(p.clone());
                    }
                }
                Ok(Expr::new_clone(e.node_type.clone(), e, decl_new_params))
            }
        },
        _ => {
            // Recurse into params
            if e.params.is_empty() {
                Ok(e.clone())
            } else {
                let default_new_params: Vec<Expr> = e.params.iter()
                    .map(|p| rename_identifier_in_expr(p, old_name, new_name))
                    .collect::<Result<Vec<_>, _>>()?;
                Ok(Expr::new_clone(e.node_type.clone(), e, default_new_params))
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
fn detect_enum_switch_from_cases(context: &Context, e: &Expr) -> Result<(bool, String), String> {
    // Look at case patterns (params[1], params[3], params[5], ...)
    let mut i = 1;
    while i < e.params.len() {
        let case_pattern = e.get(i)?;
        match &case_pattern.node_type {
            NodeType::DefaultCase => {
                // Skip default case
            },
            NodeType::Pattern(pattern_info) => {
                // Pattern with payload binding is definitely enum
                let info = parse_pattern_variant_name(&pattern_info.variant_name);
                if !info.type_name.is_empty() {
                    return Ok((true, info.type_name));
                }
                // Shorthand pattern (just variant name) - search all enums for this variant
                let found_type = find_enum_for_variant(context, &info.variant_name);
                return Ok((true, found_type));
            },
            NodeType::Identifier(name) => {
                // Identifier with nested params like Type.Variant
                if !case_pattern.params.is_empty() {
                    if let NodeType::Identifier(_variant_name) = &case_pattern.get(0)?.node_type {
                        // This looks like Type.Variant - check if Type is an enum
                        if context.scope_stack.lookup_enum(name.as_str()).is_some() {
                            return Ok((true, name.clone()));
                        }
                    }
                } else {
                    // Plain identifier - could be a variable of enum type
                    // Try to look up the variable's type
                    if let Some(symbol_info) = context.scope_stack.lookup_symbol(name) {
                        if let ValueType::TCustom(type_name) = &symbol_info.value_type {
                            if context.scope_stack.lookup_enum(type_name.as_str()).is_some() {
                                return Ok((true, type_name.clone()));
                            }
                        }
                    }
                }
            },
            NodeType::FCall(_) => {
                // FCall pattern might be Type.Variant(...) for enum with payload
                let fcall_info = get_case_variant_info(case_pattern)?;
                if !fcall_info.type_name.is_empty() {
                    if context.scope_stack.lookup_enum(&fcall_info.type_name).is_some() {
                        return Ok((true, fcall_info.type_name));
                    }
                }
            },
            _ => {},
        }
        i += 2; // Skip body to get next case pattern
    }
    Ok((false, String::new()))
}

/// Infer the type of a switch expression from its case patterns
/// This is used as a fallback when get_value_type fails
/// For non-enum switches, returns the type based on literals (I64, Str, Bool)
/// For enum switches, returns None (caller should use enum_type_name from detect_enum_switch_from_cases)
fn infer_switch_type_from_cases(e: &Expr) -> Result<Option<ValueType>, String> {
    // Look at case patterns (params[1], params[3], params[5], ...)
    let mut i = 1;
    while i < e.params.len() {
        let case_pattern = e.get(i)?;
        match &case_pattern.node_type {
            NodeType::DefaultCase => {
                // Skip default case
            },
            NodeType::LLiteral(lit) => {
                match lit {
                    Literal::Number(_) => return Ok(Some(ValueType::TCustom("I64".to_string()))),
                    Literal::Str(_) => return Ok(Some(ValueType::TCustom("Str".to_string()))),
                    _ => {},
                }
            },
            NodeType::Range => {
                // Check range bounds for type
                if !case_pattern.params.is_empty() {
                    if let NodeType::LLiteral(lit) = &case_pattern.get(0)?.node_type {
                        match lit {
                            Literal::Number(_) => return Ok(Some(ValueType::TCustom("I64".to_string()))),
                            Literal::Str(_) => return Ok(Some(ValueType::TCustom("Str".to_string()))),
                            _ => {},
                        }
                    }
                }
            },
            NodeType::Identifier(name) => {
                // Could be a variable or enum variant
                // If it's "true" or "false", it's Bool
                if name == "true" || name == "false" {
                    return Ok(Some(ValueType::TCustom("Bool".to_string())));
                }
                // If it has nested params (Type.Variant), it's an enum
                // Return the enum type name directly
                if !case_pattern.params.is_empty() {
                    // name is the enum type name (e.g., "TokenType" in "TokenType.Eof")
                    return Ok(Some(ValueType::TCustom(name.clone())));
                }
            },
            NodeType::Pattern(pattern_info) => {
                // Pattern is always enum - try to get the enum type from the variant name
                let pattern_info2 = parse_pattern_variant_name(&pattern_info.variant_name);
                if !pattern_info2.type_name.is_empty() {
                    return Ok(Some(ValueType::TCustom(pattern_info2.type_name)));
                }
                // Shorthand pattern - can't infer type here (no context available)
                // Keep searching other case patterns
            },
            _ => {},
        }
        i += 2; // Skip body to get next case pattern
    }
    Ok(None)
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

    let switch_expr = e.get(0)?;
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
        let (detected_enum, detected_type) = detect_enum_switch_from_cases(context, e)?;
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

    // Generate unique temp var names
    let switch_id = context.precomp_forin_counter;
    context.precomp_forin_counter += 1;
    let func_name = context.current_precomp_func.clone();
    let switch_var_prefix = if is_enum_switch { "_switch_variant" } else { "_switch_val" };
    let switch_var_name = make_temp_name(switch_var_prefix, &func_name, switch_id);

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
        make_temp_name("_switch_expr", &func_name, switch_id)
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
                match infer_switch_type_from_cases(e)? {
                    Some(vt) => vt,
                    None => str_to_value_type("I64"), // Default to I64 if all inference fails
                }
            }
        }
    };

    // First declaration: capture the switch expression
    // Bug #157 fix in ccodegen handles field access on throwing calls properly now
    decl_exprs.push(make_decl(&switch_expr_var_name, switch_expr_var_type.clone(), false, desugared_switch_expr.clone(), line, col));

    // For enum switches, add second declaration: _switch_variant := enum_to_str(_switch_expr)
    if is_enum_switch {
        let enum_to_str_call = make_call("enum_to_str", vec![make_id(&switch_expr_var_name, line, col)], line, col);
        decl_exprs.push(make_decl(&switch_var_name, str_to_value_type("Str"), false, enum_to_str_call, line, col));
    }

    // Build the if/else chain from cases
    // Process cases in pairs: [case_pattern, body, case_pattern, body, ...]
    let mut cases: Vec<(Expr, Expr)> = Vec::new();
    let mut default_body: Option<Expr> = None;

    let mut i = 1;
    while i + 1 < e.params.len() {
        let case_pattern = e.get(i)?;
        let case_body = e.get(i + 1)?;

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

    // Build if statements from cases
    let default_expr = match default_body {
        Some(body) => body,
        None => Expr::new_explicit(NodeType::Body, vec![], line, col), // Empty body if no default
    };

    // Process cases using else-if chains
    let total_cases = cases.len();
    let mut result_expr = default_expr;

    for (idx, (rev_case_pattern, rev_case_body)) in cases.into_iter().rev().enumerate() {
        let rev_ci = total_cases - 1 - idx;
        let cond_result = build_case_condition(
            context, &rev_case_pattern, &switch_var_name, is_enum_switch, &enum_type_name,
            &switch_expr_var_name, switch_id, rev_ci, &func_name, line, col,
        )?;

        let (rev_condition, rev_body_prefix, rename_pair, _inner_condition) = cond_result;
        let rev_renamed_case_body = match &rename_pair {
            Some((old_name, new_name)) => rename_identifier_in_expr(&rev_case_body, old_name, new_name)?,
            None => rev_case_body,
        };

        let full_case_body = if rev_body_prefix.is_empty() {
            rev_renamed_case_body
        } else {
            let mut rev_full_body_params = rev_body_prefix;
            match &rev_renamed_case_body.node_type {
                NodeType::Body => rev_full_body_params.extend(rev_renamed_case_body.params.clone()),
                _ => rev_full_body_params.push(rev_renamed_case_body),
            }
            make_body(rev_full_body_params, line, col)
        };

        result_expr = make_if(rev_condition, full_case_body, Some(result_expr), line, col);
    }

    // Wrap in outer body with declarations and if/else chain
    let mut rev_body_params = decl_exprs;
    rev_body_params.push(result_expr);
    Ok(make_body(rev_body_params, line, col
    ))
}

/// Build the condition expression and any body prefix for a case pattern
/// Returns (condition_expr, body_prefix_statements, optional_rename_pair, unused_inner_condition)
/// switch_expr_var_name: name of the temp variable holding the switch expression value (for enum_get_payload)
/// switch_id: global unique ID for this switch statement
/// case_index: index of this case within the switch (for generating unique payload names)
/// func_name: current function name for generating unique names
/// For nested patterns like ValueType.TType(TTypeDef.TEnumDef), uses enum_get_payload_type for combined condition
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
) -> Result<(Expr, Vec<Expr>, Option<(String, String)>, Option<Expr>), String> {
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
            let mut body_prefix = Vec::new();
            let mut rename_pair: Option<(String, String)> = None;
            let payload_type = get_payload_type_for_variant(context, &actual_type_name, &info.variant_name);
            if let Some(vt) = payload_type {
                let original_name = pattern_info.binding_var.clone();
                let unique_name = if !func_name.is_empty() {
                    format!("_payload_{}_{}_{}_{}", original_name, func_name, switch_id, case_index)
                } else {
                    format!("_payload_{}_{}_{}", original_name, switch_id, case_index)
                };

                let default_val = build_default_value(context, &vt, line, col);
                body_prefix.push(make_decl(&unique_name, vt.clone(), true, default_val, line, col));

                let payload_type_name = match &vt {
                    ValueType::TCustom(name) => name.clone(),
                    _ => "I64".to_string(),
                };
                body_prefix.push(make_call("enum_get_payload", vec![
                    make_id(switch_expr_var_name, line, col),
                    make_id(&payload_type_name, line, col),
                    make_id(&unique_name, line, col),
                ], line, col));

                rename_pair = Some((original_name, unique_name));
            }

            Ok((condition, body_prefix, rename_pair, None))
        },
        NodeType::Range => {
            // Range case: and(gteq(_switch_val, low), lteq(_switch_val, high))
            if case_pattern.params.len() < 2 {
                return Err("desugar: Range case requires start and end values".to_string());
            }
            let low = case_pattern.get(0)?;
            let high = case_pattern.get(1)?;

            let gteq_call = make_call("gteq", vec![make_id(switch_var_name, line, col), low.clone()], line, col);
            let lteq_call = make_call("lteq", vec![make_id(switch_var_name, line, col), high.clone()], line, col);
            let condition = make_call("and", vec![gteq_call, lteq_call], line, col);

            Ok((condition, vec![], None, None))
        },
        NodeType::Identifier(_) | NodeType::LLiteral(_) => {
            // Simple value case or enum variant without payload
            let ident_info = get_case_variant_info(case_pattern)?;

            if is_enum_switch && !ident_info.variant_name.is_empty() {
                let ident_actual_type_name = if ident_info.type_name.is_empty() { enum_type_name.to_string() } else { ident_info.type_name.clone() };
                let ident_variant_str = format!("{}.{}", ident_actual_type_name, ident_info.variant_name);
                Ok((build_str_eq_call(switch_var_name, &ident_variant_str, line, col), vec![], None, None))
            } else {
                let condition = if is_enum_switch {
                    build_enum_eq_condition(switch_var_name, case_pattern, line, col)
                } else {
                    build_eq_condition(switch_var_name, case_pattern, line, col)
                };
                Ok((condition, vec![], None, None))
            }
        },
        NodeType::FCall(_) => {
            // FCall pattern: Type.Variant() or Type.Variant(InnerEnum.Variant) or computed value
            let fcall_info = get_case_variant_info(case_pattern)?;

            if is_enum_switch && !fcall_info.variant_name.is_empty() {
                // Enum variant - check outer tag
                let fcall_actual_type_name = if fcall_info.type_name.is_empty() { enum_type_name.to_string() } else { fcall_info.type_name.clone() };
                let fcall_variant_str = format!("{}.{}", fcall_actual_type_name, fcall_info.variant_name);
                let outer_condition = build_str_eq_call(switch_var_name, &fcall_variant_str, line, col);

                // Check for nested enum patterns - e.g., ValueType.TType(TTypeDef.TEnumDef)
                if case_pattern.params.len() > 1 {
                    let inner_pattern = case_pattern.get(1)?;
                    let inner_info = get_case_variant_info(inner_pattern)?;
                    if !inner_info.variant_name.is_empty() {
                        // Nested enum pattern - use enum_get_payload_type for combined condition
                        let payload_type = get_payload_type_for_variant(context, &fcall_actual_type_name, &fcall_info.variant_name);

                        if let Some(vt) = payload_type {
                            let inner_type_name = match &vt {
                                ValueType::TCustom(name) => name.clone(),
                                _ => return Err(format!("Nested pattern: unsupported payload type {:?}", vt)),
                            };

                            // Build inner condition: enum_get_payload_type(switch_expr, VariantName, PayloadType).eq("Type.Variant")
                            let inner_actual_type = if inner_info.type_name.is_empty() { inner_type_name.clone() } else { inner_info.type_name.clone() };
                            let inner_variant_str = format!("{}.{}", inner_actual_type, inner_info.variant_name);
                            let payload_type_call = make_call("enum_get_payload_type", vec![
                                make_id(switch_expr_var_name, line, col),
                                make_id(&fcall_info.variant_name, line, col),
                                make_id(&inner_type_name, line, col),
                            ], line, col);
                            let inner_condition = build_str_eq_call_expr(payload_type_call, &inner_variant_str, line, col);

                            // Combine outer && inner
                            let combined_condition = make_call("and", vec![outer_condition, inner_condition], line, col);
                            return Ok((combined_condition, vec![], None, None));
                        } else {
                            return Err(format!("Nested pattern: could not find payload type for {}.{}", fcall_actual_type_name, fcall_info.variant_name));
                        }
                    }
                }

                Ok((outer_condition, vec![], None, None))
            } else {
                let condition = if is_enum_switch {
                    build_enum_eq_condition(switch_var_name, case_pattern, line, col)
                } else {
                    build_eq_condition(switch_var_name, case_pattern, line, col)
                };
                Ok((condition, vec![], None, None))
            }
        },
        _ => {
            let condition = if is_enum_switch {
                build_enum_eq_condition(switch_var_name, case_pattern, line, col)
            } else {
                build_eq_condition(switch_var_name, case_pattern, line, col)
            };
            Ok((condition, vec![], None, None))
        },
    }
}

/// Build: eq(var_name, "literal_str")
fn build_str_eq_call(var_name: &str, literal_str: &str, line: usize, col: usize) -> Expr {
    make_call("eq", vec![make_id(var_name, line, col), make_str(literal_str, line, col)], line, col)
}

/// Build: expr.eq("literal_str")
fn build_str_eq_call_expr(expr: Expr, literal_str: &str, line: usize, col: usize) -> Expr {
    make_call("eq", vec![expr, make_str(literal_str, line, col)], line, col)
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
        // Issue #108: Recurse into NamespaceDef default values (which may contain function defs)
        NodeType::NamespaceDef(ns_def) => {
            let mut ns_new_default_values = std::collections::HashMap::new();
            for (name, value_expr) in &ns_def.default_values {
                ns_new_default_values.insert(name.clone(), desugar_expr(context, value_expr)?);
            }
            let new_ns_def = SNamespaceDef {
                type_name: ns_def.type_name.clone(),
                members: ns_def.members.clone(),
                default_values: ns_new_default_values,
            };
            Ok(Expr::new_clone(NodeType::NamespaceDef(new_ns_def), e, vec![]))
        },
        // Track declarations in scope_stack so get_value_type can find local variables
        // This is needed for switch desugaring to determine the type of expressions like var.field
        NodeType::Declaration(decl) => {
            // Issue #110: Set current_precomp_func for function declarations so switch
            // desugaring generates variable names with proper function prefixes
            let is_func_decl = !e.params.is_empty() && matches!(&e.get(0)?.node_type, NodeType::FuncDef(_));
            let saved_func = context.current_precomp_func.clone();
            if is_func_decl {
                context.current_precomp_func = decl.name.clone();
            }

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

            // Issue #110: Restore previous function context
            if is_func_decl {
                context.current_precomp_func = saved_func;
            }

            Ok(Expr::new_clone(e.node_type.clone(), e, new_params))
        },
        // For all other nodes, recurse into params
        _ => {
            if e.params.is_empty() {
                Ok(e.clone())
            } else {
                let mut default_new_params = Vec::new();
                for p in &e.params {
                    default_new_params.push(desugar_expr(context, p)?);
                }
                Ok(Expr::new_clone(e.node_type.clone(), e, default_new_params))
            }
        }
    }
}
