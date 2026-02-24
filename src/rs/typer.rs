use std::collections::HashMap;
use crate::rs::init::{Context, SymbolInfo, RemovedSymbol, ScopeType, get_value_type, get_func_name_in_call, import_path_to_file_path};
use crate::rs::parser::{
    INFER_TYPE, Literal,
    Expr, NodeType, ValueType, EnumDef, StructDef, FuncDef, FCallInfo, NamespaceDef, Declaration, PatternInfo, FunctionType, TTypeDef,
    value_type_to_str, str_to_value_type,
};

// Type checking phase: Validates types, return/throw statements, mode constraints
// This module handles the type checking phase that runs after init.
// No eval, no heap access - pure type analysis.

// Context tracking for return value usage enforcement (Bug #8 fix)
#[derive(Clone, Copy, PartialEq)]
enum ExprContext {
    // Return value is being used (assigned, passed as arg, returned, etc)
    ValueUsed,
    // Return value is discarded (statement in Body)
    ValueDiscarded,
}

pub struct ThrownType {
    pub type_str: String,
    pub msg: String,
}

// Type-check an imported file's AST.
// Called when the typer encounters an import() call.
// The AST was stored during init phase; we just run type checking on it.
pub fn typer_import_declarations(context: &mut Context, import_path_str: &str) -> Vec<String> {
    let path = import_path_to_file_path(import_path_str);

    // Already done (or in progress)? Skip.
    // Adding to done at START handles both circular imports and re-imports.
    if context.imports_typer_done.contains(&path) {
        return vec![];
    }

    // Mark as done immediately - before processing - to handle circular imports
    context.imports_typer_done.insert(path.clone());

    // Get stored AST from init phase
    let ast = match context.imported_asts.get(&path) {
        Some(ast) => ast.clone(),
        None => {
            // This shouldn't happen - init phase should have stored the AST
            return vec![format!("typer: Import {} not found in stored ASTs - init phase should have stored it", path)];
        }
    };

    // Get stored mode from init phase (Bug #41 fix)
    let file_mode = match context.imported_modes.get(&path) {
        Some(file_mode) => file_mode.clone(),
        None => {
            // This shouldn't happen - init phase should have stored the mode
            return vec![format!("typer: Import {} not found in stored modes - init phase should have stored it", path)];
        }
    };

    // Save and restore context path and mode (Bug #41 fix: respect imported file's mode)
    let original_path = context.path.clone();
    let original_mode = context.mode_def.clone();
    context.path = path.clone();
    context.mode_def = file_mode;

    // Bug #128: Run type checking AND resolve INFER_TYPE, then update stored AST
    let (resolved_ast, errors) = match type_check(context, &ast) {
        Ok((resolved, errs)) => (resolved, errs),
        Err(err) => {
            context.path = original_path;
            context.mode_def = original_mode;
            return vec![err];
        }
    };

    // Update stored AST with resolved version
    context.imported_asts.insert(path, resolved_ast);

    context.path = original_path;
    context.mode_def = original_mode;
    return errors;
}

fn check_enum_def(context: &Context, e: &Expr, enum_def: &EnumDef) -> Result<Vec<String>, String> {
    let mut errors : Vec<String> = Vec::new();
    if e.params.len() != 0 {
        errors.push(e.exit_error("type", "in check_enum_def(): enum declarations don't have any parameters in the tree."));
        return Ok(errors)
    }

    for v in &enum_def.variants {
        match &v.payload_type {
            None => {},
            Some(value_type) => {
                match value_type {
                    ValueType::TCustom(ref custom_type_name) => {
                        // Validate that the custom type exists
                        if context.scope_stack.lookup_symbol(custom_type_name).is_none() {
                            errors.push(e.error(&context.path, "type", &format!(
                                "Enum variant '{}' uses undefined type '{}'.\nHint: Make sure '{}' is defined before this enum.",
                                v.name, custom_type_name, custom_type_name
                            )));
                        } else {
                            // Validate it's actually a type (enum or struct), not a value
                            let symbol_info = context.scope_stack.lookup_symbol(custom_type_name).unwrap();
                            match &symbol_info.value_type {
                                ValueType::TType(TTypeDef::TEnumDef) |
                                ValueType::TType(TTypeDef::TStructDef) => {
                                    // Valid type
                                },
                                _ => {
                                    errors.push(e.error(&context.path, "type", &format!(
                                        "Enum variant '{}' payload type '{}' is not a valid type (expected enum or struct, found {}).",
                                        v.name, custom_type_name, value_type_to_str(&symbol_info.value_type)
                                    )));
                                }
                            }
                        }
                    },
                    _ => {
                        errors.push(e.todo_error(&context.path, "type", &format!("'enum' does not support payloads of value type '{}' yet",
                                                                  value_type_to_str(&value_type))));
                    },
                }
            },
        }
    }
    return Ok(errors);
}

// Issue #179: Check if an expression is a cast() call
fn is_cast_call(e: &Expr) -> bool {
    if let NodeType::FCall(_) = &e.node_type {
        get_func_name_in_call(e) == "cast"
    } else {
        false
    }
}

// Public entry point: assumes Body-level context (return values discarded at statement level)
// Note: Prefer type_check() which also resolves INFER_TYPE in the AST.
fn check_types(context: &mut Context, e: &Expr) -> Result<Vec<String>, String> {
    return check_types_with_context(context, e, ExprContext::ValueDiscarded);
}

/// Bug #128: Unified type checking entry point.
/// Runs type checking and resolves all INFER_TYPE references in the AST.
/// Returns the resolved AST and any type errors found.
/// After this function, no INFER_TYPE should remain in the returned AST.
pub fn type_check(context: &mut Context, e: &Expr) -> Result<(Expr, Vec<String>), String> {
    let errors = check_types(context, e)?;
    // If check_types found errors, don't try to resolve types - just return the errors.
    // This avoids duplicate errors from resolve_inferred_types trying the same things.
    if !errors.is_empty() {
        return Ok((e.clone(), errors));
    }
    let resolved = resolve_inferred_types(context, e)?;
    Ok((resolved, errors))
}

// Issue #105 Step 4d: Check if a declared metatype annotation matches an inferred TType
fn metatype_matches(declared: &ValueType, inferred: &ValueType) -> bool {
    match (declared, inferred) {
        (ValueType::TCustom(name), ValueType::TType(TTypeDef::TStructDef)) if name == "StructDef" => true,
        (ValueType::TCustom(name), ValueType::TType(TTypeDef::TEnumDef)) if name == "EnumDef" => true,
        (ValueType::TCustom(name), ValueType::TType(TTypeDef::TFuncSig)) if name == "FuncSig" => true,
        _ => false,
    }
}

// Internal type checker with context tracking for return value usage
fn check_types_with_context(context: &mut Context, e: &Expr, expr_context: ExprContext) -> Result<Vec<String>, String> {
    let mut errors : Vec<String> = Vec::new();
    match &e.node_type {
        NodeType::Body => {
            // Statements in Body discard return values
            for p in e.params.iter() {
                errors.extend(check_types_with_context(context, &p, ExprContext::ValueDiscarded)?);
            }
        },
        NodeType::EnumDef(enum_def) => {
            errors.extend(check_enum_def(context, &e, enum_def)?);
            // Type-check namespace function bodies
            errors.extend(check_namespace_def(context, &e, &enum_def.ns)?);
        },
        NodeType::StructDef(struct_def) => {
            errors.extend(check_struct_def(context, &e, struct_def));
            // Type-check namespace function bodies
            errors.extend(check_namespace_def(context, &e, &struct_def.ns)?);
        },
        NodeType::If => {
            errors.extend(check_if_statement(context, &e)?);
        },
        NodeType::While => {
            errors.extend(check_while_statement(context, &e)?);
        },
        NodeType::Switch => {
            errors.extend(check_switch_statement(context, &e)?);
        },
        NodeType::Range => {
            if e.params.len() != 2 {
                errors.push(e.lang_error(&context.path, "type", "Range expression must have exactly two elements"));
                return Ok(errors);
            }

            // Range operands are used
            errors.extend(check_types_with_context(context, e.params.get(0).unwrap(), ExprContext::ValueUsed)?);
            errors.extend(check_types_with_context(context, e.params.get(1).unwrap(), ExprContext::ValueUsed)?);

            let left_type = get_value_type(context, e.params.get(0).unwrap());
            if let Err(err) = &left_type {
                errors.push(err.clone());
            }
            let right_type = get_value_type(context, e.params.get(1).unwrap());
            if let Err(err) = &right_type {
                errors.push(err.clone());
            }

            if let (Ok(t1), Ok(t2)) = (left_type, right_type) {
                if t1 != t2 {
                    errors.push(e.error(&context.path, "type", &format!("Range start and end must be of same type, found '{}' and '{}'",
                                                         value_type_to_str(&t1), value_type_to_str(&t2))));
                }
            }
        },
        NodeType::FCall(ref fcall_info) => {
            let does_throw = fcall_info.does_throw;
            // Special handling for import() calls - type-check the imported file
            let f_name = get_func_name_in_call(&e);
            if f_name == "import" {
                // Get the import path from the argument
                if let Some(path_expr) = e.params.get(1) {
                    if let NodeType::LLiteral(Literal::Str(import_path)) = &path_expr.node_type {
                        errors.extend(typer_import_declarations(context, import_path));
                    }
                }
            }
            // cast(Type, ptr_expr) - expression syntax
            // Variable declaration handled by the Declaration node, not here
            if f_name == "cast" {
                if e.params.len() >= 3 {
                    if let NodeType::Identifier(type_name) = &e.params.get(1).unwrap().node_type {
                        // Validate type exists
                        let type_valid = matches!(type_name.as_str(), "I64" | "U8" | "Bool" | "Str")
                            || context.scope_stack.lookup_struct(type_name).is_some()
                            || context.scope_stack.lookup_enum(type_name).is_some();
                        if !type_valid {
                            errors.push(e.error(&context.path, "type", &format!("cast: unknown type '{}'", type_name)));
                        }
                    }
                    // Type-check the ptr expression (params[2])
                    errors.extend(check_types_with_context(context, e.params.get(2).unwrap(), ExprContext::ValueUsed)?);
                }
            } else {
                errors.extend(check_fcall(context, &e, does_throw)?);
                // Check if return value usage is correct for this context
                errors.extend(check_fcall_return_usage(context, &e, expr_context)?);
            }
        },
        NodeType::FuncDef(func_def) => {
            context.scope_stack.push(ScopeType::Function);
            errors.extend(check_func_proc_types(&func_def, context, &e)?);
            context.scope_stack.pop().ok();
        },
        NodeType::Identifier(name) => {
            // Bug #32 fix: "_" is a special marker for field access on expression results
            // params[0] is the expression, params[1..] are the field chain (field names, not symbols)
            if name == "_" && !e.params.is_empty() {
                // Only check the base expression (params[0])
                // params[1..] are field identifiers that don't need symbol lookup
                errors.extend(check_types_with_context(context, e.params.get(0).unwrap(), ExprContext::ValueUsed)?);
            } else if !(context.scope_stack.has_func(name) || context.scope_stack.has_symbol(name)) {
                errors.push(e.error(&context.path, "type", &format!("Undefined symbol '{}'", name)));
            } else if context.scope_stack.is_closure_capture(name) {
                // Bug #50: Closures not supported yet
                errors.push(e.todo_error(&context.path, "type", &format!(
                    "Closures are not supported yet. Pass '{}' as a parameter to this function instead.", name)));
            } else {
                // Bug #101: Mark symbol as used
                context.scope_stack.mark_symbol_used(name);
            }
        },
        NodeType::Declaration(decl) => {
            errors.extend(check_declaration(context, &e, decl)?);
        },
        NodeType::Assignment(var_name) => {
            errors.extend(check_assignment(context, &e, var_name)?);
        },
        NodeType::Return | NodeType::Throw => {
            // Return/throw values are used
            for return_val in &e.params {
                // Issue #179: Reject cast() in return/throw position
                if is_cast_call(return_val) {
                    errors.push(return_val.error(&context.path, "type",
                        "cast(Type, expr) cannot be used in return/throw. Extract to a variable: 'x := cast(...)' then use 'x'."));
                } else {
                    errors.extend(check_types_with_context(context, &return_val, ExprContext::ValueUsed)?);
                }
            }
        },
        NodeType::Catch => {
            errors.extend(check_catch_statement(context, &e)?);
        }

        NodeType::LLiteral(_) | NodeType::DefaultCase | NodeType::Pattern(_) => {},
        NodeType::Break | NodeType::Continue => {
            // Break and Continue are simple statements with no parameters to type-check
            // Scope validation (must be inside a loop) could be added here later
        },
        NodeType::Defer => {
            // Issue #188: Defer - type-check the deferred expression (params[0])
            // Defer is desugared later in the desugarer phase
            for p in &e.params {
                errors.extend(check_types_with_context(context, p, expr_context)?);
            }
        },
        NodeType::NamedArg(_) => {
            // Named args - type check the value expression
            for p in &e.params {
                errors.extend(check_types_with_context(context, p, expr_context)?);
            }
        },
        NodeType::ForIn(_var_type) => {
            errors.extend(check_forin_statement(context, &e)?);
        },
    }

    return Ok(errors)
}

// Helper function to validate conditional statement parameters
fn validate_conditional_params(_path: &str, e: &Expr, stmt_type: &str, min: usize, max: usize) -> Option<String> {
    if e.params.len() < min || e.params.len() > max {
        if min == max {
            return Some(e.exit_error("type", &format!("{} nodes must have exactly {} parameters.", stmt_type, min)));
        } else {
            return Some(e.exit_error("type", &format!("{} nodes must have {} or {} parameters.", stmt_type, min, max)));
        }
    }
    None
}

// Helper function to validate function/procedure argument counts
fn validate_func_arg_count(path: &str, e: &Expr, f_name: &str, func_def: &FuncDef) -> Option<String> {
    let provided_args = e.params.len() - 1;

    // Check zero-arg functions
    if func_def.sig.args.len() == 0 && provided_args > 0 {
        return Some(e.error(path, "type", &format!("Function/procedure '{}' expects 0 args, but {} were provided.", f_name, provided_args)));
    }

    let has_multi_arg = func_proc_has_multi_arg(&func_def);

    // Count required args (those without default values)
    let required_args = func_def.sig.args.iter().filter(|a| a.default_value.is_none()).count();

    // Check arg count for non-variadic functions
    // Must provide at least required args, and at most total args
    if !has_multi_arg {
        if provided_args < required_args {
            return Some(e.error(path, "type", &format!("Function/procedure '{}' expects at least {} args, but {} were provided.",
                                                 f_name, required_args, provided_args)));
        }
        if provided_args > func_def.sig.args.len() {
            return Some(e.error(path, "type", &format!("Function/procedure '{}' expects at most {} args, but {} were provided.",
                                                 f_name, func_def.sig.args.len(), provided_args)));
        }
    }

    // Check minimum count for variadic functions
    if has_multi_arg && func_def.sig.args.len() - 1 > provided_args {
        return Some(e.error(path, "type", &format!("Function/procedure '{}' expects at least {} args, but {} were provided.",
                                             f_name, func_def.sig.args.len() - 1, provided_args)));
    }

    None
}

// Issue #117: snapshot_symbols and restore_removed_symbols removed.
// Replaced by lazy removal tracking via ScopeStack methods:
// begin_removal_tracking, end_removal_tracking, removal_mark,
// drain_removals_since, restore_removed.

fn check_if_statement(context: &mut Context, e: &Expr) -> Result<Vec<String>, String> {
    let mut errors : Vec<String> = Vec::new();
    if let Some(err) = validate_conditional_params(&context.path, e, "if", 2, 3) {
        errors.push(err);
        return Ok(errors);
    }

    let inner_e = match e.params.get(0) {
        Some(inner_e_) => inner_e_,
        None => {
            errors.push(e.error(&context.path, "type", "if statement missing condition"));
            return Ok(errors)
        },
    };
    // Type check the condition expression exists, but don't enforce it must be Bool
    // NOTE: Bool type checking removed - Bool is a regular struct, not a special primitive
    // DEBUG: This call to get_value_type triggers type checking of the condition
    // which might recursively process nested expressions
    match get_value_type(&context, &inner_e) {
        Ok(_val_type) => {},
        Err(error_string) => {
            errors.push(error_string);
            return Ok(errors);
        },
    };
    // Type check condition
    errors.extend(check_types_with_context(context, e.params.get(0).unwrap(), ExprContext::ValueUsed)?);

    // Issue #117: Type check then/else bodies with own-consumption isolation.
    // Uses lazy removal tracking instead of full symbol map cloning.
    context.scope_stack.begin_removal_tracking();
    let mut consumed_per_branch: Vec<Vec<RemovedSymbol>> = Vec::new();
    let branch_count = e.params.len() - 1;
    for i in 1..e.params.len() {
        let mark = context.scope_stack.removal_mark();
        errors.extend(check_types_with_context(context, e.params.get(i).unwrap(), ExprContext::ValueDiscarded)?);
        let removed = context.scope_stack.drain_removals_since(mark);
        context.scope_stack.restore_removed(&removed);
        consumed_per_branch.push(removed);
    }
    context.scope_stack.end_removal_tracking();
    // Remove symbols consumed in ALL branches (if there's both then and else)
    if branch_count >= 2 {
        if let Some(first) = consumed_per_branch.first() {
            for entry in first {
                let consumed_in_all = consumed_per_branch.iter()
                    .all(|c| c.iter().any(|e| e.name == entry.name));
                if consumed_in_all {
                    context.scope_stack.remove_symbol(&entry.name);
                }
            }
        }
    }
    return Ok(errors);
}

