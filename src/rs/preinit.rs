// Preinit phase: Auto-generates delete() and clone() methods for structs/enums.
// Issue #108: Methods are generated into namespace blocks, not into struct definitions.
// This keeps structs clean (only storage fields) while still providing auto-generated methods.

use std::collections::{HashMap, HashSet};
use crate::rs::ordered_map::OrderedMap;

use crate::rs::parser::{
    Expr, NodeType, ValueType, TTypeDef, StructDef, EnumDef, FuncDef, FuncSig, FCallInfo, NamespaceDef, FunctionType,
    Declaration,
};

/// Result of generating a method - contains the declaration and expression.
struct MethodResult {
    decl: Declaration,
    expr: Expr,
}

/// Check if a value type is a primitive (no delete/clone needed).
/// Hardcoded for now: I64, U8, Dynamic, Type
/// Issue #91: Also treats FuncSig types as primitive (function pointers don't own resources).
/// func_sig_types contains names of FuncSig types (e.g., "BinaryIntOp").
fn is_primitive_type(vt: &ValueType, func_sig_types: &HashSet<String>) -> bool {
    match vt {
        ValueType::TCustom(name) => {
            if matches!(name.as_str(), "I64" | "U8" | "Dynamic" | "Type") {
                return true;
            }
            // Issue #91: FuncSig types are like primitives (no delete/clone needed)
            if func_sig_types.contains(name) {
                return true;
            }
            false
        },
        _ => false,
    }
}

/// Generate a delete() method for a struct.
/// The method calls field.delete() for each mutable field in reverse declaration order.
fn generate_delete_method(struct_name: &str, struct_def: &StructDef, line: usize, col: usize, func_sig_types: &HashSet<String>) -> MethodResult {
    // Build: delete := proc(mut self: StructName) { self.field_n.delete(); ... self.field_0.delete(); }

    // Check if there will be any delete calls (determines if we use _self or self)
    let has_non_primitive_fields = struct_def.members.iter()
        .any(|m| m.is_mut && !is_primitive_type(&m.value_type, func_sig_types));
    let self_param_name = if has_non_primitive_fields { "self" } else { "_self" };

    let self_decl = Declaration {
        name: self_param_name.to_string(),
        value_type: ValueType::TCustom(struct_name.to_string()),
        is_mut: true,
        
        is_own: false,
        default_value: None,
    };

    let mut body_stmts: Vec<Expr> = Vec::new();

    // Process fields in reverse order (like C++/Rust destructors)
    for member in struct_def.members.iter().rev() {
        // Skip non-mut fields (constants/methods don't need delete)
        if !member.is_mut {
            continue;
        }

        // Skip primitive types that don't have delete methods
        if is_primitive_type(&member.value_type, func_sig_types) {
            continue;
        }

        // Build: self.field_name.delete()
        let delete_access = Expr::new_explicit(
            NodeType::Identifier("self".to_string()),
            vec![
                Expr::new_explicit(NodeType::Identifier(member.name.clone()), vec![], line, col),
                Expr::new_explicit(NodeType::Identifier("delete".to_string()), vec![], line, col),
            ],
            line,
            col,
        );

        let delete_call = Expr::new_explicit(
            NodeType::FCall(FCallInfo { does_throw: false, is_bang: false }),
            vec![delete_access],
            line,
            col,
        );

        body_stmts.push(delete_call);
    }

    let func_def = FuncDef {
        sig: FuncSig {
            function_type: FunctionType::FTFunc,
            args: vec![self_decl],
            return_types: vec![],
            throw_types: vec![],
        },
        arg_names: vec![self_param_name.to_string()],
        body: body_stmts,
        source_path: String::new(),
    };

    let method_decl = Declaration {
        name: "delete".to_string(),
        value_type: ValueType::TFunction(FunctionType::FTFunc),
        is_mut: false,
        
        is_own: false,
        default_value: None,
    };

    MethodResult {
        decl: method_decl,
        expr: Expr::new_explicit(NodeType::FuncDef(func_def), vec![], line, col),
    }
}

