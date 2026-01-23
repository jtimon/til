use std::fs;
use std::io::ErrorKind;
use std::collections::{HashMap, HashSet};

use crate::rs::lexer::{lexer_from_source, Token, TokenType};
use crate::rs::mode::{ModeDef, can_be_imported, parse_mode, mode_from_name};
use crate::rs::parser::{
    INFER_TYPE,
    Expr, NodeType, FunctionType, ValueType, SFuncDef, TTypeDef, Literal, SEnumDef, SStructDef, PatternInfo,
    value_type_to_str, str_to_value_type, parse_tokens,
};

// Init phase: Declaration indexing and import processing
// This module handles the "context priming" phase that runs before type checking.
// No eval, no arena access - declarations only.

// Bug #97: Track variable declarations by (name, line, col).
// Using a struct instead of tuple for TIL compatibility (TIL doesn't have tuples).
#[derive(Clone, Debug, PartialEq, Eq, Hash)]
pub struct FunctionLocal {
    pub name: String,
    pub line: usize,
    pub col: usize,
}

#[derive(Clone)]
pub struct SymbolInfo {
    pub value_type: ValueType,
    pub is_mut: bool,
    pub is_copy: bool,
    pub is_own: bool,
    pub is_comptime_const: bool,  // true if value was comptime-evaluable at declaration
}

#[derive(Debug, Clone, PartialEq)]
pub struct EnumVal {
    pub enum_type: String,
    pub enum_name: String,
    // Payload for tagged unions: stores the associated data
    // For now, supports Bool (1 byte) and I64 (8 bytes)
    pub payload: Option<Vec<u8>>,
    pub payload_type: Option<ValueType>,
}

// Scope stack for proper lexical scoping
#[derive(Debug, Clone, PartialEq)]
#[allow(dead_code)]
pub enum ScopeType {
    Global,      // Top-level module scope
    Function,    // Function body
    Block,       // Generic block (if, else, loop body)
    Catch,       // Catch block (for error handling)
}

#[derive(Clone)]
#[allow(dead_code)]
pub struct ScopeFrame {
    // maps variable names to their offsets in the arena
    pub arena_index: HashMap<String, usize>, // stores offsets

    // All declared symbols (types, constants, variables, and function names)
    // This is necessary for so called "context priming" or "declaration indexing"
    // aka declaring things in whatever order, aka not needing forward declarations
    // in theory it should only be needed for the "type" phase after the init context phase
    // but it can be convenient at times in eval or compile phases too, I guess.
    pub symbols: HashMap<String, SymbolInfo>,

    // All functions, with their function types, signatures and bodies (functions, methods, macros, etc).
    pub funcs: HashMap<String, SFuncDef>,

    // Enum type definitions (variants and associated data)
    pub enums: HashMap<String, SEnumDef>,

    // Struct type definitions (fields and associated constants [including functions, structs are namespaces, almost])
    pub structs: HashMap<String, SStructDef>,

    /// Scope type (helps with cleanup and debugging)
    pub scope_type: ScopeType,
}

#[derive(Clone)]
pub struct ScopeStack {
    /// Stack of scope frames
    pub frames: Vec<ScopeFrame>,
    /// Bug #97: Track all variable declarations in the current function by (name, line, col).
    /// Using location allows handling AST duplication from transformations like for-in desugaring,
    /// while still catching actual shadowing (same name at different source location).
    /// Uses Vec<FunctionLocal> with manual comparison for TIL compatibility (TIL's Set can't handle
    /// structs with Str fields, so both Rust and TIL use Vec with helper methods).
    pub function_locals: Vec<FunctionLocal>,
    /// Bug #101: Track which symbols have been used in the current function.
    pub used_symbols: HashSet<String>,
}

#[allow(dead_code)]
impl ScopeStack {
    pub fn new() -> Self {
        ScopeStack {
            frames: Vec::new(),
            function_locals: Vec::new(),
            used_symbols: HashSet::new(),
        }
    }

    pub fn push(&mut self, scope_type: ScopeType) {
        self.frames.push(ScopeFrame {
            arena_index: HashMap::new(),
            symbols: HashMap::new(),
            funcs: HashMap::new(),
            enums: HashMap::new(),
            structs: HashMap::new(),
            scope_type,
        });
    }

    pub fn pop(&mut self) -> Result<ScopeFrame, String> {
        if self.frames.len() <= 1 {
            return Err("Cannot pop global scope".to_string());
        }

        self.frames.pop()
            .ok_or_else(|| "Scope stack underflow".to_string())
    }

    pub fn lookup_var(&self, name: &str) -> Option<usize> {
        // Walk up the stack from innermost to outermost
        for frame in self.frames.iter().rev() {
            if let Some(offset) = frame.arena_index.get(name) {
                return Some(*offset);
            }
        }
        None
    }

    pub fn lookup_symbol(&self, name: &str) -> Option<&SymbolInfo> {
        for frame in self.frames.iter().rev() {
            if let Some(sym) = frame.symbols.get(name) {
                return Some(sym);
            }
        }
        None
    }

    /// Bug #101: Mark a symbol as used in the current function.
    pub fn mark_symbol_used(&mut self, name: &str) {
        self.used_symbols.insert(name.to_string());
    }

    /// Bug #101: Get all declared symbols in function_locals that are not in used_symbols
    /// and don't start with underscore.
    pub fn get_unused_symbols(&self) -> Vec<String> {
        let mut unused: Vec<String> = Vec::new();
        for local in &self.function_locals {
            if !local.name.starts_with('_') && !self.used_symbols.contains(&local.name) {
                // Avoid duplicates (same name at multiple locations)
                if !unused.contains(&local.name) {
                    unused.push(local.name.clone());
                }
            }
        }
        unused
    }

    /// Bug #97: Check if we're currently inside a function (not at global scope).
    pub fn is_inside_function(&self) -> bool {
        for frame in self.frames.iter().rev() {
            if frame.scope_type == ScopeType::Function {
                return true;
            }
        }
        false
    }

    /// Bug #97: Check if symbol exists in an ENCLOSING function scope (not current frame, not global).
    /// Searches from parent frame back to the nearest Function frame (inclusive).
    /// Used to detect variable shadowing - only errors if symbol is in an outer scope.
    pub fn lookup_symbol_in_enclosing_scope(&self, name: &str) -> Option<&SymbolInfo> {
        // Skip the current frame - we're looking for shadowing of outer variables
        for frame in self.frames.iter().rev().skip(1) {
            if let Some(sym) = frame.symbols.get(name) {
                return Some(sym);
            }
            // Stop at Function frame - don't search into global scope
            if frame.scope_type == ScopeType::Function {
                break;
            }
        }
        None
    }

    /// Bug #97: Check if a variable name was already declared at a DIFFERENT location in this function.
    /// Returns true if the name exists but at a different (line, col) - indicating actual shadowing.
    /// Returns false if same (name, line, col) exists - indicating AST duplication, not shadowing.
    pub fn is_shadowing_in_function(&self, name: &str, line: usize, col: usize) -> bool {
        // Check if any entry with same name but different location exists
        for local in &self.function_locals {
            if local.name == name && (local.line != line || local.col != col) {
                return true; // Same name at different location = shadowing
            }
        }
        false
    }

    /// Bug #97: Check if this exact declaration (name, line, col) was already processed.
    /// Used to detect AST duplication from transformations like for-in desugaring.
    pub fn is_already_processed(&self, name: &str, line: usize, col: usize) -> bool {
        let target = FunctionLocal { name: name.to_string(), line, col };
        for local in &self.function_locals {
            if local == &target {
                return true;
            }
        }
        false
    }

    /// Bug #97: Register a variable declaration in the current function.
    /// Call this when declaring a new variable.
    pub fn register_function_local(&mut self, name: &str, line: usize, col: usize) {
        let local = FunctionLocal { name: name.to_string(), line, col };
        // Only insert if not already present (set semantics)
        let mut already_exists = false;
        for existing in &self.function_locals {
            if existing == &local {
                already_exists = true;
                break;
            }
        }
        if !already_exists {
            self.function_locals.push(local);
        }
    }

