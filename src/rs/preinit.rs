// Preinit phase: Auto-generates delete() and clone() methods for structs.
// This phase runs before init so the generated methods are visible during type checking.
// Future consolidation: May be merged into init phase.

use crate::rs::parser::{
    Expr, NodeType, ValueType, SStructDef, SEnumDef, SFuncDef, FunctionType,
    Declaration,
};

/// Result of generating a method - contains the declaration and expression.
struct MethodResult {
    decl: Declaration,
    expr: Expr,
}

/// Generate a delete() method for a struct that doesn't have one.
/// The method calls field.delete() for each mutable field in reverse declaration order.
fn generate_delete_method(struct_name: &str, struct_def: &SStructDef, line: usize, col: usize) -> MethodResult {
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

    MethodResult {
        decl: method_decl,
        expr: func_expr,
    }
}

/// Generate a clone() method for a struct that doesn't have one.
/// The method returns a new instance with each mutable field cloned.
fn generate_clone_method(struct_name: &str, struct_def: &SStructDef, line: usize, col: usize) -> MethodResult {
    // Build: clone := func(self: StructName) returns StructName { return StructName(field1 = self.field1.clone(), ...) }

    // Create the self parameter: self: StructName (not mut - we're reading from it)
    let self_decl = Declaration {
        name: "self".to_string(),
        value_type: ValueType::TCustom(struct_name.to_string()),
        is_mut: false,
        is_copy: false,
        is_own: false,
        default_value: None,
    };

    // Build named arguments for the struct literal: field1 = self.field1.clone(), field2 = self.field2.clone(), ...
    let mut named_args: Vec<Expr> = Vec::new();

    for member in struct_def.members.iter() {
        // Skip non-mut fields (constants/methods don't need cloning)
        if !member.is_mut {
            continue;
        }

        // Build: self.field_name.clone()
        // This is: Identifier("self") [ Identifier("field_name"), Identifier("clone") ]
        let clone_access = Expr::new_explicit(
            NodeType::Identifier("self".to_string()),
            vec![
                Expr::new_explicit(NodeType::Identifier(member.name.clone()), vec![], line, col),
                Expr::new_explicit(NodeType::Identifier("clone".to_string()), vec![], line, col),
            ],
            line,
            col,
        );

        // FCall for self.field_name.clone()
        let clone_call = Expr::new_explicit(
            NodeType::FCall(false),  // doesn't throw
            vec![clone_access],
            line,
            col,
        );

        // Build named argument: field_name = self.field_name.clone()
        let named_arg = Expr::new_explicit(
            NodeType::NamedArg(member.name.clone()),
            vec![clone_call],
            line,
            col,
        );

        named_args.push(named_arg);
    }

    // Build: StructName(field1 = ..., field2 = ...)
    // This is: Identifier("StructName") followed by named args
    let struct_name_id = Expr::new_explicit(
        NodeType::Identifier(struct_name.to_string()),
        vec![],
        line,
        col,
    );

    let mut struct_literal_params = vec![struct_name_id];
    struct_literal_params.extend(named_args);

    let struct_literal = Expr::new_explicit(
        NodeType::FCall(false),
        struct_literal_params,
        line,
        col,
    );

    // Build: return StructName(...)
    let return_stmt = Expr::new_explicit(
        NodeType::Return,
        vec![struct_literal],
        line,
        col,
    );

    // Create the FuncDef
    let func_def = SFuncDef {
        function_type: FunctionType::FTFunc,
        args: vec![self_decl],
        return_types: vec![ValueType::TCustom(struct_name.to_string())],
        throw_types: vec![],
        body: vec![return_stmt],
        source_path: String::new(),
    };

    // Create the declaration for the method
    let method_decl = Declaration {
        name: "clone".to_string(),
        value_type: ValueType::TFunction(FunctionType::FTFunc),
        is_mut: false,
        is_copy: false,
        is_own: false,
        default_value: None,
    };

    let func_expr = Expr::new_explicit(NodeType::FuncDef(func_def), vec![], line, col);

    MethodResult {
        decl: method_decl,
        expr: func_expr,
    }
}

/// Generate a delete() method for an enum - no-op since enums are value types.
fn generate_enum_delete_method(enum_name: &str, line: usize, col: usize) -> Expr {
    // Build: delete := proc(mut self: EnumName) {}
    let self_decl = Declaration {
        name: "self".to_string(),
        value_type: ValueType::TCustom(enum_name.to_string()),
        is_mut: true,
        is_copy: false,
        is_own: false,
        default_value: None,
    };

    let func_def = SFuncDef {
        function_type: FunctionType::FTProc,
        args: vec![self_decl],
        return_types: vec![],
        throw_types: vec![],
        body: vec![],  // Empty body - no-op
        source_path: String::new(),
    };

    Expr::new_explicit(NodeType::FuncDef(func_def), vec![], line, col)
}

