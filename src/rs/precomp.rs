// Precomputation phase: Transforms UFCS calls into regular function calls
// and performs compile-time constant folding for pure functions.
// This phase runs after typer, before interpreter/builder.

use crate::rs::init::{Context, get_value_type, get_func_name_in_call, SymbolInfo, ScopeType, PrecomputedHeapValue};
use crate::rs::typer::get_func_def_for_fcall_with_expr;
use std::collections::HashMap;
use crate::rs::parser::{
    Expr, NodeType, ValueType, StructDef, EnumDef, EnumVariant, FuncDef, FuncSig, NamespaceDef, Declaration, Literal, TTypeDef,
    FCallInfo, PatternInfo, value_type_to_str, INFER_TYPE,
};
use crate::rs::interpreter::{eval_expr, eval_declaration, insert_struct_instance, create_default_instance};
use crate::rs::eval_heap::EvalHeap;
use crate::rs::precomp_ext::try_replace_comptime_intrinsic;
use crate::rs::preinit::{generate_struct_methods, generate_enum_methods};
use crate::rs::utils::is_function_signature;

// ---------- Issue #105: Early struct macro expansion

/// Build a substitution map from macro Type/Dynamic parameters to actual type names.
/// For `make_vec3(I64)` where `make_vec3` takes `T: Type`, returns {"T": "I64"}.
fn build_type_param_subs(func_def: &FuncDef, fcall: &Expr) -> HashMap<String, String> {
    let mut subs = HashMap::new();
    for (i, arg) in func_def.sig.args.iter().enumerate() {
        if let ValueType::TCustom(ref type_name) = arg.value_type {
            if type_name == "Type" || type_name == "Dynamic" {
                // FCall params: [0] = function name identifier, [1..] = arguments
                if let Some(actual_arg) = fcall.params.get(i + 1) {
                    if let NodeType::Identifier(ref actual_type_name) = &actual_arg.node_type {
                        subs.insert(arg.name.clone(), actual_type_name.clone());
                    }
                }
            }
        }
    }
    subs
}

/// Recursively replace Identifier nodes matching type param names with concrete types.
fn substitute_type_params_in_expr(e: &Expr, subs: &HashMap<String, String>) -> Expr {
    match &e.node_type {
        NodeType::Identifier(name) => {
            let new_name = subs.get(name).unwrap_or(name);
            let new_params: Vec<Expr> = e.params.iter().map(|p| substitute_type_params_in_expr(p, subs)).collect();
            Expr::new_clone(NodeType::Identifier(new_name.clone()), e, new_params)
        }
        NodeType::FuncDef(func_def) => {
            let new_func_def = substitute_type_params_in_funcdef(func_def, subs);
            let new_params: Vec<Expr> = e.params.iter().map(|p| substitute_type_params_in_expr(p, subs)).collect();
            Expr::new_clone(NodeType::FuncDef(new_func_def), e, new_params)
        }
        // Issue #106: Substitute type params in enum variant payload types
        NodeType::EnumDef(enum_def) => {
            let new_enum = substitute_type_params_in_enum(enum_def, subs);
            let new_params: Vec<Expr> = e.params.iter().map(|p| substitute_type_params_in_expr(p, subs)).collect();
            Expr::new_clone(NodeType::EnumDef(new_enum), e, new_params)
        }
        // Issue #106: Substitute type params in switch-case pattern variant names
        NodeType::Pattern(pattern_info) => {
            let mut new_variant_name = pattern_info.variant_name.clone();
            // Pattern variant_name format is "EnumType.Variant" - substitute the enum type prefix
            if let Some(dot_pos) = pattern_info.variant_name.find('.') {
                let enum_prefix = &pattern_info.variant_name[..dot_pos];
                if let Some(concrete) = subs.get(enum_prefix) {
                    new_variant_name = format!("{}.{}", concrete, &pattern_info.variant_name[dot_pos + 1..]);
                }
            }
            Expr::new_clone(NodeType::Pattern(PatternInfo {
                variant_name: new_variant_name,
                binding_var: pattern_info.binding_var.clone(),
            }), e, vec![])
        }
        _ => {
            let default_new_params: Vec<Expr> = e.params.iter().map(|p| substitute_type_params_in_expr(p, subs)).collect();
            Expr::new_clone(e.node_type.clone(), e, default_new_params)
        }
    }
}

/// Substitute type param names in a FuncDef's args, return types, throw types, and body.
fn substitute_type_params_in_funcdef(func_def: &FuncDef, subs: &HashMap<String, String>) -> FuncDef {
    let new_args = func_def.sig.args.iter().map(|arg| {
        if let ValueType::TCustom(ref type_name) = arg.value_type {
            if let Some(concrete) = subs.get(type_name) {
                let mut new_arg = arg.clone();
                new_arg.value_type = ValueType::TCustom(concrete.clone());
                return new_arg;
            }
        }
        arg.clone()
    }).collect();
    let new_returns = func_def.sig.return_types.iter().map(|rt| {
        if let ValueType::TCustom(ref type_name) = rt {
            if let Some(concrete) = subs.get(type_name) {
                return ValueType::TCustom(concrete.clone());
            }
        }
        rt.clone()
    }).collect();
    let new_throws = func_def.sig.throw_types.iter().map(|tt| {
        if let ValueType::TCustom(ref type_name) = tt {
            if let Some(concrete) = subs.get(type_name) {
                return ValueType::TCustom(concrete.clone());
            }
        }
        tt.clone()
    }).collect();
    let new_body = func_def.body.iter().map(|e| substitute_type_params_in_expr(e, subs)).collect();
    FuncDef {
        sig: FuncSig {
            function_type: func_def.sig.function_type.clone(),
            args: new_args,
            return_types: new_returns,
            throw_types: new_throws,
        },
        arg_names: func_def.arg_names.clone(),
        body: new_body,
        source_path: func_def.source_path.clone(),
    }
}

/// Apply type param substitution to a struct definition's member types and default values.
fn substitute_type_params_in_struct(struct_def: &StructDef, subs: &HashMap<String, String>) -> StructDef {
    let new_members = struct_def.members.iter().map(|m| {
        if let ValueType::TCustom(ref type_name) = m.value_type {
            if let Some(concrete_type) = subs.get(type_name) {
                let mut new_m = m.clone();
                new_m.value_type = ValueType::TCustom(concrete_type.clone());
                return new_m;
            }
        }
        m.clone()
    }).collect();

    let new_defaults = struct_def.default_values.iter().map(|(name, expr)| {
        (name.clone(), substitute_type_params_in_expr(expr, subs))
    }).collect();

    // Also substitute type params in ns default values
    let new_ns_defaults = struct_def.ns.default_values.iter().map(|(name, expr)| {
        (name.clone(), substitute_type_params_in_expr(expr, subs))
    }).collect();
    let new_ns = NamespaceDef {
        members: struct_def.ns.members.clone(),
        default_values: new_ns_defaults,
    };

    StructDef { members: new_members, default_values: new_defaults, ns: new_ns }
}

/// Issue #106: Apply type param substitution to an enum definition's variant payload types.
fn substitute_type_params_in_enum(enum_def: &EnumDef, subs: &HashMap<String, String>) -> EnumDef {
    let new_variants = enum_def.variants.iter().map(|v| {
        if let Some(ref payload_type) = v.payload_type {
            if let ValueType::TCustom(ref type_name) = payload_type {
                if let Some(concrete) = subs.get(type_name) {
                    return EnumVariant {
                        name: v.name.clone(),
                        payload_type: Some(ValueType::TCustom(concrete.clone())),
                    };
                }
            }
        }
        v.clone()
    }).collect();
    EnumDef { variants: new_variants, methods: enum_def.methods.clone(), ns: enum_def.ns.clone() }
}

/// Extract namespace def from a macro's body AST.
/// Scans for Return nodes or Declaration nodes containing a StructDef or EnumDef with a non-empty ns field.
/// Returns the first matching namespace def (simple macros only).
fn extract_namespace_from_macro(func_def: &FuncDef) -> NamespaceDef {
    for stmt in &func_def.body {
        // Pattern 1: return struct/enum { ... namespace: ... }
        if matches!(&stmt.node_type, NodeType::Return) {
            if let Some(ret_val) = stmt.params.first() {
                match &ret_val.node_type {
                    NodeType::StructDef(struct_def) if !struct_def.ns.members.is_empty() => {
                        return struct_def.ns.clone();
                    },
                    NodeType::EnumDef(enum_def) if !enum_def.ns.members.is_empty() => {
                        return enum_def.ns.clone();
                    },
                    _ => {}
                }
            }
        }
        // Pattern 2: TemplatedPtr/TemplatedOption := struct/enum { ... namespace: ... }
        if let NodeType::Declaration(_) = &stmt.node_type {
            if let Some(val) = stmt.params.first() {
                match &val.node_type {
                    NodeType::StructDef(struct_def) if !struct_def.ns.members.is_empty() => {
                        return struct_def.ns.clone();
                    },
                    NodeType::EnumDef(enum_def) if !enum_def.ns.members.is_empty() => {
                        return enum_def.ns.clone();
                    },
                    _ => {}
                }
            }
        }
    }
    NamespaceDef { members: Vec::new(), default_values: HashMap::new() }
}

/// Extract the internal type name from a macro body (e.g., "TemplatedPtr" from
/// `TemplatedPtr := struct { ... }` or "TemplatedOption" from `TemplatedOption := enum { ... }`).
/// Returns None for anonymous types (`return struct/enum { ... }`).
fn extract_internal_type_name(func_def: &FuncDef) -> Option<String> {
    for stmt in &func_def.body {
        if let NodeType::Declaration(inner_decl) = &stmt.node_type {
            if let Some(val) = stmt.params.first() {
                if matches!(&val.node_type, NodeType::StructDef(_)) || matches!(&val.node_type, NodeType::EnumDef(_)) {
                    return Some(inner_decl.name.clone());
                }
            }
        }
    }
    None
}