    /// Bug #50: Check if accessing this symbol would require closure capture.
    /// Returns true if we're inside a nested function and the symbol is defined
    /// in an outer function scope (not global, not current function).
    pub fn is_closure_capture(&self, name: &str) -> bool {
        let mut function_boundaries_crossed = 0;
        let mut in_function = false;

        // Walk from innermost to outermost scope
        for frame in self.frames.iter().rev() {
            // Track when we enter/exit function scopes
            if frame.scope_type == ScopeType::Function {
                if in_function {
                    // We've crossed from one function into an outer function
                    function_boundaries_crossed += 1;
                } else {
                    in_function = true;
                }
            }

            // Check if symbol is in this frame
            if frame.symbols.contains_key(name) {
                // Symbol found - is it a closure capture?
                // It's a capture if:
                // 1. We've crossed at least one function boundary to get here
                // 2. We're not in global scope
                return function_boundaries_crossed > 0 && frame.scope_type != ScopeType::Global;
            }
        }
        false
    }

    pub fn declare_var(&mut self, name: String, offset: usize, symbol: SymbolInfo)
        -> Result<(), String>
    {
        let current_frame = self.frames.last_mut()
            .ok_or_else(|| "No active scope".to_string())?;

        // Check for redeclaration in current scope only
        // Bug #35: Skip check for "_" - it's special for discarding return values
        if name != "_" && current_frame.arena_index.contains_key(&name) {
            return Err(format!("Variable '{}' already declared in this scope", name));
        }

        current_frame.arena_index.insert(name.clone(), offset);
        current_frame.symbols.insert(name, symbol);
        Ok(())
    }

    pub fn declare_symbol(&mut self, name: String, symbol: SymbolInfo) {
        if let Some(current_frame) = self.frames.last_mut() {
            current_frame.symbols.insert(name, symbol);
        }
    }

    pub fn remove_symbol(&mut self, name: &str) -> Option<SymbolInfo> {
        if let Some(current_frame) = self.frames.last_mut() {
            current_frame.symbols.remove(name)
        } else {
            None
        }
    }

    pub fn remove_var(&mut self, name: &str) -> Option<usize> {
        if let Some(current_frame) = self.frames.last_mut() {
            current_frame.arena_index.remove(name)
        } else {
            None
        }
    }

    /// Insert a variable without a corresponding symbol (simpler than declare_var)
    pub fn insert_var(&mut self, name: String, offset: usize) {
        if let Some(current_frame) = self.frames.last_mut() {
            current_frame.arena_index.insert(name, offset);
        }
    }

    pub fn lookup_func(&self, name: &str) -> Option<&SFuncDef> {
        for frame in self.frames.iter().rev() {
            if let Some(func) = frame.funcs.get(name) {
                return Some(func);
            }
        }
        None
    }

    pub fn declare_func(&mut self, name: String, func_def: SFuncDef) {
        if let Some(current_frame) = self.frames.last_mut() {
            current_frame.funcs.insert(name, func_def);
        }
    }

    pub fn lookup_enum(&self, name: &str) -> Option<&SEnumDef> {
        for frame in self.frames.iter().rev() {
            if let Some(enum_def) = frame.enums.get(name) {
                return Some(enum_def);
            }
        }
        None
    }

    pub fn declare_enum(&mut self, name: String, enum_def: SEnumDef) {
        if let Some(current_frame) = self.frames.last_mut() {
            current_frame.enums.insert(name, enum_def);
        }
    }

    pub fn lookup_struct(&self, name: &str) -> Option<&SStructDef> {
        for frame in self.frames.iter().rev() {
            if let Some(struct_def) = frame.structs.get(name) {
                return Some(struct_def);
            }
        }
        None
    }

    /// Check if a combined name (e.g., "Color.Green") refers to an enum constructor
    pub fn is_enum_constructor(&self, combined_name: &str) -> bool {
        let parts: Vec<&str> = combined_name.split('.').collect();
        if parts.len() == 2 {
            let enum_type = parts[0];
            if let Some(enum_def) = self.lookup_enum(enum_type) {
                let variant_name = parts[1];
                return enum_def.contains_key(variant_name);
            }
        }
        false
    }

    /// Check if a combined name refers to a struct constructor
    pub fn is_struct_constructor(&self, combined_name: &str) -> bool {
        let parts: Vec<&str> = combined_name.split('.').collect();
        if parts.len() == 1 {
            return self.lookup_struct(parts[0]).is_some();
        }
        false
    }

    /// Check if a combined name refers to a type constructor (enum or struct)
    pub fn is_type_constructor(&self, combined_name: &str) -> bool {
        self.is_enum_constructor(combined_name) || self.is_struct_constructor(combined_name)
    }

    pub fn all_structs(&self) -> Vec<&SStructDef> {
        let mut result = Vec::new();
        for frame in self.frames.iter().rev() {
            for struct_def in frame.structs.values() {
                result.push(struct_def);
            }
        }
        result
    }

    pub fn declare_struct(&mut self, name: String, struct_def: SStructDef) {
        if let Some(current_frame) = self.frames.last_mut() {
            current_frame.structs.insert(name, struct_def);
        }
    }

    pub fn get_symbols_with_prefix(&self, prefix: &str) -> Vec<String> {
        // Collect all keys from all scopes that start with the given prefix
        let mut keys = Vec::new();
        for frame in &self.frames {
            for key in frame.symbols.keys() {
                if key.starts_with(prefix) {
                    keys.push(key.clone());
                }
            }
        }
        keys
    }

    pub fn get_all_struct_names(&self) -> Vec<String> {
        let mut names = Vec::new();
        for frame in &self.frames {
            for key in frame.structs.keys() {
                names.push(key.clone());
            }
        }
        names
    }
}

pub fn get_func_name_in_call(e: &Expr) -> String {
    if !matches!(e.node_type, NodeType::FCall(_)) {
        return e.exit_error("init", "get_func_name_in_call(): expected fcall node.")
    }
    if e.params.len() == 0 {
        return e.exit_error("init", "get_func_name_in_call(): fcall nodes must have at least 1 parameter.")
    }
    match &e.get(0) {
        Ok(param) => {
            match &param.node_type {
                NodeType::Identifier(f_name) => return f_name.clone(),
                node_type => return e.exit_error(
                    "init", &format!("in get_func_name_in_call(): Identifiers can only contain identifiers, found '{:?}'", node_type)),
            }
        },
        Err(error_str) => return error_str.to_string(),
    }
}

fn value_type_func_proc(path: &str, e: &Expr, name: &str, func_def: &SFuncDef) -> Result<ValueType, String> {
    match func_def.return_types.len() {
        0 => {
            return Err(e.error(path, "init", &format!("func '{}' does not return anything", name)));
        },
        1 => {
            match func_def.return_types.get(0) {
                Some(ValueType::TCustom(type_str)) => Ok(ValueType::TCustom(type_str.to_string())), // TODO find a better way
                Some(other) => Err(e.error(path, "init", &format!("func '{}' returns unsupported type {}", name, value_type_to_str(other)))),
                None => Err(e.lang_error(path, "init", &format!("func '{}' has inconsistent return type info", name))),
            }
        },
        _ => {
            return Err(e.todo_error(path, "init", &format!("func '{}' returns multiple values", name)));
        },
    }
}

fn get_ufcs_fcall_value_type(context: &Context, e: &Expr, f_name: &String, id_expr: &Expr, symbol: &SymbolInfo) -> Result<ValueType, String> {
    if id_expr.params.is_empty() {
        return Err(e.error(&context.path, "init", &format!("Cannot call '{}', it is not a function or struct, it is a '{}'",
                                            &f_name, value_type_to_str(&symbol.value_type))));
    }

    // Get the last param (the method name)
    let method_name_expr = match id_expr.params.last() {
        Some(expr) => expr,
        None => return Err(e.lang_error(&context.path, "init", "Expected method name in UFCS call")),
    };

    let method_name = match &method_name_expr.node_type {
        NodeType::Identifier(name) => name,
        _ => return Err(e.error(&context.path, "init", &format!("Expected identifier for method name, found '{:?}'", method_name_expr.node_type))),
    };

    // Check if it's a regular function
    if let Some(func_def) = context.scope_stack.lookup_func(method_name) {
        return value_type_func_proc(&context.path, &e, &f_name, func_def)
    }

    // Create identifier expression without the last param (method name) to get the type
    let mut id_without_method = id_expr.clone();
    id_without_method.params.pop();

    // Get the type of the nested identifier
    let target_type = get_value_type(context, &id_without_method)?;

    // Check if it's an associated function for this type
    match &target_type {
        ValueType::TCustom(custom_type_name) => {
            let id_expr_name = format!("{}.{}", custom_type_name, method_name);
            if let Some(func_def) = context.scope_stack.lookup_func(&id_expr_name) {
                return value_type_func_proc(&context.path, &e, &id_expr_name, &func_def);
            }
            return Err(e.error(&context.path, "init", &format!("Type '{}' has no method '{}'", custom_type_name, method_name)));
        },
        _ => {
            return Err(e.error(&context.path, "init", &format!("'{}' of type '{}' doesn't support methods", f_name, value_type_to_str(&target_type))));
        }
    }
}

