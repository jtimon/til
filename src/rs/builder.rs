// Builder module - orchestrates compilation to target languages
// Mirrors src/self/builder.til

use std::fs;
use std::io::ErrorKind;
use std::process::Command;
use std::collections::HashSet;
use crate::rs::lexer::lexer_from_source;
use crate::rs::parser::{parse_tokens, Expr, NodeType};
use crate::rs::mode::{parse_mode, ModeDef};
use crate::rs::ccodegen;
use crate::rs::init::{import_path_to_file_path, init_import_declarations, Context};
use crate::rs::typer::{type_check, basic_mode_checks, typer_import_declarations, resolve_inferred_types};
use crate::rs::preinit::preinit_expr;
use crate::rs::desugarer::desugar_expr;
use crate::rs::garbager::garbager_expr;
use crate::rs::ufcs::ufcs_expr;
use crate::rs::target::{Target, Lang, toolchain_command, toolchain_extra_args, executable_extension, validate_lang_for_target, lang_to_str};

// Parse a single file and return its AST (and mode for main file)
fn parse_file(path: &str) -> Result<(Expr, ModeDef), String> {
    let source: String = match fs::read_to_string(path) {
        Ok(file) => file,
        Err(error) => match error.kind() {
            ErrorKind::NotFound => {
                return Err(format!("File '{}' not found.", path))
            },
            other_error => {
                return Err(format!("Problem opening the file '{}': {:?}", path, other_error))
            },
        },
    };

    let mut lexer = match lexer_from_source(&path.to_string(), source) {
        Ok(result) => result,
        Err(error_string) => {
            return Err(format!("{}:{}", path, error_string));
        },
    };

    let mode = parse_mode(&path.to_string(), &mut lexer)?;

    let expr = match parse_tokens(&mut lexer) {
        Ok(expr) => expr,
        Err(error_string) => return Err(format!("{}:{}", path, error_string)),
    };

    // Preinit phase: Auto-generate delete() and clone() methods for structs
    let expr = preinit_expr(&expr)?;

    Ok((expr, mode))
}