/// Issue #105: Expand struct-returning macros before type checking.
/// Runs between init and typer to make struct definitions available for type checking.
/// Only expands macros at the top-level body that return struct definitions.
pub fn expand_struct_macros(context: &mut Context, e: &Expr) -> Result<Expr, String> {
    if !matches!(&e.node_type, NodeType::Body) {
        return Ok(e.clone());
    }

    let mut new_params = Vec::new();
    let mut modified = false;

    for p in &e.params {
        if let NodeType::Declaration(decl) = &p.node_type {
            if !p.params.is_empty() {
                let inner_e = &p.params[0];
                if matches!(&inner_e.node_type, NodeType::FCall(_)) {
                    // Issue #105: anonymous struct instantiation - struct { ... }(args)
                    if let Some(first_param) = inner_e.params.first() {
                        if let NodeType::StructDef(struct_def) = &first_param.node_type {
                            let temp_name = format!("AnonStruct{}", context.anon_struct_counter);
                            context.anon_struct_counter += 1;
                            context.scope_stack.declare_struct(temp_name.clone(), struct_def.clone());
                            context.scope_stack.declare_symbol(temp_name.clone(), SymbolInfo {
                                value_type: ValueType::TType(TTypeDef::TStructDef),
                                is_mut: false,
                                
                                is_own: false,
                                is_comptime_const: false,
                            });
                            // Register immutable fields as namespace constants
                            for member_decl in &struct_def.members {
                                if !member_decl.is_mut {
                                    if let Some(member_expr) = struct_def.default_values.get(&member_decl.name) {
                                        let member_value_type = get_value_type(context, member_expr).unwrap_or(ValueType::TCustom(INFER_TYPE.to_string()));
                                        let member_full_name = format!("{}.{}", temp_name, member_decl.name);
                                        context.scope_stack.declare_symbol(member_full_name, SymbolInfo {
                                            value_type: member_value_type,
                                            is_mut: member_decl.is_mut,
                                            
                                            is_own: member_decl.is_own,
                                            is_comptime_const: false,
                                        });
                                    }
                                }
                            }
                            // Generate struct methods (delete/clone) and set ns on struct
                            let mut updated_struct_def = struct_def.clone();
                            if let Some(auto_ns) = generate_struct_methods(&temp_name, struct_def, p.line, p.col, &context.scope_stack.get_func_sig_types()) {
                                updated_struct_def.ns = auto_ns;
                                // Register ns methods via init helper
                                let mut ns_errors_vec = Vec::new();
                                crate::rs::init::init_namespace_into_struct(context, &temp_name, &updated_struct_def.ns, p, &mut ns_errors_vec);
                                if !ns_errors_vec.is_empty() {
                                    return Err(ns_errors_vec.join("\n"));
                                }
                            }
                            // Re-register the struct with ns
                            context.scope_stack.declare_struct(temp_name.clone(), updated_struct_def.clone());
                            // Build struct definition declaration for codegen
                            let struct_decl = Declaration {
                                name: temp_name.clone(),
                                value_type: ValueType::TType(TTypeDef::TStructDef),
                                is_mut: false,
                                
                                is_own: false,
                                default_value: None,
                            };
                            let struct_decl_expr = Expr::new_clone(
                                NodeType::Declaration(struct_decl),
                                first_param,
                                vec![Expr::new_clone(NodeType::StructDef(updated_struct_def), first_param, vec![])],
                            );
                            new_params.push(struct_decl_expr);
                            // Replace StructDef with Identifier in the FCall
                            let id_expr = Expr::new_clone(NodeType::Identifier(temp_name.clone()), first_param, vec![]);
                            let mut fcall_params = vec![id_expr];
                            fcall_params.extend(inner_e.params.iter().skip(1).cloned());
                            let new_fcall = Expr::new_clone(inner_e.node_type.clone(), inner_e, fcall_params);
                            let new_p = Expr::new_clone(p.node_type.clone(), p, vec![new_fcall]);
                            new_params.push(new_p);
                            modified = true;
                            continue;
                        }
                    }
                    // Check if the function is a macro returning struct
                    let f_name = get_func_name_in_call(inner_e);
                    if let Some(func_def) = context.scope_stack.lookup_func(&f_name) {
                        if func_def.is_macro() && !func_def.sig.return_types.is_empty() {
                            // Extract all data from func_def before mutable borrows
                            let macro_return_type = func_def.sig.return_types[0].clone();
                            let type_subs = build_type_param_subs(&func_def, inner_e);
                            let macro_ns = extract_namespace_from_macro(&func_def);
                            let macro_internal_name = extract_internal_type_name(&func_def);
                            if macro_return_type == ValueType::TType(TTypeDef::TStructDef) {
                                // Expand the macro (mutably borrows context)
                                let expanded = eval_comptime(context, inner_e)?;
                                if let NodeType::StructDef(struct_def) = &expanded.node_type {
                                    // Substitute type params (e.g. T -> I64) in member types and defaults
                                    let substituted = if type_subs.is_empty() {
                                        struct_def.clone()
                                    } else {
                                        substitute_type_params_in_struct(struct_def, &type_subs)
                                    };
                                    // Resolve INFER_TYPE in struct members from default values
                                    let mut resolved_members = Vec::new();
                                    for member_decl in &substituted.members {
                                        if member_decl.value_type == ValueType::TCustom(INFER_TYPE.to_string()) {
                                            if let Some(default_value) = substituted.default_values.get(&member_decl.name) {
                                                if let Ok(resolved_type) = get_value_type(context, default_value) {
                                                    let mut resolved_member = member_decl.clone();
                                                    resolved_member.value_type = resolved_type;
                                                    resolved_members.push(resolved_member);
                                                    continue;
                                                }
                                            }
                                        }
                                        resolved_members.push(member_decl.clone());
                                    }
                                    // Issue #105: Precompute struct default values (e.g. NULL → 0)
                                    // Defaults come from macro body AST and weren't processed by precomp
                                    let mut precomputed_defaults = HashMap::new();
                                    for (key, val) in &substituted.default_values {
                                        match precomp_expr(context, val) {
                                            Ok(precomputed) => { precomputed_defaults.insert(key.clone(), precomputed); },
                                            Err(_) => { precomputed_defaults.insert(key.clone(), val.clone()); },
                                        }
                                    }
                                    // Build combined ns: auto-generated + user-defined from macro namespace
                                    let mut combined_ns = NamespaceDef {
                                        members: Vec::new(),
                                        default_values: HashMap::new(),
                                    };
                                    // Check if macro namespace already defines delete/clone
                                    let ns_has_delete = macro_ns.members.iter().any(|m| m.name == "delete");
                                    let ns_has_clone = macro_ns.members.iter().any(|m| m.name == "clone");
                                    // Generate auto delete/clone methods
                                    let mut auto_struct = StructDef {
                                        members: resolved_members.clone(),
                                        default_values: precomputed_defaults.clone(),
                                        ns: NamespaceDef { members: Vec::new(), default_values: HashMap::new() },
                                    };
                                    let dummy = Expr::new_explicit(NodeType::LLiteral(Literal::Number("0".to_string())), vec![], 0, 0);
                                    if ns_has_delete { auto_struct.default_values.insert("delete".to_string(), dummy.clone()); }
                                    if ns_has_clone { auto_struct.default_values.insert("clone".to_string(), dummy); }
                                    if let Some(auto_ns) = generate_struct_methods(&decl.name, &auto_struct, p.line, p.col, &context.scope_stack.get_func_sig_types()) {
                                        combined_ns.members.extend(auto_ns.members);
                                        combined_ns.default_values.extend(auto_ns.default_values);
                                    }
                                    // Merge user namespace from macro body (with type param substitution)
                                    if !macro_ns.members.is_empty() {
                                        let mut ns_subs = type_subs.clone();
                                        if let Some(ref internal_name) = macro_internal_name {
                                            ns_subs.insert(internal_name.clone(), decl.name.clone());
                                        }
                                        for member in &macro_ns.members {
                                            // User methods override auto-generated ones
                                            combined_ns.members.retain(|m| m.name != member.name);
                                            combined_ns.members.push(member.clone());
                                        }
                                        for (name, val) in &macro_ns.default_values {
                                            let substituted_val = substitute_type_params_in_expr(val, &ns_subs);
                                            combined_ns.default_values.insert(name.clone(), substituted_val);
                                        }
                                    }
                                    let resolved_struct = StructDef {
                                        members: resolved_members,
                                        default_values: precomputed_defaults,
                                        ns: combined_ns,
                                    };
                                    let resolved_expanded = Expr::new_clone(NodeType::StructDef(resolved_struct.clone()), &expanded, vec![]);
                                    // Register the struct in context
                                    context.scope_stack.declare_struct(decl.name.clone(), resolved_struct.clone());
                                    // Register immutable fields as namespace constants (same as init_context for regular structs)
                                    for member_decl in &resolved_struct.members {
                                        if !member_decl.is_mut {
                                            if let Some(member_expr) = resolved_struct.default_values.get(&member_decl.name) {
                                                let member_value_type = get_value_type(context, member_expr).unwrap_or(ValueType::TCustom(INFER_TYPE.to_string()));
                                                let member_full_name = format!("{}.{}", decl.name, member_decl.name);
                                                context.scope_stack.declare_symbol(member_full_name, SymbolInfo {
                                                    value_type: member_value_type,
                                                    is_mut: member_decl.is_mut,
                                                    
                                                    is_own: member_decl.is_own,
                                                    is_comptime_const: false,
                                                });
                                            }
                                        }
                                    }
                                    // Register ns methods via init helper
                                    if !resolved_struct.ns.members.is_empty() {
                                        let mut ns_errors_vec = Vec::new();
                                        crate::rs::init::init_namespace_into_struct(context, &decl.name, &resolved_struct.ns, p, &mut ns_errors_vec);
                                        if !ns_errors_vec.is_empty() {
                                            return Err(ns_errors_vec.join("\n"));
                                        }
                                    }
                                    // Replace the FCall with the StructDef in the AST
                                    let new_p = Expr::new_clone(p.node_type.clone(), p, vec![resolved_expanded]);
                                    new_params.push(new_p);
                                    modified = true;
                                    continue;
                                }
                            }
                            // Issue #106: Check if macro returns an enum definition
                            if macro_return_type == ValueType::TType(TTypeDef::TEnumDef) {
                                // Expand the macro
                                let expanded = eval_comptime(context, inner_e)?;
                                if let NodeType::EnumDef(enum_def) = &expanded.node_type {
                                    // Substitute type params in variant payload types
                                    let mut substituted = if type_subs.is_empty() {
                                        enum_def.clone()
                                    } else {
                                        substitute_type_params_in_enum(enum_def, &type_subs)
                                    };
                                    // Clear preinit-generated methods (they reference the internal name)
                                    // They'll be regenerated with the correct external name below
                                    substituted.methods = crate::rs::ordered_map::OrderedMap::new();
                                    // Build combined ns: auto-generated + user-defined from macro namespace
                                    let mut combined_ns = NamespaceDef {
                                        members: Vec::new(),
                                        default_values: HashMap::new(),
                                    };
                                    let ns_has_delete = macro_ns.members.iter().any(|m| m.name == "delete");
                                    let ns_has_clone = macro_ns.members.iter().any(|m| m.name == "clone");
                                    if let Some(auto_ns) = generate_enum_methods(&decl.name, ns_has_delete, ns_has_clone, p.line, p.col) {
                                        combined_ns.members.extend(auto_ns.members);
                                        combined_ns.default_values.extend(auto_ns.default_values);
                                    }
                                    // Merge user namespace from macro body (with type param substitution)
                                    if !macro_ns.members.is_empty() {
                                        let mut ns_subs = type_subs.clone();
                                        if let Some(ref internal_name) = macro_internal_name {
                                            ns_subs.insert(internal_name.clone(), decl.name.clone());
                                        }
                                        for member in &macro_ns.members {
                                            combined_ns.members.retain(|m| m.name != member.name);
                                            combined_ns.members.push(member.clone());
                                        }
                                        for (name, val) in &macro_ns.default_values {
                                            let substituted_val = substitute_type_params_in_expr(val, &ns_subs);
                                            combined_ns.default_values.insert(name.clone(), substituted_val);
                                        }
                                    }
                                    substituted.ns = combined_ns;
                                    let resolved_expanded = Expr::new_clone(NodeType::EnumDef(substituted.clone()), &expanded, vec![]);
                                    // Register the enum in context
                                    context.scope_stack.declare_enum(decl.name.clone(), substituted.clone());
                                    // Register ns methods via init helper
                                    if !substituted.ns.members.is_empty() {
                                        let mut ns_errors_vec = Vec::new();
                                        crate::rs::init::init_namespace_into_enum(context, &decl.name, &substituted.ns, p, &mut ns_errors_vec);
                                        if !ns_errors_vec.is_empty() {
                                            return Err(ns_errors_vec.join("\n"));
                                        }
                                    }
                                    // Replace the FCall with the EnumDef in the AST
                                    let new_p = Expr::new_clone(p.node_type.clone(), p, vec![resolved_expanded]);
                                    new_params.push(new_p);
                                    modified = true;
                                    continue;
                                }
                            }
                        }
                    }
                }
            }
        }
        // Issue #105: Recurse into function/proc body to expand anonymous struct FCalls
        let mut pending_decls = Vec::new();
        let maybe_expanded = expand_anon_struct_fcalls_recursive(context, p, &mut pending_decls)?;
        if !pending_decls.is_empty() {
            for decl in pending_decls {
                new_params.push(decl);
            }
            modified = true;
        }
        let struct_result = if maybe_expanded.is_some() {
            modified = true;
            maybe_expanded.unwrap()
        } else {
            p.clone()
        };
        // Issue #106: Recurse into function/proc body to expand anonymous enum definitions
        let mut pending_enum_decls = Vec::new();
        let maybe_enum_expanded = expand_anon_enum_fcalls_recursive(context, &struct_result, &mut pending_enum_decls)?;
        if !pending_enum_decls.is_empty() {
            for decl in pending_enum_decls {
                new_params.push(decl);
            }
            modified = true;
        }
        if maybe_enum_expanded.is_some() {
            new_params.push(maybe_enum_expanded.unwrap());
            modified = true;
        } else {
            new_params.push(struct_result);
        }
    }

    if modified {
        Ok(Expr::new_clone(e.node_type.clone(), e, new_params))
    } else {
        Ok(e.clone())
    }
}