/// Generate a clone() method for a struct.
/// The method returns a new instance with each mutable field cloned.
fn generate_clone_method(struct_name: &str, struct_def: &StructDef, line: usize, col: usize, func_sig_types: &HashSet<String>) -> MethodResult {
    // Build: clone := func(self: StructName) returns StructName { return StructName(field1 = self.field1.clone(), ...) }

    // Use _self when no mut fields (body won't reference self)
    let has_mut_fields = struct_def.members.iter().any(|m| m.is_mut);
    let self_param_name = if has_mut_fields { "self" } else { "_self" };

    let self_decl = Declaration {
        name: self_param_name.to_string(),
        value_type: ValueType::TCustom(struct_name.to_string()),
        is_mut: false,
        
        is_own: false,
        default_value: None,
    };

    let mut named_args: Vec<Expr> = Vec::new();

    for member in struct_def.members.iter() {
        if !member.is_mut {
            continue;
        }

        // For primitive types, just copy the value directly: self.field_name
        // For other types, call clone: self.field_name.clone()
        let field_value = if is_primitive_type(&member.value_type, func_sig_types) {
            // Build: self.field_name
            Expr::new_explicit(
                NodeType::Identifier("self".to_string()),
                vec![
                    Expr::new_explicit(NodeType::Identifier(member.name.clone()), vec![], line, col),
                ],
                line,
                col,
            )
        } else {
            // Build: self.field_name.clone()
            let clone_access = Expr::new_explicit(
                NodeType::Identifier("self".to_string()),
                vec![
                    Expr::new_explicit(NodeType::Identifier(member.name.clone()), vec![], line, col),
                    Expr::new_explicit(NodeType::Identifier("clone".to_string()), vec![], line, col),
                ],
                line,
                col,
            );

            Expr::new_explicit(
                NodeType::FCall(FCallInfo { does_throw: false, is_bang: false }),
                vec![clone_access],
                line,
                col,
            )
        };

        let named_arg = Expr::new_explicit(
            NodeType::NamedArg(member.name.clone()),
            vec![field_value],
            line,
            col,
        );

        named_args.push(named_arg);
    }

    let struct_name_id = Expr::new_explicit(
        NodeType::Identifier(struct_name.to_string()),
        vec![],
        line,
        col,
    );

    let mut struct_literal_params = vec![struct_name_id];
    struct_literal_params.extend(named_args);

    let struct_literal = Expr::new_explicit(
        NodeType::FCall(FCallInfo { does_throw: false, is_bang: false }),
        struct_literal_params,
        line,
        col,
    );

    let return_stmt = Expr::new_explicit(
        NodeType::Return,
        vec![struct_literal],
        line,
        col,
    );

    let func_def = FuncDef {
        sig: FuncSig {
            function_type: FunctionType::FTFunc,
            args: vec![self_decl],
            return_types: vec![ValueType::TCustom(struct_name.to_string())],
            throw_types: vec![],
        },
        arg_names: vec![self_param_name.to_string()],
        body: vec![return_stmt],
        source_path: String::new(),
    };

    let method_decl = Declaration {
        name: "clone".to_string(),
        value_type: ValueType::TFunction(FunctionType::FTFunc),
        is_mut: false,
        
        is_own: false,
        default_value: None,
    };

    MethodResult {
        decl: method_decl,
        expr: Expr::new_explicit(NodeType::FuncDef(func_def), vec![], line, col),
    }
}

/// Generate a delete() method for an enum - no-op since enums are value types.
fn generate_enum_delete_method(enum_name: &str, line: usize, col: usize) -> Expr {
    let self_decl = Declaration {
        name: "_self".to_string(),
        value_type: ValueType::TCustom(enum_name.to_string()),
        is_mut: true,
        
        is_own: false,
        default_value: None,
    };

    let func_def = FuncDef {
        sig: FuncSig {
            function_type: FunctionType::FTFunc,
            args: vec![self_decl],
            return_types: vec![],
            throw_types: vec![],
        },
        arg_names: vec!["_self".to_string()],
        body: vec![],
        source_path: String::new(),
    };

    Expr::new_explicit(NodeType::FuncDef(func_def), vec![], line, col)
}