fn get_fcall_value_type(context: &Context, e: &Expr) -> Result<ValueType, String> {

    let f_name = get_func_name_in_call(&e);

    // Check if this is a UFCS call on a function/expression result
    // If e has 2+ params (func name + target + args), check if the target's type
    // has an associated method with this name, prioritizing it over standalone functions
    if e.params.len() >= 2 {
        let first_arg = e.get(1)?;  // Get the UFCS target (skip func name at index 0)

        // Try to get the type of the first argument
        if let Ok(target_type) = get_value_type(context, first_arg) {
            if let ValueType::TCustom(custom_type_name) = target_type {
                // Check if this type has an associated method with this name
                let method_name = format!("{}.{}", custom_type_name, f_name);
                if let Some(func_def) = context.scope_stack.lookup_func(&method_name) {
                    // UFCS method exists! Use it instead of standalone function
                    return value_type_func_proc(&context.path, &e, &method_name, func_def);
                }
            }
        }
        // If we couldn't determine type or no associated method exists, fall through
    }

    // Original logic: check for standalone function
    if let Some(func_def) = context.scope_stack.lookup_func(&f_name) {
        return value_type_func_proc(&context.path, &e, &f_name, func_def)
    } else if let Some(symbol) = context.scope_stack.lookup_symbol(&f_name) {

        let id_expr = e.get(0)?;
        match &symbol.value_type {
            ValueType::TType(TTypeDef::TStructDef) => {
                let struct_def = match context.scope_stack.lookup_struct(&f_name) {
                    Some(_struct_def) => _struct_def,
                    None => {
                        return Err(e.lang_error(&context.path, "init", &format!("struct '{}' not found in context", f_name)));
                    },
                };
                let after_dot = match id_expr.params.get(0) {
                    Some(_after_dot) => _after_dot,
                    None => {
                        // Constructor: MyStruct() or MyStruct(field=value, ...)
                        // Check that all args are NamedArg (struct literals require named args)
                        if e.params.len() > 1 {
                            for arg in e.params.iter().skip(1) {
                                if !matches!(&arg.node_type, NodeType::NamedArg(_)) {
                                    return Err(arg.error(&context.path, "init", &format!(
                                        "Struct literal '{}' requires named arguments (e.g., {}(x=10, y=20)). Positional arguments are not allowed.",
                                        f_name, f_name)));
                                }
                            }
                        }
                        return Ok(ValueType::TCustom(f_name.clone()));
                    },
                };
                match &after_dot.node_type {
                    NodeType::Identifier(after_dot_name) => {
                        // First check if this is a namespace member (Issue #108)
                        let namespace_full_name = format!("{}.{}", f_name, after_dot_name);
                        if context.scope_stack.lookup_symbol(&namespace_full_name).is_some() {
                            // If it's a function, get the return type
                            if let Some(func_def) = context.scope_stack.lookup_func(&namespace_full_name) {
                                return value_type_func_proc(&context.path, e, &namespace_full_name, &func_def);
                            }
                            // Otherwise return the symbol's value type
                            if let Some(symbol_info) = context.scope_stack.lookup_symbol(&namespace_full_name) {
                                return Ok(symbol_info.value_type.clone());
                            }
                        }

                        let member_decl = struct_def.get_member_or_err(after_dot_name, &f_name, &context.path, e)?;
                        let member_default_value = match struct_def.default_values.get(after_dot_name) {
                            Some(_member) => _member,
                            None => {
                                return Err(e.error(&context.path, "init", &format!("struct '{}' has no member '{}' b", f_name, after_dot_name)));
                            },
                        };
                        match &member_default_value.node_type {
                            NodeType::FuncDef(func_def) => {
                                let combined_name = format!("{}.{}", f_name, after_dot_name);
                                return value_type_func_proc(&context.path, &e, &combined_name, &func_def);
                            },
                            _  => {
                                return Err(e.error(&context.path, "init", &format!("Cannot call '{}.{}', it is not a function, it is '{}'",
                                                                    f_name, after_dot_name, value_type_to_str(&member_decl.value_type))));
                            },
                        }
                    },
                    _ => {
                        return Err(e.lang_error(&context.path, "init", &format!("Expected identifier after '{}.' found '{:?}'", f_name, after_dot.node_type)));
                    },
                }
            },
            ValueType::TType(TTypeDef::TEnumDef) => {
                // Handle enum constructor calls like Color.Green(true)
                let enum_def = match context.scope_stack.lookup_enum(&f_name) {
                    Some(_enum_def) => _enum_def,
                    None => {
                        return Err(e.lang_error(&context.path, "init", &format!("enum '{}' not found in context", f_name)));
                    },
                };
                let enum_after_dot_expr = match id_expr.params.get(0) {
                    Some(_after_dot) => _after_dot,
                    None => {
                        // Just referencing the enum type itself, not constructing
                        return Ok(ValueType::TType(TTypeDef::TEnumDef));
                    },
                };
                match &enum_after_dot_expr.node_type {
                    NodeType::Identifier(variant_name) => {
                        // First check if this is a namespace member (Issue #108)
                        let namespace_full_name = format!("{}.{}", f_name, variant_name);
                        if context.scope_stack.lookup_symbol(&namespace_full_name).is_some() {
                            // If it's a function, get the return type
                            if let Some(func_def) = context.scope_stack.lookup_func(&namespace_full_name) {
                                return value_type_func_proc(&context.path, e, &namespace_full_name, &func_def);
                            }
                            // Otherwise return the symbol's value type
                            if let Some(symbol_info) = context.scope_stack.lookup_symbol(&namespace_full_name) {
                                return Ok(symbol_info.value_type.clone());
                            }
                        }

                        // Check if this variant exists in the enum
                        let variant_type = match enum_def.get(variant_name) {
                            Some(_variant) => _variant,
                            None => {
                                return Err(e.error(&context.path, "init", &format!("enum '{}' has no variant '{}'", f_name, variant_name)));
                            },
                        };

                        // Validate argument count based on whether the variant expects a payload
                        match variant_type {
                            Some(payload_type) => {
                                // This variant expects a payload
                                if e.params.len() < 2 {
                                    return Err(e.error(&context.path, "init", &format!("Enum constructor {}.{} expects a payload of type {}", f_name, variant_name, value_type_to_str(payload_type))));
                                }
                                // Type check the payload argument
                                let payload_expr = e.get(1)?;
                                let payload_actual_type = get_value_type(context, payload_expr)?;

                                // Verify payload type matches expected type
                                if payload_actual_type != *payload_type {
                                    return Err(e.error(&context.path, "init", &format!(
                                        "Enum constructor {}.{} expects payload of type {}, but got {}",
                                        f_name, variant_name,
                                        value_type_to_str(payload_type),
                                        value_type_to_str(&payload_actual_type)
                                    )));
                                }
                            },
                            None => {
                                // This variant doesn't have a payload
                                if e.params.len() > 1 {
                                    return Err(e.error(&context.path, "init", &format!("Enum variant {}.{} does not take a payload", f_name, variant_name)));
                                }
                            },
                        }

                        // Return the enum type
                        return Ok(ValueType::TCustom(f_name.clone()));
                    },
                    _ => {
                        return Err(e.lang_error(&context.path, "init", &format!("Expected identifier after '{}.' found '{:?}'", f_name, enum_after_dot_expr.node_type)));
                    },
                }
            },
            ValueType::TCustom(custom_type_name) => {
                // Check if it's an enum first
                if context.scope_stack.lookup_enum(custom_type_name).is_some() {
                    // It's an enum - try UFCS method call
                    let enum_after_dot = match id_expr.params.get(0) {
                        Some(_after_dot) => _after_dot,
                        None => {
                            return Ok(ValueType::TCustom(f_name.clone()));
                        },
                    };
                    match &enum_after_dot.node_type {
                        NodeType::Identifier(enum_after_dot_name) => {
                            // Try associated method first
                            let enum_method_name = format!("{}.{}", custom_type_name, enum_after_dot_name);
                            if let Some(func_def) = context.scope_stack.lookup_func(&enum_method_name) {
                                return value_type_func_proc(&context.path, &e, &enum_method_name, func_def);
                            }

                            // Fall back to UFCS: try standalone function with enum as first arg
                            match get_ufcs_fcall_value_type(&context, &e, &f_name, id_expr, symbol) {
                                Ok(ok_val) => return Ok(ok_val),
                                Err(_) => {
                                    return Err(e.error(&context.path, "init", &format!("enum '{}' has no method '{}' and no matching function found for UFCS", custom_type_name, enum_after_dot_name)));
                                },
                            }
                        },
                        _ => {
                            return Err(e.lang_error(&context.path, "init", &format!("Expected identifier after '{}.' found '{:?}'", f_name, enum_after_dot.node_type)));
                        },
                    }
                }

                // Not an enum, try struct
                let custom_struct_def = match context.scope_stack.lookup_struct(custom_type_name) {
                    Some(_struct_def) => _struct_def,
                    None => {
                        return Err(e.lang_error(&context.path, "init", &format!("type '{}' not found in context", f_name)));
                    },
                };
                let struct_after_dot = match id_expr.params.get(0) {
                    Some(_after_dot) => _after_dot,
                    None => {
                        return Ok(ValueType::TCustom(f_name.clone()));
                    },
                };
                match &struct_after_dot.node_type {
                    NodeType::Identifier(struct_after_dot_name) => {
                        // Bug #10 fix: Check if we have a multi-level chain like struct.field.method
                        // If id_expr.params has 2+ elements, try to resolve all-but-last as field access
                        if id_expr.params.len() >= 2 {
                            // Try to resolve the field access chain (all params except the last)
                            // Example: for e.params.len, resolve "e.params" to get its type
                            let mut field_access_expr = id_expr.clone();
                            field_access_expr.params.pop(); // Remove the last element (method/property name)

                            if let Ok(intermediate_type) = get_value_type(context, &field_access_expr) {
                                // Successfully resolved intermediate field access
                                // Now check if the last param is a member/method of that type
                                let last_param = id_expr.params.last().unwrap();
                                if let NodeType::Identifier(final_member_name) = &last_param.node_type {
                                    match &intermediate_type {
                                        ValueType::TCustom(intermediate_type_name) => {
                                            // First check if it's a method on this type
                                            let intermediate_method_name = format!("{}.{}", intermediate_type_name, final_member_name);
                                            if let Some(func_def) = context.scope_stack.lookup_func(&intermediate_method_name) {
                                                return value_type_func_proc(&context.path, &e, &intermediate_method_name, func_def);
                                            }

                                            // Try UFCS: standalone function with intermediate type as first arg
                                            if let Some(func_def) = context.scope_stack.lookup_func(final_member_name) {
                                                return value_type_func_proc(&context.path, &e, final_member_name, func_def);
                                            }

                                            // Check if it's a struct with this member as a field
                                            if let Some(intermediate_struct_def) = context.scope_stack.lookup_struct(intermediate_type_name) {
                                                if let Some(intermediate_member_decl) = intermediate_struct_def.get_member(final_member_name) {
                                                    // It's a field access - return the field's type
                                                    return Ok(intermediate_member_decl.value_type.clone());
                                                }
                                            }
                                        },
                                        _ => {
                                            // Intermediate type is not a custom type, fall through
                                        }
                                    }
                                }
                            }
                        }

                        // Original logic: single-level access (struct.member)
                        let direct_member_decl = match custom_struct_def.get_member(struct_after_dot_name) {
                            Some(_member) => _member,
                            None => {
                                match get_ufcs_fcall_value_type(&context, &e, &f_name, id_expr, symbol) {
                                    Ok(ok_val) => return Ok(ok_val),
                                    Err(error_string) => {
                                        println!("{}", error_string);
                                        return Err(e.error(&context.path, "init", &format!("struct '{}' has no member '{}' c", custom_type_name, struct_after_dot_name)));
                                    },
                                }
                            },
                        };
                        let direct_member_default_value = match custom_struct_def.default_values.get(struct_after_dot_name) {
                            Some(_member) => _member,
                            None => {
                                return Err(e.error(&context.path, "init", &format!("struct '{}' has no member '{}' d", custom_type_name, struct_after_dot_name)));
                            },
                        };
                        match &direct_member_default_value.node_type {
                            NodeType::FuncDef(func_def) => {
                                let struct_combined_name = format!("{}.{}", custom_type_name, struct_after_dot_name);
                                return value_type_func_proc(&context.path, &e, &struct_combined_name, &func_def);
                            },
                            _  => {
                                return Err(e.error(&context.path, "init", &format!("Cannot call '{}.{}', it is not a function, it is '{}'",
                                                                    f_name, struct_after_dot_name, value_type_to_str(&direct_member_decl.value_type))));
                            },
                        }
                    },

                    _ => {
                        return Err(e.lang_error(&context.path, "init", &format!("Expected identifier after '{}.' found '{:?}'", f_name, struct_after_dot.node_type)));
                    },
                }
            },
            ValueType::TMulti(_) => {
                // Variadic parameters are implemented as Array at runtime
                // Treat them as Array for type checking method calls
                let variadic_type_name = "Array";
                let variadic_struct_def = match context.scope_stack.lookup_struct(variadic_type_name) {
                    Some(_struct_def) => _struct_def,
                    None => {
                        return Err(e.lang_error(&context.path, "init", &format!("struct '{}' not found in context", variadic_type_name)));
                    },
                };
                let variadic_after_dot = match id_expr.params.get(0) {
                    Some(_after_dot) => _after_dot,
                    None => {
                        return Ok(ValueType::TCustom(variadic_type_name.to_string()));
                    },
                };
                match &variadic_after_dot.node_type {
                    NodeType::Identifier(variadic_after_dot_name) => {
                        let variadic_member_decl = match variadic_struct_def.get_member(variadic_after_dot_name) {
                            Some(_member) => _member,
                            None => {
                                match get_ufcs_fcall_value_type(&context, &e, &f_name, id_expr, symbol) {
                                    Ok(ok_val) => return Ok(ok_val),
                                    Err(error_string) => {
                                        println!("{}", error_string);
                                        return Err(e.error(&context.path, "init", &format!("struct '{}' has no member '{}' (variadic)", variadic_type_name, variadic_after_dot_name)));
                                    },
                                }
                            },
                        };
                        let variadic_member_default_value = match variadic_struct_def.default_values.get(variadic_after_dot_name) {
                            Some(_member) => _member,
                            None => {
                                return Err(e.error(&context.path, "init", &format!("struct '{}' has no member '{}' (variadic default)", variadic_type_name, variadic_after_dot_name)));
                            },
                        };
                        match &variadic_member_default_value.node_type {
                            NodeType::FuncDef(func_def) => {
                                let variadic_combined_name = format!("{}.{}", variadic_type_name, variadic_after_dot_name);
                                return value_type_func_proc(&context.path, &e, &variadic_combined_name, &func_def);
                            },
                            _  => {
                                return Err(e.error(&context.path, "init", &format!("Cannot call '{}.{}', it is not a function, it is '{}'",
                                                                    variadic_type_name, variadic_after_dot_name, value_type_to_str(&variadic_member_decl.value_type))));
                            },
                        }
                    },

                    _ => {
                        return Err(e.lang_error(&context.path, "init", &format!("Expected identifier after '{}.' found '{:?}'", f_name, variadic_after_dot.node_type)));
                    },
                }
            },
            _ => {
                return get_ufcs_fcall_value_type(&context, &e, &f_name, id_expr, symbol)
            },
        }

    } else {
        return Err(e.error(&context.path, "init", &format!("Undefined symbol '{}'", &f_name)));
    }
}