/// Issue #105: Recursively walk an expression and expand anonymous struct FCall instantiations.
/// Returns Some(modified_expr) if any change was made, None otherwise.
/// `pending_decls` collects struct declarations + namespace blocks to inject at top level.
fn expand_anon_struct_fcalls_recursive(context: &mut Context, e: &Expr, pending_decls: &mut Vec<Expr>) -> Result<Option<Expr>, String> {
    // Check if this is an FCall with a StructDef first param
    if matches!(&e.node_type, NodeType::FCall(_)) {
        if let Some(first_param) = e.params.first() {
            if let NodeType::StructDef(struct_def) = &first_param.node_type {
                let temp_name = format!("AnonStruct{}", context.anon_struct_counter);
                context.anon_struct_counter += 1;
                context.scope_stack.declare_struct(temp_name.clone(), struct_def.clone());
                context.scope_stack.declare_symbol(temp_name.clone(), SymbolInfo {
                    value_type: ValueType::TType(TTypeDef::TStructDef),
                    is_mut: false, is_own: false, is_comptime_const: false,
                });
                // Register immutable fields as namespace constants
                for member_decl in &struct_def.members {
                    if !member_decl.is_mut {
                        if let Some(member_expr) = struct_def.default_values.get(&member_decl.name) {
                            let member_value_type = get_value_type(context, member_expr).unwrap_or(ValueType::TCustom(INFER_TYPE.to_string()));
                            let member_full_name = format!("{}.{}", temp_name, member_decl.name);
                            context.scope_stack.declare_symbol(member_full_name, SymbolInfo {
                                value_type: member_value_type,
                                is_mut: member_decl.is_mut, is_own: member_decl.is_own, is_comptime_const: false,
                            });
                        }
                    }
                }
                // Generate struct methods (delete/clone) and set ns on struct
                let mut updated_struct_def = struct_def.clone();
                if let Some(auto_ns) = generate_struct_methods(&temp_name, struct_def, e.line, e.col, &context.scope_stack.get_func_sig_types()) {
                    updated_struct_def.ns = auto_ns;
                    let mut ns_errors_vec = Vec::new();
                    crate::rs::init::init_namespace_into_struct(context, &temp_name, &updated_struct_def.ns, e, &mut ns_errors_vec);
                    if !ns_errors_vec.is_empty() {
                        return Err(ns_errors_vec.join("\n"));
                    }
                }
                context.scope_stack.declare_struct(temp_name.clone(), updated_struct_def.clone());
                // Build struct definition declaration for codegen
                let struct_decl = Declaration {
                    name: temp_name.clone(),
                    value_type: ValueType::TType(TTypeDef::TStructDef),
                    is_mut: false, is_own: false, default_value: None,
                };
                let struct_decl_expr = Expr::new_clone(
                    NodeType::Declaration(struct_decl),
                    first_param,
                    vec![Expr::new_clone(NodeType::StructDef(updated_struct_def), first_param, vec![])],
                );
                pending_decls.push(struct_decl_expr);
                // Replace StructDef with Identifier in the FCall
                let id_expr = Expr::new_clone(NodeType::Identifier(temp_name.clone()), first_param, vec![]);
                let mut fcall_params = vec![id_expr];
                fcall_params.extend(e.params.iter().skip(1).cloned());
                return Ok(Some(Expr::new_clone(e.node_type.clone(), e, fcall_params)));
            }
        }
    }

    // Check if this is a Declaration with a StructDef value (e.g. P := struct { ... })
    // Only process if the struct isn't already registered (avoids duplicating top-level structs)
    if let NodeType::Declaration(decl) = &e.node_type {
        if !e.params.is_empty() {
            if let NodeType::StructDef(struct_def) = &e.params[0].node_type {
                if context.scope_stack.lookup_struct(&decl.name).is_some() {
                    // Already registered at top level - skip
                    return Ok(None);
                }
                // Register the struct with the declared name
                context.scope_stack.declare_struct(decl.name.clone(), struct_def.clone());
                context.scope_stack.declare_symbol(decl.name.clone(), SymbolInfo {
                    value_type: ValueType::TType(TTypeDef::TStructDef),
                    is_mut: false, is_own: false, is_comptime_const: false,
                });
                // Register immutable fields as namespace constants
                for member_decl in &struct_def.members {
                    if !member_decl.is_mut {
                        if let Some(member_expr) = struct_def.default_values.get(&member_decl.name) {
                            let member_value_type = get_value_type(context, member_expr).unwrap_or(ValueType::TCustom(INFER_TYPE.to_string()));
                            let member_full_name = format!("{}.{}", decl.name, member_decl.name);
                            context.scope_stack.declare_symbol(member_full_name, SymbolInfo {
                                value_type: member_value_type,
                                is_mut: member_decl.is_mut, is_own: member_decl.is_own, is_comptime_const: false,
                            });
                        }
                    }
                }
                // Generate struct methods (delete/clone) and set ns on struct
                let mut updated_struct_def = struct_def.clone();
                if let Some(auto_ns) = generate_struct_methods(&decl.name, struct_def, e.line, e.col, &context.scope_stack.get_func_sig_types()) {
                    updated_struct_def.ns = auto_ns;
                    let mut ns_errors_vec = Vec::new();
                    crate::rs::init::init_namespace_into_struct(context, &decl.name, &updated_struct_def.ns, e, &mut ns_errors_vec);
                    if !ns_errors_vec.is_empty() {
                        return Err(ns_errors_vec.join("\n"));
                    }
                }
                context.scope_stack.declare_struct(decl.name.clone(), updated_struct_def.clone());
                // Add struct definition (with ns) to pending top-level decls for codegen
                let updated_struct_expr = Expr::new_clone(NodeType::StructDef(updated_struct_def), &e.params[0], vec![]);
                let updated_decl_expr = Expr::new_clone(e.node_type.clone(), e, vec![updated_struct_expr]);
                pending_decls.push(updated_decl_expr.clone());
                // Return the original expression (stays in body; codegen skips TType declarations)
                return Ok(Some(e.clone()));
            }
        }
    }

    // For FCall nodes, check if any non-first param is a bare StructDef (value argument).
    // Replace with struct_def_of("AnonStructN") call so compiled mode gets a runtime StructDef value.
    // Only applies to FCall args (not return statements, macro bodies, etc.)
    if matches!(&e.node_type, NodeType::FCall(_)) {
        let mut fcall_any_changed = false;
        let mut fcall_new_params = Vec::new();
        for (idx, p) in e.params.iter().enumerate() {
            if idx > 0 {  // skip first param (function name / constructor)
                // Check for bare StructDef or OwnArg-wrapped StructDef
                let inner_struct = match &p.node_type {
                    NodeType::StructDef(sd) => Some((sd, p)),
                    NodeType::OwnArg => {
                        if let Some(inner) = p.params.first() {
                            if let NodeType::StructDef(sd) = &inner.node_type { Some((sd, inner)) } else { None }
                        } else { None }
                    },
                    _ => None,
                };
                if let Some((struct_def, struct_expr)) = inner_struct {
                    let is_own = matches!(&p.node_type, NodeType::OwnArg);
                    let temp_name = format!("AnonStruct{}", context.anon_struct_counter);
                    context.anon_struct_counter += 1;
                    context.scope_stack.declare_struct(temp_name.clone(), struct_def.clone());
                    context.scope_stack.declare_symbol(temp_name.clone(), SymbolInfo {
                        value_type: ValueType::TType(TTypeDef::TStructDef),
                        is_mut: false, is_own: false, is_comptime_const: false,
                    });
                    for member_decl in &struct_def.members {
                        if !member_decl.is_mut {
                            if let Some(member_expr) = struct_def.default_values.get(&member_decl.name) {
                                let member_value_type = get_value_type(context, member_expr).unwrap_or(ValueType::TCustom(INFER_TYPE.to_string()));
                                let member_full_name = format!("{}.{}", temp_name, member_decl.name);
                                context.scope_stack.declare_symbol(member_full_name, SymbolInfo {
                                    value_type: member_value_type,
                                    is_mut: member_decl.is_mut, is_own: member_decl.is_own, is_comptime_const: false,
                                });
                            }
                        }
                    }
                    let mut updated_struct_def = struct_def.clone();
                    if let Some(auto_ns) = generate_struct_methods(&temp_name, struct_def, struct_expr.line, struct_expr.col, &context.scope_stack.get_func_sig_types()) {
                        updated_struct_def.ns = auto_ns;
                        let mut ns_errors_vec = Vec::new();
                        crate::rs::init::init_namespace_into_struct(context, &temp_name, &updated_struct_def.ns, struct_expr, &mut ns_errors_vec);
                        if !ns_errors_vec.is_empty() {
                            return Err(ns_errors_vec.join("\n"));
                        }
                    }
                    context.scope_stack.declare_struct(temp_name.clone(), updated_struct_def.clone());
                    let struct_decl = Declaration {
                        name: temp_name.clone(),
                        value_type: ValueType::TType(TTypeDef::TStructDef),
                        is_mut: false, is_own: false, default_value: None,
                    };
                    let struct_decl_expr = Expr::new_clone(
                        NodeType::Declaration(struct_decl),
                        struct_expr,
                        vec![Expr::new_clone(NodeType::StructDef(updated_struct_def), struct_expr, vec![])],
                    );
                    pending_decls.push(struct_decl_expr);
                    // Replace with struct_def_of("AnonStructN") call
                    let sdo_id = Expr::new_clone(NodeType::Identifier("struct_def_of".to_string()), struct_expr, vec![]);
                    let sdo_arg = Expr::new_clone(NodeType::LLiteral(Literal::Str(temp_name)), struct_expr, vec![]);
                    let sdo_call = Expr::new_clone(
                        NodeType::FCall(FCallInfo { does_throw: false, is_bang: false }),
                        struct_expr,
                        vec![sdo_id, sdo_arg],
                    );
                    // Preserve OwnArg wrapper if original was own
                    if is_own {
                        let own_wrapper = Expr::new_clone(NodeType::OwnArg, p, vec![sdo_call]);
                        fcall_new_params.push(own_wrapper);
                    } else {
                        fcall_new_params.push(sdo_call);
                    }
                    fcall_any_changed = true;
                    continue;
                }
            }
            // Recurse into this param normally
            if let Some(expanded) = expand_anon_struct_fcalls_recursive(context, p, pending_decls)? {
                fcall_new_params.push(expanded);
                fcall_any_changed = true;
            } else {
                fcall_new_params.push(p.clone());
            }
        }
        if fcall_any_changed {
            return Ok(Some(Expr::new_clone(e.node_type.clone(), e, fcall_new_params)));
        }
        return Ok(None);
    }

    // Recurse into child expressions
    let mut any_changed = false;
    let mut new_params = Vec::new();
    for p in &e.params {
        if let Some(expanded) = expand_anon_struct_fcalls_recursive(context, p, pending_decls)? {
            new_params.push(expanded);
            any_changed = true;
        } else {
            new_params.push(p.clone());
        }
    }

    // Also recurse into FuncDef bodies
    if let NodeType::FuncDef(func_def) = &e.node_type {
        let mut body_changed = false;
        let mut new_body = Vec::new();
        for stmt in &func_def.body {
            if let Some(expanded) = expand_anon_struct_fcalls_recursive(context, stmt, pending_decls)? {
                new_body.push(expanded);
                body_changed = true;
            } else {
                new_body.push(stmt.clone());
            }
        }
        if body_changed {
            let mut new_func_def = func_def.clone();
            new_func_def.body = new_body;
            return Ok(Some(Expr::new_clone(NodeType::FuncDef(new_func_def), e, new_params)));
        }
    }

    if any_changed {
        Ok(Some(Expr::new_clone(e.node_type.clone(), e, new_params)))
    } else {
        Ok(None)
    }
}

