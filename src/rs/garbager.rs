// Garbager phase: Auto-generates delete() methods for structs and inserts
// automatic delete() calls for ASAP destruction (Issue #117).
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

/// Check if a type needs delete() - primitives and enums don't need delete
fn needs_delete(value_type: &ValueType) -> bool {
    match value_type {
        ValueType::TCustom(type_name) => {
            // Primitives have no-op delete(), skip them for efficiency
            // Ptr is excluded because Ptr ownership semantics are manual (is_borrowed flag)
            // and Ptr.offset() creates non-owning views that shouldn't be auto-deleted
            // Str is excluded because Vec.get does shallow copy - both the Vec and the
            // copied Str share underlying memory. Deleting one invalidates the other.
            // Enums don't have delete() methods
            match type_name.as_str() {
                // Primitives
                "I64" | "U8" | "Bool" | "Type" | "Ptr" | "Str" => false,
                // Enum types (don't have delete methods)
                "TokenType" | "FunctionType" | "Literal" | "NodeType" |
                "TTypeDef" | "ValueType" | "ScopeType" | "MutArgValue" |
                "PatternInfo" | "Target" | "Lang" => false,
                _ => true  // All other types (Vec, Array, Map, etc. and custom structs)
            }
        }
        ValueType::TFunction(_) => false,  // Functions don't need delete
        ValueType::TType(_) => false,      // Type definitions don't need delete
        ValueType::TMulti(_) => true,      // Multiple return types may need delete
    }
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

        // Skip fields whose types don't need delete (primitives, enums, etc.)
        if !needs_delete(&member.value_type) {
            continue;
        }

        // Build: FieldType.delete(self.field_name) - post-UFCS format
        // Get field type name
        let field_type_name = match &member.value_type {
            ValueType::TCustom(name) => name.clone(),
            _ => continue,  // Skip if we can't get the type name
        };

        // Build: FieldType.delete
        let type_delete_access = Expr::new_explicit(
            NodeType::Identifier(field_type_name),
            vec![
                Expr::new_explicit(NodeType::Identifier("delete".to_string()), vec![], line, col),
            ],
            line,
            col,
        );

        // Build: self.field_name
        let field_access = Expr::new_explicit(
            NodeType::Identifier("self".to_string()),
            vec![
                Expr::new_explicit(NodeType::Identifier(member.name.clone()), vec![], line, col),
            ],
            line,
            col,
        );

        // FCall for FieldType.delete(self.field_name)
        let delete_call = Expr::new_explicit(
            NodeType::FCall(false),  // doesn't throw
            vec![type_delete_access, field_access],
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

// =============================================================================
// Step 4: Liveness Analysis and Delete Insertion (Issue #117)
// =============================================================================
// NOTE: Step 4 is disabled due to shallow copy semantics. When a struct like
// SFuncDef is used to construct a NodeType::FuncDef, the data is shallow-copied.
// If we delete the original variable after its "last use", the NodeType still
// references the now-freed memory. Enabling Step 4 requires tracking ownership
// transfers (e.g., knowing when a variable is consumed by a constructor).

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
        // NOTE: Step 4 (liveness analysis and delete insertion) is disabled.
        // The shallow copy semantics of structs (e.g., NodeType::FuncDef taking
        // a copy of SFuncDef) means we can't safely delete local variables after
        // their "last use" - the data may still be referenced by another object.
        // Enabling Step 4 requires tracking ownership transfers.
        NodeType::FuncDef(func_def) => {
            // Recursively process each statement
            let mut processed_body = Vec::new();
            for stmt in &func_def.body {
                processed_body.push(garbager_expr(context, stmt)?);
            }

            let new_func_def = SFuncDef {
                function_type: func_def.function_type.clone(),
                args: func_def.args.clone(),
                return_types: func_def.return_types.clone(),
                throw_types: func_def.throw_types.clone(),
                body: processed_body,
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