/// Generate a clone() method for an enum - returns self since enums are value types.
fn generate_enum_clone_method(enum_name: &str, line: usize, col: usize) -> Expr {
    let self_decl = Declaration {
        name: "self".to_string(),
        value_type: ValueType::TCustom(enum_name.to_string()),
        is_mut: false,
        
        is_own: false,
        default_value: None,
    };

    let return_stmt = Expr::new_explicit(
        NodeType::Return,
        vec![Expr::new_explicit(NodeType::Identifier("self".to_string()), vec![], line, col)],
        line,
        col,
    );

    let func_def = FuncDef {
        sig: FuncSig {
            function_type: FunctionType::FTFunc,
            args: vec![self_decl],
            return_types: vec![ValueType::TCustom(enum_name.to_string())],
            throw_types: vec![],
        },
        arg_names: vec!["self".to_string()],
        body: vec![return_stmt],
        source_path: String::new(),
    };

    Expr::new_explicit(NodeType::FuncDef(func_def), vec![], line, col)
}

/// Collect all methods defined in namespace blocks (now stored as ns field on struct/enum).
/// Returns a set of (type_name, method_name) pairs.
fn collect_namespace_methods(ast: &Expr) -> HashSet<(String, String)> {
    let mut methods = HashSet::new();

    if let NodeType::Body = &ast.node_type {
        for child in &ast.params {
            if let NodeType::Declaration(decl) = &child.node_type {
                if let Some(value_expr) = child.params.first() {
                    match &value_expr.node_type {
                        NodeType::StructDef(struct_def) => {
                            for member in &struct_def.ns.members {
                                methods.insert((decl.name.clone(), member.name.clone()));
                            }
                        },
                        NodeType::EnumDef(enum_def) => {
                            for member in &enum_def.ns.members {
                                methods.insert((decl.name.clone(), member.name.clone()));
                            }
                        },
                        _ => {}
                    }
                }
            }
        }
    }

    methods
}

/// Collect all structs that need auto-generated methods.
/// Returns a map from struct_name to (struct_def, line, col, needs_delete, needs_clone).
fn collect_structs_needing_methods(
    ast: &Expr,
    namespace_methods: &HashSet<(String, String)>,
) -> OrderedMap<String, (StructDef, usize, usize, bool, bool)> {
    let mut structs = OrderedMap::new();

    if let NodeType::Body = &ast.node_type {
        for child in &ast.params {
            if let NodeType::Declaration(decl) = &child.node_type {
                if let Some(value_expr) = child.params.first() {
                    if let NodeType::StructDef(struct_def) = &value_expr.node_type {
                        // Check if delete/clone are already defined (in struct members, struct default_values, or ns)
                        let has_delete_inline = struct_def.members.iter().any(|m| m.name == "delete")
                            || struct_def.default_values.contains_key("delete");
                        let has_delete_ns = struct_def.ns.members.iter().any(|m| m.name == "delete");
                        let has_delete_namespace = namespace_methods.contains(&(decl.name.clone(), "delete".to_string()));
                        let has_delete = has_delete_inline || has_delete_ns || has_delete_namespace;

                        let has_clone_inline = struct_def.members.iter().any(|m| m.name == "clone")
                            || struct_def.default_values.contains_key("clone");
                        let has_clone_ns = struct_def.ns.members.iter().any(|m| m.name == "clone");
                        let has_clone_namespace = namespace_methods.contains(&(decl.name.clone(), "clone".to_string()));
                        let has_clone = has_clone_inline || has_clone_ns || has_clone_namespace;

                        let needs_delete = !has_delete;
                        let needs_clone = !has_clone;

                        if needs_delete || needs_clone {
                            structs.insert(
                                decl.name.clone(),
                                (struct_def.clone(), child.line, child.col, needs_delete, needs_clone),
                            );
                        }
                    }
                }
            }
        }
    }

    structs
}

/// Issue #105: Public API for generating delete/clone methods for a macro-expanded struct.
/// Returns Some(NamespaceDef) if the struct needs auto-generated methods, None otherwise.
pub fn generate_struct_methods(struct_name: &str, struct_def: &StructDef, _line: usize, _col: usize, func_sig_types: &HashSet<String>) -> Option<NamespaceDef> {
    // Check if delete/clone are already defined (inline or in ns)
    let has_delete = struct_def.members.iter().any(|m| m.name == "delete")
        || struct_def.default_values.contains_key("delete")
        || struct_def.ns.members.iter().any(|m| m.name == "delete");
    let has_clone = struct_def.members.iter().any(|m| m.name == "clone")
        || struct_def.default_values.contains_key("clone")
        || struct_def.ns.members.iter().any(|m| m.name == "clone");

    let needs_delete = !has_delete;
    let needs_clone = !has_clone;

    if needs_delete || needs_clone {
        Some(generate_namespace_block(struct_name, struct_def, needs_delete, needs_clone, func_sig_types))
    } else {
        None
    }
}

