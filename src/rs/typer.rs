use crate::rs::init::{Context, SymbolInfo, ScopeType, get_value_type, get_func_name_in_call, import_path_to_file_path};
use crate::rs::parser::{
    INFER_TYPE, Literal,
    Expr, NodeType, ValueType, SEnumDef, SStructDef, SFuncDef, Declaration, PatternInfo, FunctionType, TTypeDef,
    value_type_to_str, str_to_value_type,
};

// Type checking phase: Validates types, return/throw statements, mode constraints
// This module handles the type checking phase that runs after init.
// No eval, no arena access - pure type analysis.

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

    // Run type checking on the imported AST
    let errors = check_types(context, &ast);

    context.path = original_path;
    context.mode_def = original_mode;
    return errors;
}

fn check_enum_def(context: &Context, e: &Expr, enum_def: &SEnumDef) -> Vec<String> {
    let mut errors : Vec<String> = Vec::new();
    if e.params.len() != 0 {
        errors.push(e.exit_error("type", "in check_enum_def(): enum declarations don't have any parameters in the tree."));
        return errors
    }

    for (enum_val_name, enum_opt) in enum_def.iter() {
        match &enum_opt {
            None => {},
            Some(value_type) => {
                match value_type {
                    ValueType::TCustom(ref custom_type_name) => {
                        // Validate that the custom type exists
                        if context.scope_stack.lookup_symbol(custom_type_name).is_none() {
                            errors.push(e.error(&context.path, "type", &format!(
                                "Enum variant '{}' uses undefined type '{}'.\nHint: Make sure '{}' is defined before this enum.",
                                enum_val_name, custom_type_name, custom_type_name
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
                                        enum_val_name, custom_type_name, value_type_to_str(&symbol_info.value_type)
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
    return errors;
}

// Public entry point: assumes Body-level context (return values discarded at statement level)
pub fn check_types(context: &mut Context, e: &Expr) -> Vec<String> {
    return check_types_with_context(context, e, ExprContext::ValueDiscarded);
}

// Internal type checker with context tracking for return value usage
fn check_types_with_context(context: &mut Context, e: &Expr, expr_context: ExprContext) -> Vec<String> {
    let mut errors : Vec<String> = Vec::new();
    match &e.node_type {
        NodeType::Body => {
            // Statements in Body discard return values
            for p in e.params.iter() {
                errors.extend(check_types_with_context(context, &p, ExprContext::ValueDiscarded));
            }
        },
        NodeType::EnumDef(enum_def) => {
            errors.extend(check_enum_def(context, &e, enum_def));
        },
        NodeType::StructDef(struct_def) => {
            errors.extend(check_struct_def(context, &e, struct_def));
        },
        NodeType::If => {
            errors.extend(check_if_statement(context, &e));
        },
        NodeType::While => {
            errors.extend(check_while_statement(context, &e));
        },
        NodeType::Switch => {
            errors.extend(check_switch_statement(context, &e));
        },
        NodeType::Range => {
            if e.params.len() != 2 {
                errors.push(e.lang_error(&context.path, "type", "Range expression must have exactly two elements"));
                return errors;
            }

            // Range operands are used
            errors.extend(check_types_with_context(context, &e.params[0], ExprContext::ValueUsed));
            errors.extend(check_types_with_context(context, &e.params[1], ExprContext::ValueUsed));

            let left_type = get_value_type(context, &e.params[0]);
            if let Err(err) = &left_type {
                errors.push(err.clone());
            }
            let right_type = get_value_type(context, &e.params[1]);
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
        NodeType::FCall => {
            // Special handling for import() calls - type-check the imported file
            let f_name = get_func_name_in_call(&e);
            if f_name == "import" {
                // Get the import path from the argument
                if let Ok(path_expr) = e.get(1) {
                    if let NodeType::LLiteral(Literal::Str(import_path)) = &path_expr.node_type {
                        errors.extend(typer_import_declarations(context, import_path));
                    }
                }
            }
            errors.extend(check_fcall(context, &e));
            // Check if return value usage is correct for this context
            errors.extend(check_fcall_return_usage(context, &e, expr_context));
        },
        NodeType::FuncDef(func_def) => {
            context.scope_stack.push(ScopeType::Function);
            errors.extend(check_func_proc_types(&func_def, context, &e));
            context.scope_stack.pop().ok();
        },
        NodeType::Identifier(name) => {
            // Bug #32 fix: "_" is a special marker for field access on expression results
            // params[0] is the expression, params[1..] are the field chain (field names, not symbols)
            if name == "_" && !e.params.is_empty() {
                // Only check the base expression (params[0])
                // params[1..] are field identifiers that don't need symbol lookup
                errors.extend(check_types_with_context(context, e.get(0).unwrap(), ExprContext::ValueUsed));
            } else if !(context.scope_stack.lookup_func(name).is_some() || context.scope_stack.lookup_symbol(name).is_some()) {
                errors.push(e.error(&context.path, "type", &format!("Undefined symbol '{}'", name)));
            } else if context.scope_stack.is_closure_capture(name) {
                // Bug #50: Closures not supported yet
                errors.push(e.todo_error(&context.path, "type", &format!(
                    "Closures are not supported yet. Pass '{}' as a parameter to this function instead.", name)));
            }
        },
        NodeType::Declaration(decl) => {
            errors.extend(check_declaration(context, &e, decl));
        },
        NodeType::Assignment(var_name) => {
            errors.extend(check_assignment(context, &e, var_name));
        },
        NodeType::Return | NodeType::Throw => {
            // Return/throw values are used
            for return_val in &e.params {
                errors.extend(check_types_with_context(context, &return_val, ExprContext::ValueUsed));
            }
        },
        NodeType::Catch => {
            errors.extend(check_catch_statement(context, &e));
        }

        NodeType::LLiteral(_) | NodeType::DefaultCase | NodeType::Pattern(_) => {},
        NodeType::Break | NodeType::Continue => {
            // Break and Continue are simple statements with no parameters to type-check
            // Scope validation (must be inside a loop) could be added here later
        },
        NodeType::NamedArg(_) => {
            // Named args - type check the value expression
            for p in &e.params {
                errors.extend(check_types_with_context(context, p, expr_context));
            }
        },
        NodeType::ForIn(_var_type) => {
            errors.extend(check_forin_statement(context, &e));
        },
    }

    return errors
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
fn validate_func_arg_count(path: &str, e: &Expr, f_name: &str, func_def: &SFuncDef) -> Option<String> {
    let provided_args = e.params.len() - 1;

    // Check zero-arg functions
    if func_def.args.len() == 0 && provided_args > 0 {
        return Some(e.error(path, "type", &format!("Function/procedure '{}' expects 0 args, but {} were provided.", f_name, provided_args)));
    }

    let has_multi_arg = func_proc_has_multi_arg(&func_def);

    // Count required args (those without default values)
    let required_args = func_def.args.iter().filter(|a| a.default_value.is_none()).count();

    // Check arg count for non-variadic functions
    // Must provide at least required args, and at most total args
    if !has_multi_arg {
        if provided_args < required_args {
            return Some(e.error(path, "type", &format!("Function/procedure '{}' expects at least {} args, but {} were provided.",
                                                 f_name, required_args, provided_args)));
        }
        if provided_args > func_def.args.len() {
            return Some(e.error(path, "type", &format!("Function/procedure '{}' expects at most {} args, but {} were provided.",
                                                 f_name, func_def.args.len(), provided_args)));
        }
    }

    // Check minimum count for variadic functions
    if has_multi_arg && func_def.args.len() - 1 > provided_args {
        return Some(e.error(path, "type", &format!("Function/procedure '{}' expects at least {} args, but {} were provided.",
                                             f_name, func_def.args.len() - 1, provided_args)));
    }

    None
}

fn check_if_statement(context: &mut Context, e: &Expr) -> Vec<String> {
    let mut errors : Vec<String> = Vec::new();
    if let Some(err) = validate_conditional_params(&context.path, e, "if", 2, 3) {
        errors.push(err);
        return errors;
    }

    let inner_e = match e.get(0) {
        Ok(inner_e_) => inner_e_,
        Err(error_str) => {
            errors.push(error_str);
            return errors
        },
    };
    // Type check the condition expression exists, but don't enforce it must be Bool
    // NOTE: Bool type checking removed - Bool is a regular struct, not a special primitive
    match get_value_type(&context, &inner_e) {
        Ok(_val_type) => {},
        Err(error_string) => {
            errors.push(error_string);
            return errors;
        },
    };
    // First param (condition) is used, remaining params (then/else bodies) discard values
    for (i, p) in e.params.iter().enumerate() {
        let ctx = if i == 0 { ExprContext::ValueUsed } else { ExprContext::ValueDiscarded };
        errors.extend(check_types_with_context(context, &p, ctx));
    }
    return errors;
}

fn check_while_statement(context: &mut Context, e: &Expr) -> Vec<String> {
    let mut errors : Vec<String> = Vec::new();
    if let Some(err) = validate_conditional_params(&context.path, e, "while", 2, 2) {
        errors.push(err);
        return errors;
    }

    let inner_e = match e.get(0) {
        Ok(inner_e_) => inner_e_,
        Err(error_str) => {
            errors.push(error_str);
            return errors
        },
    };
    // Type check the condition expression exists, but don't enforce it must be Bool
    // NOTE: Bool type checking removed - Bool is a regular struct, not a special primitive
    match get_value_type(&context, &inner_e) {
        Ok(_val_type) => {},
        Err(error_string) => {
            errors.push(error_string);
            return errors;
        },
    };
    // First param (condition) is used, second param (body) discards values
    for (i, p) in e.params.iter().enumerate() {
        let ctx = if i == 0 { ExprContext::ValueUsed } else { ExprContext::ValueDiscarded };
        errors.extend(check_types_with_context(context, &p, ctx));
    }
    return errors;
}

fn check_forin_statement(context: &mut Context, e: &Expr) -> Vec<String> {
    let mut errors: Vec<String> = Vec::new();

    // e.params[0] = Identifier(var_name)
    // e.params[1] = collection expression
    // e.params[2] = body
    // NodeType::ForIn(var_type_name)

    let var_type_name = match &e.node_type {
        NodeType::ForIn(type_name) => type_name.clone(),
        _ => return vec![e.lang_error(&context.path, "type", "Expected ForIn node")],
    };

    // Extract variable name from params[0]
    let var_name = match &e.params.get(0) {
        Some(var_expr) => match &var_expr.node_type {
            NodeType::Identifier(name) => name.clone(),
            _ => return vec![e.lang_error(&context.path, "type", "ForIn: expected identifier for loop variable")],
        },
        None => return vec![e.lang_error(&context.path, "type", "ForIn: missing loop variable")],
    };

    // Get collection expression
    let collection_expr = match e.params.get(1) {
        Some(expr) => expr,
        None => return vec![e.lang_error(&context.path, "type", "ForIn: missing collection expression")],
    };

    // Type check the collection expression
    errors.extend(check_types_with_context(context, collection_expr, ExprContext::ValueUsed));

    // Get collection type
    let collection_type = match get_value_type(context, collection_expr) {
        Ok(t) => t,
        Err(err) => {
            errors.push(err);
            return errors;
        }
    };

    let type_name = match &collection_type {
        ValueType::TCustom(name) => name.clone(),
        _ => {
            errors.push(e.error(&context.path, "type", "for-in loop requires a collection type"));
            return errors;
        }
    };

    // Check TypeName.len() exists and returns I64
    let len_method = format!("{}.len", type_name);
    match context.scope_stack.lookup_func(&len_method) {
        Some(func_def) => {
            // Verify returns I64
            if func_def.return_types.len() != 1 ||
               func_def.return_types[0] != ValueType::TCustom("I64".to_string()) {
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
            // Verify signature: get(self, I64, mut Dynamic) throws IndexOutOfBoundsError
            let mut throws_index_error = false;
            for t in &func_def.throw_types {
                if *t == ValueType::TCustom("IndexOutOfBoundsError".to_string()) {
                    throws_index_error = true;
                    break;
                }
            }
            let valid = func_def.args.len() >= 3
                && func_def.args[1].value_type == ValueType::TCustom("I64".to_string())
                && func_def.args[2].is_mut
                && func_def.args[2].value_type == ValueType::TCustom("Dynamic".to_string())
                && throws_index_error;

            if !valid {
                errors.push(e.error(&context.path, "type", &format!(
                    "for-in loop: '{}.get()' has wrong signature.\n\
                     Required: {}.get(self, index: I64, mut item: Dynamic) throws IndexOutOfBoundsError",
                    type_name, type_name)));
            }
        },
        None => {
            errors.push(e.error(&context.path, "type", &format!(
                "for-in loop: type '{}' does not have a 'get()' method.\n\
                 Required: {}.get(self, index: I64, mut item: Dynamic) throws IndexOutOfBoundsError",
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
        errors.extend(check_types_with_context(context, body_expr, ExprContext::ValueDiscarded));
    }

    context.scope_stack.pop().ok();
    errors
}

fn check_fcall(context: &mut Context, e: &Expr) -> Vec<String> {
    let mut errors: Vec<String> = Vec::new();
    let f_name = get_func_name_in_call(e);
    let mut e = e.clone();
    let func_def = match get_func_def_for_fcall_with_expr(&context, &mut e) {
        Ok(func_def_) => match func_def_ {
            Some(func_def_) => func_def_,
            None => return errors, // REM: This is to allow struct instantiation
        },
        Err(err) => {
            errors.push(err);
            return errors
        },
    };

    if let Some(err) = validate_func_arg_count(&context.path, &e, &f_name, &func_def) {
        errors.push(err);
        return errors;
    }

    let max_arg_def = func_def.args.len();
    let mut def_arg_idx: usize = 0;  // Bug #61: Track definition arg separately from provided arg
    for i in 0..e.params.len() - 1 {
        let arg_expr = match e.get(i + 1) {
            Ok(expr) => expr,
            Err(err) => {
                errors.push(err);
                return errors;
            }
        };

        // Function call arguments are being used (passed to the function)
        // This must happen BEFORE get_value_type so undefined symbol errors are detected
        errors.extend(check_types_with_context(context, &arg_expr, ExprContext::ValueUsed));

        // Bug #61: Get provided type early to check if we should skip optional args
        let found_type = match get_value_type(&context, arg_expr) {
            Ok(val_type) => val_type,
            Err(error_string) => {
                errors.push(error_string);
                return errors;
            },
        };

        // Bug #61: Skip optional args before variadic when type doesn't match
        while def_arg_idx < max_arg_def {
            let current_def = &func_def.args[def_arg_idx];
            let expected = match &current_def.value_type {
                ValueType::TMulti(inner) => str_to_value_type(&inner.clone()),
                _ => current_def.value_type.clone(),
            };

            // Check if types are compatible
            let types_ok = match &expected {
                ValueType::TCustom(tn) if tn == "Dynamic" || tn == "Type" => true,
                _ => &expected == &found_type,
            };

            if types_ok {
                break;  // Use this def arg
            }

            // Types don't match - check if we can skip this optional arg
            let has_default = current_def.default_value.is_some();
            let variadic_follows = def_arg_idx + 1 < max_arg_def &&
                matches!(&func_def.args[def_arg_idx + 1].value_type, ValueType::TMulti(_));

            if has_default && variadic_follows {
                def_arg_idx += 1;
                continue;
            }

            break;  // Can't skip, will report type error
        }

        let arg = match func_def.args.get(std::cmp::min(def_arg_idx, max_arg_def - 1)) {
            Some(arg) => arg,
            None => {
                errors.push(e.lang_error(&context.path, "type", &format!("argument index {} out of bounds for function '{}'", def_arg_idx, f_name)));
                return errors;
            }
        };
        let expected_type = &match &arg.value_type {
            ValueType::TMulti(inner_type_name) => str_to_value_type(&inner_type_name.clone()),
            _ => arg.value_type.clone(),
        };
        // Note: check_types_with_context called earlier in loop (before found_type calculation)

        // Check mut parameter requirements
        if arg.is_mut {
            // The parameter expects mut, so the argument must be a mutable variable
            match &arg_expr.node_type {
                NodeType::Identifier(var_name) => {
                    // Simple variable - check if it's mut
                    if let Some(symbol_info) = context.scope_stack.lookup_symbol(var_name) {
                        if !symbol_info.is_mut {
                            errors.push(arg_expr.error(&context.path, "type", &format!(
                                "Cannot pass const variable '{}' to mut parameter '{}' of function '{}'.\n\
                                 Suggestion: declare '{}' as 'mut {}'.",
                                var_name, arg.name, f_name, var_name, var_name
                            )));
                        }
                    }
                },
                NodeType::LLiteral(_) => {
                    // Bug #48: Literals cannot be passed to mut parameters
                    errors.push(arg_expr.error(&context.path, "type", &format!(
                        "Cannot pass literal to mut parameter '{}'. Use a variable instead.",
                        arg.name
                    )));
                },
                _ => {
                    // FCall: Allow - function results like ptr_add() are valid for mut pointer params
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
                        if let Some(struct_def) = context.scope_stack.lookup_struct(type_name) {
                            // Check if clone() exists as a const (associated function)
                            let has_clone = struct_def.get_member("clone")
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
        match expected_type {
            ValueType::TCustom(tn) if tn == "Dynamic" || tn == "Type" => {}, // Accept any type for Dynamic/Type-typed argument
            ValueType::TCustom(tn) if tn == INFER_TYPE => {
                errors.push(e.error(&context.path, "type", &format!(
                    "calling func/proc '{}' declared arg {} without type, but type inference in args is not supported.\n\
                     Suggestion: the arg should be '{} : {},' instead of just '{}'.\n\
                     Alternative option: the arg could be '{} : Dynamic,' for dynamic arguments.
                     ",
                    f_name, arg.name, arg.name, value_type_to_str(&found_type), arg.name, arg.name,
                )));
            },
            _ if expected_type != &found_type => {
                errors.push(e.error(&context.path, "type", &format!(
                    "calling function '{}' expects '{}' for arg '{}', but '{}' was provided.",
                    f_name, value_type_to_str(expected_type), arg.name, value_type_to_str(&found_type)
                )));
            },
            _ => {} // types match; no error
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

    return errors
}

// Check if a function call's return value is being used correctly (Bug #8 fix)
fn check_fcall_return_usage(context: &Context, e: &Expr, expr_context: ExprContext) -> Vec<String> {
    let mut errors: Vec<String> = Vec::new();

    // Get the function definition to check if it returns a value
    let func_def = match get_func_def_for_fcall(&context, e) {
        Ok(Some(func_def_)) => func_def_,
        Ok(None) => return errors, // Struct/enum constructor, no return value check needed
        Err(_) => return errors, // Error already reported by check_fcall
    };

    // Check if this function returns a value
    let returns_value = func_def.return_types.len() > 0;

    if returns_value && expr_context == ExprContext::ValueDiscarded {
        let f_name = get_func_name_in_call(e);

        errors.push(e.error(&context.path, "type", &format!(
            "Function '{}' returns a value that is not being used.\n\
             Hint: Capture the return value with '_ := {}(...)' or use it in an expression.",
            f_name, f_name
        )));
    }

    return errors;
}

fn check_func_proc_types(func_def: &SFuncDef, context: &mut Context, e: &Expr) -> Vec<String> {
    let mut errors : Vec<String> = Vec::new();
    if !context.mode_def.allows_procs && func_def.is_proc() {
        errors.push(e.error(&context.path, "type", "Procs not allowed in pure modes"));
    }
    let mut has_variadic = false;
    for (i, arg) in func_def.args.iter().enumerate() {
        if has_variadic {
            errors.push(e.error(&context.path, "type", &format!("Variadic argument '{}' must be the last (only one variadic argument allowed).", &arg.name)));
        }

        match &arg.value_type {
            ValueType::TMulti(_multi_type) => {
                if arg.is_mut {
                    errors.push(e.error(&context.path, "type", &format!("Variadic argument '{}' cannot be 'mut'.", &arg.name)));
                }
                if i != func_def.args.len() - 1 {
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
                        return errors
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
                    _ => {
                        // Invalid: not a type, it's a value or something else
                        errors.push(e.error(&context.path, "type", &format!("Argument '{}' has type '{}' which is not a valid type (expected struct or enum)", &arg.name, &custom_type_name)));
                    },
                }
            },
            _ => {
                context.scope_stack.declare_symbol(arg.name.clone(), SymbolInfo{value_type: arg.value_type.clone(), is_mut: arg.is_mut, is_copy: arg.is_copy, is_own: arg.is_own, is_comptime_const: false });
            },
        }
    }

    // TODO re-enable test when it is decided what to do with free, memcpy and memset
    // if func_def.function_type == FunctionType::FTFunc || func_def.function_type == FunctionType::FTFuncExt {
    //     if func_def.return_types.len() == 0 && func_def.throw_types.len() == 0 {
    //         errors.push(e.error(&context.path, "type", "funcs must return or throw something, use a proc instead"));
    //     }
    // }

    // Don't check the bodies of external functions
    if func_def.is_ext() {
        return errors;
    }

    // TODO should macros be allowed to call procs?
    if !func_def.is_proc() {
        for se in &func_def.body {
            if is_expr_calling_procs(&context, &se) {
                errors.push(se.error(&context.path, "type", "funcs cannot call procs."));
            }
        }
    }
    // Function body statements discard return values at the top level
    for p in &func_def.body {
        errors.extend(check_types_with_context(context, &p, ExprContext::ValueDiscarded));
    }

    let mut return_found = false;
    let mut thrown_types: Vec<ThrownType> = Vec::new();
    errors.extend(check_body_returns_throws(context, e, func_def, &func_def.body, &mut thrown_types, &mut return_found));

    if !return_found && func_def.return_types.len() > 0 {
        errors.push(e.error(&context.path, "type", "No return statments found in function that returns "));
    }

    // Filter and report only the thrown types that are not declared
    for te in &thrown_types {
        let mut is_declared = false;
        for declared in &func_def.throw_types {
            if value_type_to_str(declared) == te.type_str {
                is_declared = true;
                break;
            }
        }
        if !is_declared {
            errors.push(te.msg.clone());
        }
    }

    for declared_throw in &func_def.throw_types {
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

    return errors
}

pub fn check_body_returns_throws(context: &mut Context, e: &Expr, func_def: &SFuncDef, body: &[Expr], thrown_types: &mut Vec<ThrownType>, return_found: &mut bool) -> Vec<String> {

    let mut errors = vec![];
    let returns_len = func_def.return_types.len();
    let mut unconditional_exit_in_sequence = false;

    for p in body.iter() {
        // Check if we're processing code after an unconditional return or throw
        if unconditional_exit_in_sequence {
            errors.push(p.error(&context.path, "type",
                "Unreachable code after unconditional return or throw.\n\
                 Suggestion: Remove this code or move it before the return/throw statement."));
        } else {
            match &p.node_type {
            NodeType::Body => {
                let mut temp_thrown_types: Vec<ThrownType> = Vec::new();
                errors.extend(check_body_returns_throws(context, e, func_def, &p.params, &mut temp_thrown_types, return_found));
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
                        let expected_value_type_opt = match func_def.return_types.get(i) {
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
                                check_body_returns_throws(context, return_val_e, func_def, std::slice::from_ref(return_val_e), thrown_types, return_found));

                            match get_value_type(&context, return_val_e) {
                                Ok(actual_value_type) => {
                                    if expected_value_type != &actual_value_type {
                                        errors.push(return_val_e.error(&context.path,
                                            "type", &format!("Return value in pos {} expected to be '{}', but found '{}' instead",
                                                             i, value_type_to_str(&expected_value_type), value_type_to_str(&actual_value_type))));
                                        errors.push(e.error(&context.path, "type", "Suggestion: Update returns section here"));
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
                    let throw_param = &p.params[0];
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
                    let var_name_expr = &p.params[0];
                    let err_type_expr = &p.params[1];
                    let catch_body_expr = &p.params[2];

                    let var_name = match &var_name_expr.node_type {
                        NodeType::Identifier(name) => name.clone(),
                        _ => {
                            errors.push(var_name_expr.error(&context.path, "type", "Catch variable must be a valid identifier"));
                            return errors;
                        }
                    };

                    let caught_type = match &err_type_expr.node_type {
                        NodeType::Identifier(name) => name.clone(),
                        _ => {
                            errors.push(err_type_expr.error(&context.path, "type", "Catch type must be a valid identifier"));
                            return errors;
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
                        // Remove matching entries
                        let mut i = 0;
                        while i < thrown_types.len() {
                            if thrown_types[i].type_str == caught_type {
                                thrown_types.remove(i);
                            } else {
                                i += 1;
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
                    let mut temp_thrown_types: Vec<ThrownType> = Vec::new();
                    errors.extend(check_body_returns_throws(context, e, func_def, &catch_body_expr.params, &mut temp_thrown_types, return_found));
                    thrown_types.extend(temp_thrown_types);
                    context.scope_stack.pop().ok();
                }
            },

            NodeType::FCall => {
                match get_func_def_for_fcall(&context, p) {
                    Ok(Some(called_func_def)) => {
                        for called_throw in &called_func_def.throw_types {
                            let called_throw_str = value_type_to_str(called_throw);
                            let error_msg = format!(
                                "Function throws '{}', but it is not declared in this function's throws section.",
                                called_throw_str
                            );

                            thrown_types.push(ThrownType { type_str: called_throw_str.clone(), msg: p.error(&context.path, "type", &error_msg) });
                            thrown_types.push(ThrownType { type_str: called_throw_str.clone(), msg: e.error(&context.path, "type", "Suggestion: Either add it to the throws section here, or catch it with a catch block") });
                        }

                        for arg in p.params.iter().skip(1) {
                            // Handle direct function calls as arguments
                            if let NodeType::FCall = arg.node_type {
                                match get_func_def_for_fcall(&context, arg) {
                                    Ok(Some(nested_func_def)) => {
                                        let mut temp_thrown_types: Vec<ThrownType> = Vec::new();
                                        errors.extend(check_body_returns_throws(context, arg, &nested_func_def, &arg.params, &mut temp_thrown_types, return_found));
                                        thrown_types.extend(temp_thrown_types);
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
                                if let Some(value_expr) = arg.params.get(0) {
                                    if let NodeType::FCall = &value_expr.node_type {
                                        match get_func_def_for_fcall(&context, value_expr) {
                                            Ok(Some(nested_func_def)) => {
                                                let mut temp_thrown_types: Vec<ThrownType> = Vec::new();
                                                errors.extend(check_body_returns_throws(context, value_expr, &nested_func_def, &value_expr.params, &mut temp_thrown_types, return_found));
                                                thrown_types.extend(temp_thrown_types);
                                            },
                                            Ok(None) => {
                                                // Ok(None) is returned for enum constructors and struct instantiation
                                            },
                                            Err(reason) => {
                                                errors.push(value_expr.error(&context.path, "type", &format!("Failed to resolve nested function call in named arg: {}", reason)));
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
                        for arg in p.params.iter().skip(1) {
                            // Handle direct function calls as arguments
                            if let NodeType::FCall = arg.node_type {
                                match get_func_def_for_fcall(&context, arg) {
                                    Ok(Some(nested_func_def)) => {
                                        // Track the function's declared throw types
                                        for called_throw in &nested_func_def.throw_types {
                                            let called_throw_str = value_type_to_str(called_throw);
                                            let error_msg = format!(
                                                "Function throws '{}', but it is not declared in this function's throws section.",
                                                called_throw_str
                                            );
                                            thrown_types.push(ThrownType { type_str: called_throw_str.clone(), msg: arg.error(&context.path, "type", &error_msg) });
                                            thrown_types.push(ThrownType { type_str: called_throw_str.clone(), msg: e.error(&context.path, "type", "Suggestion: Either add it to the throws section here, or catch it with a catch block") });
                                        }
                                    },
                                    Ok(None) => {},
                                    Err(reason) => {
                                        errors.push(arg.error(&context.path, "type", &format!("Failed to resolve nested function call: {}", reason)));
                                    }
                                }
                            }
                            // Bug #36 fix: Handle named arguments in struct literals (e.g., Map(keys=self.keys.clone()))
                            if let NodeType::NamedArg(_) = &arg.node_type {
                                if let Some(value_expr) = arg.params.get(0) {
                                    if let NodeType::FCall = &value_expr.node_type {
                                        match get_func_def_for_fcall(&context, value_expr) {
                                            Ok(Some(nested_func_def)) => {
                                                // Track the function's declared throw types
                                                for called_throw in &nested_func_def.throw_types {
                                                    let called_throw_str = value_type_to_str(called_throw);
                                                    let error_msg = format!(
                                                        "Function throws '{}', but it is not declared in this function's throws section.",
                                                        called_throw_str
                                                    );
                                                    thrown_types.push(ThrownType { type_str: called_throw_str.clone(), msg: value_expr.error(&context.path, "type", &error_msg) });
                                                    thrown_types.push(ThrownType { type_str: called_throw_str.clone(), msg: e.error(&context.path, "type", "Suggestion: Either add it to the throws section here, or catch it with a catch block") });
                                                }
                                            },
                                            Ok(None) => {},
                                            Err(reason) => {
                                                errors.push(value_expr.error(&context.path, "type", &format!("Failed to resolve nested function call in named arg: {}", reason)));
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
                let mut temp_thrown_types: Vec<ThrownType> = Vec::new();
                if let Some(cond_expr) = p.params.get(0) {
                    errors.extend(check_body_returns_throws(context, e, func_def, std::slice::from_ref(cond_expr), &mut temp_thrown_types, return_found));
                }
                if let Some(body_expr) = p.params.get(1) {
                    errors.extend(check_body_returns_throws(context, e, func_def, &body_expr.params, &mut temp_thrown_types, return_found));
                }
                thrown_types.extend(temp_thrown_types);
            }
            NodeType::ForIn(var_type_name) => {
                // ForIn: params[0]=var, params[1]=collection, params[2]=body
                let mut temp_thrown_types: Vec<ThrownType> = Vec::new();
                if let Some(collection_expr) = p.params.get(1) {
                    errors.extend(check_body_returns_throws(context, e, func_def, std::slice::from_ref(collection_expr), &mut temp_thrown_types, return_found));
                }
                if let Some(body_expr) = p.params.get(2) {
                    // Push scope and declare loop variable before checking body
                    let var_name = p.params.get(0)
                        .and_then(|v| if let NodeType::Identifier(name) = &v.node_type { Some(name.clone()) } else { None })
                        .unwrap_or_default();
                    context.scope_stack.push(ScopeType::Block);
                    context.scope_stack.declare_symbol(var_name, SymbolInfo {
                        value_type: ValueType::TCustom(var_type_name.clone()),
                        is_mut: true,
                        is_copy: false,
                        is_own: false,
                        is_comptime_const: false,
                    });
                    errors.extend(check_body_returns_throws(context, e, func_def, &body_expr.params, &mut temp_thrown_types, return_found));
                    context.scope_stack.pop().ok();
                }
                thrown_types.extend(temp_thrown_types);
            }
            NodeType::If => {
                let mut temp_thrown_types: Vec<ThrownType> = Vec::new();
                if let Some(cond_expr) = p.params.get(0) {
                    errors.extend(check_body_returns_throws(context, e, func_def, std::slice::from_ref(cond_expr), &mut temp_thrown_types, return_found));
                }
                if let Some(then_block) = p.params.get(1) {
                    errors.extend(check_body_returns_throws(context, e, func_def, &then_block.params, &mut temp_thrown_types, return_found));
                }
                if let Some(else_block) = p.params.get(2) {
                    errors.extend(check_body_returns_throws(context, e, func_def, &else_block.params, &mut temp_thrown_types, return_found));
                }
                thrown_types.extend(temp_thrown_types);
            }
            NodeType::Switch => {
                let mut temp_thrown_types: Vec<ThrownType> = Vec::new();
                // Get switch expression type for pattern matching
                let switch_expr_type = p.params.get(0)
                    .and_then(|switch_expr| get_value_type(context, switch_expr).ok());

                // Analyze the switch expression itself (could throw)
                if let Some(switch_expr) = p.params.get(0) {
                    errors.extend(check_body_returns_throws(context, e, func_def, std::slice::from_ref(switch_expr), &mut temp_thrown_types, return_found));
                }

                let mut i = 1;
                while i + 1 < p.params.len() {
                    let case_expr = &p.params[i];
                    let body_expr = &p.params[i + 1];

                    // Check case expression
                    errors.extend(check_body_returns_throws(context, e, func_def, std::slice::from_ref(case_expr), &mut temp_thrown_types, return_found));

                    // For pattern matching, add the binding variable to scope before checking body
                    // This mirrors check_switch_statement's scope handling (Bug #28 fix)
                    if let NodeType::Pattern(PatternInfo { variant_name, binding_var }) = &case_expr.node_type {
                        if let Some(ValueType::TCustom(ref enum_name)) = switch_expr_type {
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
                                errors.extend(check_body_returns_throws(context, e, func_def, &body_expr.params, &mut temp_thrown_types, return_found));
                                context.scope_stack.pop().ok();
                            } else {
                                errors.extend(check_body_returns_throws(context, e, func_def, &body_expr.params, &mut temp_thrown_types, return_found));
                            }
                        } else {
                            errors.extend(check_body_returns_throws(context, e, func_def, &body_expr.params, &mut temp_thrown_types, return_found));
                        }
                    } else {
                        errors.extend(check_body_returns_throws(context, e, func_def, &body_expr.params, &mut temp_thrown_types, return_found));
                    }

                    i += 2;
                }
                thrown_types.extend(temp_thrown_types);
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

                    if let NodeType::FCall = initializer.node_type {
                        let id_expr_opt = match initializer.get(0) {
                            Ok(id_expr_) => Some(id_expr_),
                            Err(err) => {
                                errors.push(err);
                                None
                            },
                        };

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
                                    if let Some(symbol) = context.scope_stack.lookup_symbol(name) {
                                        if symbol.value_type == ValueType::TType(TTypeDef::TEnumDef) {
                                            if let Some(variant_expr) = id_expr.params.get(0) {
                                                if let NodeType::Identifier(_variant_name) = &variant_expr.node_type {
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
                            Ok(Some(called_func_def)) => {
                                for called_throw in &called_func_def.throw_types {
                                    let called_throw_str = value_type_to_str(called_throw);
                                    let error_msg = format!(
                                        "Function throws '{}', but it is not declared in this function's throws section.",
                                        called_throw_str
                                    );

                                    thrown_types.push(ThrownType { type_str: called_throw_str.clone(), msg: initializer.error(&context.path, "type", &error_msg) });
                                    thrown_types.push(ThrownType { type_str: called_throw_str.clone(), msg: e.error(&context.path, "type", "Suggestion: Either add it to the throws section here, or catch it with a catch block") });
                                }

                                let mut temp_thrown_types: Vec<ThrownType> = Vec::new();
                                errors.extend(check_body_returns_throws(context, initializer, &called_func_def, &initializer.params, &mut temp_thrown_types, return_found));
                                thrown_types.extend(temp_thrown_types);
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
                if let Some(initializer) = p.params.get(0) {
                    if let NodeType::FCall = initializer.node_type {

                        let id_expr_opt = match initializer.get(0) {
                            Ok(id_expr_) => Some(id_expr_),
                            Err(err) => {
                                errors.push(err);
                                None
                            },
                        };

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
                                    if let Some(symbol) = context.scope_stack.lookup_symbol(name) {
                                        if symbol.value_type == ValueType::TType(TTypeDef::TEnumDef) {
                                            if let Some(variant_expr) = id_expr.params.get(0) {
                                                if let NodeType::Identifier(_variant_name) = &variant_expr.node_type {
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
                            Ok(Some(called_func_def)) => {
                                for called_throw in &called_func_def.throw_types {
                                    let called_throw_str = value_type_to_str(called_throw);
                                    let error_msg = format!(
                                        "Function throws '{}', but it is not declared in this function's throws section.",
                                        called_throw_str
                                    );

                                    thrown_types.push(ThrownType { type_str: called_throw_str.clone(), msg: initializer.error(&context.path, "type", &error_msg) });
                                    thrown_types.push(ThrownType { type_str: called_throw_str.clone(), msg: e.error(&context.path, "type", "Suggestion: Either add it to the throws section here, or catch it with a catch block") });
                                }

                                let mut temp_thrown_types: Vec<ThrownType> = Vec::new();
                                errors.extend(check_body_returns_throws(context, initializer, &called_func_def, &initializer.params, &mut temp_thrown_types, return_found));
                                thrown_types.extend(temp_thrown_types);
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

    return errors
}

fn check_catch_statement(context: &mut Context, e: &Expr) -> Vec<String> {
    let mut errors = Vec::new();

    if e.params.len() != 3 {
        errors.push(e.error(&context.path, "type", "Catch node must have three parameters: variable, type, and body."));
        return errors
    }

    let err_var_expr = &e.params[0];
    let err_type_expr = &e.params[1];
    let body_expr = &e.params[2];

    let var_name = match &err_var_expr.node_type {
        NodeType::Identifier(name) => name.clone(),
        _ => {
            errors.push(err_var_expr.error(&context.path, "type", "First catch param must be an identifier"));
            return errors
        }
    };

    let type_name = match &err_type_expr.node_type {
        NodeType::Identifier(name) => name.clone(),
        _ => {
            errors.push(err_type_expr.error(&context.path, "type", "Second catch param must be a type identifier"));
            return errors
        }
    };

    // Confirm that the type exists in the context (as done for function args)
    if context.scope_stack.lookup_symbol(&type_name).is_none() {
        errors.push(e.error(&context.path, "type", &format!("Catch refers to undefined type '{}'", &type_name)));
        return errors
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
    errors.extend(check_types_with_context(context, body_expr, ExprContext::ValueDiscarded));
    context.scope_stack.pop().ok();

    return errors
}

fn check_declaration(context: &mut Context, e: &Expr, decl: &Declaration) -> Vec<String> {
    let mut errors : Vec<String> = Vec::new();
    if e.params.len() != 1 {
        errors.push(e.exit_error("type", &format!("in declaration of {}, declaration nodes must take exactly 1 parameter.",
                                                  decl.name)));
        return errors
    }


    let inner_e = match e.get(0) {
        Ok(inner_e_) => inner_e_,
        Err(error_str) => {
            errors.push(error_str);
            return errors
        },
    };
    if context.scope_stack.lookup_symbol(&decl.name).is_none() {
        let mut value_type = decl.value_type.clone();
        if value_type == ValueType::TCustom(INFER_TYPE.to_string()) {
            value_type = match get_value_type(&context, &inner_e) {
                Ok(val_type) => val_type,
                Err(error_string) => {
                    errors.push(error_string);
                    return errors;
                },
            };
        }
        // TODO move to init_context() ? inner contexts are not persisted in init_context
        context.scope_stack.declare_symbol(decl.name.to_string(), SymbolInfo{value_type: value_type.clone(), is_mut: decl.is_mut, is_copy: decl.is_copy, is_own: decl.is_own, is_comptime_const: false });
        match value_type {
            ValueType::TCustom(custom_type) => {
                if custom_type == INFER_TYPE {
                    errors.push(e.lang_error(&context.path, "type", &format!("Cannot infer the declaration type of {}", decl.name)));
                    return errors;
                }
                // During type checking, register struct fields so they can be accessed in the code
                // Memory allocation and default value evaluation happens during runtime in eval_declaration
                if context.scope_stack.lookup_struct(&custom_type).is_some() {
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
                        return errors;
                    },
                }
            },
            _ => {},
        }
    }
    // The RHS of a declaration is being used (assigned to the variable)
    errors.extend(check_types_with_context(context, &inner_e, ExprContext::ValueUsed));

    return errors
}

fn check_assignment(context: &mut Context, e: &Expr, var_name: &str) -> Vec<String> {
    let mut errors : Vec<String> = Vec::new();
    if e.params.len() != 1 {
        errors.push(e.exit_error("type", &format!("in assignment to {}, assignments must take exactly one value, not {}.",
                                                  var_name, e.params.len())));
        return errors
    }

    if context.scope_stack.lookup_func(var_name).is_some()  {
        errors.push(e.error(&context.path, "type", &format!("function '{}' cannot be assigned to.", var_name)));
    } else if context.scope_stack.lookup_symbol(var_name).is_some() {
        let symbol_info = match context.scope_stack.lookup_symbol(var_name) {
            Some(info) => info,
            None => {
                errors.push(e.error(&context.path, "type", &format!("Undeclared variable '{}'", var_name)));
                return errors;
            }
        };
        if !symbol_info.is_mut && !symbol_info.is_copy && !symbol_info.is_own {
            errors.push(e.error(&context.path, "type", &format!("Cannot assign to constant '{}', Suggestion: declare it as 'mut'.", var_name)));
        }
        // Additional check: if this is a field access (e.g., "s.value"), also check base instance mutability
        if var_name.contains('.') {
            let base_var = var_name.split('.').next().unwrap();
            if let Some(base_info) = context.scope_stack.lookup_symbol(base_var) {
                if !base_info.is_mut && !base_info.is_copy && !base_info.is_own {
                    errors.push(e.error(&context.path, "type", &format!("Cannot assign to field of constant '{}', Suggestion: declare it as 'mut {}'.", base_var, base_var)));
                }
            }
        }
    } else if var_name.contains('.') {
        // Field access assignment where the field itself isn't registered in symbols
        // With dynamic offset calculation, we need to validate against struct definition
        let parts: Vec<&str> = var_name.split('.').collect();
        let base_var = parts[0];

        if let Some(base_info) = context.scope_stack.lookup_symbol(base_var) {
            // Check base mutability
            if !base_info.is_mut && !base_info.is_copy && !base_info.is_own {
                errors.push(e.error(&context.path, "type", &format!("Cannot assign to field of constant '{}', Suggestion: declare it as 'mut {}'.", base_var, base_var)));
            }

            // Validate field path exists in struct definition
            let mut current_type = base_info.value_type.clone();
            let mut has_error = false;
            for field_name in &parts[1..] {
                if !has_error {
                    match current_type {
                        ValueType::TCustom(ref type_name) => {
                            if let Some(struct_def) = context.scope_stack.lookup_struct(type_name) {
                                let mut field_decl_opt: Option<&Declaration> = None;
                                for decl in &struct_def.members {
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
            errors.push(e.error(&context.path, "type", &format!("Undefined symbol '{}'", base_var)));
        }
    } else {
        errors.push(e.error(&context.path, "type", &format!("Suggestion: try changing '{} =' for '{} :='\nExplanation: Cannot assign to undefined symbol '{}'.",
                                             var_name, var_name, var_name)));
    }

    // The RHS of an assignment is being used (assigned to the variable)
    match e.get(0) {
        Ok(inner_e) => errors.extend(check_types_with_context(context, inner_e, ExprContext::ValueUsed)),
        Err(err) => errors.push(err),
    }
    return errors;
}

fn check_switch_statement(context: &mut Context, e: &Expr) -> Vec<String> {
    let mut errors: Vec<String> = Vec::new();

    let switch_expr_type = match e.get(0) {
        Ok(expr) => match get_value_type(context, expr) {
            Ok(t) => t,
            Err(err) => {
                errors.push(err);
                return errors;
            }
        },
        Err(err) => {
            errors.push(err);
            return errors;
        }
    };

    let mut case_found = false;
    let mut default_found = false;

    let mut i = 1;
    while i < e.params.len() {
        let case_expr = &e.params[i];

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
            return errors
        }

        let body_expr = &e.params[i];

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
                    errors.extend(check_types_with_context(context, body_expr, ExprContext::ValueDiscarded));
                    context.scope_stack.pop().ok();
                } else if context.scope_stack.lookup_enum(enum_name)
                    .and_then(|e| e.get(variant))
                    .is_some() {
                    // Variant exists but has no payload
                    errors.push(case_expr.error(&context.path, "type", &format!("Variant '{}' has no payload, cannot use pattern matching", variant)));
                    errors.extend(check_types_with_context(context, body_expr, ExprContext::ValueDiscarded));
                } else if context.scope_stack.lookup_enum(enum_name).is_some() {
                    // Enum exists but variant doesn't
                    errors.push(case_expr.error(&context.path, "type", &format!("Unknown variant '{}'", variant)));
                    errors.extend(check_types_with_context(context, body_expr, ExprContext::ValueDiscarded));
                } else {
                    // Enum doesn't exist
                    errors.extend(check_types_with_context(context, body_expr, ExprContext::ValueDiscarded));
                }
            } else {
                errors.extend(check_types_with_context(context, body_expr, ExprContext::ValueDiscarded));
            }
        } else {
            errors.extend(check_types_with_context(context, body_expr, ExprContext::ValueDiscarded));
        }

        i += 1;
    }

    if !case_found {
        errors.push(e.error(&context.path, "type", "Switch must have at least one case"));
    }

    // Exhaustiveness check only for enums
    if let ValueType::TCustom(enum_name) = switch_expr_type {
        if let Some(enum_def) = context.scope_stack.lookup_enum(&enum_name) {
            let mut matched_variants: Vec<String> = Vec::new();

            let mut j = 1;
            while j < e.params.len() {
                let case_expr = &e.params[j];
                match &case_expr.node_type {
                    NodeType::Pattern(PatternInfo { variant_name, .. }) => {
                        // Pattern matching: case EnumType.Variant(binding)
                        // Extract the variant name from the full "EnumType.Variant" string
                        if let Some(dot_pos) = variant_name.rfind('.') {
                            let enum_part = &variant_name[..dot_pos];
                            let variant_part = &variant_name[dot_pos + 1..];
                            if enum_part != enum_name {
                                errors.push(case_expr.error(&context.path, "type", &format!("Mismatched enum type '{}', expected '{}'.", enum_part, enum_name)));
                            }
                            matched_variants.push(variant_part.to_string());
                        } else {
                            // Just the variant name without enum prefix
                            matched_variants.push(variant_name.clone());
                        }
                    }
                    NodeType::Identifier(name) => {
                        if case_expr.params.is_empty() {
                            // case A
                            matched_variants.push(name.clone());
                        } else {
                            // case ExampleEnum.A
                            let variant_expr = &case_expr.params[0];
                            if let NodeType::Identifier(variant) = &variant_expr.node_type {
                                if name != &enum_name {
                                    errors.push(case_expr.error(&context.path, "type", &format!("Mismatched enum type '{}', expected '{}'.", name, enum_name)));
                                }
                                matched_variants.push(variant.clone());
                            } else {
                                errors.push(case_expr.error(&context.path, "type", "Invalid enum case syntax"));
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
                for variant in enum_def.keys() {
                    if !matched_variants.contains(variant) {
                        errors.push(e.error(&context.path, "type", &format!("Switch is missing case for variant '{}'", variant)));
                    }
                }
            }
        }
    }

    return errors
}

fn check_struct_def(context: &mut Context, e: &Expr, struct_def: &SStructDef) -> Vec<String> {
    let mut errors : Vec<String> = Vec::new();
    if e.params.len() != 0 {
        errors.push(e.exit_error("type", "in check_struct_def(): struct declarations must take exactly 0 params."));
        return errors
    }

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
                    // If the member's default value is a function (method), type check it
                    NodeType::FuncDef(func_def) => {
                        context.scope_stack.push(ScopeType::Function);
                        errors.extend(check_func_proc_types(&func_def, context, &inner_e));
                        context.scope_stack.pop().ok();
                    },
                    // For other types of members, check type and purity
                    _ => {
                        // Check if default value calls procs (violates purity of constructors)
                        if is_expr_calling_procs(context, inner_e) {
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
    let has_push = struct_def.get_member("push").is_some();
    let has_get = struct_def.get_member("get").is_some();
    let has_set = struct_def.get_member("set").is_some();
    let has_insert = struct_def.get_member("insert").is_some();

    if has_push || has_get || has_set || has_insert {
        // This looks like a collection type - check for len() method
        let has_len = struct_def.get_member("len")
            .map(|decl| !decl.is_mut)
            .unwrap_or(false);

        if !has_len {
            let struct_name = e.params.get(0)
                .and_then(|param| {
                    if let NodeType::Identifier(name) = &param.node_type {
                        Some(name.as_str())
                    } else {
                        None
                    }
                })
                .unwrap_or("unknown");

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
        let has_size = struct_def.get_member("size")
            .map(|decl| !decl.is_mut)
            .unwrap_or(false);

        if !has_size {
            let struct_name = e.params.get(0)
                .and_then(|param| {
                    if let NodeType::Identifier(name) = &param.node_type {
                        Some(name.as_str())
                    } else {
                        None
                    }
                })
                .unwrap_or("unknown");

            let methods: Vec<&str> = vec![
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
                struct_name, methods.join("/"), struct_name, struct_name
            )));
        }
    }

    return errors
}

pub fn get_func_def_for_fcall_with_expr(context: &Context, fcall_expr: &mut Expr) -> Result<Option<SFuncDef>, String> {
    if fcall_expr.node_type != NodeType::FCall {
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

            if let Some(_struct_def) = context.scope_stack.lookup_struct(&combined_name) {
                return Ok(None) // REM: This is to allow struct instantiation
            }

            // Check for enum constructors (e.g., Color.Green(true))
            let parts: Vec<&str> = combined_name.split('.').collect();
            if parts.len() == 2 {
                let enum_type = parts[0];
                if let Some(enum_def) = context.scope_stack.lookup_enum(enum_type) {
                    let variant_name = parts[1];
                    if enum_def.contains_key(variant_name) {
                        // This is a valid enum constructor
                        return Ok(None) // Allow enum construction
                    }
                }
            }

            // UFCS for chained calls: func(result, args) -> Type.func(result, args)
            // e.g., add(1, 2).mul(3) becomes mul(add(1,2), 3) which transforms to I64.mul(add(1,2), 3)
            // This only applies when no standalone function with this name exists (checked above).
            if fcall_expr.params.len() >= 2 {
                let first_arg = fcall_expr.get(1)?;
                if let Ok(target_type) = get_value_type(context, first_arg) {
                    if let ValueType::TCustom(custom_type_name) = target_type {
                        let method_name = format!("{}.{}", custom_type_name, combined_name);
                        if let Some(func_def) = context.scope_stack.lookup_func(&method_name) {
                            // Transform: func(target, args...) -> Type.func(target, args...)
                            let new_e = Expr::new_clone(NodeType::Identifier(method_name.clone()), fcall_expr.get(0)?, Vec::new());
                            let mut new_args = Vec::new();
                            new_args.push(new_e);
                            new_args.extend(fcall_expr.params[1..].to_vec());
                            *fcall_expr = Expr::new_clone(NodeType::FCall, fcall_expr.get(0)?, new_args);
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
                    if let Some(func_def) = context.scope_stack.lookup_func(&ufcs_func_name.to_string()) {

                        let new_e = Expr::new_clone(NodeType::Identifier(ufcs_func_name.clone()), fcall_expr.get(0)?, Vec::new());
                        let mut new_args = Vec::new();
                        new_args.push(new_e);
                        new_args.push(extra_arg_e);
                        new_args.extend(fcall_expr.params[1..].to_vec());

                        *fcall_expr = Expr::new_clone(NodeType::FCall, fcall_expr.get(0)?, new_args);
                        return Ok(Some(func_def.clone()))
                    }

                    // Associated functions used with UFCS (aka methods)
                    // Bug #28 fix: Use get_value_type() to dynamically resolve field access chains
                    // instead of lookup_symbol() which only finds pre-registered symbol names.
                    // This enables UFCS on struct fields like s.items.len() in pattern match case bodies.
                    if let Ok(value_type) = get_value_type(context, &extra_arg_e) {
                        match &value_type {
                            ValueType::TCustom(ref custom_type_name) => {
                                let id_expr_name = format!("{}.{}", custom_type_name, ufcs_func_name);
                                if let Some(func_def) = context.scope_stack.lookup_func(&id_expr_name) {

                                    let new_e = Expr::new_clone(NodeType::Identifier(id_expr_name.clone()), fcall_expr.get(0)?, Vec::new());
                                    let mut new_args = Vec::new();
                                    new_args.push(new_e);
                                    new_args.push(extra_arg_e);
                                    new_args.extend(fcall_expr.params[1..].to_vec());

                                    *fcall_expr = Expr::new_clone(NodeType::FCall, fcall_expr.get(0)?, new_args);
                                    return Ok(Some(func_def.clone()))
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
            if let Ok(value_type) = get_value_type(context, func_expr) {
                return Err(func_expr.error(&context.path, "type", &format!(
                    "Cannot call '{}', it is not a function, it is '{}'",
                    combined_name, value_type_to_str(&value_type))))
            }
            return Err(func_expr.lang_error(&context.path, "type", "Could not find function definition"))
        },
        _ => return Err(func_expr.lang_error(&context.path, "type", "Expected Identifier node type"))
    }
}

fn get_func_def_for_fcall(context: &Context, fcall_expr_: &Expr) -> Result<Option<SFuncDef>, String> {
    let mut fcall_expr = fcall_expr_.clone();
    return get_func_def_for_fcall_with_expr(&context, &mut fcall_expr);
}






// ---------- Type checking

fn is_expr_calling_procs(context: &Context, e: &Expr) -> bool {
    match &e.node_type {
        NodeType::Body => {
            for se in &e.params {
                if is_expr_calling_procs(&context, &se) {
                    return true
                }
            }
            return false
        },
        NodeType::StructDef(struct_def) => {
            // Check if any default values call procs
            for (_member_name, default_expr) in &struct_def.default_values {
                if is_expr_calling_procs(context, default_expr) {
                    return true
                }
            }
            return false
        },
        NodeType::EnumDef(_) => {
            return false
        },
        NodeType::LLiteral(_) => return false,
        NodeType::DefaultCase => return false,
        NodeType::Pattern(_) => return false,
        NodeType::Identifier(_) => return false,
        NodeType::NamedArg(_) => {
            // Named args should be handled in FCall - check the value expr
            if !e.params.is_empty() {
                return is_expr_calling_procs(context, &e.params[0])
            }
            return false
        },
        NodeType::Range => {
            for se in &e.params {
                if is_expr_calling_procs(&context, &se) {
                    return true
                }
            }
            return false
        },
        NodeType::FCall => {
            // Check if the function being called is a proc
            let f_name = get_func_name_in_call(e);
            // Check if this proc is allowed to be called from funcs in this mode
            if context.mode_def.allowed_procs_in_funcs.contains(&f_name) {
                return false
            }
            let func_is_proc = match context.scope_stack.lookup_func(&f_name) {
                Some(func) => func.is_proc(),
                None => false,
            };

            // Also check if any of the arguments call procs
            // Skip the first param which is the function name itself
            for i in 1..e.params.len() {
                if is_expr_calling_procs(context, &e.params[i]) {
                    return true
                }
            }

            return func_is_proc
        },
        NodeType::Declaration(decl) => {
            match e.params.get(0) {
                Some(inner_e) => is_expr_calling_procs(context, inner_e),
                None => {
                    e.exit_error("type", &format!("while declaring '{}', parameter is unexpectedly missing.", decl.name));
                    true
                }
            }
        },
        NodeType::Assignment(var_name) => {
            match e.params.get(0) {
                Some(inner_e) => is_expr_calling_procs(context, inner_e),
                None => {
                    e.exit_error("type", &format!("while assigning {}, parameter is unexpectedly missing.", var_name));
                    true
                }
            }
        }
        NodeType::FuncDef(func_def) => {
            for it_e in &func_def.body {
                if is_expr_calling_procs(context, it_e) {
                    return true;
                }
            }
            false
        },
        NodeType::If | NodeType::While | NodeType::Switch | NodeType::Return | NodeType::Throw => {
            for it_e in &e.params {
                if is_expr_calling_procs(context, it_e) {
                    return true;
                }
            }
            false
        },
        NodeType::Break | NodeType::Continue => {
            // Break and Continue have no params, so they don't call procs
            false
        },
        NodeType::Catch => {
            // The catch body is always the third parameter
            if let Some(body_expr) = e.params.get(2) {
                is_expr_calling_procs(context, body_expr)
            } else {
                // TODO Err(lang_error) here instead
                true
            }
        }
        NodeType::ForIn(_) => {
            // ForIn: params[0]=var, params[1]=collection, params[2]=body
            // Check collection and body for proc calls
            for param in &e.params {
                if is_expr_calling_procs(context, param) {
                    return true;
                }
            }
            false
        }
    }
}

pub fn func_proc_has_multi_arg(func_def: &SFuncDef) -> bool {
    for a in &func_def.args {
        match a.value_type {
            ValueType::TMulti(_) => {
                return true;
            }
            _ => {}
        }
    }
    return false
}

pub fn basic_mode_checks(context: &Context, e: &Expr) -> Vec<String> {
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
                    NodeType::FCall => {
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
    return errors;
}