// Issue #106: Expand anonymous enum definitions in FCall arguments and declarations
// Mirrors expand_anon_struct_fcalls_recursive but for EnumDef nodes.
// Key difference: enums appear as Type arguments (any param position), not as constructors (first param).
fn expand_anon_enum_fcalls_recursive(context: &mut Context, e: &Expr, pending_decls: &mut Vec<Expr>) -> Result<Option<Expr>, String> {
    // For FCall nodes, check if any non-first param is a bare EnumDef.
    // If so, register it AND replace with enum_def_of() (for value arg contexts like Vec.push).
    // This runs before the generic bare EnumDef check below, which replaces with Identifier
    // (correct for macros/type args but wrong for value args).
    if matches!(&e.node_type, NodeType::FCall(_)) {
        let mut fcall_any_changed = false;
        let mut fcall_new_params = Vec::new();
        for (idx, p) in e.params.iter().enumerate() {
            if idx > 0 {
                // Check for bare EnumDef or OwnArg-wrapped EnumDef
                let inner_enum = match &p.node_type {
                    NodeType::EnumDef(ed) => Some((ed, p)),
                    NodeType::OwnArg => {
                        if let Some(inner) = p.params.first() {
                            if let NodeType::EnumDef(ed) = &inner.node_type { Some((ed, inner)) } else { None }
                        } else { None }
                    },
                    _ => None,
                };
                if let Some((enum_def, enum_expr)) = inner_enum {
                    let is_own = matches!(&p.node_type, NodeType::OwnArg);
                    let temp_name = format!("AnonEnum{}", context.anon_enum_counter);
                    context.anon_enum_counter += 1;
                    context.scope_stack.declare_enum(temp_name.clone(), enum_def.clone());
                    context.scope_stack.declare_symbol(temp_name.clone(), SymbolInfo {
                        value_type: ValueType::TType(TTypeDef::TEnumDef),
                        is_mut: false, is_own: false, is_comptime_const: false,
                    });
                    let mut updated_enum_def = enum_def.clone();
                    if let Some(auto_ns) = generate_enum_methods(&temp_name, false, false, enum_expr.line, enum_expr.col) {
                        updated_enum_def.ns = auto_ns;
                        let mut ns_errors_vec = Vec::new();
                        crate::rs::init::init_namespace_into_enum(context, &temp_name, &updated_enum_def.ns, enum_expr, &mut ns_errors_vec);
                        if !ns_errors_vec.is_empty() {
                            return Err(ns_errors_vec.join("\n"));
                        }
                    }
                    context.scope_stack.declare_enum(temp_name.clone(), updated_enum_def.clone());
                    let enum_decl = Declaration {
                        name: temp_name.clone(),
                        value_type: ValueType::TType(TTypeDef::TEnumDef),
                        is_mut: false, is_own: false, default_value: None,
                    };
                    let enum_decl_expr = Expr::new_clone(
                        NodeType::Declaration(enum_decl),
                        enum_expr,
                        vec![Expr::new_clone(NodeType::EnumDef(updated_enum_def), enum_expr, vec![])],
                    );
                    pending_decls.push(enum_decl_expr);
                    // Check if the function is a macro - if so, use Identifier (for compile-time eval)
                    let func_name = if let Some(first) = e.params.first() {
                        if let NodeType::Identifier(name) = &first.node_type { Some(name.clone()) } else { None }
                    } else { None };
                    let is_macro = if let Some(ref name) = func_name {
                        context.scope_stack.lookup_func(name).map(|f| f.is_macro()).unwrap_or(false)
                    } else { false };
                    if is_macro {
                        // Macro arg: use Identifier (compile-time constant)
                        let id_expr = Expr::new_clone(NodeType::Identifier(temp_name), enum_expr, vec![]);
                        fcall_new_params.push(id_expr);
                    } else {
                        // Value arg: use enum_def_of() (runtime value)
                        let edo_id = Expr::new_clone(NodeType::Identifier("enum_def_of".to_string()), enum_expr, vec![]);
                        let edo_arg = Expr::new_clone(NodeType::LLiteral(Literal::Str(temp_name)), enum_expr, vec![]);
                        let edo_call = Expr::new_clone(
                            NodeType::FCall(FCallInfo { does_throw: false, is_bang: false }),
                            enum_expr,
                            vec![edo_id, edo_arg],
                        );
                        if is_own {
                            let own_wrapper = Expr::new_clone(NodeType::OwnArg, p, vec![edo_call]);
                            fcall_new_params.push(own_wrapper);
                        } else {
                            fcall_new_params.push(edo_call);
                        }
                    }
                    fcall_any_changed = true;
                    continue;
                }
            }
            // Recurse into this param normally
            if let Some(expanded) = expand_anon_enum_fcalls_recursive(context, p, pending_decls)? {
                fcall_new_params.push(expanded);
                fcall_any_changed = true;
            } else {
                fcall_new_params.push(p.clone());
            }
        }
        if fcall_any_changed {
            return Ok(Some(Expr::new_clone(e.node_type.clone(), e, fcall_new_params)));
        }
        return Ok(None);
    }

    // Check if this is a bare EnumDef node -- replace with a registered anonymous enum
    if let NodeType::EnumDef(enum_def) = &e.node_type {
        let temp_name = format!("AnonEnum{}", context.anon_enum_counter);
        context.anon_enum_counter += 1;
        context.scope_stack.declare_enum(temp_name.clone(), enum_def.clone());
        context.scope_stack.declare_symbol(temp_name.clone(), SymbolInfo {
            value_type: ValueType::TType(TTypeDef::TEnumDef),
            is_mut: false, is_own: false, is_comptime_const: false,
        });
        // Generate enum methods (delete/clone) and set ns on enum
        let mut updated_enum_def = enum_def.clone();
        if let Some(auto_ns) = generate_enum_methods(&temp_name, false, false, e.line, e.col) {
            updated_enum_def.ns = auto_ns;
            let mut ns_errors_vec = Vec::new();
            crate::rs::init::init_namespace_into_enum(context, &temp_name, &updated_enum_def.ns, e, &mut ns_errors_vec);
            if !ns_errors_vec.is_empty() {
                return Err(ns_errors_vec.join("\n"));
            }
        }
        context.scope_stack.declare_enum(temp_name.clone(), updated_enum_def.clone());
        // Build enum definition declaration for codegen
        let enum_decl = Declaration {
            name: temp_name.clone(),
            value_type: ValueType::TType(TTypeDef::TEnumDef),
            is_mut: false, is_own: false, default_value: None,
        };
        let enum_decl_expr = Expr::new_clone(
            NodeType::Declaration(enum_decl),
            e,
            vec![Expr::new_clone(NodeType::EnumDef(updated_enum_def), e, vec![])],
        );
        pending_decls.push(enum_decl_expr);
        // Replace EnumDef with Identifier
        let id_expr = Expr::new_clone(NodeType::Identifier(temp_name.clone()), e, vec![]);
        return Ok(Some(id_expr));
    }

    // Check if this is a Declaration with an EnumDef value (e.g. Color := enum { ... })
    // Only process if the enum isn't already registered (avoids duplicating top-level enums)
    if let NodeType::Declaration(decl) = &e.node_type {
        if !e.params.is_empty() {
            if let NodeType::EnumDef(_) = &e.params[0].node_type {
                if context.scope_stack.lookup_enum(&decl.name).is_some() {
                    // Already registered at top level - skip
                    return Ok(None);
                }
                // Not registered yet (inside function body) - let it through for
                // normal processing by precomp_declaration
                return Ok(None);
            }
        }
    }

    // Recurse into child expressions
    let mut any_changed = false;
    let mut new_params = Vec::new();
    for p in &e.params {
        if let Some(expanded) = expand_anon_enum_fcalls_recursive(context, p, pending_decls)? {
            new_params.push(expanded);
            any_changed = true;
        } else {
            new_params.push(p.clone());
        }
    }

    // Also recurse into FuncDef bodies
    if let NodeType::FuncDef(func_def) = &e.node_type {
        let mut body_changed = false;
        let mut new_body = Vec::new();
        for stmt in &func_def.body {
            if let Some(expanded) = expand_anon_enum_fcalls_recursive(context, stmt, pending_decls)? {
                new_body.push(expanded);
                body_changed = true;
            } else {
                new_body.push(stmt.clone());
            }
        }
        if body_changed {
            let mut new_func_def = func_def.clone();
            new_func_def.body = new_body;
            return Ok(Some(Expr::new_clone(NodeType::FuncDef(new_func_def), e, new_params)));
        }
    }

    if any_changed {
        Ok(Some(Expr::new_clone(e.node_type.clone(), e, new_params)))
    } else {
        Ok(None)
    }
}

