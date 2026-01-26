// Garbager phase: Auto-generates delete() methods for structs and (future) inserts
// automatic delete() calls for ASAP destruction.
// This phase runs after desugarer, before precomp.

use crate::rs::init::Context;
use crate::rs::parser::{
    Expr, NodeType, ValueType, SStructDef, SFuncDef, FunctionType,
    Declaration,
};

/// Result of generating a delete method - contains the declaration and expression.
/// Used instead of tuple to maintain Rust/TIL parity (TIL doesn't have tuples).
struct DeleteMethodResult {
    decl: Declaration,
    expr: Expr,
}

/// Generate a delete() method for a struct that doesn't have one.
/// The method calls field.delete() for each mutable field in reverse declaration order.
fn generate_delete_method(struct_name: &str, struct_def: &SStructDef, line: usize, col: usize) -> DeleteMethodResult {
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

        // Build: self.field_name.delete()
        // self.field_name.delete is: Identifier("self") [ Identifier("field_name"), Identifier("delete") ]
        let delete_access = Expr::new_explicit(
            NodeType::Identifier("self".to_string()),
            vec![
                Expr::new_explicit(NodeType::Identifier(member.name.clone()), vec![], line, col),
                Expr::new_explicit(NodeType::Identifier("delete".to_string()), vec![], line, col),
            ],
            line,
            col,
        );

        // FCall for self.field_name.delete()
        let delete_call = Expr::new_explicit(
            NodeType::FCall(false),  // doesn't throw
            vec![delete_access],
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
        // Recurse into FuncDef bodies
        NodeType::FuncDef(func_def) => {
            let mut new_body = Vec::new();
            for stmt in &func_def.body {
                new_body.push(garbager_expr(context, stmt)?);
            }
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
        // Switch should have been desugared before garbager
        NodeType::Switch => {
            Err(e.lang_error(&context.path, "garbager", "Switch should have been desugared before garbager"))
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