/// Issue #106: Public API for generating delete/clone methods for a macro-expanded enum.
/// Returns Some(NamespaceDef) if the enum needs auto-generated methods, None otherwise.
pub fn generate_enum_methods(enum_name: &str, has_delete: bool, has_clone: bool, line: usize, col: usize) -> Option<NamespaceDef> {
    let needs_delete = !has_delete;
    let needs_clone = !has_clone;

    if needs_delete || needs_clone {
        let mut members = Vec::new();
        let mut default_values = HashMap::new();

        if needs_delete {
            let delete_decl = Declaration {
                name: "delete".to_string(),
                value_type: ValueType::TFunction(FunctionType::FTFunc),
                is_mut: false,
                
                is_own: false,
                default_value: None,
            };
            let delete_expr = generate_enum_delete_method(enum_name, line, col);
            members.push(delete_decl);
            default_values.insert("delete".to_string(), delete_expr);
        }

        if needs_clone {
            let clone_decl = Declaration {
                name: "clone".to_string(),
                value_type: ValueType::TFunction(FunctionType::FTFunc),
                is_mut: false,
                
                is_own: false,
                default_value: None,
            };
            let clone_expr = generate_enum_clone_method(enum_name, line, col);
            members.push(clone_decl);
            default_values.insert("clone".to_string(), clone_expr);
        }

        Some(NamespaceDef {
            members,
            default_values,
        })
    } else {
        None
    }
}

/// Generate a NamespaceDef with auto-generated methods for a struct.
fn generate_namespace_block(
    struct_name: &str,
    struct_def: &StructDef,
    needs_delete: bool,
    needs_clone: bool,
    func_sig_types: &HashSet<String>,
) -> NamespaceDef {
    let mut members = Vec::new();
    let mut default_values = HashMap::new();

    if needs_delete {
        let delete_result = generate_delete_method(struct_name, struct_def, 0, 0, func_sig_types);
        members.push(delete_result.decl);
        default_values.insert("delete".to_string(), delete_result.expr);
    }

    if needs_clone {
        let clone_result = generate_clone_method(struct_name, struct_def, 0, 0, func_sig_types);
        members.push(clone_result.decl);
        default_values.insert("clone".to_string(), clone_result.expr);
    }

    NamespaceDef {
        members,
        default_values,
    }
}

