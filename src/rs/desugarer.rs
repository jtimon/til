// Desugarer phase: Desugars ForIn loops to while loops with get() calls.
// This phase runs after typer, before precomp.

use crate::rs::init::Context;
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

/// Desugarer phase entry point: Recursively desugar ForIn loops in the AST.
pub fn desugar_expr(context: &mut Context, e: &Expr) -> Result<Expr, String> {
    match &e.node_type {
        // ForIn desugaring: for VAR: TYPE in COLLECTION { body } -> while loop
        NodeType::ForIn(var_type_name) => {
            desugar_forin(context, e, var_type_name)
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