// ---------- Main entry point

/// Precomputation phase: Transform UFCS calls into regular function calls.
/// Takes an AST that has already passed type checking and returns a semantically
/// equivalent AST with all UFCS calls resolved.
///
/// Examples:
///   a.add(b)         -> I64.add(a, b)     (where a is I64)
///   obj.items.len()  -> Vec.len(obj.items)
///   add(1, 2).mul(3) -> I64.mul(add(1, 2), 3)
pub fn precomp_expr(context: &mut Context, e: &Expr) -> Result<Expr, String> {
    match &e.node_type {
        NodeType::Body => precomp_body(context, e),
        NodeType::FCall(_) => {
            let mut const_folded = precomp_fcall(context, e)?;

            // Try compile-time constant folding for pure functions with literal args.
            // Check if this is a macro call - macros MUST be evaluated at compile-time
            // but only when called at global scope with comptime args (same as funcs,
            // just with an error if args aren't comptime instead of silent skip)
            let at_global_scope = context.scope_stack.frames.len() == 1;
            let is_macro_call = is_macro_fcall(context, &const_folded);
            if is_macro_call {
                if is_comptime_evaluable(context, &const_folded)? {
                    // Force compile-time evaluation
                    const_folded = eval_comptime(context, &const_folded)?;
                    return Ok(const_folded);
                }
                // At global scope, macros MUST have comptime args - error
                if at_global_scope {
                    let f_name = get_func_name_in_call(&const_folded);
                    return Err(const_folded.error(&context.path, "precomp",
                        &format!("Macro '{}' requires all arguments to be compile-time constants", f_name)));
                }
                // Inside function bodies, macro args may depend on params - skip for now
            }

            if is_comptime_evaluable(context, &const_folded)? {
                // Try to evaluate at compile time. If it fails (e.g., function body
                // references symbols not available during precomp), silently skip
                // and leave the call for runtime evaluation.
                match eval_comptime(context, &const_folded) {
                    Ok(folded) => const_folded = folded,
                    Err(_) => {} // Not foldable at this point, leave for runtime
                }
            }
            return Ok(const_folded);
        },
        NodeType::If => precomp_params(context, e),
        NodeType::While => precomp_params(context, e),
        NodeType::Switch => Err(e.lang_error(&context.path, "precomp", "Switch should have been desugared to if/else by desugarer phase")),
        NodeType::FuncDef(func_def) => precomp_func_def(context, e, func_def.clone()),
        NodeType::Declaration(decl) => precomp_declaration(context, e, decl),
        NodeType::Assignment(_) => precomp_params(context, e),
        NodeType::Return | NodeType::Throw => precomp_params(context, e),
        NodeType::Catch => precomp_catch(context, e),
        NodeType::Range => precomp_params(context, e),
        // Struct/enum definitions - need to process default values (which may contain function defs)
        NodeType::StructDef(struct_def) => precomp_struct_def(context, e, struct_def),
        NodeType::EnumDef(_) => Ok(e.clone()),
        // Identifiers can have nested params (e.g., a.b.c for field access chains)
        NodeType::Identifier(_) => precomp_params(context, e),
        // Leaf nodes - no transformation needed
        NodeType::LLiteral(_) | NodeType::DefaultCase | NodeType::Pattern(_) => Ok(e.clone()),
        // Break and Continue are leaf nodes (no params) - no transformation needed
        NodeType::Break | NodeType::Continue => Ok(e.clone()),
        // Named arguments - transform the value expression
        NodeType::NamedArg(name) => {
            let mut new_params = Vec::new();
            for p in &e.params {
                new_params.push(precomp_expr(context, p)?);
            }
            Ok(Expr::new_clone(NodeType::NamedArg(name.clone()), e, new_params))
        },
        // ForIn should have been desugared in desugarer phase
        NodeType::ForIn(_) => {
            panic!("ForIn should have been desugared in desugarer phase");
        },
        // Issue #188: Defer should have been desugared in desugarer phase
        NodeType::Defer => {
            panic!("Defer should have been desugared in desugarer phase");
        },
        // Issue #185: OwnArg should have been desugared in desugarer phase
        NodeType::OwnArg => {
            panic!("OwnArg should have been desugared in desugarer phase");
        },
    }
}

// ---------- Compile-time constant folding

/// Check if an FCall is a macro call.
fn is_macro_fcall(context: &Context, e: &Expr) -> bool {
    let mut e_clone = e.clone();
    match get_func_def_for_fcall_with_expr(context, &mut e_clone) {
        Ok(Some(func_def)) => func_def.is_macro(),
        Ok(None) | Err(_) => false,
    }
}