fn check_while_statement(context: &mut Context, e: &Expr) -> Result<Vec<String>, String> {
    let mut errors : Vec<String> = Vec::new();
    if let Some(err) = validate_conditional_params(&context.path, e, "while", 2, 2) {
        errors.push(err);
        return Ok(errors);
    }

    let inner_e = match e.params.get(0) {
        Some(inner_e_) => inner_e_,
        None => {
            errors.push(e.error(&context.path, "type", "while statement missing condition"));
            return Ok(errors)
        },
    };
    // Type check the condition expression exists, but don't enforce it must be Bool
    // NOTE: Bool type checking removed - Bool is a regular struct, not a special primitive
    match get_value_type(&context, &inner_e) {
        Ok(_val_type) => {},
        Err(error_string) => {
            errors.push(error_string);
            return Ok(errors);
        },
    };
    // First param (condition) is used, second param (body) discards values
    for (i, p) in e.params.iter().enumerate() {
        let ctx = if i == 0 { ExprContext::ValueUsed } else { ExprContext::ValueDiscarded };
        errors.extend(check_types_with_context(context, &p, ctx)?);
    }
    return Ok(errors);
}

fn check_forin_statement(context: &mut Context, e: &Expr) -> Result<Vec<String>, String> {
    let mut errors: Vec<String> = Vec::new();

    // e.params[0] = Identifier(var_name)
    // e.params[1] = collection expression
    // e.params[2] = body
    // NodeType::ForIn(var_type_name)

    let var_type_name = match &e.node_type {
        NodeType::ForIn(type_name) => type_name.clone(),
        _ => return Ok(vec![e.lang_error(&context.path, "type", "Expected ForIn node")]),
    };

    // Extract variable name from params[0]
    let var_name = match &e.params.get(0) {
        Some(var_expr) => match &var_expr.node_type {
            NodeType::Identifier(name) => name.clone(),
            _ => return Ok(vec![e.lang_error(&context.path, "type", "ForIn: expected identifier for loop variable")]),
        },
        None => return Ok(vec![e.lang_error(&context.path, "type", "ForIn: missing loop variable")]),
    };

    // Get collection expression
    let collection_expr = match e.params.get(1) {
        Some(expr) => expr,
        None => return Ok(vec![e.lang_error(&context.path, "type", "ForIn: missing collection expression")]),
    };

    // Type check the collection expression
    errors.extend(check_types_with_context(context, collection_expr, ExprContext::ValueUsed)?);

    // Get collection type
    let collection_type = match get_value_type(context, collection_expr) {
        Ok(t) => t,
        Err(err) => {
            errors.push(err);
            return Ok(errors);
        }
    };

    let type_name = match &collection_type {
        ValueType::TCustom(name) => name.clone(),
        _ => {
            errors.push(e.error(&context.path, "type", "for-in loop requires a collection type"));
            return Ok(errors);
        }
    };

    // Check TypeName.len() exists and returns I64
    let len_method = format!("{}.len", type_name);
    match context.scope_stack.lookup_func(&len_method) {
        Some(func_def) => {
            // Verify returns I64
            if func_def.sig.return_types.len() != 1 ||
               func_def.sig.return_types[0] != ValueType::TCustom("I64".to_string()) {
                errors.push(e.error(&context.path, "type", &format!(
                    "for-in loop: '{}.len()' must return I64", type_name)));
            }
        },
        None => {
            errors.push(e.error(&context.path, "type", &format!(
                "for-in loop: type '{}' does not have a 'len()' method.\n\
                 Required: {}.len(self) returns I64", type_name, type_name)));
        }
    }

    // Check TypeName.get() exists with right signature
    let get_method = format!("{}.get", type_name);
    match context.scope_stack.lookup_func(&get_method) {
        Some(func_def) => {
            // Verify signature: get(self, I64) returns Ptr throws IndexOutOfBoundsError
            let mut throws_index_error = false;
            for t in &func_def.sig.throw_types {
                if *t == ValueType::TCustom("IndexOutOfBoundsError".to_string()) {
                    throws_index_error = true;
                    break;
                }
            }
            let valid = func_def.sig.args.len() >= 2
                && func_def.sig.args[1].value_type == ValueType::TCustom("I64".to_string())
                && !func_def.sig.return_types.is_empty()
                && func_def.sig.return_types[0] == ValueType::TCustom("Ptr".to_string())
                && throws_index_error;

            if !valid {
                errors.push(e.error(&context.path, "type", &format!(
                    "for-in loop: '{}.get()' has wrong signature.\n\
                     Required: {}.get(self, index: I64) returns Ptr throws IndexOutOfBoundsError",
                    type_name, type_name)));
            }
        },
        None => {
            errors.push(e.error(&context.path, "type", &format!(
                "for-in loop: type '{}' does not have a 'get()' method.\n\
                 Required: {}.get(self, index: I64) returns Ptr throws IndexOutOfBoundsError",
                type_name, type_name)));
        }
    }

    // Push scope for loop body, declare loop variable
    context.scope_stack.push(ScopeType::Block);
    context.scope_stack.declare_symbol(var_name, SymbolInfo {
        value_type: ValueType::TCustom(var_type_name),
        is_mut: true,  // Loop variable is mutable
        is_copy: false,
        is_own: false,
        is_comptime_const: false,
    });

    // Type check body
    if let Some(body_expr) = e.params.get(2) {
        errors.extend(check_types_with_context(context, body_expr, ExprContext::ValueDiscarded)?);
    }

    context.scope_stack.pop().ok();
    Ok(errors)
}

