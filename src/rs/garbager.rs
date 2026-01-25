// Garbager phase: Auto-generates delete() methods for structs and inserts
// automatic delete() calls for ASAP destruction.
// This phase runs after desugarer, before ufcs.

use crate::rs::init::{Context, ScopeType};
use crate::rs::parser::{
    Expr, NodeType, ValueType, SStructDef, SFuncDef, FunctionType,
    Declaration,
};

/// Track a variable's lifetime for ASAP destruction.
#[derive(Clone)]
#[allow(dead_code)]  // Will be used when liveness analysis is implemented
struct VarLifetime {
    name: String,
    type_name: String,  // Type name for generating post-UFCS delete calls
    #[allow(dead_code)]  // For future ASAP optimization
    last_use_stmt_idx: Option<usize>,
    is_deleted: bool,
}

/// Collect all variable declarations from a statement list.
/// Only tracks variables with types that need deletion (not primitives or enums).
#[allow(dead_code)]  // Will be used when liveness analysis is implemented
fn collect_var_declarations(context: &Context, stmts: &[Expr]) -> Vec<VarLifetime> {
    let mut vars = Vec::new();
    for stmt in stmts {
        if let NodeType::Declaration(decl) = &stmt.node_type {
            // Only track mutable variables with non-primitive, non-enum types
            if decl.is_mut && needs_delete(context, &decl.value_type) {
                // Extract type name from ValueType
                let type_name = match &decl.value_type {
                    ValueType::TCustom(name) => name.clone(),
                    _ => continue,  // Skip non-TCustom types (already filtered by needs_delete)
                };
                vars.push(VarLifetime {
                    name: decl.name.clone(),
                    type_name,
                    last_use_stmt_idx: None,
                    is_deleted: false,
                });
            }
        }
    }
    vars
}

/// Check if a type needs delete() called on it.
/// Primitives (I64, U8, Bool) have no-op delete, but we skip them for efficiency.
/// Enums are also skipped since they don't have delete methods.
fn needs_delete(context: &Context, vt: &ValueType) -> bool {
    match vt {
        ValueType::TCustom(name) => {
            // Skip primitives - their delete() is a no-op
            match name.as_str() {
                "I64" | "U8" | "Bool" | "Type" | "Dynamic" => false,
                _ => {
                    // Skip enums - they don't have delete methods
                    if context.scope_stack.lookup_enum(name).is_some() {
                        return false;
                    }
                    // All other types (Str, Vec, Array, Map, Set, List, Ptr, structs) need delete
                    true
                }
            }
        },
        ValueType::TFunction(_) | ValueType::TType(_) | ValueType::TMulti(_) => false,
    }
}

/// Generate a delete call for a variable: Type.delete(var_name)
/// Uses post-UFCS form because garbager runs after typer, so generated nodes
/// won't have type annotations that UFCS needs.
#[allow(dead_code)]  // Will be used when liveness analysis is implemented
fn generate_delete_call(var_name: &str, type_name: &str, line: usize, col: usize) -> Expr {
    // Build: Type.delete(var_name)
    let type_delete_access = Expr::new_explicit(
        NodeType::Identifier(type_name.to_string()),
        vec![
            Expr::new_explicit(NodeType::Identifier("delete".to_string()), vec![], line, col),
        ],
        line,
        col,
    );

    let var_ref = Expr::new_explicit(
        NodeType::Identifier(var_name.to_string()),
        vec![],
        line,
        col,
    );

    Expr::new_explicit(
        NodeType::FCall(false),  // doesn't throw
        vec![type_delete_access, var_ref],
        line,
        col,
    )
}

/// Generate delete calls for all live variables (in reverse order).
#[allow(dead_code)]  // Will be used when liveness analysis is implemented
fn generate_deletes_for_vars(vars: &[VarLifetime], line: usize, col: usize) -> Vec<Expr> {
    let mut deletes = Vec::new();
    // Delete in reverse declaration order (like C++/Rust destructors)
    for var in vars.iter().rev() {
        if !var.is_deleted {
            deletes.push(generate_delete_call(&var.name, &var.type_name, line, col));
        }
    }
    deletes
}