// Recursively collect all imports from an AST
// Each file is precompiled with its own path before being added to all_asts
fn collect_imports(ast: &Expr, imported: &mut HashSet<String>, all_asts: &mut Vec<Expr>, context: &mut Context) -> Result<(), String> {
    if let NodeType::Body = &ast.node_type {
        for child in &ast.params {
            if let NodeType::FCall(_) = &child.node_type {
                if !child.params.is_empty() {
                    if let NodeType::Identifier(name) = &child.get(0)?.node_type {
                        if name == "import" && child.params.len() > 1 {
                            if let NodeType::LLiteral(crate::rs::parser::Literal::Str(import_path)) = &child.get(1)?.node_type {
                                let file_path = import_path_to_file_path(import_path);
                                if !imported.contains(&file_path) {
                                    imported.insert(file_path.clone());
                                    // Bug #128: Use already-resolved AST from typer phase if available
                                    let dep_resolved = match context.imported_asts.get(&file_path) {
                                        Some(ast) => ast.clone(),
                                        None => {
                                            let (parsed_ast, _mode) = parse_file(&file_path)?;
                                            context.imported_asts.insert(file_path.clone(), parsed_ast.clone());
                                            parsed_ast
                                        }
                                    };
                                    // Recursively collect imports from this dependency
                                    collect_imports(&dep_resolved, imported, all_asts, context)?;
                                    // Desugar + Precomp with the correct path for this file
                                    // (type resolution already done by typer_import_declarations)
                                    let saved_path = context.path.clone();
                                    context.path = file_path.clone();
                                    let dep_desugared = desugar_expr(context, &dep_resolved)?;
                                    let dep_garbaged = garbager_expr(context, &dep_desugared)?;
                                    let dep_ufcs = ufcs_expr(context, &dep_garbaged)?;
                                    let dep_ast = crate::rs::precomp::precomp_expr(context, &dep_ufcs)?;
                                    // Update with precompiled version
                                    context.imported_asts.insert(file_path, dep_ast.clone());
                                    context.path = saved_path;
                                    all_asts.push(dep_ast);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    Ok(())
}

// Merge multiple ASTs into one, filtering out import statements
fn merge_asts(main_ast: Expr, dep_asts: Vec<Expr>) -> Result<Expr, String> {
    let mut all_params = Vec::new();

    // Add dependencies first (in order they were collected)
    for dep in dep_asts {
        if let NodeType::Body = &dep.node_type {
            for child in dep.params {
                // Skip import statements
                if !is_import_call(&child)? {
                    all_params.push(child);
                }
            }
        }
    }

    // Add main file contents (skip imports)
    if let NodeType::Body = &main_ast.node_type {
        for child in main_ast.params {
            if !is_import_call(&child)? {
                all_params.push(child);
            }
        }
    }

    Ok(Expr {
        node_type: NodeType::Body,
        params: all_params,
        line: main_ast.line,
        col: main_ast.col,
    })
}

fn is_import_call(expr: &Expr) -> Result<bool, String> {
    if let NodeType::FCall(_) = &expr.node_type {
        if !expr.params.is_empty() {
            if let NodeType::Identifier(name) = &expr.get(0)?.node_type {
                return Ok(name == "import");
            }
        }
    }
    Ok(false)
}

// Collect import paths from an AST without precompilation (lightweight for deps checking)
fn collect_import_paths(ast: &Expr, collected: &mut HashSet<String>) -> Result<(), String> {
    if let NodeType::Body = &ast.node_type {
        for child in &ast.params {
            if let NodeType::FCall(_) = &child.node_type {
                if !child.params.is_empty() {
                    if let NodeType::Identifier(name) = &child.get(0)?.node_type {
                        if name == "import" && child.params.len() > 1 {
                            if let NodeType::LLiteral(crate::rs::parser::Literal::Str(import_path)) = &child.get(1)?.node_type {
                                let file_path = import_path_to_file_path(import_path);
                                if !collected.contains(&file_path) {
                                    collected.insert(file_path.clone());
                                    // Recursively collect imports from this dependency
                                    if let Ok((dep_ast, _)) = parse_file(&file_path) {
                                        collect_import_paths(&dep_ast, collected)?;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    Ok(())
}

// Collect all dependencies for a TIL source file (for rebuild checking)
// Returns all file paths that the main file depends on, including:
// - The main file itself
// - core.til and its imports
// - Mode-specific imports
// - All transitive imports
pub fn collect_all_deps(path: &str) -> Result<Vec<String>, String> {
    let mut deps = HashSet::new();

    // Add main file
    deps.insert(path.to_string());

    // Parse main file to get its mode and imports
    let (main_ast, main_mode) = parse_file(path)?;

    // Add core.til and its imports (unless main file IS core.til)
    let core_path = "src/core/core.til";
    if path != core_path {
        deps.insert(core_path.to_string());
        let (core_ast, _) = parse_file(core_path)?;
        collect_import_paths(&core_ast, &mut deps)?;
    }

    // Add mode-specific imports
    for import_str in &main_mode.imports {
        let file_path = import_path_to_file_path(import_str);
        if !deps.contains(&file_path) {
            deps.insert(file_path.clone());
            if let Ok((mode_ast, _)) = parse_file(&file_path) {
                collect_import_paths(&mode_ast, &mut deps)?;
            }
        }
    }

    // Collect main file's imports
    collect_import_paths(&main_ast, &mut deps)?;

    Ok(deps.into_iter().collect())
}

// Build a TIL source file with target, lang, and translate_only options
// Returns the output path (executable or source file)
// cc: Optional compiler override (Issue #131). If None, uses default for target.
pub fn build(path: &str, target: &Target, lang: &Lang, cc: Option<&str>, translate_only: bool) -> Result<String, String> {
    // Validate lang is supported for target
    validate_lang_for_target(lang, target)?;

    // Currently only C is fully supported
    match lang {
        Lang::C => {},  // Supported
        Lang::TIL => {
            return Err("Lang 'til' is not supported yet. TIL-to-TIL translation is a placeholder for future debugging features.".to_string());
        },
        _ => {
            return Err(format!("Lang '{}' is not supported yet. Only 'c' is currently implemented.", lang_to_str(lang)));
        }
    }

    // Parse main file
    let (main_ast, main_mode) = parse_file(path)?;

    // Create context with "lib" mode first (like interpreter does at interpreter.rs:2713)
    // This ensures core.til is typechecked with lib mode, not the main file's mode
    let mut context = Context::new(&path.to_string(), "lib")?;

    // Reusable error vector to avoid shadowing
    let mut errors: Vec<String> = Vec::new();

    // Auto-import core.til first (like the interpreter does at interpreter.rs:2714-2717)
    // This runs init + typer on core.til and all its imports with lib mode
    let core_path = "src/core/core.til";
    if path != core_path {
        let (core_ast, _) = parse_file(core_path)?;
        errors = crate::rs::init::init_context(&mut context, &core_ast)?;
        if !errors.is_empty() {
            for err in &errors {
                println!("{}", err);
            }
            return Err(format!("Compiler errors: {} init errors in core.til", errors.len()));
        }
        // Issue #105: Expand struct-returning macros before type checking
        let core_ast = crate::rs::precomp::expand_struct_macros(&mut context, &core_ast)?;
        // Bug #128: type_check does both validation and INFER_TYPE resolution
        // We discard the resolved AST here since core.til is re-parsed later for codegen
        let (_, type_errors) = type_check(&mut context, &core_ast)?;
        if !type_errors.is_empty() {
            for err in &type_errors {
                println!("{}", err);
            }
            return Err(format!("Compiler errors: {} type errors in core.til", type_errors.len()));
        }
        context.imports_init_done.insert(core_path.to_string());
        context.imports_typer_done.insert(core_path.to_string());
    }

    // Now set the mode to the main file's mode (like interpreter does at interpreter.rs:2610-2611)
    context.mode_def = main_mode;

    // Process mode-specific imports (like the interpreter does at interpreter.rs:2515-2541)
    for import_str in context.mode_def.imports.clone() {
        let import_func_name_expr = Expr{node_type: NodeType::Identifier("import".to_string()), params: Vec::new(), line: 0, col: 0};
        let import_path_expr = Expr{node_type: NodeType::LLiteral(crate::rs::parser::Literal::Str(import_str.to_string())), params: Vec::new(), line: 0, col: 0};
        let import_fcall_expr = Expr{node_type: NodeType::FCall(false), params: vec![import_func_name_expr, import_path_expr], line: 0, col: 0};

        // Mode imports need init and typer phases (no eval for builder)
        if let Err(error_string) = init_import_declarations(&mut context, &import_fcall_expr, &import_str) {
            return Err(format!("{}:{}", &path, error_string));
        }
        errors = typer_import_declarations(&mut context, &import_str);
        if !errors.is_empty() {
            for err in &errors {
                println!("{}", err);
            }
            return Err(format!("Compiler errors: {} type errors found", errors.len()));
        }
    }

    // Mark main file as "done" to prevent re-processing via circular imports
    // (like interpreter does at interpreter.rs:2598-2601)
    context.imports_init_done.insert(path.to_string());
    context.imports_typer_done.insert(path.to_string());

    // Run init + typer on the main file (this handles its imports internally)
    errors.clear();
    let mut tmp_errors = crate::rs::init::init_context(&mut context, &main_ast)?;
    errors.extend(tmp_errors);
    if !errors.is_empty() {
        for err in &errors {
            println!("{}", err);
        }
        return Err(format!("Compiler errors: {} init errors found", errors.len()));
    }

    tmp_errors = basic_mode_checks(&context, &main_ast)?;
    errors.extend(tmp_errors);
    // Issue #105: Expand struct-returning macros before type checking
    let main_ast = crate::rs::precomp::expand_struct_macros(&mut context, &main_ast)?;
    // Bug #128: type_check does both validation and INFER_TYPE resolution
    // Save resolved_main_ast for precomp later
    let (resolved_main_ast, type_errors) = type_check(&mut context, &main_ast)?;
    errors.extend(type_errors);
    if !errors.is_empty() {
        for err in &errors {
            println!("{}", err);
        }
        return Err(format!("Compiler errors: {} type errors found", errors.len()));
    }

    // === Post-typer: Collect and merge ASTs for codegen ===
    // Now that type checking passed, collect all imported files for code generation
    // Each file is precompiled with its own path before merging
    let mut imported = HashSet::new();
    imported.insert(path.to_string());
    // Store resolved main file AST so circular imports can find it during precomp
    context.imported_asts.insert(path.to_string(), resolved_main_ast.clone());
    let mut dep_asts = Vec::new();

    // Collect core.til and its imports
    if path != core_path {
        let (codegen_core_ast, _) = parse_file(core_path)?;
        imported.insert(core_path.to_string());
        collect_imports(&codegen_core_ast, &mut imported, &mut dep_asts, &mut context)?;
        // Resolve types + Desugar + Precomp core.til with its own path
        let core_saved_path = context.path.clone();
        context.path = core_path.to_string();
        let core_ast = resolve_inferred_types(&mut context, &codegen_core_ast)?;
        let core_ast = desugar_expr(&mut context, &core_ast)?;
        let core_ast = garbager_expr(&mut context, &core_ast)?;
        let core_ast = ufcs_expr(&mut context, &core_ast)?;
        let core_precomp_ast = crate::rs::precomp::precomp_expr(&mut context, &core_ast)?;
        context.path = core_saved_path;
        dep_asts.push(core_precomp_ast);
    }

    // Collect mode imports
    for import_str in context.mode_def.imports.clone() {
        let file_path = import_path_to_file_path(&import_str);
        if !imported.contains(&file_path) {
            imported.insert(file_path.clone());
            let (mode_ast, _) = parse_file(&file_path)?;
            collect_imports(&mode_ast, &mut imported, &mut dep_asts, &mut context)?;
            // Resolve types + Desugar + Precomp mode file with its own path
            let mode_saved_path = context.path.clone();
            context.path = file_path.clone();
            let mode_ast = resolve_inferred_types(&mut context, &mode_ast)?;
            let mode_ast = desugar_expr(&mut context, &mode_ast)?;
            let mode_ast = garbager_expr(&mut context, &mode_ast)?;
            let mode_ast = ufcs_expr(&mut context, &mode_ast)?;
            let mode_precomp_ast = crate::rs::precomp::precomp_expr(&mut context, &mode_ast)?;
            context.path = mode_saved_path;
            dep_asts.push(mode_precomp_ast);
        }
    }

    // Collect main file's imports
    collect_imports(&resolved_main_ast, &mut imported, &mut dep_asts, &mut context)?;

    // Desugar + Garbager + UFCS + Precomp main file (already resolved by type_check above)
    let main_ast = desugar_expr(&mut context, &resolved_main_ast)?;
    let main_ast = garbager_expr(&mut context, &main_ast)?;
    let main_ast = ufcs_expr(&mut context, &main_ast)?;
    let main_ast = crate::rs::precomp::precomp_expr(&mut context, &main_ast)?;

    // Merge all precompiled ASTs for codegen
    let merged_ast = merge_asts(main_ast, dep_asts)?;

    // Scavenger phase: Remove unused function declarations
    let merged_ast = crate::rs::scavenger::scavenger_expr(&mut context, &merged_ast)?;

    // Generate C code
    let c_code = ccodegen::emit(&merged_ast, &mut context)?;

    // Write output file to ./gen/{LANG_NAME}/c/ directory instead of alongside source
    // Bug #141: Use LANG_NAME to separate rstil (rs) and til outputs
    let c_filename = path.replace(".til", ".c");
    let gen_prefix = format!("gen/{}/c/", crate::rs::lexer::LANG_NAME);
    let source_output_path = if c_filename.starts_with("src/") {
        c_filename.replacen("src/", &gen_prefix, 1)
    } else {
        format!("{}{}", gen_prefix, c_filename)
    };
    // Create output directory if it doesn't exist
    if let Some(parent) = std::path::Path::new(&source_output_path).parent() {
        let _ = fs::create_dir_all(parent);
    }
    match fs::write(&source_output_path, &c_code) {
        Ok(_) => {},
        Err(e) => return Err(format!("Failed to write '{}': {}", source_output_path, e)),
    }

    // If translate_only, return the source file path
    if translate_only {
        return Ok(source_output_path);
    }

    // Get toolchain command for target (Issue #131: use --cc override if provided)
    let compiler = match cc {
        Some(c) => c.to_string(),
        None => toolchain_command(target, lang)?,
    };

    // Compile - output to bin/{LANG_NAME}/ directory in project root, preserving relative path
    // Bug #141: Use LANG_NAME to separate rstil (rs) and til outputs
    // e.g., src/til.til -> bin/rs/til, src/examples/hello_script.til -> bin/rs/examples/hello_script
    let exe_extension = executable_extension(target);
    let bin_filename = path.replace(".til", exe_extension);
    let bin_prefix = format!("bin/{}/", crate::rs::lexer::LANG_NAME);
    let exe_path_str = if bin_filename.starts_with("src/") {
        bin_filename.replacen("src/", &bin_prefix, 1)
    } else {
        format!("{}{}", bin_prefix, bin_filename)
    };
    // Create bin directory if it doesn't exist
    if let Some(parent) = std::path::Path::new(&exe_path_str).parent() {
        let _ = fs::create_dir_all(parent);
    }

    // Build command with extra args for target
    let mut cmd = Command::new(&compiler);
    cmd.args(["-I", "src"]);
    for extra_arg in toolchain_extra_args(target, lang, &compiler) {
        cmd.arg(extra_arg);
    }
    cmd.args([&source_output_path, "-o", &exe_path_str]);

    let output = cmd.output();

    match output {
        Ok(out) => {
            if out.status.success() {
                Ok(exe_path_str)
            } else {
                let stderr = String::from_utf8_lossy(&out.stderr);
                Err(format!("{} failed: {}", compiler, stderr))
            }
        },
        Err(e) => Err(format!("Failed to run {}: {}", compiler, e)),
    }
}