/// Recursively process expression (for nested function bodies, etc.)
fn preinit_expr_inner(e: &Expr) -> Result<Expr, String> {
    match &e.node_type {
        NodeType::FuncDef(func_def) => {
            let mut new_body = Vec::new();
            for stmt in &func_def.body {
                new_body.push(preinit_expr_inner(stmt)?);
            }
            let new_func_def = FuncDef {
                sig: func_def.sig.clone(),
                arg_names: func_def.arg_names.clone(),
                body: new_body,
                source_path: func_def.source_path.clone(),
            };
            Ok(Expr::new_clone(NodeType::FuncDef(new_func_def), e, e.params.clone()))
        },
        NodeType::StructDef(struct_def) => {
            // Recurse into default values but DON'T add delete/clone here
            let mut new_default_values = HashMap::new();
            for (name, value_expr) in &struct_def.default_values {
                new_default_values.insert(name.clone(), preinit_expr_inner(value_expr)?);
            }
            let new_struct_def = StructDef {
                members: struct_def.members.clone(),
                default_values: new_default_values,
                ns: struct_def.ns.clone(),
            };
            Ok(Expr::new_clone(NodeType::StructDef(new_struct_def), e, e.params.clone()))
        },
        NodeType::Declaration(decl) => {
            // For enum definitions, still add delete/clone directly (enums don't use namespace blocks yet)
            if let Some(value_expr) = e.params.first() {
                if let NodeType::EnumDef(enum_def) = &value_expr.node_type {
                    let has_delete = enum_def.methods.contains_key("delete");
                    let has_clone = enum_def.methods.contains_key("clone");

                    if !has_delete || !has_clone {
                        let mut new_methods = enum_def.methods.clone();

                        if !has_delete {
                            new_methods.insert(
                                "delete".to_string(),
                                generate_enum_delete_method(&decl.name, e.line, e.col),
                            );
                        }

                        if !has_clone {
                            new_methods.insert(
                                "clone".to_string(),
                                generate_enum_clone_method(&decl.name, e.line, e.col),
                            );
                        }

                        let new_enum_def = EnumDef {
                            variants: enum_def.variants.clone(),
                            methods: new_methods,
                            ns: enum_def.ns.clone(),
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
            let mut decl_new_params = Vec::new();
            for p in &e.params {
                decl_new_params.push(preinit_expr_inner(p)?);
            }
            Ok(Expr::new_clone(e.node_type.clone(), e, decl_new_params))
        },
        _ => {
            if e.params.is_empty() {
                Ok(e.clone())
            } else {
                let mut default_new_params = Vec::new();
                for p in &e.params {
                    default_new_params.push(preinit_expr_inner(p)?);
                }
                Ok(Expr::new_clone(e.node_type.clone(), e, default_new_params))
            }
        }
    }
}

/// Preinit phase entry point.
/// For structs: generates namespace blocks with delete/clone methods.
/// For enums: adds delete/clone directly to the enum definition.
pub fn preinit_expr(e: &Expr) -> Result<Expr, String> {
    // For Body nodes (the AST root), do the two-pass approach
    if let NodeType::Body = &e.node_type {
        // Pass 1: Collect namespace-defined methods
        let namespace_methods = collect_namespace_methods(e);

        // Pass 2: Find structs that need auto-generated methods
        let structs_needing_methods = collect_structs_needing_methods(e, &namespace_methods);

        // Issue #91: Collect FuncSig type names (declarations with TType(TFuncSig) annotation
        // or FuncDef body that's empty {} indicating a signature type)
        let mut func_sig_types = HashSet::new();
        for child in &e.params {
            if let NodeType::Declaration(decl) = &child.node_type {
                if decl.value_type == ValueType::TType(TTypeDef::TFuncSig) {
                    func_sig_types.insert(decl.name.clone());
                } else if let Some(value_expr) = child.params.first() {
                    // Inferred: BinaryIntOp := func(I64, I64) returns I64 {}
                    if let NodeType::FuncDef(func_def) = &value_expr.node_type {
                        if func_def.body.is_empty() {
                            func_sig_types.insert(decl.name.clone());
                        }
                    }
                }
            }
        }

        // Pass 3: Process all children, setting ns on struct defs that need auto-generated methods
        let mut new_params = Vec::new();
        for child in &e.params {
            let mut processed = preinit_expr_inner(child)?;

            // If this is a Declaration of a StructDef that needs methods, set the ns field
            if let NodeType::Declaration(decl) = &processed.node_type {
                if let Some((_, (_, _, _, needs_delete, needs_clone))) = structs_needing_methods.iter().find(|(name, _)| *name == &decl.name) {
                    if let Some(value_expr) = processed.params.first() {
                        if let NodeType::StructDef(struct_def) = &value_expr.node_type {
                            let auto_ns = generate_namespace_block(&decl.name, struct_def, *needs_delete, *needs_clone, &func_sig_types);
                            // Merge auto-generated ns with any user-defined ns
                            let mut merged_ns = struct_def.ns.clone();
                            for m in auto_ns.members {
                                if !merged_ns.members.iter().any(|existing| existing.name == m.name) {
                                    merged_ns.members.push(m);
                                }
                            }
                            for (k, v) in auto_ns.default_values {
                                if !merged_ns.default_values.contains_key(&k) {
                                    merged_ns.default_values.insert(k, v);
                                }
                            }
                            let new_struct_def = StructDef {
                                members: struct_def.members.clone(),
                                default_values: struct_def.default_values.clone(),
                                ns: merged_ns,
                            };
                            let new_value_expr = Expr::new_clone(NodeType::StructDef(new_struct_def), value_expr, value_expr.params.clone());
                            processed = Expr::new_clone(processed.node_type.clone(), &processed, vec![new_value_expr]);
                        }
                    }
                }
            }

            new_params.push(processed);
        }

        return Ok(Expr::new_clone(e.node_type.clone(), e, new_params));
    }

    // For non-Body nodes, just recurse
    preinit_expr_inner(e)
}