pub fn get_value_type(context: &Context, e: &Expr) -> Result<ValueType, String> {
    match &e.node_type {
        NodeType::LLiteral(Literal::Number(_)) => Ok(ValueType::TCustom("I64".to_string())),
        NodeType::LLiteral(Literal::Str(_)) => Ok(ValueType::TCustom("Str".to_string())),
        NodeType::LLiteral(Literal::List(_)) => Ok(ValueType::TCustom("List".to_string())),
        NodeType::FuncDef(func_def) => match func_def.function_type {
            FunctionType::FTFunc | FunctionType::FTFuncExt => Ok(ValueType::TFunction(FunctionType::FTFunc)),
            FunctionType::FTProc | FunctionType::FTProcExt => Ok(ValueType::TFunction(FunctionType::FTProc)),
            FunctionType::FTMacro => Ok(ValueType::TFunction(FunctionType::FTMacro)),
        },
        NodeType::EnumDef(_) => Ok(ValueType::TType(TTypeDef::TEnumDef)),
        NodeType::StructDef(_) => Ok(ValueType::TType(TTypeDef::TStructDef)),
        NodeType::FCall(_) => get_fcall_value_type(context, e),
        NodeType::Range => Ok(ValueType::TCustom(format!("{}Range", value_type_to_str(&get_value_type(&context, e.get(0)?)?)))),

        NodeType::Identifier(name) => {
            // Bug #32 fix: Handle field access on expression results
            // When name is "_" and params[0] is an FCall, get the type of that expression first,
            // then traverse the field access chain in params[1..]
            if name == "_" && !e.params.is_empty() {
                // Get the type of the base expression (params[0])
                let base_expr = e.get(0)?;
                let mut underscore_current_type = get_value_type(context, base_expr)?;

                // Traverse the field access chain in params[1..]
                for field_idx in 1..e.params.len() {
                    let field_expr = e.get(field_idx)?;
                    let field_name = match &field_expr.node_type {
                        NodeType::Identifier(n) => n,
                        _ => return Err(e.error(&context.path, "init", "Expected identifier in field access chain")),
                    };

                    match &underscore_current_type {
                        ValueType::TCustom(type_name) => {
                            if let Some(underscore_struct_def) = context.scope_stack.lookup_struct(type_name) {
                                if let Some(member) = underscore_struct_def.get_member(field_name) {
                                    underscore_current_type = member.value_type.clone();
                                } else {
                                    return Err(e.error(&context.path, "init", &format!("Struct '{}' has no member '{}'", type_name, field_name)));
                                }
                            } else {
                                return Err(e.error(&context.path, "init", &format!("'{}' is not a struct", type_name)));
                            }
                        },
                        _ => return Err(e.error(&context.path, "init", &format!("Cannot access fields on type '{}'", value_type_to_str(&underscore_current_type)))),
                    }
                }

                return Ok(underscore_current_type);
            }

            let mut id_current_type = match context.scope_stack.lookup_symbol(name) {
                Some(symbol_info_m) => {
                    symbol_info_m.value_type.clone()
                },
                None => return Err(e.error(&context.path, "init", &format!("Undefined symbol '{}'", name))),
            };

            // If there are no parameters, just return the type of the first identifier
            if e.params.is_empty() {
                return Ok(id_current_type);
            }

            // Now, process each nested member.
            for cursor in &e.params {
                let member_name = match &cursor.node_type {
                    NodeType::Identifier(n) => n,
                    node_type => return Err(e.lang_error(&context.path, "init", &format!("Identifiers can only contain identifiers, found '{:?}'", node_type))),
                };

                match &id_current_type {
                    ValueType::TType(TTypeDef::TStructDef) => {
                        // If it's a struct, resolve its member
                        let type_struct_def = context.scope_stack.lookup_struct(name)
                            .ok_or_else(|| e.error(&context.path, "init", &format!("Struct '{}' not found", name)))?;

                        let type_decl = type_struct_def.get_member_or_err(member_name, name, &context.path, e)?;
                        id_current_type = type_decl.value_type.clone();
                    },
                    ValueType::TType(TTypeDef::TEnumDef) => {
                        // If it's an enum, resolve the variant
                        let nested_enum_def = context.scope_stack.lookup_enum(name)
                            .ok_or_else(|| e.error(&context.path, "init", &format!("Enum '{}' not found", name)))?;

                        if nested_enum_def.contains_key(member_name) {
                            return Ok(ValueType::TCustom(name.to_string()));
                        } else {
                            return Err(e.error(&context.path, "init", &format!("Enum '{}' has no value '{}'", name, member_name)));
                        }
                    },
                    ValueType::TCustom(nested_custom_type_name) => {
                        // If it's a custom type (a struct), resolve the member
                        let nested_struct_def = context.scope_stack.lookup_struct(nested_custom_type_name)
                            .ok_or_else(|| e.error(&context.path, "init", &format!("Struct '{}' not found", nested_custom_type_name)))?;

                        let nested_decl = nested_struct_def.get_member_or_err(member_name, nested_custom_type_name, &context.path, e)?;
                        id_current_type = nested_decl.value_type.clone();
                    },
                    ValueType::TMulti(_variadic_type_name) => {
                        // Variadic parameters are implemented as Array at runtime
                        id_current_type = ValueType::TCustom("Array".to_string());
                    },
                    _ => {
                        return Err(e.error(&context.path, "init", &format!("'{}' of type '{}' can't have members", name, value_type_to_str(&id_current_type))));
                    }
                }
            }

            Ok(id_current_type) // Return the type of the last field (x)
        },

        NodeType::Pattern(PatternInfo { variant_name, .. }) => {
            // Extract enum type from "EnumType.Variant" format
            if let Some(dot_pos) = variant_name.rfind('.') {
                let enum_type = &variant_name[..dot_pos];
                Ok(ValueType::TCustom(enum_type.to_string()))
            } else {
                // If no dot, assume the whole thing is the enum type (shouldn't happen in practice)
                Ok(ValueType::TCustom(variant_name.clone()))
            }
        },

        NodeType::NamedArg(_) => {
            // Named argument - return the type of the value expression
            if !e.params.is_empty() {
                get_value_type(context, &e.params[0])
            } else {
                Err(e.error(&context.path, "init", "NamedArg must have a value expression"))
            }
        },

        node_type => return Err(e.error(&context.path, "init", &format!("get_value_type() not implemented for {:?} yet.", node_type))),
    }
}