/// Process a function body to insert delete() calls.
/// TODO: Implement liveness analysis for ASAP destruction.
/// For now, just recursively process statements without inserting deletes.
/// Automatic local variable deletion is disabled until we have proper liveness
/// analysis to handle: returns, assignments, aliasing, early exits, etc.
fn process_func_body(context: &mut Context, body: &[Expr], _line: usize, _col: usize) -> Result<Vec<Expr>, String> {
    // Just recursively process all statements for now
    let mut processed_body = Vec::new();
    for stmt in body {
        processed_body.push(garbager_expr(context, stmt)?);
    }
    Ok(processed_body)
}

/// Result of generating a delete method - contains the declaration and expression.
/// Used instead of tuple to maintain Rust/TIL parity (TIL doesn't have tuples).
struct DeleteMethodResult {
    decl: Declaration,
    expr: Expr,
}

/// Generate a delete() method for a struct that doesn't have one.
/// The method calls self.field.delete() for each mutable field in reverse declaration order.
/// Uses pre-UFCS form since garbager runs before UFCS.
fn generate_delete_method(context: &Context, struct_name: &str, struct_def: &SStructDef, line: usize, col: usize) -> DeleteMethodResult {
    // Build: delete := proc(mut self: StructName) { self.field_n.delete(); ... self.field_0.delete(); }

    // Create the self parameter: mut self: StructName
    let self_decl = Declaration {
        name: "self".to_string(),
        value_type: ValueType::TCustom(struct_name.to_string()),
        is_mut: true,
        is_copy: false,
        is_own: false,
        default_value: None,
    };

    // Build the body: call delete() on each field in reverse order
    let mut body_stmts: Vec<Expr> = Vec::new();

    // Process fields in reverse order (like C++/Rust destructors)
    for member in struct_def.members.iter().rev() {
        // Skip non-mut fields (constants/methods don't need delete)
        if !member.is_mut {
            continue;
        }

        // Skip fields that don't need delete (primitives, enums)
        if !needs_delete(context, &member.value_type) {
            continue;
        }

        // Get the field's type name for post-UFCS form
        let field_type_name = match &member.value_type {
            ValueType::TCustom(name) => name.clone(),
            _ => continue,  // Skip non-TCustom types
        };

        // Build: Type.delete(self.field_name) - post-UFCS form
        // because garbager runs after typer, generated nodes won't have type annotations
        let type_delete_access = Expr::new_explicit(
            NodeType::Identifier(field_type_name),
            vec![
                Expr::new_explicit(NodeType::Identifier("delete".to_string()), vec![], line, col),
            ],
            line,
            col,
        );

        let self_field_access = Expr::new_explicit(
            NodeType::Identifier("self".to_string()),
            vec![
                Expr::new_explicit(NodeType::Identifier(member.name.clone()), vec![], line, col),
            ],
            line,
            col,
        );

        // FCall for Type.delete(self.field_name)
        let delete_call = Expr::new_explicit(
            NodeType::FCall(false),  // doesn't throw
            vec![type_delete_access, self_field_access],
            line,
            col,
        );

        body_stmts.push(delete_call);
    }

    // Create the FuncDef
    let func_def = SFuncDef {
        function_type: FunctionType::FTProc,
        args: vec![self_decl],
        return_types: vec![],
        throw_types: vec![],
        body: body_stmts,
        source_path: String::new(),
    };

    // Create the declaration for the method
    let method_decl = Declaration {
        name: "delete".to_string(),
        value_type: ValueType::TFunction(FunctionType::FTProc),
        is_mut: false,
        is_copy: false,
        is_own: false,
        default_value: None,
    };

    let func_expr = Expr::new_explicit(NodeType::FuncDef(func_def), vec![], line, col);

    DeleteMethodResult {
        decl: method_decl,
        expr: func_expr,
    }
}