/// Check if an expression can be evaluated at compile time.
/// Currently only handles literals and pure function calls with literal arguments.
fn is_comptime_evaluable(context: &Context, e: &Expr) -> Result<bool, String> {
    match &e.node_type {
        NodeType::LLiteral(_) => Ok(true),
        // Type definitions and function definitions are static metadata - always comptime
        NodeType::StructDef(_) => Ok(true),
        NodeType::EnumDef(_) => Ok(true),
        NodeType::FuncDef(_) => Ok(true),
        NodeType::Identifier(name) => {
            // Check if this is a simple identifier (no field access chain)
            if !e.params.is_empty() {
                return Ok(false);  // Field access chains not supported
            }
            // Look up the symbol and check if it's a comptime const
            if let Some(symbol) = context.scope_stack.lookup_symbol(name) {
                return Ok(symbol.is_comptime_const);
            }
            Ok(false)
        }
        NodeType::FCall(_) => {
            let f_name = get_func_name_in_call(e);
            // Special case: exit terminates the program
            if f_name == "exit" {
                return Ok(false);
            }
            // TODO: Properly detect ext_funcs and functions with side effects.
            // For now, hardcode malloc exclusion since it's an ext_func with side effects.
            if f_name == "malloc" {
                return Ok(false);
            }
            // Use get_func_def_for_fcall_with_expr like interpreter does
            let mut e_clone = e.clone();
            let func_def = match get_func_def_for_fcall_with_expr(context, &mut e_clone) {
                Ok(Some(f)) => f,
                Ok(None) => {
                    // Could be a struct constructor - check if all args are comptime
                    let combined_name = crate::rs::parser::get_combined_name(&context.path, e.params.first().unwrap()).unwrap_or_default();
                    if context.scope_stack.has_struct(&combined_name) {
                        // Struct constructors can't be faithfully folded to AST literals
                        // (e.g., Str() becomes a borrowed literal, not owned empty string).
                        // Only fold at global scope where precomp_declaration handles storage.
                        let at_global = context.scope_stack.frames.len() == 1;
                        if !at_global {
                            return Ok(false);
                        }
                        // At global scope: check all args are comptime
                        for i in 1..e.params.len() {
                            // Handle named args - check the value inside
                            let arg = e.params.get(i).unwrap();
                            let arg_to_check = if let NodeType::NamedArg(_) = &arg.node_type {
                                arg.params.first().unwrap_or(arg)
                            } else {
                                arg
                            };
                            if !is_comptime_evaluable(context, arg_to_check)? {
                                return Ok(false);
                            }
                        }
                        return Ok(true); // Struct constructor with all comptime args
                    }
                    // Check if it's an enum constructor (e.g., Color.Green(true))
                    if context.scope_stack.is_enum_constructor(&combined_name) {
                        // Enum constructors: only fold at global scope
                        let at_global = context.scope_stack.frames.len() == 1;
                        if !at_global {
                            return Ok(false);
                        }
                        for i in 1..e.params.len() {
                            if !is_comptime_evaluable(context, e.params.get(i).unwrap())? {
                                return Ok(false);
                            }
                        }
                        return Ok(true);
                    }
                    return Ok(false);
                },
                Err(_) => {
                    return Ok(false); // Unknown function
                }
            };
            // Must be pure function (not proc) that returns a value
            if func_def.is_proc() {
                return Ok(false);
            }
            // Funcs with no return type can't be folded (nothing to fold to)
            if func_def.sig.return_types.is_empty() {
                return Ok(false);
            }
            // Functions that can throw are allowed - if they actually throw,
            // we'll report the error in eval_comptime.
            // Inside function bodies: zero-arg functions likely depend on global
            // mutable state (e.g., counters) - don't fold them.
            let at_global = context.scope_stack.frames.len() == 1;
            if !at_global && e.params.len() <= 1 {
                return Ok(false); // No user args = likely stateful
            }
            // All arguments must be comptime-evaluable
            for i in 1..e.params.len() {
                if !is_comptime_evaluable(context, e.params.get(i).unwrap())? {
                    return Ok(false);
                }
            }
            Ok(true)
        },
        // Future: handle constant identifiers (true, false, user constants)
        _ => Ok(false),
    }
}

/// Evaluate a comptime-evaluable expression and convert result back to AST literal.
fn eval_comptime(context: &mut Context, e: &Expr) -> Result<Expr, String> {
    // Save and restore context.path - interpreter may change it during function calls
    let saved_path = context.path.clone();
    let eval_result = eval_expr(context, e);
    context.path = saved_path;
    let result = eval_result?;

    // Check if the function threw an exception during evaluation
    if result.is_throw {
        let thrown_type = if result.thrown_type.is_empty() { "unknown" } else { &result.thrown_type };
        return Err(e.error(&context.path, "precomp",
            &format!("Exception '{}' thrown during precomputation: {}", thrown_type, result.value)));
    }

    // EvalResult.value is a String representation of the value
    // Convert back to LLiteral based on the result type
    let value_type = get_value_type(context, e)?;
    match &value_type {
        ValueType::TCustom(ref t) if t == "I64" => {
            Ok(Expr::new_clone(NodeType::LLiteral(Literal::Number(result.value.clone())), e, vec![]))
        },
        ValueType::TCustom(ref t) if t == "U8" => {
            // U8 literals can't be represented distinctly from I64 in the AST
            // (both use Literal::Number), so skip folding to avoid type erasure.
            Ok(e.clone())
        },
        ValueType::TCustom(ref t) if t == "Str" => {
            Ok(Expr::new_clone(NodeType::LLiteral(Literal::Str(result.value.clone())), e, vec![]))
        },
        ValueType::TCustom(ref type_name) => {
            // Check if it's a struct type - result.value is the instance name
            if context.scope_stack.has_struct(type_name) {
                // Try to convert struct back to literal, fall back to original expr if unsupported
                return EvalHeap::to_struct_literal(context, &result.value, type_name, e)
                    .or_else(|_| Ok(e.clone()));
            }
            // For enums and other types: eval_expr was called (catching any errors),
            // but we can't convert the result back to AST literal, so return original
            Ok(e.clone())
        },
        // Issue #105: First-class structs - macro returning a struct definition
        ValueType::TType(TTypeDef::TStructDef) => {
            let struct_name = &result.value;
            match context.scope_stack.lookup_struct(struct_name) {
                Some(struct_def) => {
                    let sd = struct_def.clone();
                    Ok(Expr::new_clone(NodeType::StructDef(sd), e, vec![]))
                },
                None => Err(e.error(&context.path, "precomp",
                    &format!("Macro returned struct type but definition '{}' not found", struct_name)))
            }
        },
        // Issue #106: First-class enums - macro returning an enum definition
        ValueType::TType(TTypeDef::TEnumDef) => {
            let enum_name = &result.value;
            match context.scope_stack.lookup_enum(enum_name) {
                Some(enum_def) => {
                    let ed = enum_def.clone();
                    Ok(Expr::new_clone(NodeType::EnumDef(ed), e, vec![]))
                },
                None => Err(e.error(&context.path, "precomp",
                    &format!("Macro returned enum type but definition '{}' not found", enum_name)))
            }
        },
        // For other types, eval was done (errors caught), return original (no folding)
        _ => Ok(e.clone()),
    }
}

// ---------- AST transformation

/// Transform Body node - recursively transform all statements
fn precomp_body(context: &mut Context, e: &Expr) -> Result<Expr, String> {
    let mut new_params = Vec::new();
    for p in &e.params {
        let saved_decl_count = context.anon_struct_decls.len();
        let saved_enum_decl_count = context.anon_enum_decls.len();
        let result = precomp_expr(context, p)?;
        // Issue #105: inject pending anonymous struct declarations before the statement that uses them
        if context.anon_struct_decls.len() > saved_decl_count {
            let pending: Vec<Expr> = context.anon_struct_decls.drain(saved_decl_count..).collect();
            for decl in pending {
                new_params.push(decl);
            }
        }
        // Issue #106: inject pending anonymous enum declarations before the statement that uses them
        if context.anon_enum_decls.len() > saved_enum_decl_count {
            let pending: Vec<Expr> = context.anon_enum_decls.drain(saved_enum_decl_count..).collect();
            for decl in pending {
                new_params.push(decl);
            }
        }
        new_params.push(result);
    }
    Ok(Expr::new_clone(e.node_type.clone(), e, new_params))
}

/// Transform node params - recursively transform all child expressions
fn precomp_params(context: &mut Context, e: &Expr) -> Result<Expr, String> {
    let mut new_params = Vec::new();
    for p in &e.params {
        new_params.push(precomp_expr(context, p)?);
    }
    Ok(Expr::new_clone(e.node_type.clone(), e, new_params))
}

/// Transform StructDef - recursively transform default values (which contain function defs)
fn precomp_struct_def(context: &mut Context, e: &Expr, struct_def: &StructDef) -> Result<Expr, String> {
    let mut new_default_values = HashMap::new();
    for (name, value_expr) in &struct_def.default_values {
        // Bug #40 fix: For method definitions, set function name context
        let is_func = matches!(&value_expr.node_type, NodeType::FuncDef(_));
        let saved_func = context.current_precomp_func.clone();
        let saved_counter = context.precomp_forin_counter;
        if is_func {
            context.current_precomp_func = name.clone();
            context.precomp_forin_counter = 0;
        }

        new_default_values.insert(name.clone(), precomp_expr(context, value_expr)?);

        // Bug #40 fix: Restore previous function context
        if is_func {
            context.current_precomp_func = saved_func;
            context.precomp_forin_counter = saved_counter;
        }
    }
    // Also transform ns default values (namespace function bodies)
    let mut ns_new_default_values = HashMap::new();
    for (name, value_expr) in &struct_def.ns.default_values {
        let is_func = matches!(&value_expr.node_type, NodeType::FuncDef(_));
        let saved_func = context.current_precomp_func.clone();
        let saved_counter = context.precomp_forin_counter;
        if is_func {
            context.current_precomp_func = name.clone();
            context.precomp_forin_counter = 0;
        }

        let transformed = precomp_expr(context, value_expr)?;
        ns_new_default_values.insert(name.clone(), transformed);

        if is_func {
            context.current_precomp_func = saved_func;
            context.precomp_forin_counter = saved_counter;
        }
    }
    let new_ns = NamespaceDef {
        members: struct_def.ns.members.clone(),
        default_values: ns_new_default_values,
    };

    let new_struct_def = StructDef {
        members: struct_def.members.clone(),
        default_values: new_default_values,
        ns: new_ns,
    };
    Ok(Expr::new_clone(NodeType::StructDef(new_struct_def), e, e.params.clone()))
}

/// Transform FuncDef - push scope frame for function args, transform body, pop frame
fn precomp_func_def(context: &mut Context, e: &Expr, func_def: FuncDef) -> Result<Expr, String> {
    // Push a new scope frame with the function's parameters
    context.scope_stack.push(ScopeType::Function);
    for arg in &func_def.sig.args {
        context.scope_stack.declare_symbol(arg.name.clone(), SymbolInfo {
            value_type: arg.value_type.clone(),
            is_mut: arg.is_mut,
            
            is_own: arg.is_own,
            is_comptime_const: false,  // Function args are not comptime constants
        });
    }

    // Transform the function body
    let mut new_body = Vec::new();
    for stmt in &func_def.body {
        new_body.push(precomp_expr(context, stmt)?);
    }

    // Pop the function scope frame
    let _ = context.scope_stack.pop();

    let new_func_def = FuncDef {
        sig: func_def.sig.clone(),
        arg_names: func_def.arg_names.clone(),
        body: new_body,
        source_path: func_def.source_path.clone(),
    };
    Ok(Expr::new_clone(NodeType::FuncDef(new_func_def), e, e.params.clone()))
}