// Convert dot-based import path to OS-specific file path
// Example: "std.io" -> "src/std/io.til" (Unix) or "src\std\io.til" (Windows)
// Auto-prefixes with "src."
pub fn import_path_to_file_path(import_path: &str) -> String {
    let full_path = format!("src.{}", import_path);
    let file_path = full_path.replace(".", std::path::MAIN_SEPARATOR_STR);
    format!("{}.til", file_path)
}

// Import declarations only (no eval) - for init phase
// This processes imports during declaration indexing, copying only declarations
// to the parent context. The typer and eval phases will use the stored AST.
pub fn init_import_declarations(context: &mut Context, e: &Expr, import_path_str: &str) -> Result<(), String> {
    let path = import_path_to_file_path(import_path_str);
    let original_path = context.path.clone();

    // Already done (or in progress)? Skip.
    // Adding to done at START handles both circular imports and re-imports.
    if context.imports_init_done.contains(&path) {
        return Ok(());
    }

    // Mark as done immediately - before processing - to handle circular imports
    context.imports_init_done.insert(path.clone());

    // Read and parse the imported file
    let source: String = match fs::read_to_string(&path) {
        Ok(file) => file,
        Err(error) => {
            return match error.kind() {
                ErrorKind::NotFound => Err(e.error(&context.path, "import", &format!("File '{}' not found", path))),
                other_error => Err(e.error(&context.path, "import", &format!("Problem reading file '{}': {}", path, other_error))),
            };
        },
    };

    context.path = path.clone();

    // Lex the imported file
    let mut lexer = match lexer_from_source(&path, source) {
        Ok(lexer) => lexer,
        Err(error_string) => {
            let orig_path_clone = original_path.clone();
            context.path = original_path;
            return Err(e.error(&context.path, "import", &format!("While trying to import {} from {}:\n{}",
                                                  path, orig_path_clone, error_string)));
        },
    };

    // Parse mode
    let mode = match parse_mode(&path, &mut lexer) {
        Ok(mode_) => mode_,
        Err(error_string) => {
            let orig_path_clone = original_path.clone();
            context.path = original_path;
            return Err(e.error(&context.path, "import", &format!("While trying to import {} from {}:\n{}",
                                                  path, orig_path_clone, error_string)));
        },
    };

    // Check if mode can be imported
    if !can_be_imported(&mode) {
        context.path = original_path;
        return Err(e.error(&context.path, "import", &format!("file '{}' of mode '{}' cannot be imported", path, mode.name)));
    }

    let previous_mode = context.mode_def.clone();
    context.mode_def = mode;

    // Process mode imports recursively
    for import_str in context.mode_def.imports.clone() {
        let import_func_name_expr = Expr{node_type: NodeType::Identifier("import".to_string()), params: Vec::new(), line: 0, col: 0};
        let import_path_expr = Expr{node_type: NodeType::LLiteral(Literal::Str(import_str.to_string())), params: Vec::new(), line: 0, col: 0};
        let import_fcall_expr = Expr{node_type: NodeType::FCall(false), params: vec![import_func_name_expr, import_path_expr], line: 0, col: 0};
        if let Err(error_string) = init_import_declarations(context, &import_fcall_expr, &import_str) {
            context.mode_def = previous_mode;
            context.path = original_path;
            return Err(error_string);
        }
    }

    // Parse to AST
    let imported_ast: Expr = match parse_tokens(&mut lexer) {
        Ok(expr) => expr,
        Err(error_string) => {
            context.mode_def = previous_mode;
            let orig_path_clone = original_path.clone();
            context.path = original_path;
            return Err(e.error(&context.path, "import", &format!("While trying to import {} from {}:\n{}",
                                                  path, orig_path_clone, error_string)));
        },
    };

    // Run init_context to extract declarations
    // This will recursively handle any imports in the imported file
    let errors = init_context(context, &imported_ast);
    if errors.len() > 0 {
        context.mode_def = previous_mode;
        let orig_path_clone = original_path.clone();
        context.path = original_path;
        let mut error_msg = format!("While trying to import {} from {}:\n", path, orig_path_clone);
        for err in &errors {
            error_msg.push_str(&format!("{}:{}\n", path, err));
        }
        return Err(error_msg);
    }

    // Store AST and mode for typer and eval phases
    context.imported_asts.insert(path.clone(), imported_ast);
    context.imported_modes.insert(path.clone(), context.mode_def.clone());

    // Restore context state
    context.mode_def = previous_mode;
    context.path = original_path;

    Ok(())
}