/// Garbager phase entry point: Recursively process AST to auto-generate delete methods.
pub fn garbager_expr(context: &mut Context, e: &Expr) -> Result<Expr, String> {
    match &e.node_type {
        // Handle Declaration nodes - check for struct definitions that need delete method
        NodeType::Declaration(decl) => {
            // Check if this is a struct definition
            if let Some(value_expr) = e.params.first() {
                if let NodeType::StructDef(struct_def) = &value_expr.node_type {
                    // Check if struct already has a delete method (check both members and default_values)
                    let has_delete_in_members = struct_def.members.iter().any(|m| m.name == "delete");
                    let has_delete_in_values = struct_def.default_values.contains_key("delete");
                    let has_delete = has_delete_in_members || has_delete_in_values;

                    // Check if struct has any mutable fields (skip delete for empty/constant-only structs)
                    let has_mut_fields = struct_def.members.iter().any(|m| m.is_mut);

                    if !has_delete && has_mut_fields {
                        // Generate delete method
                        let delete_result = generate_delete_method(
                            context,
                            &decl.name,
                            struct_def,
                            e.line,
                            e.col,
                        );

                        // Create new struct def with delete method added
                        let mut decl_new_members = struct_def.members.clone();
                        decl_new_members.push(delete_result.decl);

                        let mut decl_new_default_values = std::collections::HashMap::new();
                        for (decl_name, decl_val_expr) in &struct_def.default_values {
                            decl_new_default_values.insert(decl_name.clone(), garbager_expr(context, decl_val_expr)?);
                        }
                        decl_new_default_values.insert("delete".to_string(), delete_result.expr);

                        let decl_new_struct_def = SStructDef {
                            members: decl_new_members,
                            default_values: decl_new_default_values,
                        };

                        // Update the Context so UFCS can find the new delete method
                        context.scope_stack.declare_struct(decl.name.clone(), decl_new_struct_def.clone());

                        let decl_new_struct_expr = Expr::new_clone(
                            NodeType::StructDef(decl_new_struct_def),
                            value_expr,
                            value_expr.params.clone(),
                        );

                        return Ok(Expr::new_clone(
                            NodeType::Declaration(decl.clone()),
                            e,
                            vec![decl_new_struct_expr],
                        ));
                    }
                }
            }

            // Default: recurse into params
            let mut decl_new_params = Vec::new();
            for decl_p in &e.params {
                decl_new_params.push(garbager_expr(context, decl_p)?);
            }
            Ok(Expr::new_clone(e.node_type.clone(), e, decl_new_params))
        },
        // Recurse into FuncDef bodies with proper scope management
        NodeType::FuncDef(func_def) => {
            context.scope_stack.push(ScopeType::Function);
            let new_body = process_func_body(context, &func_def.body, e.line, e.col)?;
            context.scope_stack.pop().ok();
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
        // Handle block-creating nodes with proper scope management
        NodeType::Body | NodeType::If | NodeType::While => {
            context.scope_stack.push(ScopeType::Block);
            let mut new_params = Vec::new();
            for p in &e.params {
                new_params.push(garbager_expr(context, p)?);
            }
            context.scope_stack.pop().ok();
            Ok(Expr::new_clone(e.node_type.clone(), e, new_params))
        },
        NodeType::ForIn(_) => {
            context.scope_stack.push(ScopeType::Block);
            let mut new_params = Vec::new();
            for p in &e.params {
                new_params.push(garbager_expr(context, p)?);
            }
            context.scope_stack.pop().ok();
            Ok(Expr::new_clone(e.node_type.clone(), e, new_params))
        },
        // Recurse into StructDef default values (which may contain function defs)
        NodeType::StructDef(struct_def) => {
            let mut sdef_new_default_values = std::collections::HashMap::new();
            for (sdef_name, sdef_value_expr) in &struct_def.default_values {
                sdef_new_default_values.insert(sdef_name.clone(), garbager_expr(context, sdef_value_expr)?);
            }
            let sdef_new_struct_def = SStructDef {
                members: struct_def.members.clone(),
                default_values: sdef_new_default_values,
            };
            Ok(Expr::new_clone(NodeType::StructDef(sdef_new_struct_def), e, e.params.clone()))
        },
        // For all other nodes, recurse into params
        _ => {
            if e.params.is_empty() {
                Ok(e.clone())
            } else {
                let mut new_params = Vec::new();
                for p in &e.params {
                    new_params.push(garbager_expr(context, p)?);
                }
                Ok(Expr::new_clone(e.node_type.clone(), e, new_params))
            }
        }
    }
}