// Issue #105 Step 4d: Check if a declared metatype annotation matches an inferred TType
fn metatype_matches(declared: &ValueType, inferred: &ValueType) -> bool {
    match (declared, inferred) {
        (ValueType::TCustom(name), ValueType::TType(TTypeDef::TStructDef)) if name == "StructDef" => true,
        (ValueType::TCustom(name), ValueType::TType(TTypeDef::TEnumDef)) if name == "EnumDef" => true,
        (ValueType::TCustom(name), ValueType::TType(TTypeDef::TFuncSig)) if name == "FuncSig" => true,
        (ValueType::TCustom(name), ValueType::TType(TTypeDef::TFuncDef)) if name == "FuncDef" => true,
        // name : FuncDef = func(a: I64) { body } -- func literal inferred as TFunction
        (ValueType::TCustom(name), ValueType::TFunction(_)) if name == "FuncDef" => true,
        _ => false,
    }
}

/// Transform Declaration - register the declared variable in scope, then transform value
fn precomp_declaration(context: &mut Context, e: &Expr, decl: &crate::rs::parser::Declaration) -> Result<Expr, String> {
    // Eagerly create default instance template for this struct type
    let inner_e = e.params.get(0).unwrap();
    let mut value_type = match get_value_type(context, &inner_e) {
        Ok(val_type) => val_type,
        Err(error_string) => {
            return Err(e.lang_error(&context.path, "precomp", &error_string));
        },
    };
    // Issue #91: Detect function signature definitions
    if let NodeType::FuncDef(func_def) = &inner_e.node_type {
        if is_function_signature(func_def) {
            value_type = ValueType::TType(TTypeDef::TFuncSig);
        }
    }

    // Issue #91: Resolve function signature type references
    // When decl.value_type is a custom type name that resolves to a FunctionSig,
    // look up the signature and set value_type to match the function type.
    let mut sig_func_def: Option<FuncDef> = None;
    if let ValueType::TCustom(ref sig_name) = decl.value_type {
        if let Some(sym) = context.scope_stack.lookup_symbol(sig_name) {
            if sym.value_type == ValueType::TType(TTypeDef::TFuncSig) {
                if let Some(sfd) = context.scope_stack.lookup_func(sig_name) {
                    sig_func_def = Some(sfd.clone());
                    value_type = ValueType::TFunction(sfd.sig.function_type.clone());
                }
            }
        }
    }

    // Issue #105: Accept INFER_TYPE inside macro bodies (typer doesn't resolve inside FuncDef bodies)
    if decl.value_type == ValueType::TCustom(INFER_TYPE.to_string()) {
        // Infer type from the value - this is the := pattern inside a macro
    } else if sig_func_def.is_some() {
        // Issue #91: FunctionSig reference resolved above - skip type check
    // Issue #105 Step 4d: Accept explicit metatype annotations
    } else if metatype_matches(&decl.value_type, &value_type) {
        // StructDef/EnumDef/FuncSig annotations match TType variants
    } else
    // Type checking
    if decl.value_type == ValueType::TCustom("U8".to_string()) && value_type == ValueType::TCustom("I64".to_string()) {
        value_type = decl.value_type.clone();
    } else if value_type != decl.value_type {
        return Err(e.lang_error(&context.path, "precomp", &format!("'{}' declared of type {} but initialized to type {:?}.", decl.name, value_type_to_str(&decl.value_type), value_type_to_str(&value_type))));
    }
    if let ValueType::TType(TTypeDef::TEnumDef) = value_type {
        match &inner_e.node_type {
            NodeType::EnumDef(enum_def) => {
                context.scope_stack.declare_enum(decl.name.clone(), enum_def.clone());
                context.scope_stack.declare_symbol(decl.name.to_string(), SymbolInfo{value_type: value_type.clone(), is_mut: decl.is_mut, is_own: decl.is_own, is_comptime_const: true });
                // Update scope_stack with namespace FuncDefs so interpreter uses desugared versions
                for (name, ns_value_expr) in &enum_def.ns.default_values {
                    if let NodeType::FuncDef(func_def) = &ns_value_expr.node_type {
                        let full_name = format!("{}.{}", decl.name, name);
                        context.scope_stack.update_func(&full_name, func_def.clone());
                    }
                }
                return Ok(e.clone());
            },
            _ => return Err(e.lang_error(&context.path, "precomp", &format!("Cannot declare '{}' of type '{}', expected enum definition.",
                                                          &decl.name, value_type_to_str(&decl.value_type)))),
        }
    }
    if let ValueType::TType(TTypeDef::TStructDef) = value_type {
        if let NodeType::StructDef(struct_def) = &inner_e.node_type {
            // Issue #108: Don't overwrite if struct already exists with merged namespace members
            if context.scope_stack.lookup_struct(&decl.name).is_none() {
                context.scope_stack.declare_struct(decl.name.clone(), struct_def.clone());
            }
            let saved_path = context.path.clone();
            eval_declaration(decl, context, e)?;
            context.path = saved_path;
        }
    }
    // Issue #91: Register function signature type and return early
    if let ValueType::TType(TTypeDef::TFuncSig) = value_type {
        if let NodeType::FuncDef(func_def) = &inner_e.node_type {
            context.scope_stack.declare_func(decl.name.clone(), func_def.clone());
            context.scope_stack.declare_symbol(decl.name.clone(), SymbolInfo {
                value_type: value_type.clone(),
                is_mut: decl.is_mut,
                
                is_own: decl.is_own,
                is_comptime_const: true,
            });
            return Ok(e.clone());
        }
    }

    // Issue #105: If inner_e is an FCall (e.g. macro call returning struct), we need to
    // process it through precomp_expr first, then check if the result is a StructDef.
    // The struct registration for literal StructDef RHS already happened above.
    // For macro-expanded StructDefs, we do it after new_params processing below.

    // Bug #40 fix: For function declarations, set the function name and reset counter
    // BEFORE processing the body so for-in loops get deterministic names
    let is_func_decl = !e.params.is_empty() && matches!(&e.params.get(0).unwrap().node_type, NodeType::FuncDef(_));
    let saved_func = context.current_precomp_func.clone();
    let saved_counter = context.precomp_forin_counter;
    if is_func_decl {
        context.current_precomp_func = decl.name.clone();
        context.precomp_forin_counter = 0;
    }

    // Issue #91: Resolve arg/return/throw types from function signature into the FuncDef
    // BEFORE processing the body, so UFCS resolution inside the body knows the arg types.
    let resolved_inner_e;
    if let Some(ref sig) = sig_func_def {
        if let NodeType::FuncDef(ref func_def) = inner_e.node_type {
            if func_def.sig.args.len() != sig.sig.args.len() {
                return Err(e.lang_error(&context.path, "precomp", &format!(
                    "'{}' has {} parameters but function signature '{}' expects {}.",
                    decl.name, func_def.sig.args.len(),
                    value_type_to_str(&decl.value_type), sig.sig.args.len())));
            }
            let mut resolved_fd = func_def.clone();
            for (i, sig_arg) in sig.sig.args.iter().enumerate() {
                resolved_fd.sig.args[i].value_type = sig_arg.value_type.clone();
            }
            resolved_fd.sig.return_types = sig.sig.return_types.clone();
            resolved_fd.sig.throw_types = sig.sig.throw_types.clone();
            resolved_fd.sig.function_type = sig.sig.function_type.clone();
            resolved_inner_e = Some(Expr::new_clone(NodeType::FuncDef(resolved_fd), &inner_e, inner_e.params.clone()));
        } else {
            resolved_inner_e = None;
        }
    } else {
        resolved_inner_e = None;
    }

    // First transform the value expression (if any)
    let new_params = if !e.params.is_empty() {
        let mut new_params = Vec::new();
        if let Some(ref resolved) = resolved_inner_e {
            new_params.push(precomp_expr(context, resolved)?);
        } else {
            for p in &e.params {
                new_params.push(precomp_expr(context, p)?);
            }
        }
        new_params
    } else {
        Vec::new()
    };

    // Bug #40 fix: Restore previous function context
    if is_func_decl {
        context.current_precomp_func = saved_func;
        context.precomp_forin_counter = saved_counter;
    }

    // REM: Declarations currently always require an initialization value,
    // so new_params should never be empty.
    if e.params.len() != 1 {
        return Err(e.lang_error(&context.path, "precomp", "Declarations can have only one child expression"));
    }

    // Issue #105: After anonymous struct expansion, re-evaluate the type from the transformed expression
    if value_type == ValueType::TCustom(INFER_TYPE.to_string()) && !new_params.is_empty() {
        if let Ok(new_type) = get_value_type(context, &new_params[0]) {
            if new_type != ValueType::TCustom(INFER_TYPE.to_string()) {
                value_type = new_type;
            }
        }
    }

    // Issue #105: After macro expansion, check if the result is a StructDef
    // and register it (the pre-expansion check above only handles literal StructDef RHS)
    if let ValueType::TType(TTypeDef::TStructDef) = &value_type {
        if !new_params.is_empty() {
            if let NodeType::StructDef(struct_def) = &new_params[0].node_type {
                if context.scope_stack.lookup_struct(&decl.name).is_none() {
                    context.scope_stack.declare_struct(decl.name.clone(), struct_def.clone());
                    let new_e = Expr::new_clone(e.node_type.clone(), e, new_params.clone());
                    let saved_path = context.path.clone();
                    eval_declaration(decl, context, &new_e)?;
                    context.path = saved_path;
                }
            }
        }
    }

    // Update scope_stack with transformed namespace FuncDefs so interpreter uses them
    if !new_params.is_empty() {
        if let NodeType::StructDef(struct_def) = &new_params[0].node_type {
            for (name, ns_value_expr) in &struct_def.ns.default_values {
                if let NodeType::FuncDef(func_def) = &ns_value_expr.node_type {
                    let full_name = format!("{}.{}", decl.name, name);
                    context.scope_stack.update_func(&full_name, func_def.clone());
                }
            }
        }
    }

    // Determine if this is a compile-time constant
    // Only mut matters for constantness - copy/own are about ownership, orthogonal to comptime.
    // Any type can be comptime - the type doesn't matter, only how the value is computed.
    let is_comptime_const = !decl.is_mut
        && is_comptime_evaluable(context, &new_params[0])?;

    // Register the declared variable in scope
    context.scope_stack.declare_symbol(decl.name.clone(), SymbolInfo {
        value_type: value_type.clone(),
        is_mut: decl.is_mut,
        
        is_own: decl.is_own,
        is_comptime_const,
    });

    // Also register function definitions so UFCS can resolve their return types
    if let ValueType::TFunction(_) = &value_type {
        if let NodeType::FuncDef(func_def) = &new_params[0].node_type {
            context.scope_stack.declare_func(decl.name.clone(), func_def.clone());
        }
    }

    // Store I64/U8/Str declarations in heap when their initializer is comptime-evaluable.
    // Unlike the is_comptime_const flag (which also requires !is_mut for folding identifiers),
    // we store ALL comptime-evaluable values including mut ones, just like interpreter does.
    // This is needed for eval_expr to work during constant folding (e.g., mut loop variables).
    // Only do this at global scope - inside function bodies, evaluating could cause side effects
    // to run at compile time AND runtime (e.g., print_debug func in mode liba).
    let at_global_scope = context.scope_stack.frames.len() == 1;
    if at_global_scope {
        if let ValueType::TCustom(ref custom_type_name) = &value_type {
            match custom_type_name.as_str() {
                "I64" | "U8" | "Str" => {
                    if is_comptime_evaluable(context, &new_params[0])? {
                        let inner_e = &new_params[0];
                        let result = eval_expr(context, inner_e)?;
                        if !result.is_throw {
                            EvalHeap::insert_primitive(context, &decl.name, &value_type, &result.value, e)?;
                        }
                    }
                },
                _ => {},
            }
        }
    }

    // For non-mut struct instance declarations (like `true := Bool.from_i64(1)`),
    // run eval_declaration to store the instance in EvalHeap so ccodegen can find it.
    // Only do this at global scope (same reason as above - avoid side effects inside func bodies).
    if at_global_scope && !decl.is_mut && !decl.is_own && !new_params.is_empty() && is_comptime_evaluable(context, &new_params[0])? {
        if let ValueType::TCustom(ref custom_type_name) = &value_type {
            // Skip primitives (I64, U8) - handled above. Skip Str - needs special handling.
            if custom_type_name != "I64" && custom_type_name != "U8" && custom_type_name != "Str" {
                // Check if this is a struct type (not a struct definition)
                if let Some(sym) = context.scope_stack.lookup_symbol(custom_type_name) {
                    if sym.value_type == ValueType::TType(TTypeDef::TStructDef) {
                        let saved_path = context.path.clone();
                        eval_declaration(decl, context, e)?;
                        context.path = saved_path;

                        // Bug #133 fix: Track precomputed heap values for static array serialization
                        let needs_heap = EvalHeap::type_needs_heap_serialization(context, custom_type_name);
                        if needs_heap {
                            context.precomputed_heap_values.push(PrecomputedHeapValue {
                                var_name: decl.name.clone(),
                                instance_name: decl.name.clone(),
                                type_name: custom_type_name.clone(),
                            });
                        }
                    }
                }
            }
        }
    }

    Ok(Expr::new_clone(e.node_type.clone(), e, new_params))
}