// aka "context priming" or "declaration indexing"
pub fn init_context(context: &mut Context, e: &Expr) -> Vec<String> {
    let mut errors : Vec<String> = Vec::new();
    match &e.node_type {
        NodeType::Body => {
            for se in &e.params {
                errors.extend(init_context(context, &se));
            }
        },
        NodeType::FCall(_) => {
            let f_name = get_func_name_in_call(&e);
            if f_name == "import" {
                // Extract import path (must be literal string)
                let import_path_expr = match e.get(1) {
                    Ok(import_path_expr_) => import_path_expr_,
                    Err(err) => {
                        errors.push(e.exit_error("import", &format!("{}:{}", context.path, err)));
                        return errors
                    },
                };
                let import_path = match &import_path_expr.node_type {
                    NodeType::LLiteral(import_path_str_lit_expr) => match import_path_str_lit_expr {
                        Literal::Str(import_path_) => import_path_,
                        literal_type => {
                            errors.push(import_path_expr.exit_error("import", &format!("Expected literal 'Str' for import, found literal '{:?}'",
                                                                                       literal_type)));
                            return errors
                        },

                    },
                    import_node_type => {
                        errors.push(import_path_expr.exit_error("import", &format!("Expected literal Str for import, found '{:?}'",
                                                                                   import_node_type)));
                        return errors
                    },
                };

                // Process import declarations (no eval)
                match init_import_declarations(context, &e, import_path) {
                    Ok(_) => {},
                    Err(err) => {
                        errors.push(err);
                        return errors;
                    },
                }
            }
        },
        NodeType::Declaration(decl) => {
            // Bug #35: Skip "already declared" check for "_" - it's special for discarding return values
            if decl.name != "_" && (context.scope_stack.lookup_func(&decl.name).is_some() || context.scope_stack.lookup_symbol(&decl.name).is_some()) {
                errors.push(e.error(&context.path, "init", &format!("'{}' already declared.", decl.name)));
            }
            if e.params.len() != 1 {
                errors.push(e.exit_error("init", &format!("in init_context, while declaring {}, declarations must take exactly one value.", decl.name)));
                return errors
            }
            let inner_e = match e.get(0) {
                Ok(inner_e_) => inner_e_,
                Err(error_str) => {
                    errors.push(error_str);
                    return errors
                },
            };
            let mut value_type = match get_value_type(&context, &inner_e) {
                Ok(val_type) => val_type,
                Err(error_string) => {
                    errors.push(error_string);
                    return errors;
                },
            };
            if decl.value_type != str_to_value_type(INFER_TYPE) {
                if decl.value_type == ValueType::TCustom("U8".to_string()) && value_type == ValueType::TCustom("I64".to_string()) {
                    value_type = decl.value_type.clone();
                } else if value_type != decl.value_type {
                    errors.push(e.error(&context.path, "init", &format!("'{}' declared of type '{}' but initialized to type '{}'.",
                                                         decl.name, value_type_to_str(&decl.value_type), value_type_to_str(&value_type))));
                }
            }
            match value_type {
                ValueType::TFunction(ref ftype) => match ftype {
                    FunctionType::FTFunc | FunctionType::FTFuncExt |
                    FunctionType::FTProc | FunctionType::FTProcExt |
                    FunctionType::FTMacro => {
                        match &inner_e.node_type {
                            NodeType::FuncDef(func_def) => {
                                context.scope_stack.declare_symbol(decl.name.to_string(), SymbolInfo{value_type: value_type.clone(), is_mut: decl.is_mut, is_copy: decl.is_copy, is_own: decl.is_own, is_comptime_const: false });
                                context.scope_stack.declare_func(decl.name.to_string(), func_def.clone());
                            },
                            _ => {
                                errors.push(e.lang_error(&context.path, "init", &format!("{}s should have definitions", value_type_to_str(&value_type))));
                                return errors;
                            },
                        }
                    }
                },

                ValueType::TType(TTypeDef::TEnumDef) => {
                    if inner_e.params.len() != 0 {
                        errors.push(e.exit_error("init", &format!("while declaring {}: enum declarations don't have any parameters in the tree.",
                                                                  decl.name)));
                        return errors
                    }
                    match &inner_e.node_type {
                        NodeType::EnumDef(enum_def) => {
                            context.scope_stack.declare_symbol(decl.name.to_string(), SymbolInfo{value_type: value_type.clone(), is_mut: decl.is_mut, is_copy: decl.is_copy, is_own: decl.is_own, is_comptime_const: false });
                            context.scope_stack.declare_enum(decl.name.to_string(), enum_def.clone());
                        },
                        _ => {
                            errors.push(e.lang_error(&context.path, "init", "enums should have definitions."));
                            return errors;
                        },
                    }
                },

                ValueType::TType(TTypeDef::TStructDef) => {
                    if inner_e.params.len() != 0 {
                        errors.push(e.exit_error("init", &format!("while declaring {}, struct declarations must have exactly 0 params.",
                                                                  decl.name)));
                        return errors
                    }
                    match &inner_e.node_type {
                        NodeType::StructDef(struct_def) => {
                            // Check for directly recursive struct (infinite size)
                            for member_decl in &struct_def.members {
                                if let ValueType::TCustom(ref member_type_name) = member_decl.value_type {
                                    if member_type_name == &decl.name {
                                        errors.push(e.error(&context.path, "init", &format!(
                                            "recursive type '{}' has infinite size\n  --> field '{}' is recursive without indirection\nhelp: insert some indirection (e.g., a Ptr or Vec) to break the cycle",
                                            decl.name, member_decl.name
                                        )));
                                        return errors;
                                    }
                                }
                            }
                            // Register the struct itself
                            context.scope_stack.declare_symbol(decl.name.to_string(), SymbolInfo { value_type: value_type.clone(), is_mut: decl.is_mut, is_copy: decl.is_copy, is_own: decl.is_own, is_comptime_const: false });
                            context.scope_stack.declare_struct(decl.name.to_string(), struct_def.clone());
                            // Register associated funcs and constants (non-mut members only)
                            for member_decl in &struct_def.members {
                                if !member_decl.is_mut {
                                    // Try to find a default_value (required for funcs/consts)
                                    if let Some(member_expr) = struct_def.default_values.get(&member_decl.name) {
                                        let member_value_type = get_value_type(&context, member_expr).unwrap_or(ValueType::TCustom(INFER_TYPE.to_string()));
                                        let full_name = format!("{}.{}", decl.name, member_decl.name); // Note: using '.' not '::'
                                        // Register in symbols
                                        context.scope_stack.declare_symbol(full_name.clone(), SymbolInfo { value_type: member_value_type.clone(), is_mut: member_decl.is_mut, is_copy: member_decl.is_copy, is_own: member_decl.is_own, is_comptime_const: false });
                                        // If it's a function, also register in funcs
                                        if let NodeType::FuncDef(func_def) = &member_expr.node_type {
                                            context.scope_stack.declare_func(full_name, func_def.clone());
                                        }
                                    }
                                }
                            }
                        },
                        _ => {
                            errors.push(e.lang_error(&context.path, "init", "struct declarations should have definitions."));
                            return errors;
                        },
                    }
                }

                ValueType::TMulti(_) | ValueType::TCustom(_) => {
                    context.scope_stack.declare_symbol(decl.name.to_string(), SymbolInfo{value_type: value_type.clone(), is_mut: decl.is_mut, is_copy: decl.is_copy, is_own: decl.is_own, is_comptime_const: false });
                },
            }
        }
        NodeType::NamespaceDef(namespace_def) => {
            // Verify the type exists (either struct or enum)
            let type_name = &namespace_def.type_name;
            let type_exists = context.scope_stack.lookup_struct(type_name).is_some()
                || context.scope_stack.lookup_enum(type_name).is_some();

            if !type_exists {
                errors.push(e.error(&context.path, "init", &format!(
                    "namespace '{}' refers to undefined type. Define the struct or enum first.",
                    type_name
                )));
                return errors;
            }

            // Register namespace members as TypeName.member_name
            for member_decl in &namespace_def.members {
                if !member_decl.is_mut {
                    // Get the member's expression (required for funcs/consts in namespaces)
                    if let Some(member_expr) = namespace_def.default_values.get(&member_decl.name) {
                        let member_value_type = get_value_type(&context, member_expr).unwrap_or(ValueType::TCustom(INFER_TYPE.to_string()));
                        let full_name = format!("{}.{}", type_name, member_decl.name);

                        // Check for duplicate
                        if context.scope_stack.lookup_symbol(&full_name).is_some() {
                            errors.push(e.error(&context.path, "init", &format!(
                                "'{}.{}' already defined. Only one namespace block per type allowed.",
                                type_name, member_decl.name
                            )));
                            continue;
                        }

                        // Register in symbols
                        context.scope_stack.declare_symbol(full_name.clone(), SymbolInfo {
                            value_type: member_value_type.clone(),
                            is_mut: member_decl.is_mut,
                            is_copy: member_decl.is_copy,
                            is_own: member_decl.is_own,
                            is_comptime_const: false
                        });

                        // If it's a function, also register in funcs
                        if let NodeType::FuncDef(func_def) = &member_expr.node_type {
                            context.scope_stack.declare_func(full_name, func_def.clone());
                        }
                    }
                } else {
                    errors.push(e.error(&context.path, "init", &format!(
                        "namespace member '{}' cannot be mutable. Namespaces only contain constants and functions.",
                        member_decl.name
                    )));
                }
            }
        }
        _ => {
            if !context.mode_def.allows_base_anything {
                if context.mode_def.allows_base_calls {
                    errors.push(e.error(&context.path, "mode", &format!("mode '{}' allows only declarations and calls in the root context, found {:?}.",
                                                         context.mode_def.name, e.node_type)));
                } else {
                    errors.push(e.error(&context.path, "mode", &format!("mode '{}' allows only declarations in the root context, found {:?}.",
                                                         context.mode_def.name, e.node_type)));
                }
            }
        },
    }
    errors
}

