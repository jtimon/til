// Desugarer phase: Desugars ForIn loops and Switch statements.
// This phase runs after typer, before UFCS/precomp.
//
// ForIn: for VAR: TYPE in COLLECTION { body } -> while loop with get() calls
// Switch: switch expr { case X: body } -> if/else chains with eq()/gteq()/lteq() calls

use crate::rs::init::Context;
use crate::rs::parser::{
    Expr, NodeType, ValueType, SStructDef, SFuncDef, Literal, PatternInfo,
    Declaration, str_to_value_type, transform_continue_with_step,
};
use crate::rs::init::get_value_type;

/// Helper struct for tracking variant names with payload info during enum type inference
#[derive(Clone)]
pub struct VariantPayloadInfo {
    pub name: String,
    pub has_payload: bool,
}

/// Helper struct for switch cases (case_expr, body_expr, is_default)
#[derive(Clone)]
pub struct SwitchCase {
    pub case_expr: Expr,
    pub body_expr: Expr,
    pub is_default: bool,
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

/// Desugar Switch to if/else chains
/// Issue #110: Move switch handling to desugarer, simplify downstream phases
///
/// For enum switches:
///   switch expr { case Color.Green(x): body1  case Color.Unknown: body2  case: body3 }
/// becomes:
///   { _switch_variant := enum_to_str(expr)
///     if Str.eq(_switch_variant, "Color.Green") { mut x := false; enum_get_payload(expr, Bool, x); body1 }
///     else if Str.eq(_switch_variant, "Color.Unknown") { body2 }
///     else { body3 } }
///
/// For non-enum switches (I64, Str):
///   switch val { case 5: body1  case 1..10: body2  case: body3 }
/// becomes:
///   if val.eq(5) { body1 }
///   else if val.gteq(1) && val.lteq(10) { body2 }
///   else { body3 }
fn desugar_switch(context: &mut Context, e: &Expr) -> Result<Expr, String> {
    if e.params.len() < 3 {
        return Err(e.lang_error(&context.path, "desugar", "switch nodes must have at least 3 parameters (expr, case, body)"));
    }

    // Get switch expression and its type
    let switch_expr = desugar_expr(context, e.get(0)?)?;
    // Try to get type from expression - may fail for local variables since desugarer
    // runs before evaluation when variables are registered in scope_stack
    let mut switch_type = get_value_type(context, &switch_expr).ok();

    // If type inference failed, try to infer enum type from Pattern nodes
    // This handles cases where local variables aren't in scope_stack yet
    if switch_type.is_none() {
        if let Some(enum_type) = infer_enum_type_from_patterns(context, e) {
            switch_type = Some(ValueType::TCustom(enum_type));
        }
    }

    // If still no type and expression is a field access, try to infer from field name
    // e.g., "x.token_type" might suggest TokenType
    if switch_type.is_none() {
        if let Some(field_type) = infer_type_from_field_access(context, &switch_expr) {
            switch_type = Some(field_type);
        }
    }

    // Determine if this is an enum switch by checking if any case is a Pattern or enum variant
    let is_enum_switch = is_enum_switch_expr(context, e, &switch_type);

    // Generate unique variable name for storing switch expression result
    let forin_id = context.precomp_forin_counter;
    context.precomp_forin_counter += 1;
    let func_name = &context.current_precomp_func;
    let switch_var_name = if !func_name.is_empty() {
        format!("_switch_{}_{}", func_name, forin_id)
    } else {
        format!("_switch_{}", forin_id)
    };

    // Collect cases
    let mut cases: Vec<SwitchCase> = Vec::new();
    let mut i = 1;
    while i + 1 < e.params.len() {
        let case_expr = e.get(i)?;
        let body_expr = desugar_expr(context, e.get(i + 1)?)?;
        let is_default = matches!(case_expr.node_type, NodeType::DefaultCase);
        cases.push(SwitchCase { case_expr: case_expr.clone(), body_expr, is_default });
        i += 2;
    }

    // For non-trivial switch expressions where we know the type, store in a temp variable
    // to avoid re-evaluation. If we don't know the type, use the expression directly.
    let is_simple_expr = matches!(&switch_expr.node_type,
        NodeType::Identifier(_) if switch_expr.params.is_empty()
    );

    // Build declarations for temp variables
    let mut preamble: Vec<Expr> = Vec::new();

    // Create a temp variable for the switch expression value only if:
    // 1. Expression is non-trivial AND
    // 2. We know the type (so we can declare the variable properly)
    let switch_value_var = format!("{}_val", switch_var_name);
    let switch_expr_for_use = if is_simple_expr || switch_type.is_none() {
        // Use expression directly
        switch_expr.clone()
    } else {
        // Build: _switch_val := switch_expr
        let switch_val_decl = Declaration {
            name: switch_value_var.clone(),
            value_type: switch_type.clone().unwrap(),
            is_mut: false,
            is_copy: false,
            is_own: false,
            default_value: None,
        };
        let switch_val_decl_expr = Expr::new_explicit(
            NodeType::Declaration(switch_val_decl),
            vec![switch_expr.clone()],
            e.line,
            e.col,
        );
        preamble.push(switch_val_decl_expr);

        // Use the temp variable in subsequent code
        Expr::new_explicit(NodeType::Identifier(switch_value_var), vec![], e.line, e.col)
    };

    // Build if/else chain from cases (reverse order to build from inside out)
    let if_chain = build_switch_if_chain(context, e, &switch_expr_for_use, &switch_var_name, &switch_type, is_enum_switch, &cases)?;

    if is_enum_switch {
        // For enum switches, also create a variant string variable:
        // { _switch_val := switch_expr; _switch_variant := enum_to_str(_switch_val); if_chain }
        let variant_var_name = format!("{}_variant", switch_var_name);

        // Build: _switch_variant := enum_to_str(_switch_val)
        let enum_to_str_call = Expr::new_explicit(
            NodeType::FCall(false),
            vec![
                Expr::new_explicit(NodeType::Identifier("enum_to_str".to_string()), vec![], e.line, e.col),
                switch_expr_for_use.clone(),
            ],
            e.line,
            e.col,
        );
        let variant_decl = Declaration {
            name: variant_var_name.clone(),
            value_type: str_to_value_type("Str"),
            is_mut: false,
            is_copy: false,
            is_own: false,
            default_value: None,
        };
        let variant_decl_expr = Expr::new_explicit(NodeType::Declaration(variant_decl), vec![enum_to_str_call], e.line, e.col);
        preamble.push(variant_decl_expr);

        preamble.push(if_chain);
        Ok(Expr::new_explicit(NodeType::Body, preamble, e.line, e.col))
    } else {
        // For non-enum switches, include preamble if we have temp var declarations
        if preamble.is_empty() {
            Ok(if_chain)
        } else {
            preamble.push(if_chain);
            Ok(Expr::new_explicit(NodeType::Body, preamble, e.line, e.col))
        }
    }
}

/// Try to infer enum type from Pattern nodes when get_value_type fails
/// Scans all patterns for one with a qualified name (EnumType.Variant) and extracts the type
fn infer_enum_type_from_patterns(context: &Context, e: &Expr) -> Option<String> {
    // First, look for patterns with qualified names
    let mut i = 1;
    while i + 1 < e.params.len() {
        if let Ok(case_expr) = e.get(i) {
            match &case_expr.node_type {
                NodeType::Pattern(PatternInfo { variant_name, binding_var: _ }) => {
                    // Check if variant_name has enum type prefix (contains '.')
                    if let Some(dot_pos) = variant_name.rfind('.') {
                        return Some(variant_name[..dot_pos].to_string());
                    }
                },
                NodeType::Identifier(name) => {
                    // Check if it's a qualified name like EnumType.Variant
                    if let Some(dot_pos) = name.rfind('.') {
                        return Some(name[..dot_pos].to_string());
                    }
                    // Also check params for EnumType.Variant structure
                    if !case_expr.params.is_empty() {
                        // name is EnumType, check if it looks like an enum reference
                        // This is EnumType.Variant where name=EnumType, params[0]=Variant identifier
                        if let Some(variant_expr) = case_expr.params.first() {
                            if let NodeType::Identifier(_) = &variant_expr.node_type {
                                return Some(name.clone());
                            }
                        }
                    }
                },
                NodeType::FCall(_) => {
                    // FCall pattern like ValueType.TType(TTypeDef.TStructDef)
                    // Get the variant name from the FCall function (first param)
                    let variant_name = get_fcall_variant_name(&case_expr);
                    if let Some(dot_pos) = variant_name.rfind('.') {
                        return Some(variant_name[..dot_pos].to_string());
                    }
                },
                _ => {}
            }
        }
        i += 2;
    }

    // If no qualified names found, try to find enum by searching for variant names
    // Collect all unqualified pattern variant names
    let mut variant_names: Vec<String> = Vec::new();
    i = 1;
    while i + 1 < e.params.len() {
        if let Ok(case_expr2) = e.get(i) {
            match &case_expr2.node_type {
                NodeType::Pattern(PatternInfo { variant_name, binding_var: _ }) => {
                    if !variant_name.contains('.') {
                        variant_names.push(variant_name.clone());
                    }
                },
                NodeType::Identifier(name) => {
                    if !name.contains('.') && case_expr2.params.is_empty() {
                        // Simple identifier - might be a variant name
                        variant_names.push(name.clone());
                    }
                },
                _ => {}
            }
        }
        i += 2;
    }

    // Search all known enums for one that has ALL the variant names with matching payload presence
    // Collect variant names with their "has binding" info
    let mut variants_with_payload: Vec<VariantPayloadInfo> = Vec::new();
    i = 1;
    while i + 1 < e.params.len() {
        if let Ok(case_expr) = e.get(i) {
            match &case_expr.node_type {
                NodeType::Pattern(PatternInfo { variant_name, binding_var: _ }) => {
                    if !variant_name.contains('.') {
                        // Pattern always has a binding, so variant must have payload
                        variants_with_payload.push(VariantPayloadInfo { name: variant_name.clone(), has_payload: true });
                    }
                },
                NodeType::Identifier(name) => {
                    if !name.contains('.') && case_expr.params.is_empty() {
                        // Simple identifier - variant without payload
                        variants_with_payload.push(VariantPayloadInfo { name: name.clone(), has_payload: false });
                    }
                },
                _ => {}
            }
        }
        i += 2;
    }

    // Search all known enums for one where ALL variants match name AND payload presence
    if !variants_with_payload.is_empty() {
        for entry in context.scope_stack.get_all_enums() {
            let all_match = variants_with_payload.iter().all(|vpi| {
                entry.enum_def.variants.iter().any(|v| {
                    v.name == vpi.name && (v.payload_type.is_some() == vpi.has_payload)
                })
            });
            if all_match {
                return Some(entry.name.clone());
            }
        }
    }

    None
}

/// Try to infer type from field access expression by looking up field types
/// e.g., for "x.token_type" where x: Token, look up Token.token_type
fn infer_type_from_field_access(context: &Context, expr: &Expr) -> Option<ValueType> {
    // Check if this is a field access pattern: Identifier with params
    if let NodeType::Identifier(_base_name) = &expr.node_type {
        if !expr.params.is_empty() {
            // Get the field name from the last param
            if let Some(last_param) = expr.params.last() {
                if let NodeType::Identifier(field_name) = &last_param.node_type {
                    // Try to find a struct with this field name and return its type
                    // This is a heuristic - we look for ANY struct with a field of this name
                    for struct_def in context.scope_stack.get_all_structs() {
                        for member in &struct_def.members {
                            if member.name == *field_name {
                                return Some(member.value_type.clone());
                            }
                        }
                    }
                }
            }
        }
    }

    // Also handle "_" marker for field access on expression results (Bug #32 pattern)
    if let NodeType::Identifier(name) = &expr.node_type {
        if name == "_" && !expr.params.is_empty() {
            // params[0] is the expression, params[1..] are field chain
            // Try to get the last field name
            if let Some(last_param) = expr.params.last() {
                if let NodeType::Identifier(field_name) = &last_param.node_type {
                    // Look up field type in any struct
                    for struct_def in context.scope_stack.get_all_structs() {
                        for member in &struct_def.members {
                            if member.name == *field_name {
                                return Some(member.value_type.clone());
                            }
                        }
                    }
                }
            }
        }
    }

    // Handle simple identifier that matches a known struct field name
    // e.g., "token_type" might be a local variable assigned from some_struct.token_type
    // Look for any struct field with this name and check if its type is an enum
    if let NodeType::Identifier(name) = &expr.node_type {
        if expr.params.is_empty() {
            // Simple identifier - look for struct fields with this name
            for struct_def in context.scope_stack.get_all_structs() {
                for member in &struct_def.members {
                    if member.name == *name {
                        // Found a struct field with this name
                        // Check if its type is an enum
                        if let ValueType::TCustom(ref type_name) = member.value_type {
                            if context.scope_stack.lookup_enum(type_name).is_some() {
                                return Some(member.value_type.clone());
                            }
                        }
                    }
                }
            }
        }
    }

    None
}

/// Check if a switch is on an enum type
fn is_enum_switch_expr(context: &Context, e: &Expr, switch_type: &Option<ValueType>) -> bool {
    // Check if switch expression type is an enum
    if let Some(ValueType::TCustom(type_name)) = switch_type {
        if context.scope_stack.lookup_enum(type_name).is_some() {
            return true;
        }
    }

    // Also check if any case is a Pattern (payload binding) or enum variant
    let mut i = 1;
    while i + 1 < e.params.len() {
        if let Ok(switch_case_expr) = e.get(i) {
            match &switch_case_expr.node_type {
                NodeType::Pattern(_) => return true,
                NodeType::Identifier(name) => {
                    // Check if it looks like EnumType.Variant
                    if name.contains('.') || !switch_case_expr.params.is_empty() {
                        return true;
                    }
                },
                _ => {}
            }
        }
        i += 2;
    }
    false
}

/// Build if/else chain from switch cases
fn build_switch_if_chain(
    context: &mut Context,
    e: &Expr,
    switch_expr: &Expr,
    switch_var_name: &str,
    switch_type: &Option<ValueType>,
    is_enum_switch: bool,
    cases: &[SwitchCase],
) -> Result<Expr, String> {
    // Find the default case (if any) - it becomes the final else
    let default_body: Option<&Expr> = cases.iter()
        .find(|c| c.is_default)
        .map(|c| &c.body_expr);

    // Filter out default case for the if/else if chain
    let non_default_cases: Vec<&SwitchCase> = cases.iter()
        .filter(|c| !c.is_default)
        .collect();

    if non_default_cases.is_empty() {
        // Only default case - just return its body
        return Ok(default_body.cloned().unwrap_or_else(|| {
            Expr::new_explicit(NodeType::Body, vec![], e.line, e.col)
        }));
    }

    // Build if chain from end to beginning
    // Start with the innermost else (default or empty)
    let mut result = default_body.cloned();

    // Process cases in reverse order to build inside-out
    // Use enumerate to track case index for unique binding variable names
    for (rev_idx, case) in non_default_cases.iter().rev().enumerate() {
        // Convert reverse index to forward index for deterministic naming
        let case_index = non_default_cases.len() - 1 - rev_idx;
        let condition = build_case_condition(context, e, switch_expr, switch_var_name, switch_type, is_enum_switch, &case.case_expr)?;
        let case_body = build_case_body(context, e, switch_expr, switch_var_name, switch_type, is_enum_switch, &case.case_expr, &case.body_expr, case_index)?;

        // Build if node: If(condition, then_body) or If(condition, then_body, else_body)
        let if_params = if let Some(else_expr) = result {
            vec![condition, case_body, else_expr]
        } else {
            vec![condition, case_body]
        };

        result = Some(Expr::new_explicit(NodeType::If, if_params, e.line, e.col));
    }

    Ok(result.unwrap())
}

/// Build the condition expression for a case
fn build_case_condition(
    context: &Context,
    e: &Expr,
    switch_expr: &Expr,
    switch_var_name: &str,
    switch_type: &Option<ValueType>,
    is_enum_switch: bool,
    case_expr: &Expr,
) -> Result<Expr, String> {
    match &case_expr.node_type {
        NodeType::Pattern(PatternInfo { variant_name, binding_var: _ }) => {
            // Enum pattern with payload: compare variant string
            // Str.eq(_switch_variant, "EnumType.Variant")
            build_enum_variant_condition(e, switch_var_name, variant_name, switch_type)
        },
        NodeType::Identifier(name) => {
            if is_enum_switch {
                // Check if name is a known enum variant or a variable
                if is_known_enum_variant(context, name, switch_type) {
                    // Known enum variant without payload
                    let full_variant_name1 = get_full_variant_name(name, case_expr, switch_type);
                    build_enum_variant_condition(e, switch_var_name, &full_variant_name1, switch_type)
                } else if name.contains('.') {
                    // Qualified name
                    let full_variant_name2 = get_full_variant_name(name, case_expr, switch_type);
                    build_enum_variant_condition(e, switch_var_name, &full_variant_name2, switch_type)
                } else if !case_expr.params.is_empty() {
                    // Has params (EnumType.Variant structure)
                    let full_variant_name3 = get_full_variant_name(name, case_expr, switch_type);
                    build_enum_variant_condition(e, switch_var_name, &full_variant_name3, switch_type)
                } else {
                    // Variable of enum type: compare enum_to_str(switch) with enum_to_str(case_var)
                    build_enum_variable_condition(e, switch_var_name, case_expr)
                }
            } else {
                // Non-enum: val.eq(case_val)
                build_eq_condition(e, switch_expr, case_expr)
            }
        },
        NodeType::LLiteral(_) => {
            // Literal value: val.eq(literal)
            build_eq_condition(e, switch_expr, case_expr)
        },
        NodeType::Range => {
            // Range: val.gteq(lo) && val.lteq(hi)
            build_range_condition(context, e, switch_expr, case_expr)
        },
        NodeType::FCall(_) => {
            // FCall pattern (e.g., enum with complex payload) - treat as enum
            if is_enum_switch {
                let variant_name = get_fcall_variant_name(case_expr);
                // Just return the outer condition - nested check handled in build_case_body
                build_enum_variant_condition(e, switch_var_name, &variant_name, switch_type)
            } else {
                // Fallback to eq comparison
                build_eq_condition(e, switch_expr, case_expr)
            }
        },
        _ => {
            // Fallback: val.eq(case_val)
            build_eq_condition(e, switch_expr, case_expr)
        }
    }
}

/// Get full variant name, prepending enum type if needed
fn get_full_variant_name(name: &str, case_expr: &Expr, switch_type: &Option<ValueType>) -> String {
    // If name already contains '.', it's fully qualified
    if name.contains('.') {
        return name.to_string();
    }

    // Check if case_expr has params (EnumType.Variant structure)
    if !case_expr.params.is_empty() {
        if let Some(variant_expr) = case_expr.params.first() {
            if let NodeType::Identifier(variant_name) = &variant_expr.node_type {
                // name is EnumType, variant_name is Variant
                return format!("{}.{}", name, variant_name);
            }
        }
    }

    // Try to get enum type from switch expression type
    if let Some(ValueType::TCustom(enum_type)) = switch_type {
        return format!("{}.{}", enum_type, name);
    }

    name.to_string()
}

/// Get nested enum pattern from FCall argument (e.g., TTypeDef.TEnumDef from TType(TTypeDef.TEnumDef))
/// Returns (nested_enum_type, nested_variant_name) if the FCall arg is an enum pattern, None otherwise
fn get_fcall_nested_enum_pattern(context: &Context, case_expr: &Expr) -> Option<(String, String)> {
    // FCall: params[0] = function, params[1] = argument
    if case_expr.params.len() < 2 {
        eprintln!("DEBUG nested: FCall has < 2 params");
        return None;
    }
    let arg_expr = &case_expr.params[1];

    // Check if arg is an identifier with a dot (e.g., TTypeDef.TEnumDef)
    if let NodeType::Identifier(name) = &arg_expr.node_type {
        // Check for EnumType.Variant structure in params
        if !arg_expr.params.is_empty() {
            if let Some(variant_expr) = arg_expr.params.first() {
                if let NodeType::Identifier(variant_name) = &variant_expr.node_type {
                    // name is EnumType, variant_name is Variant
                    // Check if name is a known enum
                    if context.scope_stack.lookup_enum(name).is_some() {
                        eprintln!("DEBUG nested: found {}.{}", name, variant_name);
                        return Some((name.clone(), format!("{}.{}", name, variant_name)));
                    } else {
                        eprintln!("DEBUG nested: enum '{}' NOT FOUND in scope for nested pattern {}.{}", name, name, variant_name);
                    }
                }
            }
        }
        // Check for qualified name like "TTypeDef.TEnumDef"
        if let Some(dot_pos) = name.rfind('.') {
            let enum_type = &name[..dot_pos];
            if context.scope_stack.lookup_enum(enum_type).is_some() {
                eprintln!("DEBUG nested: found qualified {}", name);
                return Some((enum_type.to_string(), name.clone()));
            } else {
                eprintln!("DEBUG nested: enum '{}' NOT FOUND for qualified {}", enum_type, name);
            }
        }
    } else {
        eprintln!("DEBUG nested: arg is not Identifier, it's {:?}", arg_expr.node_type);
    }
    None
}

/// Get variant name from an FCall pattern (e.g., Color.Green(payload))
fn get_fcall_variant_name(case_expr: &Expr) -> String {
    // FCall structure: params[0] is the function (e.g., Color.Green identifier chain)
    if let Some(func_expr) = case_expr.params.first() {
        if let NodeType::Identifier(name) = &func_expr.node_type {
            // Build full name from identifier chain
            let mut full_name = name.clone();
            for param in &func_expr.params {
                if let NodeType::Identifier(part) = &param.node_type {
                    full_name.push('.');
                    full_name.push_str(part);
                }
            }
            return full_name;
        }
    }
    String::new()
}

/// Check if a name is a known variant of the enum type
fn is_known_enum_variant(context: &Context, name: &str, switch_type: &Option<ValueType>) -> bool {
    // If name contains '.', check if it's EnumType.Variant form
    if name.contains('.') {
        let parts: Vec<&str> = name.split('.').collect();
        if parts.len() == 2 {
            let enum_type = parts[0];
            let variant_name = parts[1];
            if let Some(enum_def) = context.scope_stack.lookup_enum(enum_type) {
                return enum_def.contains_key(variant_name);
            }
        }
        return false;
    }

    // For simple names, check if it's a variant of the switch expression's enum type
    if let Some(ValueType::TCustom(enum_type)) = switch_type {
        if let Some(enum_def) = context.scope_stack.lookup_enum(enum_type) {
            return enum_def.contains_key(name);
        }
    }
    false
}

/// Build Str.eq(_switch_variant, enum_to_str(case_var)) condition for enum variable comparison
fn build_enum_variable_condition(e: &Expr, switch_var_name: &str, case_expr: &Expr) -> Result<Expr, String> {
    let variant_var = format!("{}_variant", switch_var_name);

    // Build: enum_to_str(case_var)
    let case_enum_to_str = Expr::new_explicit(
        NodeType::FCall(false),
        vec![
            Expr::new_explicit(NodeType::Identifier("enum_to_str".to_string()), vec![], e.line, e.col),
            case_expr.clone(),
        ],
        e.line,
        e.col,
    );

    // Build: Str.eq(_switch_variant, enum_to_str(case_var))
    Ok(Expr::new_explicit(
        NodeType::FCall(false),
        vec![
            Expr::new_explicit(NodeType::Identifier("eq".to_string()), vec![], e.line, e.col),
            Expr::new_explicit(NodeType::Identifier(variant_var), vec![], e.line, e.col),
            case_enum_to_str,
        ],
        e.line,
        e.col,
    ))
}

/// Build Str.eq(_switch_variant, "EnumType.Variant") condition
fn build_enum_variant_condition(e: &Expr, switch_var_name: &str, variant_name: &str, switch_type: &Option<ValueType>) -> Result<Expr, String> {
    let variant_var = format!("{}_variant", switch_var_name);

    // If variant_name doesn't have a dot, prepend the enum type from switch expression
    let full_variant_name = if variant_name.contains('.') {
        variant_name.to_string()
    } else if let Some(ValueType::TCustom(enum_type)) = switch_type {
        format!("{}.{}", enum_type, variant_name)
    } else {
        variant_name.to_string()
    };

    // Build: Str.eq(_switch_variant, "EnumType.Variant")
    // Using method call form: _switch_variant.eq("EnumType.Variant")
    // UFCS will transform this to Str.eq(_switch_variant, "...")
    Ok(Expr::new_explicit(
        NodeType::FCall(false),
        vec![
            Expr::new_explicit(
                NodeType::Identifier("eq".to_string()),
                vec![],
                e.line,
                e.col,
            ),
            Expr::new_explicit(NodeType::Identifier(variant_var), vec![], e.line, e.col),
            Expr::new_explicit(NodeType::LLiteral(Literal::Str(full_variant_name)), vec![], e.line, e.col),
        ],
        e.line,
        e.col,
    ))
}

/// Build val.eq(case_val) condition
fn build_eq_condition(e: &Expr, switch_expr: &Expr, case_expr: &Expr) -> Result<Expr, String> {
    Ok(Expr::new_explicit(
        NodeType::FCall(false),
        vec![
            Expr::new_explicit(NodeType::Identifier("eq".to_string()), vec![], e.line, e.col),
            switch_expr.clone(),
            case_expr.clone(),
        ],
        e.line,
        e.col,
    ))
}

/// Build val.gteq(lo) && val.lteq(hi) condition for range
fn build_range_condition(context: &Context, e: &Expr, switch_expr: &Expr, case_expr: &Expr) -> Result<Expr, String> {
    if case_expr.params.len() < 2 {
        return Err(e.lang_error(&context.path, "desugar", "Range case requires start and end values"));
    }

    let lo = &case_expr.params[0];
    let hi = &case_expr.params[1];

    // Build: val.gteq(lo)
    let gteq_call = Expr::new_explicit(
        NodeType::FCall(false),
        vec![
            Expr::new_explicit(NodeType::Identifier("gteq".to_string()), vec![], e.line, e.col),
            switch_expr.clone(),
            lo.clone(),
        ],
        e.line,
        e.col,
    );

    // Build: val.lteq(hi)
    let lteq_call = Expr::new_explicit(
        NodeType::FCall(false),
        vec![
            Expr::new_explicit(NodeType::Identifier("lteq".to_string()), vec![], e.line, e.col),
            switch_expr.clone(),
            hi.clone(),
        ],
        e.line,
        e.col,
    );

    // Build: gteq_call && lteq_call
    Ok(Expr::new_explicit(
        NodeType::FCall(false),
        vec![
            Expr::new_explicit(NodeType::Identifier("and".to_string()), vec![], e.line, e.col),
            gteq_call,
            lteq_call,
        ],
        e.line,
        e.col,
    ))
}

/// Rename all occurrences of a base identifier in an expression.
/// Only renames the BASE of identifier chains, not field access names.
/// E.g., for old_name="val": val -> new_name, val.field -> new_name.field
/// But: other.val stays as other.val (val is a field, not a base)
fn rename_identifier(expr: &Expr, old_name: &str, new_name: &str) -> Expr {
    match &expr.node_type {
        NodeType::Identifier(name) if name == old_name => {
            // Base identifier matches - rename it
            // DON'T recurse into params (those are field names, not base identifiers)
            Expr::new_explicit(NodeType::Identifier(new_name.to_string()), expr.params.clone(), expr.line, expr.col)
        },
        NodeType::Identifier(_) => {
            // Different base identifier - DON'T rename field access params
            // Field names should never be renamed
            expr.clone()
        },
        NodeType::Declaration(decl) if decl.name == old_name => {
            // Don't rename declarations - this is a new binding that shadows
            expr.clone()
        },
        _ => {
            // Recursively rename in params for other node types
            let new_params: Vec<Expr> = expr.params.iter()
                .map(|p| rename_identifier(p, old_name, new_name))
                .collect();
            Expr::new_clone(expr.node_type.clone(), expr, new_params)
        }
    }
}

/// Build the body for a case, including payload extraction for enum patterns
fn build_case_body(
    context: &mut Context,
    e: &Expr,
    switch_expr: &Expr,
    switch_var_name: &str,
    switch_type: &Option<ValueType>,
    is_enum_switch: bool,
    case_expr: &Expr,
    body_expr: &Expr,
    case_index: usize,
) -> Result<Expr, String> {
    // For enum patterns with payload binding, prepend payload extraction
    if let NodeType::Pattern(PatternInfo { variant_name: _, binding_var }) = &case_expr.node_type {
        if is_enum_switch {
            // Get the payload type from the enum definition
            let payload_type = get_payload_type_for_pattern(context, case_expr, e, switch_type)?;

            // Generate unique binding variable name to avoid type conflicts
            // when multiple cases use the same binding name with different types
            let unique_binding_name = format!("{}_bind_{}", switch_var_name, case_index);

            // Build: mut unique_binding := default_value
            let default_value = build_default_value(context, &payload_type, e.line, e.col);
            let binding_decl = Declaration {
                name: unique_binding_name.clone(),
                value_type: payload_type.clone(),
                is_mut: true,
                is_copy: false,
                is_own: false,
                default_value: None,
            };
            let binding_decl_expr = Expr::new_explicit(
                NodeType::Declaration(binding_decl),
                vec![default_value],
                e.line,
                e.col,
            );

            // Build: enum_get_payload(switch_expr, PayloadType, unique_binding)
            let payload_type_name = match &payload_type {
                ValueType::TCustom(name) => name.clone(),
                _ => "Dynamic".to_string(),
            };
            let get_payload_call = Expr::new_explicit(
                NodeType::FCall(false),
                vec![
                    Expr::new_explicit(NodeType::Identifier("enum_get_payload".to_string()), vec![], e.line, e.col),
                    switch_expr.clone(),
                    Expr::new_explicit(NodeType::Identifier(payload_type_name), vec![], e.line, e.col),
                    Expr::new_explicit(NodeType::Identifier(unique_binding_name.clone()), vec![], e.line, e.col),
                ],
                e.line,
                e.col,
            );

            // Rename all references to binding_var in body to unique_binding_name
            let renamed_body = rename_identifier(body_expr, binding_var, &unique_binding_name);

            // Build body: { binding_decl; enum_get_payload; renamed_body_stmts }
            let mut body_stmts = vec![binding_decl_expr, get_payload_call];
            match &renamed_body.node_type {
                NodeType::Body => {
                    body_stmts.extend(renamed_body.params.clone());
                },
                _ => {
                    body_stmts.push(renamed_body);
                }
            }
            return Ok(Expr::new_explicit(NodeType::Body, body_stmts, e.line, e.col));
        }
    }

    // For FCall with nested enum pattern, wrap body in nested if
    if let NodeType::FCall(_) = &case_expr.node_type {
        eprintln!("DEBUG build_case_body: FCall case, is_enum_switch={}", is_enum_switch);
        if is_enum_switch {
            let nested_result = get_fcall_nested_enum_pattern(context, case_expr);
            eprintln!("DEBUG build_case_body: nested_result={:?}", nested_result);
            if let Some((nested_enum_type, nested_variant_name)) = nested_result {
                // Generate:
                // {
                //     mut _payload: NestedType = NestedType.Default()
                //     enum_get_payload(switch_expr, NestedType, _payload)
                //     if Str.eq(enum_to_str(_payload), "NestedType.ExpectedVariant") {
                //         original_body
                //     }
                // }
                let payload_var_name = format!("{}_nested_{}", switch_var_name, case_index);

                // Build default value for nested enum type
                let default_value = build_default_value(context, &ValueType::TCustom(nested_enum_type.clone()), e.line, e.col);

                // Build: mut _payload := default_value
                let payload_decl = Declaration {
                    name: payload_var_name.clone(),
                    value_type: ValueType::TCustom(nested_enum_type.clone()),
                    is_mut: true,
                    is_copy: false,
                    is_own: false,
                    default_value: None,
                };
                let payload_decl_expr = Expr::new_explicit(
                    NodeType::Declaration(payload_decl),
                    vec![default_value],
                    e.line,
                    e.col,
                );

                // Build: enum_get_payload(switch_expr, NestedType, _payload)
                let get_payload_call = Expr::new_explicit(
                    NodeType::FCall(false),
                    vec![
                        Expr::new_explicit(NodeType::Identifier("enum_get_payload".to_string()), vec![], e.line, e.col),
                        switch_expr.clone(),
                        Expr::new_explicit(NodeType::Identifier(nested_enum_type.clone()), vec![], e.line, e.col),
                        Expr::new_explicit(NodeType::Identifier(payload_var_name.clone()), vec![], e.line, e.col),
                    ],
                    e.line,
                    e.col,
                );

                // Build: enum_to_str(_payload)
                let enum_to_str_call = Expr::new_explicit(
                    NodeType::FCall(false),
                    vec![
                        Expr::new_explicit(NodeType::Identifier("enum_to_str".to_string()), vec![], e.line, e.col),
                        Expr::new_explicit(NodeType::Identifier(payload_var_name.clone()), vec![], e.line, e.col),
                    ],
                    e.line,
                    e.col,
                );

                // Build: Str.eq(enum_to_str(_payload), "NestedType.ExpectedVariant")
                let nested_condition = Expr::new_explicit(
                    NodeType::FCall(false),
                    vec![
                        Expr::new_explicit(NodeType::Identifier("eq".to_string()), vec![], e.line, e.col),
                        enum_to_str_call,
                        Expr::new_explicit(NodeType::LLiteral(Literal::Str(nested_variant_name)), vec![], e.line, e.col),
                    ],
                    e.line,
                    e.col,
                );

                // Wrap original body
                let wrapped_body = match &body_expr.node_type {
                    NodeType::Body => body_expr.clone(),
                    _ => Expr::new_explicit(NodeType::Body, vec![body_expr.clone()], e.line, e.col),
                };

                // Build: if nested_condition { wrapped_body }
                let nested_if = Expr::new_explicit(
                    NodeType::If,
                    vec![nested_condition, wrapped_body],
                    e.line,
                    e.col,
                );

                // Build outer body: { payload_decl; get_payload; nested_if }
                return Ok(Expr::new_explicit(
                    NodeType::Body,
                    vec![payload_decl_expr, get_payload_call, nested_if],
                    e.line,
                    e.col,
                ));
            }
        }
    }

    // For non-pattern cases, just use the body as-is
    // Ensure it's wrapped in a Body node
    match &body_expr.node_type {
        NodeType::Body => Ok(body_expr.clone()),
        _ => Ok(Expr::new_explicit(NodeType::Body, vec![body_expr.clone()], e.line, e.col)),
    }
}

/// Get the payload type for an enum pattern
fn get_payload_type_for_pattern(context: &Context, case_expr: &Expr, e: &Expr, switch_type: &Option<ValueType>) -> Result<ValueType, String> {
    if let NodeType::Pattern(PatternInfo { variant_name, binding_var: _ }) = &case_expr.node_type {
        // Parse variant name to get enum type and variant
        // Handles both "EnumType.Variant" and shorthand "Variant" (infer enum type from switch expression)
        let (enum_type, variant) = if let Some(dot_pos) = variant_name.rfind('.') {
            (variant_name[..dot_pos].to_string(), variant_name[dot_pos + 1..].to_string())
        } else {
            // Shorthand syntax: infer enum type from switch expression
            if let Some(ValueType::TCustom(switch_enum_type)) = switch_type {
                (switch_enum_type.clone(), variant_name.clone())
            } else {
                return Err(e.lang_error(&context.path, "desugar", &format!("Pattern variant '{}' missing enum type prefix and cannot infer from switch type", variant_name)));
            }
        };

        // Look up enum definition
        if let Some(enum_def) = context.scope_stack.lookup_enum(&enum_type) {
            // Find the variant
            for v in &enum_def.variants {
                if v.name == variant {
                    if let Some(payload_type) = &v.payload_type {
                        return Ok(payload_type.clone());
                    } else {
                        return Err(e.lang_error(&context.path, "desugar", &format!("Enum variant '{}.{}' has no payload", enum_type, variant)));
                    }
                }
            }
            return Err(e.lang_error(&context.path, "desugar", &format!("Enum '{}' has no variant '{}'", enum_type, variant)));
        } else {
            return Err(e.lang_error(&context.path, "desugar", &format!("Unknown enum type '{}'", enum_type)));
        }
    }

    Err(e.lang_error(&context.path, "desugar", "Expected Pattern node for payload type lookup"))
}

/// Desugarer phase entry point: Recursively desugar ForIn loops and Switch statements.
pub fn desugar_expr(context: &mut Context, e: &Expr) -> Result<Expr, String> {
    match &e.node_type {
        // ForIn desugaring: for VAR: TYPE in COLLECTION { body } -> while loop
        NodeType::ForIn(var_type_name) => {
            desugar_forin(context, e, var_type_name)
        },
        // Switch desugaring: switch expr { cases } -> if/else chains
        NodeType::Switch => {
            desugar_switch(context, e)
        },
        // Recurse into FuncDef bodies
        NodeType::FuncDef(func_def) => {
            // Bug #130 fix: Reset counter per-function for deterministic output
            let saved_counter = context.precomp_forin_counter;
            context.precomp_forin_counter = 0;
            let mut new_body = Vec::new();
            for stmt in &func_def.body {
                new_body.push(desugar_expr(context, stmt)?);
            }
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
