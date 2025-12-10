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
use crate::rs::typer::{check_types, basic_mode_checks, typer_import_declarations};

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

    match parse_tokens(&mut lexer) {
        Ok(expr) => Ok((expr, mode)),
        Err(error_string) => Err(format!("{}:{}", path, error_string)),
    }
}

// Recursively collect all imports from an AST
fn collect_imports(ast: &Expr, imported: &mut HashSet<String>, all_asts: &mut Vec<Expr>) -> Result<(), String> {
    if let NodeType::Body = &ast.node_type {
        for child in &ast.params {
            if let NodeType::FCall = &child.node_type {
                if !child.params.is_empty() {
                    if let NodeType::Identifier(name) = &child.params[0].node_type {
                        if name == "import" && child.params.len() > 1 {
                            if let NodeType::LLiteral(crate::rs::parser::Literal::Str(import_path)) = &child.params[1].node_type {
                                let file_path = import_path_to_file_path(import_path);
                                if !imported.contains(&file_path) {
                                    imported.insert(file_path.clone());
                                    let (dep_ast, _mode) = parse_file(&file_path)?;
                                    // Recursively collect imports from this dependency
                                    collect_imports(&dep_ast, imported, all_asts)?;
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
fn merge_asts(main_ast: Expr, dep_asts: Vec<Expr>) -> Expr {
    let mut all_params = Vec::new();

    // Add dependencies first (in order they were collected)
    for dep in dep_asts {
        if let NodeType::Body = &dep.node_type {
            for child in dep.params {
                // Skip import statements
                if !is_import_call(&child) {
                    all_params.push(child);
                }
            }
        }
    }

    // Add main file contents (skip imports)
    if let NodeType::Body = &main_ast.node_type {
        for child in main_ast.params {
            if !is_import_call(&child) {
                all_params.push(child);
            }
        }
    }

    Expr {
        node_type: NodeType::Body,
        params: all_params,
        line: main_ast.line,
        col: main_ast.col,
    }
}

fn is_import_call(expr: &Expr) -> bool {
    if let NodeType::FCall = &expr.node_type {
        if !expr.params.is_empty() {
            if let NodeType::Identifier(name) = &expr.params[0].node_type {
                return name == "import";
            }
        }
    }
    false
}

// Build a TIL source file to C (default target)
pub fn build(path: &str) -> Result<(), String> {
    println!("Building file '{}'", path);

    // Parse main file
    let (main_ast, main_mode) = parse_file(path)?;

    // Collect all imports recursively
    let mut imported = HashSet::new();
    imported.insert(path.to_string());
    let mut dep_asts = Vec::new();

    // Auto-import core.til first (like the interpreter does)
    let core_path = "src/core/core.til";
    if path != core_path && !imported.contains(core_path) {
        imported.insert(core_path.to_string());
        let (core_ast, _) = parse_file(core_path)?;
        // Collect core.til's imports first
        collect_imports(&core_ast, &mut imported, &mut dep_asts)?;
        dep_asts.push(core_ast);
    }

    collect_imports(&main_ast, &mut imported, &mut dep_asts)?;

    // Merge all ASTs into one
    let merged_ast = merge_asts(main_ast, dep_asts);

    // Run init phase (register declarations in context)
    // Use the mode from the main file, not DEFAULT_MODE
    let mut context = Context::new(&path.to_string(), &main_mode.name)?;

    // Init the merged AST first (includes core.til) so basic types are available
    let _ = crate::rs::init::init_context(&mut context, &merged_ast);

    // Mark all already-imported files as done so mode imports don't re-import them
    // Both init and typer phases need to skip these files
    for file_path in &imported {
        context.imports_init_done.insert(file_path.clone());
        context.imports_typer_done.insert(file_path.clone());
    }

    // Auto-import mode-specific files (like the interpreter does at interpreter.rs:2518-2544)
    // This must happen after init_context so basic types (Str, Dynamic, etc.) are available
    // Skip files already in our imported set to avoid duplicate declarations
    for import_str in context.mode_def.imports.clone() {
        let file_path = import_path_to_file_path(&import_str);
        if imported.contains(&file_path) {
            continue;  // Already processed via collect_imports
        }

        let import_func_name_expr = Expr{node_type: NodeType::Identifier("import".to_string()), params: Vec::new(), line: 0, col: 0};
        let import_path_expr = Expr{node_type: NodeType::LLiteral(crate::rs::parser::Literal::Str(import_str.to_string())), params: Vec::new(), line: 0, col: 0};
        let import_fcall_expr = Expr{node_type: NodeType::FCall, params: vec![import_func_name_expr, import_path_expr], line: 0, col: 0};

        // Mode imports need init and typer phases (no eval for builder)
        if let Err(error_string) = init_import_declarations(&mut context, &import_fcall_expr, &import_str) {
            return Err(format!("{}:{}", &path, error_string));
        }
        let typer_errors = typer_import_declarations(&mut context, &import_str);
        if !typer_errors.is_empty() {
            for err in &typer_errors {
                println!("{}:{}", path, err);
            }
            return Err(format!("Compiler errors: {} type errors found", typer_errors.len()));
        }
    }

    // Run typer phase (type checking) - like the interpreter does
    let mut errors: Vec<String> = Vec::new();
    errors.extend(basic_mode_checks(&context, &merged_ast));
    errors.extend(check_types(&mut context, &merged_ast));

    if !errors.is_empty() {
        for err in &errors {
            println!("{}:{}", path, err);
        }
        return Err(format!("Compiler errors: {} type errors found", errors.len()));
    }

    // Precomputation phase: Transform UFCS calls into regular function calls
    let merged_ast = crate::rs::precomp::precomp_expr(&mut context, &merged_ast)?;

    // Generate C code
    let c_code = ccodegen::emit(&merged_ast, &mut context)?;

    // Write output file
    let output_path = path.replace(".til", ".c");
    match fs::write(&output_path, &c_code) {
        Ok(_) => println!("Wrote C output to '{}'", output_path),
        Err(e) => return Err(format!("Failed to write '{}': {}", output_path, e)),
    }

    // Compile with gcc - output to bin/ subdirectory
    let source_dir = std::path::Path::new(path).parent().unwrap_or(std::path::Path::new("."));
    let bin_dir = source_dir.join("bin");
    // Create bin directory if it doesn't exist
    let _ = fs::create_dir_all(&bin_dir);
    let exe_name = std::path::Path::new(path)
        .file_stem()
        .and_then(|s| s.to_str())
        .unwrap_or("out");
    let exe_path = bin_dir.join(exe_name);
    let exe_path_str = exe_path.to_string_lossy().to_string();
    let output = Command::new("gcc")
        .args(["-I", "src", &output_path, "-o", &exe_path_str])
        .output();

    match output {
        Ok(out) => {
            if out.status.success() {
                println!("Compiled executable to '{}'", exe_path_str);
                Ok(())
            } else {
                let stderr = String::from_utf8_lossy(&out.stderr);
                Err(format!("gcc failed: {}", stderr))
            }
        },
        Err(e) => Err(format!("Failed to run gcc: {}", e)),
    }
}