/// Temporary storage for enum payload data during construction
#[derive(Clone)]
pub struct EnumPayload {
    pub data: Vec<u8>,
    pub value_type: ValueType,
}

#[derive(Clone)]
pub struct Context {
    pub mode_def: ModeDef, // All contexts need a mode
    // TODO use Context.path to properly report eval errors, or...no, don't refactor the whole eval phase to return Result<String, String>
    pub path: String, // this is needed for core func "loc"
    // Scope stack for proper lexical scoping
    pub scope_stack: ScopeStack,
    // Temporary storage for enum payload data during construction
    pub temp_enum_payload: Option<EnumPayload>,
    // Import tracking - per-phase to allow circular imports
    // Add to done at START of processing (not end) - handles both circular and re-imports
    pub imported_asts: HashMap<String, Expr>,  // path → parsed AST (stored after init, used by typer and eval)
    pub imported_modes: HashMap<String, ModeDef>,  // path → mode (stored after init, used by typer)
    pub imports_init_done: HashSet<String>,
    pub imports_typer_done: HashSet<String>,
    pub imports_precomp_done: HashSet<String>,
    pub imports_eval_done: HashSet<String>,
    // REM: A hashmap for in the future return a struct (namespace) so that it can be assigned to a constant/var
    // REM: This would enable: std := import("src/std") and then std.panic(), std.format(), etc.
    // REM: TODO change the cached type to support import as returning a struct_def
    // Bug #40 fix: Track current function name and forin counter for deterministic _for_i_ names
    pub current_precomp_func: String,  // Empty string means None/global scope
    pub precomp_forin_counter: usize,
}

impl Context {
    pub fn new(path: &String, mode_name: &str) -> Result<Context, String> {
        let mut scope_stack = ScopeStack::new();
        scope_stack.push(ScopeType::Global); // Initialize global scope

        // Create a dummy token for mode initialization errors
        let dummy_token = Token {
            token_type: TokenType::Mode,
            token_str: mode_name.to_string(),
            line: 0,
            col: 0,
        };

        return Ok(Context {
            path: path.to_string(),
            mode_def: mode_from_name(mode_name, path, &dummy_token)?,
            scope_stack,
            temp_enum_payload: None,
            imported_asts: HashMap::new(),
            imported_modes: HashMap::new(),
            imports_init_done: HashSet::new(),
            imports_typer_done: HashSet::new(),
            imports_precomp_done: HashSet::new(),
            imports_eval_done: HashSet::new(),
            // Bug #40 fix: Initialize precomp tracking fields
            current_precomp_func: String::new(),
            precomp_forin_counter: 0,
        });
    }

    // Bug #38 fix: Use ordered variants Vec for consistent variant positioning
    pub fn get_variant_pos(selfi: &SEnumDef, variant_name: &str, path: &str, e: &Expr) -> Result<i64, String> {
        for (search_idx, search_v) in selfi.variants.iter().enumerate() {
            if search_v.name == variant_name {
                return Ok(search_idx as i64);
            }
        }
        let mut names: Vec<&str> = vec![];
        for name_v in &selfi.variants {
            names.push(name_v.name.as_str());
        }
        Err(e.lang_error(path, "context", &format!("Error: Enum variant '{}' not found in variants: {:?}.", variant_name, names)))
    }

    // Bug #38 fix: Use ordered variants Vec for consistent variant positioning
    pub fn variant_pos_to_str(selfi: &SEnumDef, position: i64, path: &str, e: &Expr) -> Result<String, String> {
        if position < 0 || position >= selfi.variants.len() as i64 {
            let mut err_names: Vec<&str> = vec![];
            for err_v in &selfi.variants {
                err_names.push(err_v.name.as_str());
            }
            return Err(e.lang_error(path, "context", &format!("Error: Invalid position '{}' for enum variant in '{:?}'.",
                                                        position, err_names)));
        }

        return Ok(selfi.variants[position as usize].name.clone())
    }

    pub fn map_instance_fields(&mut self, custom_type_name: &str, instance_name: &str, e: &Expr) -> Result<(), String> {
        let struct_def = self.scope_stack.lookup_struct(custom_type_name)
            .ok_or_else(|| e.lang_error(&self.path, "context", &format!("map_instance_fields: definition for '{}' not found", custom_type_name)))?;

        let is_mut = self.scope_stack.lookup_symbol(instance_name)
            .ok_or_else(|| e.lang_error(&self.path, "context", &format!("map_instance_fields: instance '{}' not found in symbols", instance_name)))?
            .is_mut;

        let base_offset = self.scope_stack.lookup_var(instance_name)
            .ok_or_else(|| e.lang_error(&self.path, "context", &format!("map_instance_fields: base offset for '{}' not found", instance_name)))?;

        let members = struct_def.members.clone();

        let mut current_offset = 0;
        for decl in members {
            if decl.is_mut {
                let combined_name = format!("{}.{}", instance_name, decl.name);
                let field_offset = base_offset + current_offset;
                self.scope_stack.insert_var(combined_name.clone(), field_offset);

                self.scope_stack.declare_symbol(
                    combined_name.clone(),
                    SymbolInfo {
                        value_type: decl.value_type.clone(),
                        is_mut,
                        is_copy: false,
                        is_own: false,
                        is_comptime_const: false,
                    },
                );

                if let ValueType::TCustom(type_name) = &decl.value_type {
                    if self.scope_stack.lookup_struct(type_name).is_some() {
                        self.map_instance_fields(type_name, &combined_name, e).map_err(|_| {
                            e.lang_error(&self.path, "context", &format!("map_instance_fields: failed to map nested struct field '{}'", combined_name))
                        })?;
                    }
                }

                let field_size = match &decl.value_type {
                    ValueType::TCustom(name) => self.get_type_size(name)?,
                    _ => return Err(e.lang_error(&self.path, "context", &format!(
                        "map_instance_fields: Unsupported value type '{}'", value_type_to_str(&decl.value_type)
                    ))),
                };

                current_offset += field_size;
            }
            // Immutable struct fields are handled generically through struct_defs
        }
        return Ok(())
    }

