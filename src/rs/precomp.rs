// Precomputation phase: Transforms UFCS calls into regular function calls
// and performs compile-time constant folding for pure functions.
// This phase runs after typer, before interpreter/builder.

use crate::rs::init::{Context, get_value_type, get_func_name_in_call, SymbolInfo, ScopeType, PrecomputedHeapValue};
use crate::rs::typer::get_func_def_for_fcall_with_expr;
use std::collections::HashMap;
use crate::rs::parser::{
    Expr, NodeType, ValueType, SStructDef, SEnumDef, EnumVariant, SFuncDef, SNamespaceDef, Declaration, Literal, TTypeDef,
    FunctionType, PatternInfo, value_type_to_str, INFER_TYPE,
};
use crate::rs::interpreter::{eval_expr, eval_declaration, insert_struct_instance, create_default_instance};
use crate::rs::eval_heap::EvalHeap;
use crate::rs::precomp_ext::try_replace_comptime_intrinsic;
use crate::rs::preinit::{generate_struct_methods, generate_enum_methods};

// ---------- Issue #105: Early struct macro expansion

/// Build a substitution map from macro Type/Dynamic parameters to actual type names.
/// For `make_vec3(I64)` where `make_vec3` takes `T: Type`, returns {"T": "I64"}.
fn build_type_param_subs(func_def: &SFuncDef, fcall: &Expr) -> HashMap<String, String> {
    let mut subs = HashMap::new();
    for (i, arg) in func_def.args.iter().enumerate() {
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
fn substitute_type_params_in_funcdef(func_def: &SFuncDef, subs: &HashMap<String, String>) -> SFuncDef {
    let new_args = func_def.args.iter().map(|arg| {
        if let ValueType::TCustom(ref type_name) = arg.value_type {
            if let Some(concrete) = subs.get(type_name) {
                let mut new_arg = arg.clone();
                new_arg.value_type = ValueType::TCustom(concrete.clone());
                return new_arg;
            }
        }
        arg.clone()
    }).collect();
    let new_returns = func_def.return_types.iter().map(|rt| {
        if let ValueType::TCustom(ref type_name) = rt {
            if let Some(concrete) = subs.get(type_name) {
                return ValueType::TCustom(concrete.clone());
            }
        }
        rt.clone()
    }).collect();
    let new_throws = func_def.throw_types.iter().map(|tt| {
        if let ValueType::TCustom(ref type_name) = tt {
            if let Some(concrete) = subs.get(type_name) {
                return ValueType::TCustom(concrete.clone());
            }
        }
        tt.clone()
    }).collect();
    let new_body = func_def.body.iter().map(|e| substitute_type_params_in_expr(e, subs)).collect();
    SFuncDef {
        function_type: func_def.function_type.clone(),
        args: new_args,
        return_types: new_returns,
        throw_types: new_throws,
        body: new_body,
        source_path: func_def.source_path.clone(),
    }
}

/// Apply type param substitution to a struct definition's member types and default values.
fn substitute_type_params_in_struct(struct_def: &SStructDef, subs: &HashMap<String, String>) -> SStructDef {
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

    SStructDef { members: new_members, default_values: new_defaults }
}

/// Issue #106: Apply type param substitution to an enum definition's variant payload types.
fn substitute_type_params_in_enum(enum_def: &SEnumDef, subs: &HashMap<String, String>) -> SEnumDef {
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
    SEnumDef { variants: new_variants, methods: enum_def.methods.clone() }
}

/// Extract namespace stmts from a macro's body AST.
/// Scans for Return nodes or Declaration nodes containing a StructDef or EnumDef with params (namespace stmts).
/// Returns the first matching set of namespace params (simple macros only).
fn extract_namespace_stmts_from_macro(func_def: &SFuncDef) -> Vec<Expr> {
    for stmt in &func_def.body {
        // Pattern 1: return struct/enum { ... namespace: ... }
        if matches!(&stmt.node_type, NodeType::Return) {
            if let Some(ret_val) = stmt.params.first() {
                if (matches!(&ret_val.node_type, NodeType::StructDef(_)) || matches!(&ret_val.node_type, NodeType::EnumDef(_)))
                    && !ret_val.params.is_empty() {
                    return ret_val.params.clone();
                }
            }
        }
        // Pattern 2: TemplatedPtr/TemplatedOption := struct/enum { ... namespace: ... }
        if let NodeType::Declaration(_) = &stmt.node_type {
            if let Some(val) = stmt.params.first() {
                if (matches!(&val.node_type, NodeType::StructDef(_)) || matches!(&val.node_type, NodeType::EnumDef(_)))
                    && !val.params.is_empty() {
                    return val.params.clone();
                }
            }
        }
    }
    Vec::new()
}

/// Extract the internal type name from a macro body (e.g., "TemplatedPtr" from
/// `TemplatedPtr := struct { ... }` or "TemplatedOption" from `TemplatedOption := enum { ... }`).
/// Returns None for anonymous types (`return struct/enum { ... }`).
fn extract_internal_type_name(func_def: &SFuncDef) -> Option<String> {
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
                    // Check if the function is a macro returning struct
                    let f_name = get_func_name_in_call(inner_e);
                    if let Some(func_def) = context.scope_stack.lookup_func(&f_name) {
                        if func_def.is_macro() && !func_def.return_types.is_empty() {
                            // Extract all data from func_def before mutable borrows
                            let macro_return_type = func_def.return_types[0].clone();
                            let type_subs = build_type_param_subs(&func_def, inner_e);
                            let macro_ns_stmts = extract_namespace_stmts_from_macro(&func_def);
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
                                    let resolved_struct = SStructDef {
                                        members: resolved_members,
                                        default_values: precomputed_defaults,
                                    };
                                    let resolved_expanded = Expr::new_clone(NodeType::StructDef(resolved_struct.clone()), &expanded, vec![]);
                                    // Register the struct in context
                                    context.scope_stack.declare_struct(decl.name.clone(), resolved_struct.clone());
                                    // Replace the FCall with the StructDef in the AST
                                    let new_p = Expr::new_clone(p.node_type.clone(), p, vec![resolved_expanded]);
                                    new_params.push(new_p);
                                    // Issue #105: Check if macro namespace stmts already define delete/clone
                                    let ns_has_delete = macro_ns_stmts.iter().any(|s| {
                                        matches!(&s.node_type, NodeType::Declaration(d) if d.name == "delete")
                                    });
                                    let ns_has_clone = macro_ns_stmts.iter().any(|s| {
                                        matches!(&s.node_type, NodeType::Declaration(d) if d.name == "clone")
                                    });
                                    // Generate delete/clone methods only if not provided by macro namespace
                                    let auto_struct = if ns_has_delete || ns_has_clone {
                                        // Add fake members so generate_struct_methods skips them
                                        let mut fake = resolved_struct.clone();
                                        let dummy = Expr::new_explicit(NodeType::LLiteral(Literal::Number("0".to_string())), vec![], 0, 0);
                                        if ns_has_delete { fake.default_values.insert("delete".to_string(), dummy.clone()); }
                                        if ns_has_clone { fake.default_values.insert("clone".to_string(), dummy); }
                                        fake
                                    } else {
                                        resolved_struct.clone()
                                    };
                                    if let Some(ns_block) = generate_struct_methods(&decl.name, &auto_struct, p.line, p.col) {
                                        // Run init on the namespace block to register the methods
                                        let ns_errors = crate::rs::init::init_context(context, &Expr::new_clone(NodeType::Body, p, vec![ns_block.clone()]))?;
                                        if !ns_errors.is_empty() {
                                            return Err(ns_errors.join("\n"));
                                        }
                                        new_params.push(ns_block);
                                    }
                                    // Issue #105: Process namespace stmts extracted from macro body
                                    if !macro_ns_stmts.is_empty() {
                                        // Build substitution map: type params + internal struct name → external name
                                        let mut ns_subs = type_subs.clone();
                                        if let Some(ref internal_name) = macro_internal_name {
                                            ns_subs.insert(internal_name.clone(), decl.name.clone());
                                        }
                                        // Apply type substitution to namespace stmts
                                        let substituted_stmts: Vec<Expr> = macro_ns_stmts.iter()
                                            .map(|s| substitute_type_params_in_expr(s, &ns_subs))
                                            .collect();
                                        // Build NamespaceDef from substituted stmts (same pattern as split_inline_namespaces)
                                        let mut ns_members = Vec::new();
                                        let mut ns_default_values = HashMap::new();
                                        for stmt in &substituted_stmts {
                                            match &stmt.node_type {
                                                NodeType::Declaration(ns_decl) => {
                                                    ns_members.push(ns_decl.clone());
                                                    if let Some(val) = stmt.params.first() {
                                                        ns_default_values.insert(ns_decl.name.clone(), val.clone());
                                                    }
                                                },
                                                NodeType::Assignment(name) => {
                                                    if let Some(val) = stmt.params.first() {
                                                        let ns_decl = Declaration {
                                                            name: name.clone(),
                                                            value_type: ValueType::TCustom(INFER_TYPE.to_string()),
                                                            is_mut: false,
                                                            is_copy: false,
                                                            is_own: false,
                                                            default_value: None,
                                                        };
                                                        ns_members.push(ns_decl);
                                                        ns_default_values.insert(name.clone(), val.clone());
                                                    }
                                                },
                                                _ => {}
                                            }
                                        }
                                        if !ns_members.is_empty() {
                                            let user_ns_def = SNamespaceDef {
                                                type_name: decl.name.clone(),
                                                members: ns_members,
                                                default_values: ns_default_values,
                                            };
                                            let user_ns_expr = Expr::new_explicit(
                                                NodeType::NamespaceDef(user_ns_def),
                                                vec![],
                                                p.line,
                                                p.col,
                                            );
                                            // Run init on the namespace to register methods
                                            let user_ns_errors = crate::rs::init::init_context(context, &Expr::new_clone(NodeType::Body, p, vec![user_ns_expr.clone()]))?;
                                            if !user_ns_errors.is_empty() {
                                                return Err(user_ns_errors.join("\n"));
                                            }
                                            new_params.push(user_ns_expr);
                                        }
                                    }
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
                                    let resolved_expanded = Expr::new_clone(NodeType::EnumDef(substituted.clone()), &expanded, vec![]);
                                    // Register the enum in context
                                    context.scope_stack.declare_enum(decl.name.clone(), substituted.clone());
                                    // Replace the FCall with the EnumDef in the AST
                                    let new_p = Expr::new_clone(p.node_type.clone(), p, vec![resolved_expanded]);
                                    new_params.push(new_p);
                                    // Check if macro namespace stmts already define delete/clone
                                    let ns_has_delete = macro_ns_stmts.iter().any(|s| {
                                        matches!(&s.node_type, NodeType::Declaration(d) if d.name == "delete")
                                    });
                                    let ns_has_clone = macro_ns_stmts.iter().any(|s| {
                                        matches!(&s.node_type, NodeType::Declaration(d) if d.name == "clone")
                                    });
                                    // Generate delete/clone methods if not provided by macro namespace
                                    if let Some(ns_block) = generate_enum_methods(&decl.name, ns_has_delete, ns_has_clone, p.line, p.col) {
                                        let ns_errors = crate::rs::init::init_context(context, &Expr::new_clone(NodeType::Body, p, vec![ns_block.clone()]))?;
                                        if !ns_errors.is_empty() {
                                            return Err(ns_errors.join("\n"));
                                        }
                                        new_params.push(ns_block);
                                    }
                                    // Process namespace stmts extracted from macro body
                                    if !macro_ns_stmts.is_empty() {
                                        let mut ns_subs = type_subs.clone();
                                        if let Some(ref internal_name) = macro_internal_name {
                                            ns_subs.insert(internal_name.clone(), decl.name.clone());
                                        }
                                        let substituted_stmts: Vec<Expr> = macro_ns_stmts.iter()
                                            .map(|s| substitute_type_params_in_expr(s, &ns_subs))
                                            .collect();
                                        let mut ns_members = Vec::new();
                                        let mut ns_default_values = HashMap::new();
                                        for stmt in &substituted_stmts {
                                            match &stmt.node_type {
                                                NodeType::Declaration(ns_decl) => {
                                                    ns_members.push(ns_decl.clone());
                                                    if let Some(val) = stmt.params.first() {
                                                        ns_default_values.insert(ns_decl.name.clone(), val.clone());
                                                    }
                                                },
                                                NodeType::Assignment(name) => {
                                                    if let Some(val) = stmt.params.first() {
                                                        let ns_decl = Declaration {
                                                            name: name.clone(),
                                                            value_type: ValueType::TCustom(INFER_TYPE.to_string()),
                                                            is_mut: false,
                                                            is_copy: false,
                                                            is_own: false,
                                                            default_value: None,
                                                        };
                                                        ns_members.push(ns_decl);
                                                        ns_default_values.insert(name.clone(), val.clone());
                                                    }
                                                },
                                                _ => {}
                                            }
                                        }
                                        if !ns_members.is_empty() {
                                            let user_ns_def = SNamespaceDef {
                                                type_name: decl.name.clone(),
                                                members: ns_members,
                                                default_values: ns_default_values,
                                            };
                                            let user_ns_expr = Expr::new_explicit(
                                                NodeType::NamespaceDef(user_ns_def),
                                                vec![],
                                                p.line,
                                                p.col,
                                            );
                                            let user_ns_errors = crate::rs::init::init_context(context, &Expr::new_clone(NodeType::Body, p, vec![user_ns_expr.clone()]))?;
                                            if !user_ns_errors.is_empty() {
                                                return Err(user_ns_errors.join("\n"));
                                            }
                                            new_params.push(user_ns_expr);
                                        }
                                    }
                                    modified = true;
                                    continue;
                                }
                            }
                        }
                    }
                }
            }
        }
        new_params.push(p.clone());
    }

    if modified {
        Ok(Expr::new_clone(e.node_type.clone(), e, new_params))
    } else {
        Ok(e.clone())
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
            // Only fold at global scope - inside function definitions, values from other
            // modules may not be available yet (import ordering). Interpreter doesn't
            // evaluate function bodies during import either.
            let at_global_scope = context.scope_stack.frames.len() == 1;

            // Check if this is a macro call - macros MUST be evaluated at compile-time
            // but only when called at global scope with comptime args (same as funcs,
            // just with an error if args aren't comptime instead of silent skip)
            let is_macro_call = is_macro_fcall(context, &const_folded);
            if at_global_scope && is_macro_call {
                // Macros require all arguments to be compile-time evaluable
                if !is_comptime_evaluable(context, &const_folded)? {
                    let f_name = get_func_name_in_call(&const_folded);
                    return Err(const_folded.error(&context.path, "precomp",
                        &format!("Macro '{}' requires all arguments to be compile-time constants", f_name)));
                }
                // Force compile-time evaluation
                const_folded = eval_comptime(context, &const_folded)?;
                return Ok(const_folded);
            }

            if at_global_scope && is_comptime_evaluable(context, &const_folded)? {
                const_folded = eval_comptime(context, &const_folded)?;
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
        // Issue #108: NamespaceDef - transform function bodies like StructDef
        NodeType::NamespaceDef(ns_def) => precomp_namespace_def(context, e, ns_def),
        // ForIn should have been desugared in desugarer phase
        NodeType::ForIn(_) => {
            panic!("ForIn should have been desugared in desugarer phase");
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
                        // It's a struct constructor - check all args are comptime
                        for i in 1..e.params.len() {
                            // Handle named args - check the value inside
                            let arg = e.get(i)?;
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
                        // It's an enum constructor - check all args are comptime
                        for i in 1..e.params.len() {
                            if !is_comptime_evaluable(context, e.get(i)?)? {
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
            if func_def.return_types.is_empty() {
                return Ok(false);
            }
            // Functions that can throw are allowed - if they actually throw,
            // we'll report the error in eval_comptime.
            // All arguments must be comptime-evaluable
            for i in 1..e.params.len() {
                if !is_comptime_evaluable(context, e.get(i)?)? {
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
            Ok(Expr::new_clone(NodeType::LLiteral(Literal::Number(result.value.clone())), e, vec![]))
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
        new_params.push(precomp_expr(context, p)?);
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
fn precomp_struct_def(context: &mut Context, e: &Expr, struct_def: &SStructDef) -> Result<Expr, String> {
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
    let new_struct_def = SStructDef {
        members: struct_def.members.clone(),
        default_values: new_default_values,
    };
    Ok(Expr::new_clone(NodeType::StructDef(new_struct_def), e, e.params.clone()))
}

/// Issue #108: Transform NamespaceDef - recursively transform function bodies
fn precomp_namespace_def(context: &mut Context, e: &Expr, ns_def: &SNamespaceDef) -> Result<Expr, String> {
    let mut new_default_values = HashMap::new();
    for (name, value_expr) in &ns_def.default_values {
        let is_func = matches!(&value_expr.node_type, NodeType::FuncDef(_));
        let saved_func = context.current_precomp_func.clone();
        let saved_counter = context.precomp_forin_counter;
        if is_func {
            context.current_precomp_func = name.clone();
            context.precomp_forin_counter = 0;
        }

        let transformed = precomp_expr(context, value_expr)?;

        // Issue #108: Update scope_stack with transformed FuncDef so interpreter uses it
        if let NodeType::FuncDef(func_def) = &transformed.node_type {
            let full_name = format!("{}.{}", ns_def.type_name, name);
            context.scope_stack.update_func(&full_name, func_def.clone());
        }

        new_default_values.insert(name.clone(), transformed);

        if is_func {
            context.current_precomp_func = saved_func;
            context.precomp_forin_counter = saved_counter;
        }
    }
    let new_ns_def = SNamespaceDef {
        type_name: ns_def.type_name.clone(),
        members: ns_def.members.clone(),
        default_values: new_default_values,
    };
    Ok(Expr::new_clone(NodeType::NamespaceDef(new_ns_def), e, vec![]))
}

/// Transform FuncDef - push scope frame for function args, transform body, pop frame
fn precomp_func_def(context: &mut Context, e: &Expr, func_def: SFuncDef) -> Result<Expr, String> {
    // Push a new scope frame with the function's parameters
    context.scope_stack.push(ScopeType::Function);
    for arg in &func_def.args {
        context.scope_stack.declare_symbol(arg.name.clone(), SymbolInfo {
            value_type: arg.value_type.clone(),
            is_mut: arg.is_mut,
            is_copy: arg.is_copy,
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

    let new_func_def = SFuncDef {
        function_type: func_def.function_type.clone(),
        args: func_def.args.clone(),
        return_types: func_def.return_types.clone(),
        throw_types: func_def.throw_types.clone(),
        body: new_body,
        source_path: func_def.source_path.clone(),
    };
    Ok(Expr::new_clone(NodeType::FuncDef(new_func_def), e, e.params.clone()))
}

/// Transform Declaration - register the declared variable in scope, then transform value
fn precomp_declaration(context: &mut Context, e: &Expr, decl: &crate::rs::parser::Declaration) -> Result<Expr, String> {
    // Eagerly create default instance template for this struct type
    let inner_e = e.get(0)?;
    let mut value_type = match get_value_type(context, &inner_e) {
        Ok(val_type) => val_type,
        Err(error_string) => {
            return Err(e.lang_error(&context.path, "precomp", &error_string));
        },
    };
    // Issue #91: Detect function signature definitions
    // A FuncDef with empty body and type-only args (no names) is a function signature type
    if let NodeType::FuncDef(func_def) = &inner_e.node_type {
        if func_def.body.is_empty() && func_def.args.iter().all(|a| a.name.is_empty())
            && matches!(func_def.function_type, FunctionType::FTFunc | FunctionType::FTProc) {
            value_type = ValueType::TType(TTypeDef::TFuncSig);
        }
    }

    // Issue #91: Resolve function signature type references
    // When decl.value_type is a custom type name that resolves to a FunctionSig,
    // look up the signature and set value_type to match the function type.
    let mut sig_func_def: Option<SFuncDef> = None;
    if let ValueType::TCustom(ref sig_name) = decl.value_type {
        if let Some(sym) = context.scope_stack.lookup_symbol(sig_name) {
            if sym.value_type == ValueType::TType(TTypeDef::TFuncSig) {
                if let Some(sfd) = context.scope_stack.lookup_func(sig_name) {
                    sig_func_def = Some(sfd.clone());
                    value_type = ValueType::TFunction(sfd.function_type.clone());
                }
            }
        }
    }

    // Issue #105: Accept INFER_TYPE inside macro bodies (typer doesn't resolve inside FuncDef bodies)
    if decl.value_type == ValueType::TCustom(INFER_TYPE.to_string()) {
        // Infer type from the value - this is the := pattern inside a macro
    } else if sig_func_def.is_some() {
        // Issue #91: FunctionSig reference resolved above - skip type check
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
                context.scope_stack.declare_symbol(decl.name.to_string(), SymbolInfo{value_type: value_type.clone(), is_mut: decl.is_mut, is_copy: decl.is_copy, is_own: decl.is_own, is_comptime_const: true });
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
                is_copy: decl.is_copy,
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
    let is_func_decl = !e.params.is_empty() && matches!(&e.get(0)?.node_type, NodeType::FuncDef(_));
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
            if func_def.args.len() != sig.args.len() {
                return Err(e.lang_error(&context.path, "precomp", &format!(
                    "'{}' has {} parameters but function signature '{}' expects {}.",
                    decl.name, func_def.args.len(),
                    value_type_to_str(&decl.value_type), sig.args.len())));
            }
            let mut resolved_fd = func_def.clone();
            for (i, sig_arg) in sig.args.iter().enumerate() {
                resolved_fd.args[i].value_type = sig_arg.value_type.clone();
            }
            resolved_fd.return_types = sig.return_types.clone();
            resolved_fd.throw_types = sig.throw_types.clone();
            resolved_fd.function_type = sig.function_type.clone();
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

    // Determine if this is a compile-time constant
    // Only mut matters for constantness - copy/own are about ownership, orthogonal to comptime.
    // Any type can be comptime - the type doesn't matter, only how the value is computed.
    let is_comptime_const = !decl.is_mut
        && is_comptime_evaluable(context, &new_params[0])?;

    // Register the declared variable in scope
    context.scope_stack.declare_symbol(decl.name.clone(), SymbolInfo {
        value_type: value_type.clone(),
        is_mut: decl.is_mut,
        is_copy: decl.is_copy,
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
    if at_global_scope && !decl.is_mut && !decl.is_copy && !decl.is_own && !new_params.is_empty() && is_comptime_evaluable(context, &new_params[0])? {
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
    let var_name = match &e.get(0)?.node_type {
        NodeType::Identifier(name) => name.clone(),
        _ => return precomp_params(context, e), // Not a simple identifier, use default handling
    };
    let type_name = match &e.get(1)?.node_type {
        NodeType::Identifier(name) => name.clone(),
        _ => return precomp_params(context, e), // Not a simple type, use default handling
    };

    // Push a scope frame for the catch block
    context.scope_stack.push(ScopeType::Catch);

    // Register the catch variable in the scope
    context.scope_stack.declare_symbol(var_name.clone(), SymbolInfo {
        value_type: ValueType::TCustom(type_name),
        is_mut: false,
        is_copy: false,
        is_own: false,
        is_comptime_const: false,
    });

    // Transform the catch body (params[2])
    let new_body = precomp_expr(context, e.get(2)?)?;

    // Pop the scope frame
    let _ = context.scope_stack.pop();

    // Return the transformed catch with original var_name, type, and new body
    Ok(Expr::new_clone(
        NodeType::Catch,
        e,
        vec![e.get(0)?.clone(), e.get(1)?.clone(), new_body],
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