/// Generate a clone() method for an enum - returns self since enums are value types.
fn generate_enum_clone_method(enum_name: &str, line: usize, col: usize) -> Expr {
    // Build: clone := func(self: EnumName) returns EnumName { return self }
    let self_decl = Declaration {
        name: "self".to_string(),
        value_type: ValueType::TCustom(enum_name.to_string()),
        is_mut: false,
        is_copy: false,
        is_own: false,
        default_value: None,
    };

    // Build: return self
    let return_stmt = Expr::new_explicit(
        NodeType::Return,
        vec![Expr::new_explicit(NodeType::Identifier("self".to_string()), vec![], line, col)],
        line,
        col,
    );

    let func_def = SFuncDef {
        function_type: FunctionType::FTFunc,
        args: vec![self_decl],
        return_types: vec![ValueType::TCustom(enum_name.to_string())],
        throw_types: vec![],
        body: vec![return_stmt],
        source_path: String::new(),
    };

    Expr::new_explicit(NodeType::FuncDef(func_def), vec![], line, col)
}

/// Preinit phase entry point: Recursively process AST to auto-generate delete and clone methods.
pub fn preinit_expr(e: &Expr) -> Result<Expr, String> {
    match &e.node_type {
        // Handle Declaration nodes - check for struct definitions that need delete/clone methods
        NodeType::Declaration(decl) => {
            // Check if this is a struct definition
            if let Some(value_expr) = e.params.first() {
                if let NodeType::StructDef(struct_def) = &value_expr.node_type {
                    // Check if struct already has delete method (check both members and default_values)
                    let has_delete_in_members = struct_def.members.iter().any(|m| m.name == "delete");
                    let has_delete_in_values = struct_def.default_values.contains_key("delete");
                    let has_delete = has_delete_in_members || has_delete_in_values;

                    // Check if struct already has clone method
                    let has_clone_in_members = struct_def.members.iter().any(|m| m.name == "clone");
                    let has_clone_in_values = struct_def.default_values.contains_key("clone");
                    let has_clone = has_clone_in_members || has_clone_in_values;

                    // Check if struct has any mutable fields (skip methods for empty/constant-only structs)
                    let has_mut_fields = struct_def.members.iter().any(|m| m.is_mut);

                    // Generate missing methods if struct has mutable fields
                    let needs_delete = !has_delete && has_mut_fields;
                    let needs_clone = !has_clone && has_mut_fields;

                    if needs_delete || needs_clone {
                        let mut new_members = struct_def.members.clone();
                        let mut new_default_values = std::collections::HashMap::new();

                        // Copy existing default values (recursively process them)
                        for (name, val_expr) in &struct_def.default_values {
                            new_default_values.insert(name.clone(), preinit_expr(val_expr)?);
                        }

                        // Generate delete method if needed
                        if needs_delete {
                            let delete_result = generate_delete_method(
                                &decl.name,
                                struct_def,
                                e.line,
                                e.col,
                            );
                            new_members.push(delete_result.decl);
                            new_default_values.insert("delete".to_string(), delete_result.expr);
                        }

                        // Generate clone method if needed
                        if needs_clone {
                            let clone_result = generate_clone_method(
                                &decl.name,
                                struct_def,
                                e.line,
                                e.col,
                            );
                            new_members.push(clone_result.decl);
                            new_default_values.insert("clone".to_string(), clone_result.expr);
                        }

                        let new_struct_def = SStructDef {
                            members: new_members,
                            default_values: new_default_values,
                        };

                        let new_struct_expr = Expr::new_clone(
                            NodeType::StructDef(new_struct_def),
                            value_expr,
                            value_expr.params.clone(),
                        );

                        return Ok(Expr::new_clone(
                            NodeType::Declaration(decl.clone()),
                            e,
                            vec![new_struct_expr],
                        ));
                    }
                }

                // Check if this is an enum definition
                if let NodeType::EnumDef(enum_def) = &value_expr.node_type {
                    // Check if enum already has delete/clone methods
                    let has_delete = enum_def.methods.contains_key("delete");
                    let has_clone = enum_def.methods.contains_key("clone");

                    if !has_delete || !has_clone {
                        let mut new_methods = enum_def.methods.clone();

                        // Generate delete method if needed
                        if !has_delete {
                            new_methods.insert(
                                "delete".to_string(),
                                generate_enum_delete_method(&decl.name, e.line, e.col),
                            );
                        }

                        // Generate clone method if needed
                        if !has_clone {
                            new_methods.insert(
                                "clone".to_string(),
                                generate_enum_clone_method(&decl.name, e.line, e.col),
                            );
                        }

                        let new_enum_def = SEnumDef {
                            variants: enum_def.variants.clone(),
                            methods: new_methods,
                        };

                        let new_enum_expr = Expr::new_clone(
                            NodeType::EnumDef(new_enum_def),
                            value_expr,
                            value_expr.params.clone(),
                        );

                        return Ok(Expr::new_clone(
                            NodeType::Declaration(decl.clone()),
                            e,
                            vec![new_enum_expr],
                        ));
                    }
                }
            }

            // Default: recurse into params
            let mut new_params = Vec::new();
            for p in &e.params {
                new_params.push(preinit_expr(p)?);
            }
            Ok(Expr::new_clone(e.node_type.clone(), e, new_params))
        },
        // Recurse into FuncDef bodies
        NodeType::FuncDef(func_def) => {
            let mut new_body = Vec::new();
            for stmt in &func_def.body {
                new_body.push(preinit_expr(stmt)?);
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
            let mut new_default_values = std::collections::HashMap::new();
            for (name, value_expr) in &struct_def.default_values {
                new_default_values.insert(name.clone(), preinit_expr(value_expr)?);
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
                    new_params.push(preinit_expr(p)?);
                }
                Ok(Expr::new_clone(e.node_type.clone(), e, new_params))
            }
        }
    }
}