fn check_fcall(context: &mut Context, e: &Expr, does_throw: bool) -> Result<Vec<String>, String> {
    let mut errors: Vec<String> = Vec::new();
    let f_name = get_func_name_in_call(e);
    // Bug #101: Mark the function name as used (for local function declarations)
    context.scope_stack.mark_symbol_used(&f_name);
    let mut e = e.clone();
    let func_def = match get_func_def_for_fcall_with_expr(&context, &mut e) {
        Ok(func_def_) => match func_def_ {
            Some(func_def_) => func_def_,
            None => {
                // Struct or enum instantiation - validate field names and types for structs (Bug #85, Bug #139)
                // Clone member info to avoid borrow conflict with check_types_with_context
                let struct_members: Option<Vec<(String, ValueType)>> = context.scope_stack
                    .lookup_struct(&f_name)
                    .map(|s| s.members.iter().map(|m| (m.name.clone(), m.value_type.clone())).collect());

                for struct_arg_idx in 1..e.params.len() {
                    if let Some(struct_arg) = e.params.get(struct_arg_idx) {
                        if let NodeType::NamedArg(field_name) = &struct_arg.node_type {
                            if let Some(ref members) = struct_members {
                                let field_info = members.iter().find(|(n, _)| n == field_name);
                                if field_info.is_none() {
                                    errors.push(struct_arg.error(&context.path, "type",
                                        &format!("Field '{}' does not exist in struct '{}'", field_name, f_name)));
                                } else if let Some((_, expected_type)) = field_info {
                                    // Bug #139: Check that the argument type matches the field type
                                    if let Some(value_expr) = struct_arg.params.get(0) {
                                        if let Ok(actual_type) = get_value_type(&context, value_expr) {
                                            // Bug #124: Allow I64 literals to be passed as U8 fields
                                            let is_u8_i64_coercion = matches!(expected_type, ValueType::TCustom(tn) if tn == "U8")
                                                && matches!(&actual_type, ValueType::TCustom(ft) if ft == "I64")
                                                && matches!(&value_expr.node_type, NodeType::LLiteral(Literal::Number(_)));
                                            if &actual_type != expected_type && !is_u8_i64_coercion {
                                                errors.push(struct_arg.error(&context.path, "type",
                                                    &format!("Field '{}' expects type '{}' but got '{}'",
                                                        field_name, value_type_to_str(expected_type), value_type_to_str(&actual_type))));
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        // Also type-check the argument value
                        errors.extend(check_types_with_context(context, struct_arg, ExprContext::ValueUsed)?);
                    }
                }
                // Issue #132: Struct/enum constructors don't throw, so ? is not allowed
                if does_throw {
                    errors.push(e.error(&context.path, "type",
                        &format!("'{}' is a constructor and does not throw, remove the '?' from the call", f_name)));
                }
                return Ok(errors);
            }
        },
        Err(err) => {
            errors.push(err);
            return Ok(errors)
        },
    };

    // Update f_name after UFCS transformation (Bug #TODO)
    // The transformation may have changed e.g. "val.eq" -> "U8.eq"
    let f_name = get_func_name_in_call(&e);

    // Issue #132: Check mandatory ? for throwing functions
    let func_throws = !func_def.sig.throw_types.is_empty();
    if func_throws && !does_throw {
        let throw_types_str = func_def.sig.throw_types.iter()
            .map(|t| value_type_to_str(t))
            .collect::<Vec<_>>()
            .join(", ");
        errors.push(e.error(&context.path, "type",
            &format!("Function '{}' throws {} but call is missing '?'. Add '?' after the closing parenthesis: {}(...)?",
                f_name, throw_types_str, f_name)));
    }
    if !func_throws && does_throw {
        errors.push(e.error(&context.path, "type",
            &format!("Function '{}' does not throw, remove the '?' from the call", f_name)));
    }

    if let Some(err) = validate_func_arg_count(&context.path, &e, &f_name, &func_def) {
        errors.push(err);
        return Ok(errors);
    }

    let max_arg_def = func_def.sig.args.len();
    let mut def_arg_idx: usize = 0;  // Bug #61: Track definition arg separately from provided arg
    for fcall_arg_idx in 0..e.params.len() - 1 {
        let arg_expr = match e.params.get(fcall_arg_idx + 1) {
            Some(expr) => expr,
            None => {
                return Ok(errors);
            }
        };

        // Issue #179: Reject cast() as function argument
        if is_cast_call(arg_expr) {
            errors.push(arg_expr.error(&context.path, "type",
                "cast(Type, expr) cannot be used as a function argument. Extract to a variable: 'x := cast(...)' then pass 'x'."));
            continue;
        }

        // Function call arguments are being used (passed to the function)
        // This must happen BEFORE get_value_type so undefined symbol errors are detected
        errors.extend(check_types_with_context(context, &arg_expr, ExprContext::ValueUsed)?);

        // Bug #61: Get provided type early to check if we should skip optional args
        let found_type = match get_value_type(&context, arg_expr) {
            Ok(val_type) => val_type,
            Err(error_string) => {
                errors.push(error_string);
                return Ok(errors);
            },
        };

        // Bug #61: Skip optional args before variadic when type doesn't match
        while def_arg_idx < max_arg_def {
            let current_def = &func_def.sig.args[def_arg_idx];
            let expected = match &current_def.value_type {
                ValueType::TMulti(inner) => str_to_value_type(&inner.clone()),
                _ => current_def.value_type.clone(),
            };

            // Check if types are compatible
            // Bug #124: Allow I64 literals to be passed as U8 arguments
            let is_u8_i64_coercion_skip = matches!(&expected, ValueType::TCustom(tn) if tn == "U8")
                && matches!(&found_type, ValueType::TCustom(ft) if ft == "I64")
                && matches!(&arg_expr.node_type, NodeType::LLiteral(Literal::Number(_)));
            let types_ok = match &expected {
                ValueType::TCustom(tn) if tn == "Dynamic" || tn == "Type" => true,
                _ => &expected == &found_type || is_u8_i64_coercion_skip,
            };

            if types_ok {
                break;  // Use this def arg
            }

            // Types don't match - check if we can skip this optional arg
            let has_default = current_def.default_value.is_some();
            let variadic_follows = def_arg_idx + 1 < max_arg_def &&
                matches!(&func_def.sig.args[def_arg_idx + 1].value_type, ValueType::TMulti(_));

            if has_default && variadic_follows {
                def_arg_idx += 1;
                continue;
            }

            break;  // Can't skip, will report type error
        }

        let arg = match func_def.sig.args.get(std::cmp::min(def_arg_idx, max_arg_def - 1)) {
            Some(arg) => arg,
            None => {
                errors.push(e.lang_error(&context.path, "type", &format!("argument index {} out of bounds for function '{}'", def_arg_idx, f_name)));
                return Ok(errors);
            }
        };
        let arg_expected_type = &match &arg.value_type {
            ValueType::TMulti(inner_type_name) => str_to_value_type(&inner_type_name.clone()),
            _ => arg.value_type.clone(),
        };
        // Note: check_types_with_context called earlier in loop (before found_type calculation)

        // Check mut parameter requirements (Bug #48, Bug #63)
        // Only mut parameters require mutable variables.
        // own parameters accept const variables (ownership transfer, not mutation).
        if arg.is_mut {
            let param_kind = "mut";
            match &arg_expr.node_type {
                NodeType::Identifier(var_name) => {
                    // Simple variable - check if it's mut
                    if let Some(symbol_info) = context.scope_stack.lookup_symbol(var_name) {
                        if !symbol_info.is_mut {
                            errors.push(arg_expr.error(&context.path, "type", &format!(
                                "Cannot pass const variable '{}' to {} parameter '{}' of function '{}'.\n\
                                 Suggestion: declare '{}' as 'mut {}'.",
                                var_name, param_kind, arg.name, f_name, var_name, var_name
                            )));
                        }
                    }
                },
                NodeType::LLiteral(_) => {
                    errors.push(arg_expr.error(&context.path, "type", &format!(
                        "Cannot pass literal to {} parameter '{}'. Use a variable instead.",
                        param_kind, arg.name
                    )));
                },
                _ => {
                    // FCall: Allow - function results can be passed to mut/own parameters
                    // Other node types: Shouldn't happen, but allow to avoid false positives
                }
            }
        }

        // Check copy parameter requirements - structs must have clone() implementation
        // Only check for explicit 'copy' parameters, not regular immutable parameters
        if arg.is_copy {
            // Get the actual type being passed
            let arg_type_opt = match get_value_type(&context, arg_expr) {
                Ok(val_type) => Some(val_type),
                Err(_) => {
                    // Type error already reported, skip clone check
                    None
                }
            };

            if let Some(arg_type) = arg_type_opt {
                // Only check for custom types (user-defined structs)
                if let ValueType::TCustom(type_name) = &arg_type {
                    // Skip primitive types that are trivially copyable (don't require clone())
                    // These types are copy-by-value and don't need deep cloning
                    // NOTE: Bool removed from this list - it's a regular struct, not a special primitive
                    let primitives = vec!["I64", "U8", "Str"];
                    if !primitives.contains(&type_name.as_str()) {
                        if let Some(copy_struct_def) = context.scope_stack.lookup_struct(type_name) {
                            // Check if clone() exists as a const (associated function)
                            let has_clone = copy_struct_def.get_member("clone")
                                .map(|decl| !decl.is_mut)
                                .unwrap_or(false);

                            if !has_clone {
                                errors.push(arg_expr.error(&context.path, "type", &format!(
                                    "Cannot pass struct '{}' to copy parameter '{}' of function '{}'.\n\
                                     Reason: struct '{}' does not implement clone() method.\n\
                                     Suggestion: add 'clone := func(self: {}) returns {} {{ ... }}' to struct '{}'.",
                                    type_name, arg.name, f_name, type_name, type_name, type_name, type_name
                                )));
                            }
                        }
                    }
                }
            }
        }

        // Note: found_type was already computed at start of loop for Bug #61 skip logic
        // Bug #124: Allow I64 literals to be passed as U8 arguments
        let arg_is_u8_i64_coercion = matches!(arg_expected_type, ValueType::TCustom(tn) if tn == "U8")
            && matches!(&found_type, ValueType::TCustom(ft) if ft == "I64")
            && matches!(&arg_expr.node_type, NodeType::LLiteral(Literal::Number(_)));
        match arg_expected_type {
            ValueType::TCustom(tn) if tn == "Dynamic" || tn == "Type" => {}, // Accept any type for Dynamic/Type-typed argument
            // Issue #91: Verify function signature compatibility for FuncSig-typed parameters
            ValueType::TCustom(tn) if context.scope_stack.lookup_symbol(tn)
                .map(|s| s.value_type == ValueType::TType(TTypeDef::TFuncSig))
                .unwrap_or(false) => {
                // Same type name -> trivially compatible
                if arg_expected_type != &found_type {
                    let arg_name = if let NodeType::Identifier(ref name) = arg_expr.node_type {
                        name.as_str()
                    } else if matches!(arg_expr.node_type, NodeType::FuncDef(_)) {
                        "<anonymous>"
                    } else { "?" };
                    // Look up the expected FuncSig definition
                    let expected_fd = context.scope_stack.lookup_func(tn);
                    // Try to find the function def for the argument
                    let found_fd_owned: Option<FuncDef>;
                    let found_fd: Option<&FuncDef> = if let NodeType::Identifier(ref _name) = arg_expr.node_type {
                        let combined_arg_name = crate::rs::parser::get_combined_name(&context.path, arg_expr)?;
                        found_fd_owned = context.scope_stack.lookup_func(&combined_arg_name).cloned();
                        found_fd_owned.as_ref()
                    } else if let NodeType::FuncDef(ref anon_fd) = arg_expr.node_type {
                        // Issue #91: Anonymous inline function - use definition directly
                        if !anon_fd.body.is_empty() {
                            Some(anon_fd)
                        } else {
                            None
                        }
                    } else {
                        None
                    };
                    let mut sig_ok = false;
                    if let (Some(expected_fd), Some(found_fd)) = (expected_fd, found_fd) {
                        let args_match = expected_fd.sig.args.len() == found_fd.sig.args.len()
                            && expected_fd.sig.args.iter().zip(found_fd.sig.args.iter())
                                .all(|(a, b)| a.value_type == b.value_type);
                        let func_kind_match = expected_fd.is_proc() == found_fd.is_proc();
                        sig_ok = args_match
                            && expected_fd.sig.return_types == found_fd.sig.return_types
                            && expected_fd.sig.throw_types == found_fd.sig.throw_types
                            && func_kind_match;
                        if !sig_ok && !func_kind_match {
                            let expected_kind = if expected_fd.is_proc() { "proc" } else { "func" };
                            let found_kind = if found_fd.is_proc() { "proc" } else { "func" };
                            errors.push(e.error(&context.path, "type", &format!(
                                "Cannot pass '{}' ({}) where '{}' ({}) is expected for parameter '{}' of '{}'.",
                                arg_name, found_kind, tn, expected_kind, arg.name, f_name
                            )));
                        }
                    }
                    if !sig_ok {
                        errors.push(e.error(&context.path, "type", &format!(
                            "Cannot pass '{}' of type '{}' to function-pointer parameter '{}' of '{}': expected function type '{}'.",
                            arg_name, value_type_to_str(&found_type), arg.name, f_name, tn
                        )));
                    }
                }
            },
            ValueType::TCustom(tn) if tn == INFER_TYPE => {
                errors.push(e.error(&context.path, "type", &format!(
                    "calling func/proc '{}' declared arg {} without type, but type inference in args is not supported.\n\
                     Suggestion: the arg should be '{} : {},' instead of just '{}'.\n\
                     Alternative option: the arg could be '{} : Dynamic,' for dynamic arguments.
                     ",
                    f_name, arg.name, arg.name, value_type_to_str(&found_type), arg.name, arg.name,
                )));
            },
            _ if arg_expected_type != &found_type && !arg_is_u8_i64_coercion => {
                errors.push(e.error(&context.path, "type", &format!(
                    "calling function '{}' expects '{}' for arg '{}', but '{}' was provided.",
                    f_name, value_type_to_str(arg_expected_type), arg.name, value_type_to_str(&found_type)
                )));
            },
            _ => {} // types match or U8/I64 coercion; no error
        }

        // Bug #49: Handle ownership transfer for 'own' parameters
        // Remove the symbol from scope so subsequent uses get "undefined symbol" error
        if arg.is_own {
            if let NodeType::Identifier(var_name) = &arg_expr.node_type {
                // Only invalidate simple identifiers, not field access or function calls
                if arg_expr.params.is_empty() {
                    context.scope_stack.remove_symbol(var_name);
                }
            }
        }

        // Bug #61: Advance def_arg_idx for non-variadic args
        if !matches!(&arg.value_type, ValueType::TMulti(_)) {
            def_arg_idx += 1;
        }
    }

    return Ok(errors)
}

// Check if a function call's return value is being used correctly (Bug #8 fix)
fn check_fcall_return_usage(context: &Context, e: &Expr, expr_context: ExprContext) -> Result<Vec<String>, String> {
    let mut errors: Vec<String> = Vec::new();

    // Get the function definition to check if it returns a value
    let func_def = match get_func_def_for_fcall(&context, e) {
        Ok(Some(func_def_)) => func_def_,
        Ok(None) => return Ok(errors), // Struct/enum constructor, no return value check needed
        Err(_) => return Ok(errors), // Error already reported by check_fcall
    };

    // Check if this function returns a value
    let returns_value = func_def.sig.return_types.len() > 0;

    if returns_value && expr_context == ExprContext::ValueDiscarded {
        let f_name = get_func_name_in_call(e);

        errors.push(e.error(&context.path, "type", &format!(
            "Function '{}' returns a value that is not being used.\n\
             Hint: Capture the return value with '_ := {}(...)' or use it in an expression.",
            f_name, f_name
        )));
    }

    return Ok(errors);
}

fn check_func_proc_types(func_def: &FuncDef, context: &mut Context, e: &Expr) -> Result<Vec<String>, String> {
    let mut errors : Vec<String> = Vec::new();
    // Bug #101: Save outer function's tracking state for nested function support
    let saved_function_locals = context.scope_stack.function_locals.clone();
    let mut saved_used_symbols = context.scope_stack.used_symbols.clone();
    // Bug #97: Clear function_locals at start of each function
    context.scope_stack.function_locals.clear();
    // Bug #101: Clear used_symbols at start of each function
    context.scope_stack.used_symbols.clear();
    if !context.mode_def.allows_procs && func_def.is_proc() {
        errors.push(e.error(&context.path, "type", "Procs not allowed in pure modes"));
    }
    let mut has_variadic = false;
    for (i, arg) in func_def.sig.args.iter().enumerate() {
        if has_variadic {
            errors.push(e.error(&context.path, "type", &format!("Variadic argument '{}' must be the last (only one variadic argument allowed).", &arg.name)));
        }

        match &arg.value_type {
            ValueType::TMulti(_multi_type) => {
                if arg.is_mut {
                    errors.push(e.error(&context.path, "type", &format!("Variadic argument '{}' cannot be 'mut'.", &arg.name)));
                }
                if i != func_def.sig.args.len() - 1 {
                    errors.push(e.error(&context.path, "type", &format!("Variadic argument '{}' must be the last.", &arg.name)));
                }
                has_variadic = true;

                // All array types now use the generic Array
                let array_type_name = "Array".to_string();

                context.scope_stack.declare_symbol(arg.name.clone(), SymbolInfo {
                    value_type: ValueType::TCustom(array_type_name),
                    is_mut: false,
                    is_copy: false,
                    is_own: false,
                    is_comptime_const: false,
                });
            },
            ValueType::TCustom(ref custom_type_name) => {
                let custom_symbol = match context.scope_stack.lookup_symbol(custom_type_name) {
                    Some(custom_symbol_) => custom_symbol_.clone(),
                    None => {
                        errors.push(e.error(&context.path, "type", &format!("Argument '{}' is of undefined type '{}'.", &arg.name, &custom_type_name)));
                        return Ok(errors)
                    },
                };

                // Validate that the custom type is actually a type definition, not a value
                match &custom_symbol.value_type {
                    ValueType::TType(TTypeDef::TStructDef) => {
                        // Valid: struct type
                        context.scope_stack.declare_symbol(arg.name.clone(), SymbolInfo{value_type: arg.value_type.clone(), is_mut: arg.is_mut, is_copy: arg.is_copy, is_own: arg.is_own, is_comptime_const: false });
                        // Register struct fields for type checking
                        context.register_struct_fields_for_typecheck(&arg.name, custom_type_name);
                    },
                    ValueType::TType(TTypeDef::TEnumDef) => {
                        // Valid: enum type
                        context.scope_stack.declare_symbol(arg.name.clone(), SymbolInfo{value_type: arg.value_type.clone(), is_mut: arg.is_mut, is_copy: arg.is_copy, is_own: arg.is_own, is_comptime_const: false });
                    },
                    ValueType::TType(TTypeDef::TFuncSig) => {
                        // Issue #91: Valid: function signature type as parameter
                        context.scope_stack.declare_symbol(arg.name.clone(), SymbolInfo{value_type: arg.value_type.clone(), is_mut: arg.is_mut, is_copy: arg.is_copy, is_own: arg.is_own, is_comptime_const: false });
                    },
                    _ => {
                        // Invalid: not a type, it's a value or something else
                        errors.push(e.error(&context.path, "type", &format!("Argument '{}' has type '{}' which is not a valid type (expected struct, enum, or function signature)", &arg.name, &custom_type_name)));
                    },
                }
            },
            _ => {
                context.scope_stack.declare_symbol(arg.name.clone(), SymbolInfo{value_type: arg.value_type.clone(), is_mut: arg.is_mut, is_copy: arg.is_copy, is_own: arg.is_own, is_comptime_const: false });
            },
        }
        // Bug #101: Register argument in function_locals for unused tracking
        context.scope_stack.register_function_local(&arg.name, e.line, e.col);
    }

    // TODO re-enable test when it is decided what to do with free, memcpy and memset
    // if func_def.sig.function_type == FunctionType::FTFunc || func_def.sig.function_type == FunctionType::FTFuncExt {
    //     if func_def.sig.return_types.len() == 0 && func_def.sig.throw_types.len() == 0 {
    //         errors.push(e.error(&context.path, "type", "funcs must return or throw something, use a proc instead"));
    //     }
    // }

    // Don't check the bodies of external functions
    if func_def.is_ext() {
        // Bug #101: Restore outer function's tracking state before returning
        context.scope_stack.function_locals = saved_function_locals;
        context.scope_stack.used_symbols = saved_used_symbols;
        return Ok(errors);
    }

    // Issue #91: Skip type-checking function signature definitions
    // These have empty body and type-only args (no names)
    if func_def.body.is_empty() && func_def.sig.args.iter().all(|a| a.name.is_empty()) {
        context.scope_stack.function_locals = saved_function_locals;
        context.scope_stack.used_symbols = saved_used_symbols;
        return Ok(errors);
    }

    // Skip body type-checking for macros with Type parameters.
    // These bodies contain placeholder types (T) that only resolve at expansion time.
    // The expanded result is type-checked separately.
    if func_def.is_macro() && func_def.sig.args.iter().any(|a|
        matches!(&a.value_type, ValueType::TCustom(t) if t == "Type" || t == "Dynamic"))
    {
        context.scope_stack.function_locals = saved_function_locals;
        context.scope_stack.used_symbols = saved_used_symbols;
        return Ok(errors);
    }

    // TODO should macros be allowed to call procs?
    if !func_def.is_proc() {
        for se in &func_def.body {
            if is_expr_calling_procs(&context, &se)? {
                errors.push(se.error(&context.path, "type", "funcs cannot call procs."));
            }
        }
    }
    // Function body statements discard return values at the top level
    // Bug #162: Track own-consumed symbols so we can restore them before check_body_returns_throws.
    // The type-check pass removes symbols consumed by own params, but check_body_returns_throws
    // re-walks the AST doing UFCS resolution (get_func_def_for_fcall) which needs those symbols.
    // Local variables are re-declared by check_body_returns_throws's Declaration handler,
    // but function parameters are not, so UFCS on consumed parameters fails without this restore.
    context.scope_stack.begin_removal_tracking();
    let body_mark = context.scope_stack.removal_mark();
    for p in &func_def.body {
        errors.extend(check_types_with_context(context, &p, ExprContext::ValueDiscarded)?);
    }
    let body_removed = context.scope_stack.drain_removals_since(body_mark);
    context.scope_stack.restore_removed(&body_removed);
    context.scope_stack.end_removal_tracking();

    let mut return_found = false;
    let mut thrown_types: Vec<ThrownType> = Vec::new();
    errors.extend(check_body_returns_throws(context, e, func_def, &func_def.body, &mut thrown_types, &mut return_found)?);

    if !return_found && func_def.sig.return_types.len() > 0 {
        errors.push(e.error(&context.path, "type", "No return statments found in function that returns "));
    }

    // Filter and report only the thrown types that are not declared
    for te in &thrown_types {
        let mut is_declared = false;
        for declared in &func_def.sig.throw_types {
            if value_type_to_str(declared) == te.type_str {
                is_declared = true;
                break;
            }
        }
        if !is_declared {
            errors.push(te.msg.clone());
        }
    }

    for declared_throw in &func_def.sig.throw_types {
        let declared_str = value_type_to_str(declared_throw);
        let mut is_thrown = false;
        for te in &thrown_types {
            if te.type_str == declared_str {
                is_thrown = true;
                break;
            }
        }
        if !is_thrown {
            errors.push(e.error(&context.path, "type", &format!("`{}` is declared in the throws section, but this function never throws it.\nSuggestion: Remove it from the throws section.",
                                                    declared_str)));
        }
    }

    // Bug #101: Check for unused variables/arguments
    for unused_name in context.scope_stack.get_unused_symbols() {
        errors.push(e.error(&context.path, "type", &format!(
            "Unused variable '{}'. Suggestion: Use it or rename to '_{}'.",
            unused_name, unused_name)));
    }

    // Bug #101: Restore outer function's tracking state
    // Merge inner function's used_symbols into saved state (for nested function closures)
    for used_name in &context.scope_stack.used_symbols {
        saved_used_symbols.insert(used_name.clone());
    }
    context.scope_stack.function_locals = saved_function_locals;
    context.scope_stack.used_symbols = saved_used_symbols;

    return Ok(errors)
}

pub fn check_body_returns_throws(context: &mut Context, e: &Expr, func_def: &FuncDef, body: &[Expr], thrown_types: &mut Vec<ThrownType>, return_found: &mut bool) -> Result<Vec<String>, String> {

    let mut errors = vec![];
    let returns_len = func_def.sig.return_types.len();
    let mut unconditional_exit_in_sequence = false;

    for p in body.iter() {
        // Check if we're processing code after an unconditional return or throw
        // Bug #96 fix: Catch blocks are reachable via the throw path, not sequential flow.
        // A return/throw on the success path doesn't make catch unreachable.
        let is_catch = matches!(&p.node_type, NodeType::Catch);
        if unconditional_exit_in_sequence && !is_catch {
            errors.push(p.error(&context.path, "type",
                "Unreachable code after unconditional return or throw."));
        } else {
            match &p.node_type {
            NodeType::Body => {
                let mut temp_thrown_types: Vec<ThrownType> = Vec::new();
                errors.extend(check_body_returns_throws(context, e, func_def, &p.params, &mut temp_thrown_types, return_found)?);
                thrown_types.extend(temp_thrown_types);
            },
            NodeType::Return => {
                *return_found = true;
                unconditional_exit_in_sequence = true;
                if returns_len != p.params.len() {
                    errors.push(p.error(&context.path, "type", &format!("Returning {} values when {} were expected.", p.params.len(), returns_len)));
                    errors.push(e.error(&context.path, "type", "Suggestion: Update returns section here"));
                } else {
                    for i in 0..p.params.len() {
                        let expected_value_type_opt = match func_def.sig.return_types.get(i) {
                            Some(t) => Some(t),
                            None => {
                                errors.push(e.lang_error(&context.path, "type", &format!("Fewer return values than provided at position {}", i)));
                                None
                            }
                        };
                        let return_val_e_opt = match p.params.get(i) {
                            Some(val) => Some(val),
                            None => {
                                errors.push(e.lang_error(&context.path, "type", &format!("Missing return value at position {}", i)));
                                None
                            }
                        };

                        if let (Some(expected_value_type), Some(return_val_e)) = (expected_value_type_opt, return_val_e_opt) {
                            // Recursively check this return expression for throws
                            errors.extend(
                                check_body_returns_throws(context, return_val_e, func_def, std::slice::from_ref(return_val_e), thrown_types, return_found)?);

                            match get_value_type(&context, return_val_e) {
                                Ok(actual_value_type) => {
                                    if expected_value_type != &actual_value_type {
                                        // Issue #91: Allow returning functions where FuncSig return type is expected
                                        let mut funcsig_return_ok = false;
                                        if let ValueType::TCustom(ref tn) = expected_value_type {
                                            if context.scope_stack.lookup_symbol(tn)
                                                .map(|s| s.value_type == ValueType::TType(TTypeDef::TFuncSig))
                                                .unwrap_or(false)
                                            {
                                                // Expected is a FuncSig type - look up the returned function's def
                                                if let NodeType::Identifier(ref _name) = return_val_e.node_type {
                                                    let combined = crate::rs::parser::get_combined_name(&context.path, return_val_e)?;
                                                    if let (Some(expected_fd), Some(found_fd)) = (
                                                        context.scope_stack.lookup_func(tn),
                                                        context.scope_stack.lookup_func(&combined),
                                                    ) {
                                                        let args_match = expected_fd.sig.args.len() == found_fd.sig.args.len()
                                                            && expected_fd.sig.args.iter().zip(found_fd.sig.args.iter())
                                                                .all(|(a, b)| a.value_type == b.value_type);
                                                        let func_kind_match = expected_fd.is_proc() == found_fd.is_proc();
                                                        funcsig_return_ok = args_match
                                                            && expected_fd.sig.return_types == found_fd.sig.return_types
                                                            && expected_fd.sig.throw_types == found_fd.sig.throw_types
                                                            && func_kind_match;
                                                        if !funcsig_return_ok && !func_kind_match {
                                                            let expected_kind = if expected_fd.is_proc() { "proc" } else { "func" };
                                                            let found_kind = if found_fd.is_proc() { "proc" } else { "func" };
                                                            errors.push(return_val_e.error(&context.path,
                                                                "type", &format!("Cannot return '{}' ({}) where '{}' ({}) is expected",
                                                                    _name, found_kind, tn, expected_kind)));
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                        if !funcsig_return_ok {
                                            errors.push(return_val_e.error(&context.path,
                                                "type", &format!("Return value in pos {} expected to be '{}', but found '{}' instead",
                                                                 i, value_type_to_str(&expected_value_type), value_type_to_str(&actual_value_type))));
                                            errors.push(e.error(&context.path, "type", "Suggestion: Update returns section here"));
                                        }
                                    }
                                },
                                Err(error_string) => {
                                    errors.push(error_string);
                                },
                            };
                        }
                    }
                }
            },
            NodeType::Throw => {
                unconditional_exit_in_sequence = true;
                if p.params.len() != 1 {
                    errors.push(p.error(&context.path, "type", "Throw statement must have exactly one parameter."));
                } else {
                    let throw_param = p.params.get(0).unwrap();
                    // Recursively check this throw expression for throws (just in case, although users should avoid this)
                    // TODO fix this, not a priority
                    // errors.extend(
                    //     check_body_returns_throws(context, throw_param, func_def, std::slice::from_ref(throw_param), thrown_types, return_found));

                    match get_value_type(&context, throw_param) {
                        Ok(thrown_type) => {
                            if thrown_type == ValueType::TType(TTypeDef::TStructDef) {
                                errors.push(throw_param.error(&context.path, "type", "Cannot throw a struct definition.\nSuggestion: Create an instance by adding parentheses at the end."));
                            } else {
                                // Track the thrown type as a string and another string with its error
                                let thrown_type_str = value_type_to_str(&thrown_type);
                                thrown_types.push(ThrownType { type_str: thrown_type_str.clone(), msg: throw_param.error(&context.path, "type", &format!("Function throws '{}', but it is not declared in this function's throws section.", thrown_type_str)) });
                                thrown_types.push(ThrownType { type_str: thrown_type_str.clone(), msg: e.error(&context.path, "type", "Suggestion: Either add it to the throws section here, or catch it with a catch block") });
                            }
                        },
                        Err(err) => {
                            errors.push(err);
                        }
                    }
                }
            },

            NodeType::Catch => {
                if p.params.len() != 3 {
                    errors.push(p.error(&context.path, "type", "Catch must have 3 parameters: variable, type, and body."));
                } else {
                    let var_name_expr = p.params.get(0).unwrap();
                    let err_type_expr = p.params.get(1).unwrap();
                    let catch_body_expr = p.params.get(2).unwrap();

                    let var_name = match &var_name_expr.node_type {
                        NodeType::Identifier(name) => name.clone(),
                        _ => {
                            errors.push(var_name_expr.error(&context.path, "type", "Catch variable must be a valid identifier"));
                            return Ok(errors);
                        }
                    };

                    let caught_type = match &err_type_expr.node_type {
                        NodeType::Identifier(name) => name.clone(),
                        _ => {
                            errors.push(err_type_expr.error(&context.path, "type", "Catch type must be a valid identifier"));
                            return Ok(errors);
                        }
                    };

                    // Remove first, before descending into body
                    let mut found_match = false;
                    for te in thrown_types.iter() {
                        if te.type_str == caught_type {
                            found_match = true;
                            break;
                        }
                    }
                    if found_match {
                        // Remove matching entries (reverse to avoid index shift issues)
                        for i in (0..thrown_types.len()).rev() {
                            if thrown_types[i].type_str == caught_type {
                                thrown_types.remove(i);
                            }
                        }
                    } else {
                        errors.push(p.error(&context.path, "type", &format!("Trying to catch '{}', but it is not among the thrown types.", caught_type)));
                    }

                    // Create scoped context for catch body with the error variable registered
                    context.scope_stack.push(ScopeType::Block);
                    context.scope_stack.declare_symbol(var_name.clone(), SymbolInfo {
                        value_type: ValueType::TCustom(caught_type.clone()),
                        is_mut: false,
                        is_copy: false,
                        is_own: false,
                        is_comptime_const: false,
                    });

                    // Register struct fields so err.msg etc. can be accessed during type-checking
                    let members = context.scope_stack.lookup_struct(&caught_type)
                        .map(|s| s.members.clone());
                    if let Some(members) = members {
                        for field_decl in &members {
                            let combined_name = format!("{}.{}", var_name, field_decl.name);
                            context.scope_stack.declare_symbol(
                                combined_name.clone(),
                                SymbolInfo {
                                    value_type: field_decl.value_type.clone(),
                                    is_mut: false,
                                    is_copy: false,
                                    is_own: false,
                                    is_comptime_const: false,
                                },
                            );
                        }
                    }

                    // Then check body for other thrown exceptions
                    let mut catch_thrown_types: Vec<ThrownType> = Vec::new();
                    errors.extend(check_body_returns_throws(context, e, func_def, &catch_body_expr.params, &mut catch_thrown_types, return_found)?);
                    thrown_types.extend(catch_thrown_types);
                    context.scope_stack.pop().ok();

                    // Bug #96: After a catch, code becomes reachable again.
                    // The catch provides an alternative path - if it doesn't exit,
                    // control continues to statements after the catch.
                    unconditional_exit_in_sequence = false;
                }
            },

            NodeType::FCall(_) => {
                // Issue #180: Check if this is a bang call (!) -- if so, skip throw tracking
                // since the desugarer will insert catch+panic blocks
                let is_bang_call = matches!(&p.node_type, NodeType::FCall(ref info) if info.is_bang);
                match get_func_def_for_fcall(&context, p) {
                    Ok(Some(called_func_def)) => {
                        if !is_bang_call {
                        for called_throw in &called_func_def.sig.throw_types {
                            let called_throw_str = value_type_to_str(called_throw);
                            let error_msg = format!(
                                "Function throws '{}', but it is not declared in this function's throws section.",
                                called_throw_str
                            );

                            thrown_types.push(ThrownType { type_str: called_throw_str.clone(), msg: p.error(&context.path, "type", &error_msg) });
                            thrown_types.push(ThrownType { type_str: called_throw_str.clone(), msg: e.error(&context.path, "type", "Suggestion: Either add it to the throws section here, or catch it with a catch block") });
                        }
                        }

                        for arg in p.params.iter().skip(1) {
                            // Handle direct function calls as arguments
                            if let NodeType::FCall(_) = arg.node_type {
                                match get_func_def_for_fcall(&context, arg) {
                                    Ok(Some(arg_nested_func_def)) => {
                                        // Add the nested function's own throw types (only if it has ?)
                                        if matches!(arg.node_type, NodeType::FCall(ref info) if info.does_throw) {
                                            for arg_nested_throw in &arg_nested_func_def.sig.throw_types {
                                                let arg_nested_throw_str = value_type_to_str(arg_nested_throw);
                                                let arg_nested_error_msg = format!(
                                                    "Function throws '{}', but it is not declared in this function's throws section.",
                                                    arg_nested_throw_str
                                                );
                                                thrown_types.push(ThrownType { type_str: arg_nested_throw_str.clone(), msg: arg.error(&context.path, "type", &arg_nested_error_msg) });
                                                thrown_types.push(ThrownType { type_str: arg_nested_throw_str.clone(), msg: e.error(&context.path, "type", "Suggestion: Either add it to the throws section here, or catch it with a catch block") });
                                            }
                                        }
                                        let mut arg_thrown_types: Vec<ThrownType> = Vec::new();
                                        errors.extend(check_body_returns_throws(context, arg, &arg_nested_func_def, &arg.params, &mut arg_thrown_types, return_found)?);
                                        thrown_types.extend(arg_thrown_types);
                                    },
                                    Ok(None) => {
                                        // Ok(None) is returned for enum constructors and struct instantiation
                                        // These are valid and don't throw errors, so we don't add an error here
                                    },
                                    Err(reason) => {
                                        errors.push(arg.error(&context.path, "type", &format!("Failed to resolve nested function call: {}", reason)));
                                    }
                                }
                            }
                            // Bug #36 fix: Handle named arguments in struct literals (e.g., Map(keys=self.keys.clone()))
                            // The throwing function call is inside the NamedArg's params
                            if let NodeType::NamedArg(_) = &arg.node_type {
                                if let Some(named_arg_value_expr) = arg.params.get(0) {
                                    if let NodeType::FCall(_) = &named_arg_value_expr.node_type {
                                        match get_func_def_for_fcall(&context, named_arg_value_expr) {
                                            Ok(Some(named_arg_nested_func_def)) => {
                                                let mut named_arg_thrown_types: Vec<ThrownType> = Vec::new();
                                                errors.extend(check_body_returns_throws(context, named_arg_value_expr, &named_arg_nested_func_def, &named_arg_value_expr.params, &mut named_arg_thrown_types, return_found)?);
                                                thrown_types.extend(named_arg_thrown_types);
                                            },
                                            Ok(None) => {
                                                // Ok(None) is returned for enum constructors and struct instantiation
                                            },
                                            Err(reason) => {
                                                errors.push(named_arg_value_expr.error(&context.path, "type", &format!("Failed to resolve nested function call in named arg: {}", reason)));
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    },
                    Ok(None) => {
                        // Ok(None) is returned for enum constructors and struct instantiation
                        // These are valid and don't throw errors themselves, but their arguments
                        // may contain throwing function calls (Bug #36 fix)
                        for ctor_arg in p.params.iter().skip(1) {
                            // Handle direct function calls as arguments
                            if let NodeType::FCall(_) = ctor_arg.node_type {
                                match get_func_def_for_fcall(&context, ctor_arg) {
                                    Ok(Some(ctor_nested_func_def)) => {
                                        // Track the function's declared throw types
                                        for ctor_called_throw in &ctor_nested_func_def.sig.throw_types {
                                            let ctor_called_throw_str = value_type_to_str(ctor_called_throw);
                                            let ctor_error_msg = format!(
                                                "Function throws '{}', but it is not declared in this function's throws section.",
                                                ctor_called_throw_str
                                            );
                                            thrown_types.push(ThrownType { type_str: ctor_called_throw_str.clone(), msg: ctor_arg.error(&context.path, "type", &ctor_error_msg) });
                                            thrown_types.push(ThrownType { type_str: ctor_called_throw_str.clone(), msg: e.error(&context.path, "type", "Suggestion: Either add it to the throws section here, or catch it with a catch block") });
                                        }
                                    },
                                    Ok(None) => {},
                                    Err(reason) => {
                                        errors.push(ctor_arg.error(&context.path, "type", &format!("Failed to resolve nested function call: {}", reason)));
                                    }
                                }
                            }
                            // Bug #36 fix: Handle named arguments in struct literals (e.g., Map(keys=self.keys.clone()))
                            if let NodeType::NamedArg(_) = &ctor_arg.node_type {
                                if let Some(ctor_named_value_expr) = ctor_arg.params.get(0) {
                                    if let NodeType::FCall(_) = &ctor_named_value_expr.node_type {
                                        match get_func_def_for_fcall(&context, ctor_named_value_expr) {
                                            Ok(Some(ctor_named_nested_func_def)) => {
                                                // Track the function's declared throw types
                                                for ctor_named_called_throw in &ctor_named_nested_func_def.sig.throw_types {
                                                    let ctor_named_called_throw_str = value_type_to_str(ctor_named_called_throw);
                                                    let ctor_named_error_msg = format!(
                                                        "Function throws '{}', but it is not declared in this function's throws section.",
                                                        ctor_named_called_throw_str
                                                    );
                                                    thrown_types.push(ThrownType { type_str: ctor_named_called_throw_str.clone(), msg: ctor_named_value_expr.error(&context.path, "type", &ctor_named_error_msg) });
                                                    thrown_types.push(ThrownType { type_str: ctor_named_called_throw_str.clone(), msg: e.error(&context.path, "type", "Suggestion: Either add it to the throws section here, or catch it with a catch block") });
                                                }
                                            },
                                            Ok(None) => {},
                                            Err(reason) => {
                                                errors.push(ctor_named_value_expr.error(&context.path, "type", &format!("Failed to resolve nested function call in named arg: {}", reason)));
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    },
                    Err(reason) => {
                        errors.push(p.error(&context.path, "type", &reason));
                    }
                }
            }

            NodeType::While => {
                let mut while_thrown_types: Vec<ThrownType> = Vec::new();
                if let Some(while_cond_expr) = p.params.get(0) {
                    errors.extend(check_body_returns_throws(context, e, func_def, std::slice::from_ref(while_cond_expr), &mut while_thrown_types, return_found)?);
                }
                if let Some(while_body_expr) = p.params.get(1) {
                    errors.extend(check_body_returns_throws(context, e, func_def, &while_body_expr.params, &mut while_thrown_types, return_found)?);
                }
                thrown_types.extend(while_thrown_types);
            }
            NodeType::ForIn(var_type_name) => {
                // ForIn: params[0]=var, params[1]=collection, params[2]=body
                let mut forin_thrown_types: Vec<ThrownType> = Vec::new();
                if let Some(collection_expr) = p.params.get(1) {
                    errors.extend(check_body_returns_throws(context, e, func_def, std::slice::from_ref(collection_expr), &mut forin_thrown_types, return_found)?);
                }
                if let Some(forin_body_expr) = p.params.get(2) {
                    // Push scope and declare loop variable before checking body
                    let forin_var_name = p.params.get(0)
                        .and_then(|v| if let NodeType::Identifier(name) = &v.node_type { Some(name.clone()) } else { None })
                        .unwrap_or_default();
                    context.scope_stack.push(ScopeType::Block);
                    context.scope_stack.declare_symbol(forin_var_name, SymbolInfo {
                        value_type: ValueType::TCustom(var_type_name.clone()),
                        is_mut: true,
                        is_copy: false,
                        is_own: false,
                        is_comptime_const: false,
                    });
                    errors.extend(check_body_returns_throws(context, e, func_def, &forin_body_expr.params, &mut forin_thrown_types, return_found)?);
                    context.scope_stack.pop().ok();
                }
                thrown_types.extend(forin_thrown_types);
            }
            NodeType::If => {
                let mut if_thrown_types: Vec<ThrownType> = Vec::new();
                if let Some(if_cond_expr) = p.params.get(0) {
                    errors.extend(check_body_returns_throws(context, e, func_def, std::slice::from_ref(if_cond_expr), &mut if_thrown_types, return_found)?);
                }
                if let Some(then_block) = p.params.get(1) {
                    errors.extend(check_body_returns_throws(context, e, func_def, &then_block.params, &mut if_thrown_types, return_found)?);
                }
                if let Some(else_block) = p.params.get(2) {
                    errors.extend(check_body_returns_throws(context, e, func_def, &else_block.params, &mut if_thrown_types, return_found)?);
                }
                thrown_types.extend(if_thrown_types);
            }
            NodeType::Switch => {
                let mut switch_thrown_types: Vec<ThrownType> = Vec::new();
                // Get switch expression type for pattern matching
                let switch_expr_type = p.params.get(0)
                    .and_then(|switch_expr| get_value_type(context, switch_expr).ok());

                // Analyze the switch expression itself (could throw)
                if let Some(switch_expr) = p.params.get(0) {
                    errors.extend(check_body_returns_throws(context, e, func_def, std::slice::from_ref(switch_expr), &mut switch_thrown_types, return_found)?);
                }

                let mut si = 1;
                while si + 1 < p.params.len() {
                    let switch_case_expr = p.params.get(si).unwrap();
                    let switch_body_expr = p.params.get(si + 1).unwrap();

                    // Check case expression
                    errors.extend(check_body_returns_throws(context, e, func_def, std::slice::from_ref(switch_case_expr), &mut switch_thrown_types, return_found)?);

                    // For pattern matching, add the binding variable to scope before checking body
                    // This mirrors check_switch_statement's scope handling (Bug #28 fix)
                    if let NodeType::Pattern(PatternInfo { variant_name, binding_var }) = &switch_case_expr.node_type {
                        if let Some(ValueType::TCustom(ref enum_name)) = switch_expr_type {
                            let variant = if let Some(dot_pos) = variant_name.rfind('.') {
                                &variant_name[dot_pos + 1..]
                            } else {
                                variant_name.as_str()
                            };

                            let payload_type = context.scope_stack.lookup_enum(enum_name)
                                .and_then(|switch_enum_def| switch_enum_def.get(variant).cloned())
                                .flatten();

                            if let Some(payload_type) = payload_type {
                                context.scope_stack.push(ScopeType::Block);
                                context.scope_stack.declare_symbol(
                                    binding_var.clone(),
                                    SymbolInfo {
                                        value_type: payload_type,
                                        is_mut: false,
                                        is_copy: false,
                                        is_own: false,
                                        is_comptime_const: false,
                                    }
                                );
                                errors.extend(check_body_returns_throws(context, e, func_def, &switch_body_expr.params, &mut switch_thrown_types, return_found)?);
                                context.scope_stack.pop().ok();
                            } else {
                                errors.extend(check_body_returns_throws(context, e, func_def, &switch_body_expr.params, &mut switch_thrown_types, return_found)?);
                            }
                        } else {
                            errors.extend(check_body_returns_throws(context, e, func_def, &switch_body_expr.params, &mut switch_thrown_types, return_found)?);
                        }
                    } else {
                        errors.extend(check_body_returns_throws(context, e, func_def, &switch_body_expr.params, &mut switch_thrown_types, return_found)?);
                    }

                    si += 2;
                }
                thrown_types.extend(switch_thrown_types);
            }

            NodeType::Declaration(decl) => {
                // Bug #28 fix: Declare variables so subsequent statements can reference them
                // This mirrors check_declaration's behavior but without full type inference
                if let Some(initializer) = p.params.get(0) {
                    // Try to infer the type from the initializer (only if not already declared)
                    if context.scope_stack.lookup_symbol(&decl.name).is_none() {
                        if let Ok(value_type) = get_value_type(&context, initializer) {
                            context.scope_stack.declare_symbol(
                                decl.name.clone(),
                                SymbolInfo {
                                    value_type,
                                    is_mut: decl.is_mut,
                                    is_copy: decl.is_copy,
                                    is_own: decl.is_own,
                                    is_comptime_const: false,
                                }
                            );
                        }
                    }

                    if let NodeType::FCall(_) = initializer.node_type {
                        // Issue #180: Check if this is a bang call (!)
                        let decl_is_bang = matches!(&initializer.node_type, NodeType::FCall(ref info) if info.is_bang);
                        let id_expr_opt = initializer.params.get(0);

                        let mut is_constructor = false;
                        if let Some(id_expr) = id_expr_opt {
                            if let NodeType::Identifier(name) = &id_expr.node_type {
                                // Only skip default constructor calls (simple StructName() with no dots)
                                // Don't skip method calls like Struct.method()
                                if id_expr.params.is_empty() {
                                    if let Some(symbol) = context.scope_stack.lookup_symbol(name) {
                                        if symbol.value_type == ValueType::TType(TTypeDef::TStructDef) {
                                            is_constructor = true; // Skip default constructor calls, for instantiations like 'StructName()'
                                        }
                                    }
                                }

                                // Check for enum constructors (e.g., Color.Green(true))
                                if id_expr.params.len() == 1 {
                                    if let Some(enum_symbol) = context.scope_stack.lookup_symbol(name) {
                                        if enum_symbol.value_type == ValueType::TType(TTypeDef::TEnumDef) {
                                            if let Some(enum_variant_expr) = id_expr.params.get(0) {
                                                if let NodeType::Identifier(_variant_name) = &enum_variant_expr.node_type {
                                                    is_constructor = true; // Skip enum constructor calls, for instantiations like 'Color.Green(true)'
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }

                        if !is_constructor {
                        match get_func_def_for_fcall(&context, initializer) {
                            Ok(Some(decl_called_func_def)) => {
                                // Issue #180: Skip throw tracking for bang calls
                                if !decl_is_bang {
                                for decl_called_throw in &decl_called_func_def.sig.throw_types {
                                    let decl_called_throw_str = value_type_to_str(decl_called_throw);
                                    let decl_error_msg = format!(
                                        "Function throws '{}', but it is not declared in this function's throws section.",
                                        decl_called_throw_str
                                    );

                                    thrown_types.push(ThrownType { type_str: decl_called_throw_str.clone(), msg: initializer.error(&context.path, "type", &decl_error_msg) });
                                    thrown_types.push(ThrownType { type_str: decl_called_throw_str.clone(), msg: e.error(&context.path, "type", "Suggestion: Either add it to the throws section here, or catch it with a catch block") });
                                }
                                }

                                let mut decl_thrown_types: Vec<ThrownType> = Vec::new();
                                errors.extend(check_body_returns_throws(context, initializer, &decl_called_func_def, &initializer.params, &mut decl_thrown_types, return_found)?);
                                thrown_types.extend(decl_thrown_types);
                            },
                            Ok(None) => {
                                // Struct constructor or enum constructor - no throw checking needed
                            },
                            Err(_) => {
                                // If we can't resolve the function, skip throw checking.
                                // The main type checking pass already validated the code.
                            }
                        }
                        }
                    }
                }
            }

            NodeType::Assignment(_) => {
                if let Some(assign_initializer) = p.params.get(0) {
                    if let NodeType::FCall(_) = assign_initializer.node_type {
                        // Issue #180: Check if this is a bang call (!)
                        let assign_is_bang = matches!(&assign_initializer.node_type, NodeType::FCall(ref info) if info.is_bang);

                        let assign_id_expr_opt = assign_initializer.params.get(0);

                        let mut assign_is_constructor = false;
                        if let Some(assign_id_expr) = assign_id_expr_opt {
                            if let NodeType::Identifier(name) = &assign_id_expr.node_type {
                                // Only skip default constructor calls (simple StructName() with no dots)
                                // Don't skip method calls like Struct.method()
                                if assign_id_expr.params.is_empty() {
                                    if let Some(assign_symbol) = context.scope_stack.lookup_symbol(name) {
                                        if assign_symbol.value_type == ValueType::TType(TTypeDef::TStructDef) {
                                            assign_is_constructor = true; // Skip default constructor calls, for instantiations like 'StructName()'
                                        }
                                    }
                                }

                                // Check for enum constructors (e.g., Color.Green(true))
                                if assign_id_expr.params.len() == 1 {
                                    if let Some(assign_symbol2) = context.scope_stack.lookup_symbol(name) {
                                        if assign_symbol2.value_type == ValueType::TType(TTypeDef::TEnumDef) {
                                            if let Some(assign_variant_expr) = assign_id_expr.params.get(0) {
                                                if let NodeType::Identifier(_variant_name) = &assign_variant_expr.node_type {
                                                    assign_is_constructor = true; // Skip enum constructor calls, for instantiations like 'Color.Green(true)'
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }

                        if !assign_is_constructor {
                        match get_func_def_for_fcall(&context, assign_initializer) {
                            Ok(Some(assign_called_func_def)) => {
                                // Issue #180: Skip throw tracking for bang calls
                                if !assign_is_bang {
                                for assign_called_throw in &assign_called_func_def.sig.throw_types {
                                    let assign_called_throw_str = value_type_to_str(assign_called_throw);
                                    let assign_error_msg = format!(
                                        "Function throws '{}', but it is not declared in this function's throws section.",
                                        assign_called_throw_str
                                    );

                                    thrown_types.push(ThrownType { type_str: assign_called_throw_str.clone(), msg: assign_initializer.error(&context.path, "type", &assign_error_msg) });
                                    thrown_types.push(ThrownType { type_str: assign_called_throw_str.clone(), msg: e.error(&context.path, "type", "Suggestion: Either add it to the throws section here, or catch it with a catch block") });
                                }
                                }

                                let mut assign_thrown_types: Vec<ThrownType> = Vec::new();
                                errors.extend(check_body_returns_throws(context, assign_initializer, &assign_called_func_def, &assign_initializer.params, &mut assign_thrown_types, return_found)?);
                                thrown_types.extend(assign_thrown_types);
                            },
                            Ok(None) => {
                                // Struct constructor or enum constructor - no throw checking needed
                            },
                            Err(_) => {
                                // If we can't resolve the function, skip throw checking.
                                // The main type checking pass already validated the code.
                            }
                        }
                        }
                    }
                }
            }


            _ => {},
            }
        }
    }

    return Ok(errors)
}

fn check_catch_statement(context: &mut Context, e: &Expr) -> Result<Vec<String>, String> {
    let mut errors = Vec::new();

    if e.params.len() != 3 {
        errors.push(e.error(&context.path, "type", "Catch node must have three parameters: variable, type, and body."));
        return Ok(errors)
    }

    let err_var_expr = e.params.get(0).unwrap();
    let err_type_expr = e.params.get(1).unwrap();
    let body_expr = e.params.get(2).unwrap();

    let var_name = match &err_var_expr.node_type {
        NodeType::Identifier(name) => name.clone(),
        _ => {
            errors.push(err_var_expr.error(&context.path, "type", "First catch param must be an identifier"));
            return Ok(errors)
        }
    };

    let type_name = match &err_type_expr.node_type {
        NodeType::Identifier(name) => name.clone(),
        _ => {
            errors.push(err_type_expr.error(&context.path, "type", "Second catch param must be a type identifier"));
            return Ok(errors)
        }
    };

    // Confirm that the type exists in the context (as done for function args)
    if context.scope_stack.lookup_symbol(&type_name).is_none() {
        errors.push(e.error(&context.path, "type", &format!("Catch refers to undefined type '{}'", &type_name)));
        return Ok(errors)
    }

    // Create scoped context for catch body
    context.scope_stack.push(ScopeType::Block);
    context.scope_stack.declare_symbol(var_name.clone(), SymbolInfo {
        value_type: ValueType::TCustom(type_name.clone()),
        is_mut: false,
        is_copy: false,
        is_own: false,
        is_comptime_const: false,
    });

    // Map struct fields so err.msg etc. can be accessed during type-checking
    let members = context.scope_stack.lookup_struct(&type_name)
        .map(|s| s.members.clone());
    if let Some(members) = members {
        for field_decl in &members {
            let combined_name = format!("{}.{}", var_name, field_decl.name);
            context.scope_stack.declare_symbol(
                combined_name.clone(),
                SymbolInfo {
                    value_type: field_decl.value_type.clone(),
                    is_mut: false,  // Error variables are not mutable in catch blocks
                    is_copy: false,
                    is_own: false,
                    is_comptime_const: false,
                },
            );
        }
    }

    // Catch body statements discard return values
    errors.extend(check_types_with_context(context, body_expr, ExprContext::ValueDiscarded)?);
    context.scope_stack.pop().ok();

    return Ok(errors)
}

fn check_declaration(context: &mut Context, e: &Expr, decl: &Declaration) -> Result<Vec<String>, String> {
    let mut errors : Vec<String> = Vec::new();
    if e.params.len() != 1 {
        errors.push(e.exit_error("type", &format!("in declaration of {}, declaration nodes must take exactly 1 parameter.",
                                                  decl.name)));
        return Ok(errors)
    }


    let inner_e = match e.params.get(0) {
        Some(inner_e_) => inner_e_,
        None => {
            errors.push(e.error(&context.path, "type", "declaration missing initializer"));
            return Ok(errors)
        },
    };

    // Bug #97: Disallow variable shadowing within a function
    // Only check when inside a function (not at global scope).
    // Track declarations by (name, line, col) to handle AST duplication from transformations
    // like for-in desugaring, while still catching actual shadowing.
    if decl.name != "_" && context.scope_stack.is_inside_function() {
        if context.scope_stack.is_already_processed(&decl.name, e.line, e.col) {
            // Same declaration visited again due to AST duplication - skip
        } else if context.scope_stack.is_shadowing_in_function(&decl.name, e.line, e.col) {
            // Same name at different location - actual shadowing
            errors.push(e.lang_error(&context.path, "type", &format!(
                "Variable '{}' already declared in this function (shadowing not allowed)", decl.name)));
            return Ok(errors);
        } else {
            // New declaration - register it
            context.scope_stack.register_function_local(&decl.name, e.line, e.col);
        }
    }

    // Bug #97: Always register the declaration (allow shadowing/overwriting)
    // Previous code only registered if lookup_symbol returned None, which prevented
    // re-declaring a variable with a different type.
    // Block scopes value_type.
    {
        let mut value_type = decl.value_type.clone();
        if value_type == ValueType::TCustom(INFER_TYPE.to_string()) {
            value_type = match get_value_type(&context, &inner_e) {
                Ok(val_type) => val_type,
                Err(error_string) => {
                    errors.push(error_string);
                    return Ok(errors);
                },
            };
        }
        // Issue #105 Step 4d: When declared type is a metatype annotation (StructDef/EnumDef/FuncSig),
        // use the inferred type from the RHS instead, so the symbol gets registered correctly.
        if let Ok(inferred) = get_value_type(&context, &inner_e) {
            if metatype_matches(&value_type, &inferred) {
                value_type = inferred;
            }
        }

        // Issue #91: Detect function signature definitions (empty body + type-only args)
        if let NodeType::FuncDef(func_def) = &inner_e.node_type {
            if func_def.body.is_empty() && func_def.sig.args.iter().all(|a| a.name.is_empty())
                && matches!(func_def.sig.function_type, FunctionType::FTFunc | FunctionType::FTProc) {
                value_type = ValueType::TType(TTypeDef::TFuncSig);
            }
        }

        // Issue #91: Resolve function signature type references
        // When decl.value_type is TCustom("BinaryIntOp") and that resolves to a FunctionSig,
        // look up the registered (resolved) func_def from init and use it for type checking
        let mut sig_resolved_fd: Option<FuncDef> = None;
        if let ValueType::TCustom(ref sig_name) = value_type {
            if let Some(sym) = context.scope_stack.lookup_symbol(sig_name) {
                if sym.value_type == ValueType::TType(TTypeDef::TFuncSig) {
                    if let Some(resolved_fd) = context.scope_stack.lookup_func(&decl.name) {
                        sig_resolved_fd = Some(resolved_fd.clone());
                    }
                }
            }
        }
        if let Some(resolved_fd) = sig_resolved_fd {
            let resolved_value_type = ValueType::TFunction(resolved_fd.sig.function_type.clone());
            context.scope_stack.declare_symbol(decl.name.to_string(), SymbolInfo{value_type: resolved_value_type, is_mut: decl.is_mut, is_copy: decl.is_copy, is_own: decl.is_own, is_comptime_const: false });
            // Type-check the function body using the resolved func_def (with proper arg types)
            context.scope_stack.push(ScopeType::Function);
            errors.extend(check_func_proc_types(&resolved_fd, context, &inner_e)?);
            context.scope_stack.pop().ok();
            return Ok(errors);
        }

        // TODO move to init_context() ? inner contexts are not persisted in init_context
        context.scope_stack.declare_symbol(decl.name.to_string(), SymbolInfo{value_type: value_type.clone(), is_mut: decl.is_mut, is_copy: decl.is_copy, is_own: decl.is_own, is_comptime_const: false });
        match value_type {
            ValueType::TCustom(custom_type) => {
                if custom_type == INFER_TYPE {
                    errors.push(e.lang_error(&context.path, "type", &format!("Cannot infer the declaration type of {}", decl.name)));
                    return Ok(errors);
                }
                // During type checking, register struct fields so they can be accessed in the code
                // Memory allocation and default value evaluation happens during runtime in eval_declaration
                if context.scope_stack.has_struct(&custom_type) {
                    context.register_struct_fields_for_typecheck(&decl.name, &custom_type);
                }
            }
            ValueType::TFunction(FunctionType::FTFunc) | ValueType::TFunction(FunctionType::FTProc) | ValueType::TFunction(FunctionType::FTMacro) => {
                match &inner_e.node_type {
                    NodeType::FuncDef(func_def) => {
                        // TODO move to init_context() ? inner contexts are not persisted in init_context
                        context.scope_stack.declare_func(decl.name.clone(), func_def.clone());
                    },
                    _ => {
                        errors.push(e.lang_error(&context.path, "type", "functions should have definitions"));
                        return Ok(errors);
                    },
                }
            },
            _ => {},
        }
    }
    // The RHS of a declaration is being used (assigned to the variable)
    errors.extend(check_types_with_context(context, &inner_e, ExprContext::ValueUsed)?);

    return Ok(errors)
}

fn check_assignment(context: &mut Context, e: &Expr, var_name: &str) -> Result<Vec<String>, String> {
    let mut errors : Vec<String> = Vec::new();
    if e.params.len() != 1 {
        errors.push(e.exit_error("type", &format!("in assignment to {}, assignments must take exactly one value, not {}.",
                                                  var_name, e.params.len())));
        return Ok(errors)
    }

    if context.scope_stack.has_func(var_name)  {
        errors.push(e.error(&context.path, "type", &format!("function '{}' cannot be assigned to.", var_name)));
    } else if context.scope_stack.has_symbol(var_name) {
        // Bug #101: Mark the variable as used (even though we're assigning to it)
        context.scope_stack.mark_symbol_used(var_name);
        let symbol_info = match context.scope_stack.lookup_symbol(var_name) {
            Some(info) => info,
            None => {
                errors.push(e.error(&context.path, "type", &format!("Undeclared variable '{}'", var_name)));
                return Ok(errors);
            }
        };
        if !symbol_info.is_mut && !symbol_info.is_copy && !symbol_info.is_own {
            errors.push(e.error(&context.path, "type", &format!("Cannot assign to constant '{}', Suggestion: declare it as 'mut'.", var_name)));
        }
        // Additional check: if this is a field access (e.g., "s.value"), also check base instance mutability
        // Issue #161: For namespace mutables, the full name is a registered mut symbol,
        // so skip the base mutability check (the base is a type name, not an instance)
        let sym_is_mut = symbol_info.is_mut;
        if var_name.contains('.') {
            let base_var = var_name.split('.').next().unwrap();
            // Bug #101: Mark base variable as used
            context.scope_stack.mark_symbol_used(base_var);
            if !sym_is_mut {
                if let Some(base_info) = context.scope_stack.lookup_symbol(base_var) {
                    if !base_info.is_mut && !base_info.is_copy && !base_info.is_own {
                        errors.push(e.error(&context.path, "type", &format!("Cannot assign to field of constant '{}', Suggestion: declare it as 'mut {}'.", base_var, base_var)));
                    }
                }
            }
        }
    } else if var_name.contains('.') {
        // Field access assignment where the field itself isn't registered in symbols
        // With dynamic offset calculation, we need to validate against struct definition
        let field_parts: Vec<&str> = var_name.split('.').collect();
        let field_base_var = field_parts[0];
        // Bug #101: Mark base variable as used
        context.scope_stack.mark_symbol_used(field_base_var);

        if let Some(field_base_info) = context.scope_stack.lookup_symbol(field_base_var) {
            // Check base mutability
            if !field_base_info.is_mut && !field_base_info.is_copy && !field_base_info.is_own {
                errors.push(e.error(&context.path, "type", &format!("Cannot assign to field of constant '{}', Suggestion: declare it as 'mut {}'.", field_base_var, field_base_var)));
            }

            // Validate field path exists in struct definition
            let mut current_type = field_base_info.value_type.clone();
            let mut has_error = false;
            for field_name in &field_parts[1..] {
                if !has_error {
                    match current_type {
                        ValueType::TCustom(ref type_name) => {
                            if let Some(field_struct_def) = context.scope_stack.lookup_struct(type_name) {
                                let mut field_decl_opt: Option<&Declaration> = None;
                                for decl in &field_struct_def.members {
                                    if decl.name == *field_name {
                                        field_decl_opt = Some(decl);
                                        break;
                                    }
                                }
                                if let Some(field_decl) = field_decl_opt {
                                    current_type = field_decl.value_type.clone();
                                } else {
                                    errors.push(e.error(&context.path, "type", &format!("Field '{}' not found in struct '{}'", field_name, type_name)));
                                    has_error = true;
                                }
                            } else {
                                errors.push(e.error(&context.path, "type", &format!("Struct '{}' not found", type_name)));
                                has_error = true;
                            }
                        },
                        _ => {
                            errors.push(e.error(&context.path, "type", &format!("Cannot access field '{}' on non-struct type", field_name)));
                            has_error = true;
                        }
                    }
                }
            }
        } else {
            errors.push(e.error(&context.path, "type", &format!("Undefined symbol '{}'", field_base_var)));
        }
    } else {
        errors.push(e.error(&context.path, "type", &format!("Suggestion: try changing '{} =' for '{} :='\nExplanation: Cannot assign to undefined symbol '{}'.",
                                             var_name, var_name, var_name)));
    }

    // The RHS of an assignment is being used (assigned to the variable)
    match e.params.get(0) {
        Some(inner_e) => {
            // Issue #179: Reject cast() in assignment position
            if is_cast_call(inner_e) {
                errors.push(inner_e.error(&context.path, "type",
                    "cast(Type, expr) can only be used in declarations (:=), not assignments (=). Use a new declaration instead."));
            } else {
                errors.extend(check_types_with_context(context, inner_e, ExprContext::ValueUsed)?);
            }
        },
        None => errors.push(e.error(&context.path, "type", "assignment missing value")),
    }
    return Ok(errors);
}

fn check_switch_statement(context: &mut Context, e: &Expr) -> Result<Vec<String>, String> {
    let mut errors: Vec<String> = Vec::new();

    let switch_expr_type = match e.params.get(0) {
        Some(expr) => {
            // Bug #101: Check the switch expression to mark variables as used
            errors.extend(check_types_with_context(context, expr, ExprContext::ValueUsed)?);
            match get_value_type(context, expr) {
                Ok(t) => t,
                Err(err) => {
                    errors.push(err);
                    return Ok(errors);
                }
            }
        },
        None => {
            return Ok(errors);
        }
    };

    let mut case_found = false;
    let mut default_found = false;

    // Issue #117: Begin removal tracking for switch cases
    context.scope_stack.begin_removal_tracking();

    let mut i = 1;
    while i < e.params.len() {
        let case_expr = e.params.get(i).unwrap();

        match &case_expr.node_type {
            NodeType::DefaultCase => {
                if default_found {
                    errors.push(case_expr.error(&context.path, "type", "Duplicate default case in switch"));
                }
                default_found = true;
                case_found = true;
            }
            NodeType::Pattern(_) => {
                // Pattern matching - type is checked in exhaustiveness check below
                case_found = true;
                // No need to check type here - patterns implicitly match the switch type
            }
            _ => {
                case_found = true;

                match get_value_type(context, case_expr) {
                    Ok(case_type) => {
                        let switch_type_str = value_type_to_str(&switch_expr_type);
                        let case_type_str = value_type_to_str(&case_type);
                        if case_type_str != switch_type_str && case_type_str != format!("{}Range", switch_type_str) {
                            errors.push(case_expr.error(&context.path, "type", &format!(
                                "Switch value type '{}', case value type '{}' do not match",
                                switch_type_str, case_type_str
                            )));
                        }
                    }
                    Err(err) => {
                        errors.push(err);
                    }
                }
            }
        }

        i += 1;

        if i >= e.params.len() {
            errors.push(e.error(&context.path, "type", "Switch case missing body expression"));
            return Ok(errors)
        }

        let body_expr = e.params.get(i).unwrap();

        // Issue #117: Mark before each case body so removals can be restored
        let case_mark = context.scope_stack.removal_mark();

        // For pattern matching, add the binding variable to the context before type checking the body
        if let NodeType::Pattern(PatternInfo { variant_name, binding_var }) = &case_expr.node_type {
            // Get the payload type for this variant
            if let ValueType::TCustom(enum_name) = &switch_expr_type {
                // Extract just the variant name (remove enum prefix if present)
                let variant = if let Some(dot_pos) = variant_name.rfind('.') {
                    &variant_name[dot_pos + 1..]
                } else {
                    variant_name.as_str()
                };

                // Clone the payload type before mutating context
                let payload_type = context.scope_stack.lookup_enum(enum_name)
                    .and_then(|e| e.get(variant).cloned())
                    .flatten();

                if let Some(payload_type) = payload_type {
                    // Create a scoped context with the binding variable
                    context.scope_stack.push(ScopeType::Block);
                    context.scope_stack.declare_symbol(
                        binding_var.clone(),
                        SymbolInfo {
                            value_type: payload_type,
                            is_mut: false,
                            is_copy: false,
                            is_own: false,
                            is_comptime_const: false,
                        }
                    );
                    // Switch case body statements discard return values
                    errors.extend(check_types_with_context(context, body_expr, ExprContext::ValueDiscarded)?);
                    context.scope_stack.pop().ok();
                } else if context.scope_stack.lookup_enum(enum_name)
                    .and_then(|e| e.get(variant))
                    .is_some() {
                    // Variant exists but has no payload
                    errors.push(case_expr.error(&context.path, "type", &format!("Variant '{}' has no payload, cannot use pattern matching", variant)));
                    errors.extend(check_types_with_context(context, body_expr, ExprContext::ValueDiscarded)?);
                } else if context.scope_stack.has_enum(enum_name) {
                    // Enum exists but variant doesn't
                    errors.push(case_expr.error(&context.path, "type", &format!("Unknown variant '{}'", variant)));
                    errors.extend(check_types_with_context(context, body_expr, ExprContext::ValueDiscarded)?);
                } else {
                    // Enum doesn't exist
                    errors.extend(check_types_with_context(context, body_expr, ExprContext::ValueDiscarded)?);
                }
            } else {
                errors.extend(check_types_with_context(context, body_expr, ExprContext::ValueDiscarded)?);
            }
        } else {
            errors.extend(check_types_with_context(context, body_expr, ExprContext::ValueDiscarded)?);
        }

        // Issue #117: Restore removals from this case body
        let case_removed = context.scope_stack.drain_removals_since(case_mark);
        context.scope_stack.restore_removed(&case_removed);

        i += 1;
    }

    context.scope_stack.end_removal_tracking();

    if !case_found {
        errors.push(e.error(&context.path, "type", "Switch must have at least one case"));
    }

    // Exhaustiveness check only for enums
    if let ValueType::TCustom(enum_name) = switch_expr_type {
        if let Some(exh_enum_def) = context.scope_stack.lookup_enum(&enum_name) {
            let mut matched_variants: Vec<String> = Vec::new();

            let mut j = 1;
            while j < e.params.len() {
                let exh_case_expr = e.params.get(j).unwrap();
                match &exh_case_expr.node_type {
                    NodeType::Pattern(PatternInfo { variant_name: exh_variant_name, .. }) => {
                        // Pattern matching: case EnumType.Variant(binding)
                        // Extract the variant name from the full "EnumType.Variant" string
                        if let Some(exh_dot_pos) = exh_variant_name.rfind('.') {
                            let enum_part = &exh_variant_name[..exh_dot_pos];
                            let variant_part = &exh_variant_name[exh_dot_pos + 1..];
                            if enum_part != enum_name {
                                errors.push(exh_case_expr.error(&context.path, "type", &format!("Mismatched enum type '{}', expected '{}'.", enum_part, enum_name)));
                            }
                            matched_variants.push(variant_part.to_string());
                        } else {
                            // Just the variant name without enum prefix
                            matched_variants.push(exh_variant_name.clone());
                        }
                    }
                    NodeType::Identifier(exh_name) => {
                        if exh_case_expr.params.is_empty() {
                            // case A
                            matched_variants.push(exh_name.clone());
                        } else {
                            // case ExampleEnum.A
                            let exh_variant_expr = exh_case_expr.params.get(0).unwrap();
                            if let NodeType::Identifier(variant) = &exh_variant_expr.node_type {
                                if exh_name != &enum_name {
                                    errors.push(exh_case_expr.error(&context.path, "type", &format!("Mismatched enum type '{}', expected '{}'.", exh_name, enum_name)));
                                }
                                matched_variants.push(variant.clone());
                            } else {
                                errors.push(exh_case_expr.error(&context.path, "type", "Invalid enum case syntax"));
                            }
                        }
                    }
                    NodeType::DefaultCase => {
                        default_found = true;
                    }
                    _ => {}
                }
                j += 2;
            }

            if !default_found {
                for exh_v in &exh_enum_def.variants {
                    if !matched_variants.contains(&exh_v.name) {
                        errors.push(e.error(&context.path, "type", &format!("Switch is missing case for variant '{}'", exh_v.name)));
                    }
                }
            }
        }
    }

    return Ok(errors)
}

fn check_struct_def(context: &mut Context, e: &Expr, struct_def: &StructDef) -> Vec<String> {
    let mut errors : Vec<String> = Vec::new();
    if e.params.len() != 0 {
        errors.push(e.exit_error("type", "in check_struct_def(): struct declarations must take exactly 0 params."));
        return errors
    }

    // Get struct name from first param (used for error messages)
    let struct_name = e.params.get(0)
        .and_then(|param| {
            if let NodeType::Identifier(name) = &param.node_type {
                Some(name.clone())
            } else {
                None
            }
        })
        .unwrap_or_else(|| "unknown".to_string());

    for member_decl in &struct_def.members {
        // Validate that the member's declared type exists (if it's a custom type)
        match &member_decl.value_type {
            ValueType::TCustom(ref custom_type_name) => {
                // Skip built-in types and special types
                if custom_type_name != "Dynamic" && custom_type_name != "Type" && custom_type_name != INFER_TYPE {
                    // Check if the type exists
                    if context.scope_stack.lookup_symbol(custom_type_name).is_none() {
                        errors.push(e.error(&context.path, "type", &format!(
                            "Struct member '{}' uses undefined type '{}'.\nHint: Make sure '{}' is defined before this struct.",
                            member_decl.name, custom_type_name, custom_type_name
                        )));
                    } else {
                        // Validate it's actually a type (enum or struct), not a value
                        let symbol_info = context.scope_stack.lookup_symbol(custom_type_name).unwrap();
                        match &symbol_info.value_type {
                            ValueType::TType(TTypeDef::TEnumDef) |
                            ValueType::TType(TTypeDef::TStructDef) |
                            ValueType::TCustom(_) => {
                                // Valid type (TCustom covers built-in types like I64, Str, etc.)
                            },
                            _ => {
                                errors.push(e.error(&context.path, "type", &format!(
                                    "Struct member '{}' type '{}' is not a valid type (expected enum, struct, or primitive, found {}).",
                                    member_decl.name, custom_type_name, value_type_to_str(&symbol_info.value_type)
                                )));
                            }
                        }
                    }
                }
            },
            _ => {} // Non-custom types (like functions) are handled elsewhere
        }

        match struct_def.default_values.get(&member_decl.name) {
            Some(inner_e) => {
                // println!("inner_e {:?}", inner_e);
                match &inner_e.node_type {
                    // Issue #108: Functions inside structs are no longer allowed.
                    // They must be moved to a namespace block.
                    NodeType::FuncDef(_func_def) => {
                        errors.push(inner_e.error(&context.path, "type", &format!(
                            "Function '{}' is defined inside struct. Functions must be in namespace blocks.\n\
                             Move this function outside the struct into: namespace {} {{ {} := func(...) {{ ... }} }}",
                            member_decl.name, struct_name, member_decl.name
                        )));
                    },
                    // For other types of members, check type and purity
                    _ => {
                        // Bug #148: Type-check the default value expression (catches ? on non-throwing calls)
                        match check_types_with_context(context, inner_e, ExprContext::ValueUsed) {
                            Ok(v) => errors.extend(v),
                            Err(e) => errors.push(e),
                        }

                        // Check if default value calls procs (violates purity of constructors)
                        if is_expr_calling_procs(context, inner_e).unwrap_or(false) {
                            errors.push(inner_e.exit_error("type",
                                &format!("Struct field '{}' has default value that calls proc. Default values must be pure (can only call funcs, not procs).", member_decl.name)));
                        }

                        // Check if default value type matches declared member type
                        let expected_type = &member_decl.value_type;
                        let found_type_opt = match get_value_type(&context, inner_e) {
                            Ok(val_type) => Some(val_type),
                            Err(error_string) => {
                                errors.push(error_string);
                                None
                            },
                        };

                        if let Some(found_type) = found_type_opt {
                            // Check if the value is a numeric literal (for implicit conversion)
                            let is_numeric_literal = match &inner_e.node_type {
                                NodeType::LLiteral(Literal::Number(_)) => true,
                                _ => false
                            };

                            match expected_type {
                                ValueType::TCustom(tn) if tn == "Dynamic" || tn == "Type" => {}, // Accept any type for Dynamic/Type
                                ValueType::TCustom(tn) if tn == INFER_TYPE => {}, // Type inference is OK
                                // Allow implicit conversion from I64 literals to U8
                                ValueType::TCustom(tn) if tn == "U8" && found_type == ValueType::TCustom("I64".to_string()) && is_numeric_literal => {},
                                _ if expected_type != &found_type => {
                                    errors.push(inner_e.error(&context.path, "type", &format!(
                                        "Struct field '{}' declared as '{}' but default value has type '{}'.",
                                        member_decl.name, value_type_to_str(expected_type), value_type_to_str(&found_type)
                                    )));
                                },
                                _ => {} // types match; no error
                            }
                        }
                    }
                }
            },
            None => {
                errors.push(e.todo_error(&context.path, "type", &format!("Member '{}' lacks a default value. Not allowed yet.", member_decl.name)));
            }
        }
    }

    // Check if collection-like structs have mandatory len() and size() methods
    // A struct is considered collection-like if it has push/get/set/insert methods
    // Note: delete() is excluded as it's a cleanup method, not a collection operation
    // Issue #108: Use merged struct from scope_stack (includes namespace methods)
    // struct_name already extracted at top of function

    // Get the merged struct from scope_stack (includes namespace members)
    let merged_struct = context.scope_stack.lookup_struct(&struct_name)
        .cloned()
        .unwrap_or_else(|| struct_def.clone());

    let has_push = merged_struct.get_member("push").is_some();
    let has_get = merged_struct.get_member("get").is_some();
    let has_set = merged_struct.get_member("set").is_some();
    let has_insert = merged_struct.get_member("insert").is_some();

    if has_push || has_get || has_set || has_insert {
        // This looks like a collection type - check for len() method
        let has_len = merged_struct.get_member("len")
            .map(|decl| !decl.is_mut)
            .unwrap_or(false);

        if !has_len {
            let methods: Vec<&str> = vec![
                if has_push { Some("push()") } else { None },
                if has_get { Some("get()") } else { None },
                if has_set { Some("set()") } else { None },
                if has_insert { Some("insert()") } else { None },
            ].into_iter().filter_map(|x| x).collect();

            errors.push(e.error(&context.path, "type", &format!(
                "Collection-like struct '{}' has {} method(s) but no len() method.\n\
                 Reason: Collection types must provide a way to query their size.\n\
                 Suggestion: add 'len := func(self: {}) returns I64 {{ ... }}' to struct '{}'.",
                struct_name, methods.join("/"), struct_name, struct_name
            )));
        }

        // Also check for size() method (returns size in bytes)
        let has_size = merged_struct.get_member("size")
            .map(|decl| !decl.is_mut)
            .unwrap_or(false);

        if !has_size {
            let size_methods_str: Vec<&str> = vec![
                if has_push { Some("push()") } else { None },
                if has_get { Some("get()") } else { None },
                if has_set { Some("set()") } else { None },
                if has_insert { Some("insert()") } else { None },
            ].into_iter().filter_map(|x| x).collect();

            errors.push(e.error(&context.path, "type", &format!(
                "Collection-like struct '{}' has {} method(s) but no size() method.\n\
                 Reason: Collection types must provide their size in bytes.\n\
                 Suggestion: add 'size := func(self: {}) returns I64 {{ ... }}' to struct '{}'.\n\
                 Note: size() should return the total size in bytes, not element count (use len() for that).",
                struct_name, size_methods_str.join("/"), struct_name, struct_name
            )));
        }
    }

    return errors
}

/// Issue #108: Type-check namespace function bodies (like check_struct_def but simpler)
fn check_namespace_def(context: &mut Context, _e: &Expr, ns_def: &NamespaceDef) -> Result<Vec<String>, String> {
    let mut errors: Vec<String> = Vec::new();

    for member_decl in &ns_def.members {
        if let Some(inner_e) = ns_def.default_values.get(&member_decl.name) {
            if let NodeType::FuncDef(func_def) = &inner_e.node_type {
                context.scope_stack.push(ScopeType::Function);
                errors.extend(check_func_proc_types(&func_def, context, &inner_e)?);
                context.scope_stack.pop().ok();
            }
        }
    }

    return Ok(errors)
}

pub fn get_func_def_for_fcall_with_expr(context: &Context, fcall_expr: &mut Expr) -> Result<Option<FuncDef>, String> {
    if !matches!(fcall_expr.node_type, NodeType::FCall(_)) {
        return Err(fcall_expr.lang_error(&context.path, "type", "Expected FCall node type"));
    }
    let func_expr = match fcall_expr.params.first() {
        Some(expr) => expr,
        None => return Err(fcall_expr.lang_error(&context.path, "type", "get_func_def_for_fcall_with_expr: Fcalls must have a name")),
    };

    match &func_expr.node_type {
        NodeType::Identifier(_) => {
            // Regular functions and associated functions used directly
            let combined_name = crate::rs::parser::get_combined_name(&context.path, func_expr)?;

            // Regular function call - check if it exists
            if let Some(func_def) = context.scope_stack.lookup_func(&combined_name) {
                return Ok(Some(func_def.clone()))
            }

            // Issue #91: Check if this is a call through a function-typed parameter
            if let Some(sym) = context.scope_stack.lookup_symbol(&combined_name) {
                if let ValueType::TCustom(ref type_name) = sym.value_type {
                    if let Some(type_sym) = context.scope_stack.lookup_symbol(type_name) {
                        if type_sym.value_type == ValueType::TType(TTypeDef::TFuncSig) {
                            if let Some(sig_fd) = context.scope_stack.lookup_func(type_name) {
                                return Ok(Some(sig_fd.clone()));
                            }
                        }
                    }
                }
            }

            if let Some(_struct_def) = context.scope_stack.lookup_struct(&combined_name) {
                return Ok(None) // REM: This is to allow struct instantiation
            }

            // Check for enum constructors (e.g., Color.Green(true))
            if context.scope_stack.is_enum_constructor(&combined_name) {
                return Ok(None) // Allow enum construction
            }

            // UFCS for chained calls: func(result, args) -> Type.func(result, args)
            // e.g., add(1, 2).mul(3) becomes mul(add(1,2), 3) which transforms to I64.mul(add(1,2), 3)
            // This only applies when no standalone function with this name exists (checked above).
            if fcall_expr.params.len() >= 2 {
                let first_arg = fcall_expr.params.get(1).unwrap();
                if let Ok(target_type) = get_value_type(context, first_arg) {
                    if let ValueType::TCustom(custom_type_name) = target_type {
                        let method_name = format!("{}.{}", custom_type_name, combined_name);
                        if let Some(func_def) = context.scope_stack.lookup_func(&method_name) {
                            // Transform: func(target, args...) -> Type.func(target, args...)
                            let new_e = Expr::new_clone(NodeType::Identifier(method_name.clone()), fcall_expr.params.get(0).unwrap(), Vec::new());
                            let mut new_args = Vec::new();
                            new_args.push(new_e);
                            new_args.extend(fcall_expr.params[1..].to_vec());
                            // Issue #132: Preserve does_throw flag from original FCall
                            let typer_fcall_info = if let NodeType::FCall(ref info) = fcall_expr.node_type { info.clone() } else { FCallInfo { does_throw: false, is_bang: false } };
                            *fcall_expr = Expr::new_clone(NodeType::FCall(typer_fcall_info), fcall_expr.params.get(0).unwrap(), new_args);
                            return Ok(Some(func_def.clone()));
                        }
                    }
                }
            }

            // UFCS with dot notation
            if let Some(func_name_expr) = func_expr.params.last() {
                if let NodeType::Identifier(ufcs_func_name) = &func_name_expr.node_type {
                    let mut parts: Vec<&str> = combined_name.split('.').collect();
                    parts.pop(); // Remove the last element (the function name)
                    let new_combined_name = parts.join(".");

                    // Create identifier expression preserving nested structure
                    // Copy func_expr but remove the last param (the method name)
                    let mut id_params = func_expr.params.clone();
                    id_params.pop(); // Remove the method name
                    let extra_arg_e = Expr::new_clone(func_expr.node_type.clone(), fcall_expr, id_params);

                    // Regular functions used with UFCS
                    if let Some(ufcs_func_def) = context.scope_stack.lookup_func(&ufcs_func_name.to_string()) {

                        let ufcs_new_e = Expr::new_clone(NodeType::Identifier(ufcs_func_name.clone()), fcall_expr.params.get(0).unwrap(), Vec::new());
                        let mut ufcs_new_args = Vec::new();
                        ufcs_new_args.push(ufcs_new_e);
                        ufcs_new_args.push(extra_arg_e);
                        ufcs_new_args.extend(fcall_expr.params[1..].to_vec());

                        // Issue #132: Preserve does_throw flag from original FCall
                        let typer_fcall_info = if let NodeType::FCall(ref info) = fcall_expr.node_type { info.clone() } else { FCallInfo { does_throw: false, is_bang: false } };
                        *fcall_expr = Expr::new_clone(NodeType::FCall(typer_fcall_info), fcall_expr.params.get(0).unwrap(), ufcs_new_args);
                        return Ok(Some(ufcs_func_def.clone()))
                    }

                    // Associated functions used with UFCS (aka methods)
                    // Bug #28 fix: Use get_value_type() to dynamically resolve field access chains
                    // instead of lookup_symbol() which only finds pre-registered symbol names.
                    // This enables UFCS on struct fields like s.items.len() in pattern match case bodies.
                    if let Ok(ufcs_value_type) = get_value_type(context, &extra_arg_e) {
                        match &ufcs_value_type {
                            ValueType::TCustom(ref custom_type_name) => {
                                let id_expr_name = format!("{}.{}", custom_type_name, ufcs_func_name);
                                if let Some(assoc_func_def) = context.scope_stack.lookup_func(&id_expr_name) {

                                    let assoc_new_e = Expr::new_clone(NodeType::Identifier(id_expr_name.clone()), fcall_expr.params.get(0).unwrap(), Vec::new());
                                    let mut assoc_new_args = Vec::new();
                                    assoc_new_args.push(assoc_new_e);
                                    assoc_new_args.push(extra_arg_e);
                                    assoc_new_args.extend(fcall_expr.params[1..].to_vec());

                                    // Issue #132: Preserve does_throw flag from original FCall
                                    let typer_fcall_info = if let NodeType::FCall(ref info) = fcall_expr.node_type { info.clone() } else { FCallInfo { does_throw: false, is_bang: false } };
                                    *fcall_expr = Expr::new_clone(NodeType::FCall(typer_fcall_info), fcall_expr.params.get(0).unwrap(), assoc_new_args);
                                    return Ok(Some(assoc_func_def.clone()))
                                }
                            },
                            found_value_type => return Err(func_expr.error(&context.path, "type", &format!(
                                "'{}' is of type '{}' and thus can't have a '{}' associated function",
                                new_combined_name, value_type_to_str(&found_value_type), ufcs_func_name)))
                        }
                    }
                }
            }
            // Check if this is actually a field being called as a function
            if let Ok(field_value_type) = get_value_type(context, func_expr) {
                return Err(func_expr.error(&context.path, "type", &format!(
                    "Cannot call '{}', it is not a function, it is '{}'",
                    combined_name, value_type_to_str(&field_value_type))))
            }
            return Err(func_expr.lang_error(&context.path, "type", &format!("Could not find function definition for '{}'", combined_name)))
        },
        _ => return Err(func_expr.lang_error(&context.path, "type", "Expected Identifier node type"))
    }
}

fn get_func_def_for_fcall(context: &Context, fcall_expr_: &Expr) -> Result<Option<FuncDef>, String> {
    let mut fcall_expr = fcall_expr_.clone();
    return get_func_def_for_fcall_with_expr(&context, &mut fcall_expr);
}






// ---------- Type checking

fn is_expr_calling_procs(context: &Context, e: &Expr) -> Result<bool, String> {
    match &e.node_type {
        NodeType::Body => {
            for se in &e.params {
                if is_expr_calling_procs(&context, &se)? {
                    return Ok(true)
                }
            }
            return Ok(false)
        },
        NodeType::StructDef(struct_def) => {
            // Check if any default values call procs
            for (_member_name, default_expr) in &struct_def.default_values {
                if is_expr_calling_procs(context, default_expr)? {
                    return Ok(true)
                }
            }
            return Ok(false)
        },
        NodeType::EnumDef(_) => {
            return Ok(false)
        },
        NodeType::LLiteral(_) => return Ok(false),
        NodeType::DefaultCase => return Ok(false),
        NodeType::Pattern(_) => return Ok(false),
        NodeType::Identifier(_) => return Ok(false),
        NodeType::NamedArg(_) => {
            // Named args should be handled in FCall - check the value expr
            if !e.params.is_empty() {
                return is_expr_calling_procs(context, e.params.get(0).unwrap())
            }
            return Ok(false)
        },
        NodeType::Range => {
            for se in &e.params {
                if is_expr_calling_procs(&context, &se)? {
                    return Ok(true)
                }
            }
            return Ok(false)
        },
        NodeType::FCall(_) => {
            // Check if the function being called is a proc
            let f_name = get_func_name_in_call(e);
            // Check if this proc is allowed to be called from funcs in this mode
            if context.mode_def.allowed_procs_in_funcs.contains(&f_name) {
                return Ok(false)
            }
            let func_is_proc = match context.scope_stack.lookup_func(&f_name) {
                Some(func) => func.is_proc(),
                None => false,
            };

            // Also check if any of the arguments call procs
            // Skip the first param which is the function name itself
            for i in 1..e.params.len() {
                if is_expr_calling_procs(context, e.params.get(i).unwrap())? {
                    return Ok(true)
                }
            }

            return Ok(func_is_proc)
        },
        NodeType::Declaration(decl) => {
            match e.params.get(0) {
                Some(inner_e) => is_expr_calling_procs(context, inner_e),
                None => {
                    e.exit_error("type", &format!("while declaring '{}', parameter is unexpectedly missing.", decl.name));
                    Ok(true)
                }
            }
        },
        NodeType::Assignment(var_name) => {
            match e.params.get(0) {
                Some(assign_inner_e) => is_expr_calling_procs(context, assign_inner_e),
                None => {
                    e.exit_error("type", &format!("while assigning {}, parameter is unexpectedly missing.", var_name));
                    Ok(true)
                }
            }
        }
        NodeType::FuncDef(func_def) => {
            for it_e in &func_def.body {
                if is_expr_calling_procs(context, it_e)? {
                    return Ok(true);
                }
            }
            Ok(false)
        },
        NodeType::If | NodeType::While | NodeType::Switch | NodeType::Return | NodeType::Throw => {
            for it_e in &e.params {
                if is_expr_calling_procs(context, it_e)? {
                    return Ok(true);
                }
            }
            Ok(false)
        },
        NodeType::Break | NodeType::Continue => {
            // Break and Continue have no params, so they don't call procs
            Ok(false)
        },
        NodeType::Catch => {
            // The catch body is always the third parameter
            if let Some(body_expr) = e.params.get(2) {
                is_expr_calling_procs(context, body_expr)
            } else {
                // TODO Err(lang_error) here instead
                Ok(true)
            }
        }
        NodeType::ForIn(_) => {
            // ForIn: params[0]=var, params[1]=collection, params[2]=body
            // Check collection and body for proc calls
            for param in &e.params {
                if is_expr_calling_procs(context, param)? {
                    return Ok(true);
                }
            }
            Ok(false)
        },
        NodeType::Defer => {
            // Issue #188: Defer - check if deferred expression calls procs
            for p in &e.params {
                if is_expr_calling_procs(context, p)? {
                    return Ok(true);
                }
            }
            Ok(false)
        },
    }
}

pub fn func_proc_has_multi_arg(func_def: &FuncDef) -> bool {
    for a in &func_def.sig.args {
        match a.value_type {
            ValueType::TMulti(_) => {
                return true;
            }
            _ => {}
        }
    }
    return false
}

pub fn basic_mode_checks(context: &Context, e: &Expr) -> Result<Vec<String>, String> {
    let mut errors : Vec<String> = Vec::new();

    match &e.node_type {
        NodeType::Body => {
            for p in e.params.iter() {
                match &p.node_type {

                    NodeType::Declaration(decl) => {
                        if !context.mode_def.allows_base_mut && decl.is_mut {
                            errors.push(e.error(&context.path, "mode", &format!("mode {} doesn't allow mut declarations of 'mut {}'.\nSuggestion: remove 'mut' or change to mode script or cli",
                                                                 context.mode_def.name, decl.name)));
                        }
                    },
                    NodeType::FCall(_) => {
                        if !context.mode_def.allows_base_calls {
                            let f_name = get_func_name_in_call(&p);
                            if f_name != "import" {
                                errors.push(e.error(&context.path, "mode", &format!("mode {} doesn't allow calls in the root context of the file'.\nSuggestion: remove the call to '{}' or change mode 'test' or 'script'",
                                                                     context.mode_def.name, f_name)));
                            }
                        }
                    },
                    _ => {},
                }
            }
        },
        _ => {
            errors.push(e.lang_error(&context.path, "mode", "basic_mode_checks() expects a body expression, this should never happen."))
        },
    }

    if context.mode_def.needs_main_proc {
        match context.scope_stack.lookup_symbol("main") {
            Some(symbol_info) => {
                if symbol_info.value_type != ValueType::TFunction(FunctionType::FTProc) {
                    errors.push(e.error(&context.path, "mode", &format!("mode {} requires 'main' to be defined as a proc. It was defined as a {} instead",
                                                         context.mode_def.name, value_type_to_str(&symbol_info.value_type))));
                }
            },
            None => {
                errors.push(e.error(&context.path, "mode", &format!("mode {} requires 'main' to be defined as a proc.", context.mode_def.name)));
            },
        };
    }
    return Ok(errors);
}

// ---------- Bug #128: Resolve INFER_TYPE in AST after type checking ----------

/// Resolve all INFER_TYPE references in the AST after type checking.
/// This replaces Declaration.value_type = INFER_TYPE with the resolved type
/// from the scope stack (which typer populated during check_types).
///
/// After this pass, no INFER_TYPE should remain in the AST, allowing
/// post-typer phases (sugar, precomp, ccodegen) to read types directly
/// without needing type inference.
pub fn resolve_inferred_types(context: &mut Context, e: &Expr) -> Result<Expr, String> {
    match &e.node_type {
        NodeType::Declaration(decl) => {
            // Check if this declaration has INFER_TYPE
            let resolved_type = if decl.value_type == ValueType::TCustom(INFER_TYPE.to_string()) {
                // Infer type from the value expression
                if let Some(inner_e) = e.params.first() {
                    let mut inferred = get_value_type(context, inner_e)?;
                    // Issue #91: Detect function signature definitions
                    if let NodeType::FuncDef(func_def) = &inner_e.node_type {
                        if func_def.body.is_empty() && func_def.sig.args.iter().all(|a| a.name.is_empty())
                            && matches!(func_def.sig.function_type, FunctionType::FTFunc | FunctionType::FTProc) {
                            inferred = ValueType::TType(TTypeDef::TFuncSig);
                        }
                    }
                    inferred
                } else {
                    return Err(e.lang_error(&context.path, "resolve_types",
                        &format!("Cannot resolve type for '{}': no value expression", decl.name)));
                }
            } else {
                decl.value_type.clone()
            };

            // Create new Declaration with resolved type
            let new_decl = Declaration {
                name: decl.name.clone(),
                value_type: resolved_type,
                is_mut: decl.is_mut,
                is_copy: decl.is_copy,
                is_own: decl.is_own,
                default_value: decl.default_value.clone(),
            };

            // Recurse into params
            let mut new_params = Vec::with_capacity(e.params.len());
            for p in &e.params {
                new_params.push(resolve_inferred_types(context, p)?);
            }

            // Register the symbol with resolved type (in case it wasn't already)
            if context.scope_stack.lookup_symbol(&new_decl.name).is_none() {
                context.scope_stack.declare_symbol(new_decl.name.clone(), SymbolInfo {
                    value_type: new_decl.value_type.clone(),
                    is_mut: new_decl.is_mut,
                    is_copy: new_decl.is_copy,
                    is_own: new_decl.is_own,
                    is_comptime_const: false,
                });
            }

            // Issue #91: Resolve FuncDef arg types from function signature reference
            // This must happen before downstream phases (UFCS, precomp) process the body
            if let ValueType::TCustom(ref sig_name) = new_decl.value_type {
                if let Some(sym) = context.scope_stack.lookup_symbol(sig_name) {
                    if sym.value_type == ValueType::TType(TTypeDef::TFuncSig) {
                        if let Some(sfd) = context.scope_stack.lookup_func(sig_name) {
                            let sfd = sfd.clone();
                            if let Some(inner_e) = new_params.first_mut() {
                                if let NodeType::FuncDef(ref mut func_def) = inner_e.node_type {
                                    if func_def.sig.args.len() == sfd.sig.args.len() {
                                        for (i, sig_arg) in sfd.sig.args.iter().enumerate() {
                                            func_def.sig.args[i].value_type = sig_arg.value_type.clone();
                                        }
                                    }
                                    func_def.sig.return_types = sfd.sig.return_types.clone();
                                    func_def.sig.throw_types = sfd.sig.throw_types.clone();
                                    func_def.sig.function_type = sfd.sig.function_type.clone();
                                }
                            }
                        }
                    }
                }
            }

            // For function declarations, also register the function definition (like type checker does)
            match &new_decl.value_type {
                ValueType::TFunction(_) => {
                    if let Some(decl_inner_e) = new_params.first() {
                        if let NodeType::FuncDef(func_def) = &decl_inner_e.node_type {
                            context.scope_stack.declare_func(new_decl.name.clone(), func_def.clone());
                        }
                    }
                },
                _ => {},
            }

            // Re-register resolved ns func_defs in scope_stack so interpreter uses resolved types
            if let Some(inner_e) = new_params.first() {
                if let NodeType::StructDef(struct_def) = &inner_e.node_type {
                    for (name, ns_value_expr) in &struct_def.ns.default_values {
                        if let NodeType::FuncDef(func_def) = &ns_value_expr.node_type {
                            let full_name = format!("{}.{}", new_decl.name, name);
                            context.scope_stack.update_func(&full_name, func_def.clone());
                        }
                    }
                }
            }

            Ok(Expr::new_explicit(NodeType::Declaration(new_decl), new_params, e.line, e.col))
        }

        // FuncDef - push function scope and recurse into body
        NodeType::FuncDef(func_def) => {
            // Skip body resolution for macros with Type parameters
            if func_def.is_macro() && func_def.sig.args.iter().any(|a|
                matches!(&a.value_type, ValueType::TCustom(t) if t == "Type" || t == "Dynamic"))
            {
                return Ok(e.clone());
            }

            context.scope_stack.push(ScopeType::Function);

            // Register function parameters in scope
            for arg in &func_def.sig.args {
                context.scope_stack.declare_symbol(arg.name.clone(), SymbolInfo {
                    value_type: arg.value_type.clone(),
                    is_mut: arg.is_mut,
                    is_copy: arg.is_copy,
                    is_own: arg.is_own,
                    is_comptime_const: false,
                });
            }

            // Recurse into body statements
            let mut new_body = Vec::with_capacity(func_def.body.len());
            for stmt in &func_def.body {
                new_body.push(resolve_inferred_types(context, stmt)?);
            }

            let _ = context.scope_stack.pop();

            let new_func_def = FuncDef {
                sig: func_def.sig.clone(),
                arg_names: func_def.arg_names.clone(),
                body: new_body,
                source_path: func_def.source_path.clone(),
            };
            Ok(Expr::new_explicit(NodeType::FuncDef(new_func_def), e.params.clone(), e.line, e.col))
        }

        // Body - push block scope
        NodeType::Body => {
            context.scope_stack.push(ScopeType::Block);
            let mut new_params = Vec::with_capacity(e.params.len());
            for p in &e.params {
                new_params.push(resolve_inferred_types(context, p)?);
            }
            let _ = context.scope_stack.pop();
            Ok(Expr::new_clone(e.node_type.clone(), e, new_params))
        }

        // If/While - push block scope
        NodeType::If | NodeType::While => {
            context.scope_stack.push(ScopeType::Block);
            let mut new_params = Vec::with_capacity(e.params.len());
            for p in &e.params {
                new_params.push(resolve_inferred_types(context, p)?);
            }
            let _ = context.scope_stack.pop();
            Ok(Expr::new_clone(e.node_type.clone(), e, new_params))
        }

        // ForIn - declare loop variable in scope before processing body
        NodeType::ForIn(var_type_name) => {
            context.scope_stack.push(ScopeType::Block);

            // Declare loop variable - get name from params[0], type from node_type
            if let Some(var_expr) = e.params.get(0) {
                if let NodeType::Identifier(var_name) = &var_expr.node_type {
                    let var_type = str_to_value_type(var_type_name);
                    context.scope_stack.declare_symbol(var_name.clone(), SymbolInfo {
                        value_type: var_type,
                        is_mut: false,
                        is_copy: false,
                        is_own: false,
                        is_comptime_const: false,
                    });
                }
            }

            let mut new_params = Vec::with_capacity(e.params.len());
            for p in &e.params {
                new_params.push(resolve_inferred_types(context, p)?);
            }

            let _ = context.scope_stack.pop();
            Ok(Expr::new_clone(e.node_type.clone(), e, new_params))
        }

        // Switch - declare pattern binding variables in scope before processing case bodies
        NodeType::Switch => {
            let mut new_params = Vec::with_capacity(e.params.len());

            // Get switch expression type for pattern binding
            let switch_expr_type = if let Some(switch_expr) = e.params.get(0) {
                new_params.push(resolve_inferred_types(context, switch_expr)?);
                get_value_type(context, switch_expr).ok()
            } else {
                None
            };

            // Process case/body pairs (params[1..] are case, body, case, body, ...)
            let mut i = 1;
            while i < e.params.len() {
                let case_expr = e.params.get(i).unwrap();
                new_params.push(resolve_inferred_types(context, case_expr)?);
                i += 1;

                if i >= e.params.len() {
                    break;
                }

                let body_expr = e.params.get(i).unwrap();

                // For pattern matching, add binding variable to scope
                if let NodeType::Pattern(PatternInfo { variant_name, binding_var }) = &case_expr.node_type {
                    if let Some(ValueType::TCustom(enum_name)) = &switch_expr_type {
                        let variant = if let Some(dot_pos) = variant_name.rfind('.') {
                            &variant_name[dot_pos + 1..]
                        } else {
                            variant_name.as_str()
                        };

                        let payload_type = context.scope_stack.lookup_enum(enum_name)
                            .and_then(|e| e.get(variant).cloned())
                            .flatten();

                        if let Some(payload_type) = payload_type {
                            context.scope_stack.push(ScopeType::Block);
                            context.scope_stack.declare_symbol(
                                binding_var.clone(),
                                SymbolInfo {
                                    value_type: payload_type,
                                    is_mut: false,
                                    is_copy: false,
                                    is_own: false,
                                    is_comptime_const: false,
                                }
                            );
                            new_params.push(resolve_inferred_types(context, body_expr)?);
                            let _ = context.scope_stack.pop();
                        } else {
                            new_params.push(resolve_inferred_types(context, body_expr)?);
                        }
                    } else {
                        new_params.push(resolve_inferred_types(context, body_expr)?);
                    }
                } else {
                    new_params.push(resolve_inferred_types(context, body_expr)?);
                }

                i += 1;
            }

            Ok(Expr::new_clone(e.node_type.clone(), e, new_params))
        }

        // Catch - declare catch variable in scope before processing body
        NodeType::Catch => {
            if e.params.len() != 3 {
                return Err(e.lang_error(&context.path, "resolve_types", "Catch node must have three parameters: variable, type, and body."));
            }

            let err_var_expr = e.params.get(0).unwrap();
            let err_type_expr = e.params.get(1).unwrap();
            let body_expr = e.params.get(2).unwrap();

            let var_name = match &err_var_expr.node_type {
                NodeType::Identifier(name) => name.clone(),
                _ => return Err(e.lang_error(&context.path, "resolve_types", "Catch variable must be an identifier")),
            };

            let type_name = match &err_type_expr.node_type {
                NodeType::Identifier(name) => name.clone(),
                _ => return Err(e.lang_error(&context.path, "resolve_types", "Catch type must be an identifier")),
            };

            // Create scoped context for catch body
            context.scope_stack.push(ScopeType::Block);
            context.scope_stack.declare_symbol(var_name.clone(), SymbolInfo {
                value_type: ValueType::TCustom(type_name.clone()),
                is_mut: false,
                is_copy: false,
                is_own: false,
                is_comptime_const: false,
            });

            // Map struct fields so err.msg etc. can be accessed
            let members = context.scope_stack.lookup_struct(&type_name)
                .map(|s| s.members.clone());
            if let Some(members) = members {
                for field_decl in &members {
                    let combined_name = format!("{}.{}", var_name, field_decl.name);
                    context.scope_stack.declare_symbol(
                        combined_name.clone(),
                        SymbolInfo {
                            value_type: field_decl.value_type.clone(),
                            is_mut: false,
                            is_copy: false,
                            is_own: false,
                            is_comptime_const: false,
                        },
                    );
                }
            }

            // Process body only
            let new_body = resolve_inferred_types(context, body_expr)?;
            context.scope_stack.pop().ok();

            Ok(Expr::new_explicit(e.node_type.clone(), vec![err_var_expr.clone(), err_type_expr.clone(), new_body], e.line, e.col))
        }

        // StructDef - resolve member types and recurse into default_values
        NodeType::StructDef(struct_def) => {
            // First, resolve types and recurse into default_values
            let mut new_default_values = HashMap::new();
            for (name, value_expr) in &struct_def.default_values {
                new_default_values.insert(name.clone(), resolve_inferred_types(context, value_expr)?);
            }

            // Then, resolve INFER_TYPE in member declarations
            let mut new_members = Vec::new();
            for member in &struct_def.members {
                let resolved_type = match &member.value_type {
                    ValueType::TCustom(s) if s == INFER_TYPE => {
                        // Get resolved default_value for this member
                        match new_default_values.get(&member.name) {
                            Some(default_value) => get_value_type(context, default_value)?,
                            None => return Err(e.lang_error(&context.path, "resolve_types",
                                &format!("Cannot infer type for struct member '{}': no default value", member.name))),
                        }
                    },
                    _ => member.value_type.clone(),
                };
                new_members.push(Declaration {
                    name: member.name.clone(),
                    value_type: resolved_type,
                    is_mut: member.is_mut,
                    is_copy: member.is_copy,
                    is_own: member.is_own,
                    default_value: member.default_value.clone(),
                });
            }

            // Recurse into ns default_values (function bodies)
            let mut ns_new_default_values = HashMap::new();
            for (name, ns_value_expr) in &struct_def.ns.default_values {
                let resolved_expr = resolve_inferred_types(context, ns_value_expr)?;
                ns_new_default_values.insert(name.clone(), resolved_expr);
            }
            // Issue #161: Resolve INFER_TYPE in namespace member declarations
            let mut ns_new_members = Vec::new();
            for ns_member in &struct_def.ns.members {
                let ns_resolved_type = match &ns_member.value_type {
                    ValueType::TCustom(s) if s == INFER_TYPE => {
                        match ns_new_default_values.get(&ns_member.name) {
                            Some(ns_default_value) => get_value_type(context, ns_default_value)?,
                            None => ns_member.value_type.clone(),
                        }
                    },
                    _ => ns_member.value_type.clone(),
                };
                ns_new_members.push(Declaration {
                    name: ns_member.name.clone(),
                    value_type: ns_resolved_type,
                    is_mut: ns_member.is_mut,
                    is_copy: ns_member.is_copy,
                    is_own: ns_member.is_own,
                    default_value: ns_member.default_value.clone(),
                });
            }
            let new_ns = NamespaceDef {
                members: ns_new_members,
                default_values: ns_new_default_values,
            };

            let new_struct_def = StructDef {
                members: new_members,
                default_values: new_default_values,
                ns: new_ns,
            };
            Ok(Expr::new_explicit(NodeType::StructDef(new_struct_def), e.params.clone(), e.line, e.col))
        }

        // Issue #161: Resolve INFER_TYPE in enum namespace member declarations
        NodeType::EnumDef(enum_def) => {
            // Recurse into ns default_values (function bodies)
            let mut ns_new_default_values = HashMap::new();
            for (name, ns_value_expr) in &enum_def.ns.default_values {
                let resolved_expr = resolve_inferred_types(context, ns_value_expr)?;
                ns_new_default_values.insert(name.clone(), resolved_expr);
            }
            // Resolve INFER_TYPE in namespace member declarations
            let mut ns_new_members = Vec::new();
            for ns_member in &enum_def.ns.members {
                let ns_resolved_type = match &ns_member.value_type {
                    ValueType::TCustom(s) if s == INFER_TYPE => {
                        match ns_new_default_values.get(&ns_member.name) {
                            Some(ns_default_value) => get_value_type(context, ns_default_value)?,
                            None => ns_member.value_type.clone(),
                        }
                    },
                    _ => ns_member.value_type.clone(),
                };
                ns_new_members.push(Declaration {
                    name: ns_member.name.clone(),
                    value_type: ns_resolved_type,
                    is_mut: ns_member.is_mut,
                    is_copy: ns_member.is_copy,
                    is_own: ns_member.is_own,
                    default_value: ns_member.default_value.clone(),
                });
            }
            let new_ns = NamespaceDef {
                members: ns_new_members,
                default_values: ns_new_default_values,
            };
            // Recurse into method default_values
            let mut new_methods = enum_def.methods.clone();
            for (_method_name, method_expr) in new_methods.iter_mut() {
                *method_expr = resolve_inferred_types(context, method_expr)?;
            }
            let new_enum_def = EnumDef {
                variants: enum_def.variants.clone(),
                methods: new_methods,
                ns: new_ns,
            };
            Ok(Expr::new_explicit(NodeType::EnumDef(new_enum_def), e.params.clone(), e.line, e.col))
        }

        // Default: recurse into all params
        _ => {
            if e.params.is_empty() {
                Ok(e.clone())
            } else {
                let mut new_params = Vec::with_capacity(e.params.len());
                for p in &e.params {
                    new_params.push(resolve_inferred_types(context, p)?);
                }
                Ok(Expr::new_clone(e.node_type.clone(), e, new_params))
            }
        }
    }
}