    pub fn get_struct(&self, id: &str, e: &Expr) -> Result<String, String> {
        // Validate that the struct variable exists by checking if we can get its offset
        if self.scope_stack.lookup_var(id).is_some() {
            // Direct variable lookup succeeded
            Ok(id.to_string())
        } else if id.contains('.') {
            // For field paths, validate we can calculate offset
            self.get_field_offset(id).map_err(|err| {
                e.lang_error(&self.path, "context", &format!("get_struct: {}", err))
            })?;
            Ok(id.to_string())
        } else {
            Err(e.lang_error(&self.path, "context", &format!("struct not found for id '{}'", id)))
        }
    }

    pub fn register_struct_fields_for_typecheck(&mut self, instance_name: &str, custom_type_name: &str) {
        let struct_def = match self.scope_stack.lookup_struct(custom_type_name) {
            Some(def) => def.clone(),
            None => return,
        };

        for decl in &struct_def.members {
            let combined_name = format!("{}.{}", instance_name, decl.name);
            self.scope_stack.declare_symbol(
                combined_name.clone(),
                SymbolInfo {
                    value_type: decl.value_type.clone(),
                    is_mut: decl.is_mut,
                    is_copy: false,
                    is_own: false,
                    is_comptime_const: false,
                },
            );

            if let ValueType::TCustom(nested_type_name) = &decl.value_type {
                if self.scope_stack.lookup_struct(nested_type_name).is_some() {
                    self.register_struct_fields_for_typecheck(&combined_name, nested_type_name);
                }
            }
        }
    }

    // Scope management helpers for upcoming context clone refactor
    // These will replace context cloning with proper scope push/pop

    /// Push a new function scope and switch to the function's source path
    /// Returns the saved path that should be restored when popping
    #[allow(dead_code)]
    pub fn push_function_scope(&mut self, function_path: &str) -> String {
        self.scope_stack.push(ScopeType::Function);
        let saved_path = self.path.clone();
        self.path = function_path.to_string();
        saved_path
    }

    /// Pop the current function scope and restore the previous path
    #[allow(dead_code)]
    pub fn pop_function_scope(&mut self, saved_path: String) -> Result<(), String> {
        self.path = saved_path;
        self.scope_stack.pop()?;
        Ok(())
    }

    /// Get the size of a type in bytes
    pub fn get_type_size(&self, type_name: &str) -> Result<usize, String> {
        match type_name {
            "U8"   => return Ok(1),
            "I64"  => return Ok(8),
            _ => {},
        }
        if let Some(enum_def) = self.scope_stack.lookup_enum(type_name) {
            // Calculate maximum variant size (8 bytes for tag + largest payload)
            let mut max_size = 8; // Start with tag size

            for v in &enum_def.variants {
                if let Some(payload_type) = &v.payload_type {
                    let payload_size = match payload_type {
                        ValueType::TCustom(t) => self.get_type_size(&t)?,
                        _ => {
                            return Err(format!(
                                "get_type_size: unsupported payload type in enum '{}': {:?}",
                                type_name, payload_type
                            ));
                        }
                    };
                    let variant_total = 8 + payload_size; // tag + payload
                    if variant_total > max_size {
                        max_size = variant_total;
                    }
                }
            }

            return Ok(max_size);
        }

        if let Some(struct_def) = self.scope_stack.lookup_struct(type_name) {
            // Check if struct has size() method (associated function)
            let has_size = struct_def.get_member("size")
                .map(|decl| !decl.is_mut)
                .unwrap_or(false);

            if has_size {
                // TODO: Type has size() method - ideally call TIL's implementation
                // But get_type_size() asks for type's struct size (for field offsets),
                // while instance.size() returns data size (which varies per instance)
                // For now, fall through to calculate struct field size
            }

            // Fallback: Calculate size of struct's fields manually
            let mut total_size = 0;

            for decl in &struct_def.members {
                if decl.is_mut {
                    let field_size = match &decl.value_type {
                        ValueType::TCustom(t) => {
                            self.get_type_size(t)?
                        }
                        _ => {
                            return Err(format!(
                                "get_type_size: unsupported value type '{}' in '{}.{}'",
                                value_type_to_str(&decl.value_type),
                                type_name,
                                decl.name
                            ));
                        }
                    };

                    total_size += field_size;
                }
            }

            Ok(total_size)
        } else {
            Err(format!("get_type_size: type '{}' not found in struct or enum defs", type_name))
        }
    }

    /// Calculate the offset of a specific field within a struct type
    pub fn calculate_field_offset(&self, struct_type: &str, field_name: &str) -> Result<usize, String> {
        let struct_def = self.scope_stack.lookup_struct(struct_type)
            .ok_or_else(|| format!("calculate_field_offset: struct '{}' not found", struct_type))?;

        let mut current_offset = 0;

        for decl in &struct_def.members {
            if decl.is_mut {
                if decl.name == field_name {
                    return Ok(current_offset);
                }

                let field_size = match &decl.value_type {
                    ValueType::TCustom(type_name) => self.get_type_size(type_name)?,
                    _ => return Err(format!(
                        "calculate_field_offset: unsupported field type '{}' in '{}.{}'",
                        value_type_to_str(&decl.value_type), struct_type, decl.name
                    )),
                };

                current_offset += field_size;
            }
        }

        Err(format!("calculate_field_offset: field '{}' not found in struct '{}'", field_name, struct_type))
    }

    /// Get the absolute arena offset for a field path (e.g., "my_vec._len")
    pub fn get_field_offset(&self, field_path: &str) -> Result<usize, String> {
        let parts: Vec<&str> = field_path.split('.').collect();
        if parts.is_empty() {
            return Err(format!("get_field_offset: empty field path"));
        }

        let base_var = parts[0];
        let mut current_offset = self.scope_stack.lookup_var(base_var)
            .ok_or_else(|| format!("get_field_offset: base variable '{}' not found in arena_index", base_var))?;

        let mut current_type = match self.scope_stack.lookup_symbol(base_var) {
            Some(symbol) => match &symbol.value_type {
                ValueType::TCustom(type_name) => type_name.clone(),
                _ => return Err(format!("get_field_offset: base variable '{}' is not a struct", base_var)),
            },
            None => return Err(format!("get_field_offset: base variable '{}' not found in symbols", base_var)),
        };

        let mut should_continue_path = true;
        for field_name in &parts[1..] {
            if should_continue_path {
                let field_offset = self.calculate_field_offset(&current_type, field_name)?;
                current_offset += field_offset;

                let struct_def = self.scope_stack.lookup_struct(&current_type)
                    .ok_or_else(|| format!("get_field_offset: struct '{}' not found", current_type))?;

                let field_decl = struct_def.members.iter()
                    .find(|decl| decl.name == *field_name)
                    .ok_or_else(|| format!("get_field_offset: field '{}' not found in struct '{}'", field_name, current_type))?;

                current_type = match &field_decl.value_type {
                    ValueType::TCustom(type_name) => type_name.clone(),
                    _ => {
                        if field_name == parts.last().unwrap() {
                            should_continue_path = false;
                            String::new()
                        } else {
                            return Err(format!("get_field_offset: field '{}' in '{}' is not a struct, cannot continue path", field_name, current_type));
                        }
                    }
                };
            }
        }

        Ok(current_offset)
    }

    /// Get the type for a field path (e.g., "s.color" returns the type of the color field)
    pub fn get_field_type(&self, field_path: &str) -> Result<ValueType, String> {
        let parts: Vec<&str> = field_path.split('.').collect();
        if parts.is_empty() {
            return Err(format!("get_field_type: empty field path"));
        }

        let base_var = parts[0];
        let mut current_type = match self.scope_stack.lookup_symbol(base_var) {
            Some(symbol) => symbol.value_type.clone(),
            None => return Err(format!("get_field_type: base variable '{}' not found in symbols", base_var)),
        };

        for field_name in &parts[1..] {
            let type_name = match &current_type {
                ValueType::TCustom(name) => name.clone(),
                _ => return Err(format!("get_field_type: cannot access field '{}' on non-struct type", field_name)),
            };

            let struct_def = self.scope_stack.lookup_struct(&type_name)
                .ok_or_else(|| format!("get_field_type: struct '{}' not found", type_name))?;

            let field_decl = struct_def.members.iter()
                .find(|decl| decl.name == *field_name)
                .ok_or_else(|| format!("get_field_type: field '{}' not found in struct '{}'", field_name, type_name))?;

            current_type = field_decl.value_type.clone();
        }

        Ok(current_type)
    }
}