/// Transform Catch node - register the catch variable in scope before processing body
/// This enables UFCS resolution for methods called on the error variable
/// Catch structure: [var_name_expr, type_expr, body_expr]
fn precomp_catch(context: &mut Context, e: &Expr) -> Result<Expr, String> {
    if e.params.len() < 3 {
        // Malformed catch - just use default handling
        return precomp_params(context, e);
    }

    // Get the catch variable name and type
    let var_name = match &e.params.get(0).unwrap().node_type {
        NodeType::Identifier(name) => name.clone(),
        _ => return precomp_params(context, e), // Not a simple identifier, use default handling
    };
    let type_name = match &e.params.get(1).unwrap().node_type {
        NodeType::Identifier(name) => name.clone(),
        _ => return precomp_params(context, e), // Not a simple type, use default handling
    };

    // Push a scope frame for the catch block
    context.scope_stack.push(ScopeType::Catch);

    // Register the catch variable in the scope
    context.scope_stack.declare_symbol(var_name.clone(), SymbolInfo {
        value_type: ValueType::TCustom(type_name),
        is_mut: false,
        
        is_own: false,
        is_comptime_const: false,
    });

    // Transform the catch body (params[2])
    let new_body = precomp_expr(context, e.params.get(2).unwrap())?;

    // Pop the scope frame
    let _ = context.scope_stack.pop();

    // Return the transformed catch with original var_name, type, and new body
    Ok(Expr::new_clone(
        NodeType::Catch,
        e,
        vec![e.params.get(0).unwrap().clone(), e.params.get(1).unwrap().clone(), new_body],
    ))
}

/// Transform FCall node - handles comptime intrinsics, struct/enum constructors, and import()
/// UFCS resolution and named argument reordering happen in the ufcs phase (before precomp)
fn precomp_fcall(context: &mut Context, e: &Expr) -> Result<Expr, String> {
    // 1. Check for compile-time intrinsics (loc, _file, _line, _col)
    if let Some(replaced) = try_replace_comptime_intrinsic(context, e) {
        return Ok(replaced);
    }

    // Get func_expr and combined_name before any transformation
    let func_expr = match e.params.first() {
        Some(expr) => expr,
        None => return Ok(e.clone()), // Empty FCall, shouldn't happen but just return as-is
    };

    // Issue #105: anonymous struct instantiation - struct { ... }(args)
    // Register the anonymous struct and replace StructDef with Identifier
    if let NodeType::StructDef(struct_def) = &func_expr.node_type {
        let temp_name = format!("AnonStruct{}", context.anon_struct_counter);
        context.anon_struct_counter += 1;
        context.scope_stack.declare_struct(temp_name.clone(), struct_def.clone());
        context.scope_stack.declare_symbol(temp_name.clone(), SymbolInfo {
            value_type: ValueType::TType(TTypeDef::TStructDef),
            is_mut: false,
            
            is_own: false,
            is_comptime_const: false,
        });
        // Register immutable fields as namespace constants
        for member_decl in &struct_def.members {
            if !member_decl.is_mut {
                if let Some(member_expr) = struct_def.default_values.get(&member_decl.name) {
                    let member_value_type = get_value_type(context, member_expr).unwrap_or(ValueType::TCustom(INFER_TYPE.to_string()));
                    let member_full_name = format!("{}.{}", temp_name, member_decl.name);
                    context.scope_stack.declare_symbol(member_full_name, SymbolInfo {
                        value_type: member_value_type,
                        is_mut: member_decl.is_mut,
                        
                        is_own: member_decl.is_own,
                        is_comptime_const: false,
                    });
                }
            }
        }
        // Generate struct methods (delete/clone) and set ns on struct
        if let Some(auto_ns) = generate_struct_methods(&temp_name, struct_def, e.line, e.col, &context.scope_stack.get_func_sig_types()) {
            // Update the registered struct's ns field
            let mut updated = struct_def.clone();
            updated.ns = auto_ns;
            context.scope_stack.declare_struct(temp_name.clone(), updated.clone());
            let mut ns_errors_vec = Vec::new();
            crate::rs::init::init_namespace_into_struct(context, &temp_name, &updated.ns, e, &mut ns_errors_vec);
            if !ns_errors_vec.is_empty() {
                return Err(ns_errors_vec.join("\n"));
            }
        }
        // Create default instance for codegen
        create_default_instance(context, &temp_name, e)?;
        // Add struct declaration to pending list for codegen to emit
        let struct_decl = Declaration {
            name: temp_name.clone(),
            value_type: ValueType::TType(TTypeDef::TStructDef),
            is_mut: false,
            
            is_own: false,
            default_value: None,
        };
        let struct_decl_expr = Expr::new_clone(
            NodeType::Declaration(struct_decl),
            func_expr,
            vec![Expr::new_clone(NodeType::StructDef(struct_def.clone()), func_expr, vec![])],
        );
        context.anon_struct_decls.push(struct_decl_expr);
        // Replace StructDef with Identifier and continue as normal struct constructor
        let id_expr = Expr::new_clone(NodeType::Identifier(temp_name.clone()), func_expr, vec![]);
        let mut new_params = vec![id_expr];
        for p in e.params.iter().skip(1) {
            new_params.push(precomp_expr(context, p)?);
        }
        return Ok(Expr::new_clone(e.node_type.clone(), e, new_params));
    }

    let combined_name = if let NodeType::Identifier(_) = &func_expr.node_type {
        crate::rs::parser::get_combined_name(&context.path, func_expr)?
    } else {
        String::new()
    };

    // 2. Struct constructor - create instance like eval does (before arg transform)
    if !combined_name.is_empty() && context.scope_stack.has_struct(&combined_name) {
        create_default_instance(context, &combined_name, &e)?;
        if let NodeType::Identifier(id_name) = &func_expr.node_type {
            if func_expr.params.is_empty() {
                insert_struct_instance(context, id_name, &combined_name, &e)?;
            }
        }
        // Transform arguments for struct constructor
        let mut struct_params = Vec::new();
        for p in &e.params {
            struct_params.push(precomp_expr(context, p)?);
        }
        return Ok(Expr::new_clone(e.node_type.clone(), &e, struct_params));
    }

    // 3. Enum constructor (e.g., Color.Green(true)) - before arg transform
    if context.scope_stack.is_enum_constructor(&combined_name) {
        // Transform arguments for enum constructor
        let mut enum_params = Vec::new();
        for p in &e.params {
            enum_params.push(precomp_expr(context, p)?);
        }
        return Ok(Expr::new_clone(e.node_type.clone(), &e, enum_params));
    }

    // 4. Transform all arguments
    let mut all_transformed_params = Vec::new();
    for p in &e.params {
        all_transformed_params.push(precomp_expr(context, p)?);
    }
    let e = Expr::new_clone(e.node_type.clone(), &e, all_transformed_params);

    // Get func_expr again from transformed expression
    let func_expr = match e.params.first() {
        Some(expr) => expr,
        None => return Ok(e),
    };

    if let NodeType::Identifier(_id_name) = &func_expr.node_type {
        let combined_name = crate::rs::parser::get_combined_name(&context.path, func_expr)?;

        // 5. Handle ext functions and import()
        if let Some(func_def) = context.scope_stack.lookup_func(&combined_name) {
            // Ext functions: evaluation happens through eval_comptime path (see doc/precomp.org)
            // Exception: import() must run during precomp to load code
            if func_def.is_ext() {
                let parts: Vec<&str> = combined_name.split('.').collect();
                if let Some(&"import") = parts.last() {
                    eval_expr(context, &e)?;
                }
            }
        }
    }

    // No transformation needed (UFCS already resolved in ufcs phase)
    Ok(e)
}
