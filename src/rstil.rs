use std::env;
use std::fs;
use std::time::SystemTime;

mod rs {
    pub mod lexer;
    pub mod mode;
    pub mod target;
    pub mod parser;
    pub mod init;
    pub mod typer;
    pub mod desugarer;
    pub mod garbager;
    pub mod ufcs;
    pub mod precomp;
    pub mod precomp_ext;
    pub mod scavenger;
    pub mod arena;
    pub mod eval_arena;
    pub mod interpreter;
    pub mod ext;
    pub mod ccodegen;
    pub mod builder;
    pub mod ordered_map;
}
use rs::lexer::LANG_NAME;
use rs::interpreter::interpret_file;
use rs::builder;
use rs::eval_arena::EvalArena;
use rs::target::{Target, Lang, target_from_str, lang_from_str, detect_current_target, default_lang_for_target, executable_extension};

const REPL_PATH            : &str = "src/modes/repl.til";

// Get file modification time as Unix timestamp, returns -1 if file doesn't exist
fn file_mtime(path: &str) -> i64 {
    match fs::metadata(path) {
        Ok(meta) => {
            match meta.modified() {
                Ok(time) => {
                    match time.duration_since(SystemTime::UNIX_EPOCH) {
                        Ok(duration) => duration.as_secs() as i64,
                        Err(_) => -1,
                    }
                },
                Err(_) => -1,
            }
        },
        Err(_) => -1,
    }
}

// Compute the binary output path from a TIL source path
// Mirrors the logic in builder.rs
// Bug #141: Use LANG_NAME_141 to separate rstil (rs) and til outputs
fn source_to_binary_path(path: &str, target: &Target) -> String {
    let exe_extension = executable_extension(target);
    let bin_filename = path.replace(".til", exe_extension);
    let bin_prefix = format!("bin/{}/", rs::lexer::LANG_NAME_141);
    if bin_filename.starts_with("src/") {
        bin_filename.replacen("src/", &bin_prefix, 1)
    } else {
        format!("{}{}", bin_prefix, bin_filename)
    }
}

// Check if binary needs to be rebuilt based on source file modification times
// Returns true if binary doesn't exist or any dependency is newer than binary
fn needs_rebuild(binary_path: &str, deps: &[String]) -> bool {
    let binary_mtime = file_mtime(binary_path);
    if binary_mtime == -1 {
        return true; // Binary doesn't exist
    }

    for dep in deps {
        let dep_mtime = file_mtime(dep);
        if dep_mtime > binary_mtime {
            return true; // Dependency is newer
        }
    }
    false
}

// Parse --target=X and --lang=X options from args, return (remaining_args, target, lang, translate_only, force_rebuild)
fn parse_build_options(args: &[String]) -> Result<(Vec<String>, Target, Lang, Option<String>, bool, bool), String> {
    let mut remaining = Vec::new();
    let mut target: Option<Target> = None;
    let mut lang: Option<Lang> = None;
    let mut cc: Option<String> = None;
    let mut translate_only = false;
    let mut force_rebuild = false;

    for opt_arg in args {
        if opt_arg.starts_with("--target=") {
            let target_value = &opt_arg[9..];
            target = Some(target_from_str(target_value)?);
        } else if opt_arg.starts_with("--lang=") {
            let lang_value = &opt_arg[7..];
            lang = Some(lang_from_str(lang_value)?);
        } else if opt_arg.starts_with("--cc=") {
            // Issue #131: Allow specifying C compiler (e.g., --cc=clang)
            cc = Some(opt_arg[5..].to_string());
        } else if opt_arg == "--translate" {
            translate_only = true;
        } else if opt_arg == "--force-rebuild" {
            force_rebuild = true;
        } else {
            remaining.push(opt_arg.clone());
        }
    }

    // Default target is current platform
    let final_target = target.unwrap_or_else(detect_current_target);
    // Default lang is determined by target
    let final_lang = lang.unwrap_or_else(|| default_lang_for_target(&final_target));

    Ok((remaining, final_target, final_lang, cc, translate_only, force_rebuild))
}

// ---------- main, usage, args, etc

fn usage() {
    println!("Usage: {} [command] [path] [options]\n", LANG_NAME);
    println!("Entering no arguments is equavalent to: {} repl", LANG_NAME);
    println!("Entering a single argument that's not a command is interpreted as a path, equivalent to: {} interpret <path>\n", LANG_NAME);

    println!("Commands:\n");

    println!("repl: read eval print loop.");
    println!("interpret: reads a file in provided <path> and evaluates it.");
    println!("build: reads a file in provided <path> and compiles it.");
    println!("translate: reads a file in provided <path> and generates source code (no compilation).");
    println!("run: reads a file in provided <path>, compiles and runs it.");
    println!("help: Prints this.\n");

    println!("Build/Translate Options:\n");
    println!("--target=TARGET   Cross-compile for target platform.");
    println!("                  Supported: linux-x64, linux-arm64, windows-x64, macos-x64, macos-arm64");
    println!("--lang=LANG       Output language for codegen (default: c).");
    println!("                  Supported: c");
    println!("--cc=COMPILER     C compiler to use (default: gcc on Linux/Windows, clang on macOS).");
    println!("                  Example: --cc=clang");
    println!("--force-rebuild   Force rebuild even if binary is up-to-date.\n");
}

fn interpret_file_or_exit(path: &String, args: Vec<String>) {
    match interpret_file(path, args) {
        Ok(_) => {},
        Err(err) => {
            println!("ERROR: {err}");
            std::process::exit(1);
        },
    };
    if path.ends_with("tests.til") {
        println!("Total memory used by interpreted program: {} bytes", EvalArena::g().len());
    }
}

fn build_file_or_exit(path: &String, target: &Target, lang: &Lang, cc: Option<&str>, translate_only: bool, force_rebuild: bool) {
    // Skip rebuild check for translate (always regenerate source)
    if !translate_only && !force_rebuild {
        let exe_path = source_to_binary_path(path, target);
        let should_rebuild = match builder::collect_all_deps(path) {
            Ok(deps) => needs_rebuild(&exe_path, &deps),
            Err(_) => true,
        };
        if !should_rebuild {
            return; // Binary is up-to-date
        }
    }

    match builder::build(path, target, lang, cc, translate_only) {
        Ok(output_path) => {
            if translate_only {
                println!("Generated: {}", output_path);
            }
        },
        Err(err) => {
            println!("ERROR: {err}");
            std::process::exit(1);
        },
    };
}

fn run_file_or_exit(path: &String, target: &Target, lang: &Lang, cc: Option<&str>, extra_args: &[String], force_rebuild: bool) {
    // Compute expected binary path
    let exe_path = source_to_binary_path(path, target);

    // Collect dependencies and check if rebuild is needed
    let should_rebuild = if force_rebuild {
        true
    } else {
        match builder::collect_all_deps(path) {
            Ok(deps) => needs_rebuild(&exe_path, &deps),
            Err(_) => true, // If we can't collect deps, assume rebuild needed
        }
    };

    // Only build if needed
    if should_rebuild {
        match builder::build(path, target, lang, cc, false) {
            Ok(_) => {},
            Err(err) => {
                println!("ERROR: {err}");
                std::process::exit(1);
            },
        };
    }

    // Run the compiled binary with any extra arguments
    let status = std::process::Command::new(&exe_path)
        .args(extra_args)
        .status();

    match status {
        Ok(exit_status) => {
            if !exit_status.success() {
                std::process::exit(exit_status.code().unwrap_or(1));
            }
        },
        Err(e) => {
            println!("Failed to run '{}': {}", exe_path, e);
            std::process::exit(1);
        },
    }
}

fn main() {
    env::set_var("RUST_BACKTRACE", "1");
    let args: Vec<String> = env::args().collect();

    if args.len() > 2 {
        let command = args[1].as_str();
        let remaining_args: Vec<String> = args[2..].to_vec();

        match command {
            "interpret" => {
                // interpret doesn't use build options, just pass remaining args
                let path = &args[2];
                let main_args: Vec<String> = args[3..].to_vec();
                interpret_file_or_exit(path, main_args);
            },
            "build" | "translate" => {
                // Parse build options from remaining args
                match parse_build_options(&remaining_args) {
                    Ok((paths, target, lang, cc, translate_flag, force_rebuild)) => {
                        if paths.is_empty() {
                            println!("Error: No path specified");
                            usage();
                            std::process::exit(1);
                        }
                        let translate_only = command == "translate" || translate_flag;
                        build_file_or_exit(&paths[0], &target, &lang, cc.as_deref(), translate_only, force_rebuild);
                    },
                    Err(err) => {
                        println!("Error: {}", err);
                        std::process::exit(1);
                    },
                }
            },
            "run" => {
                // Parse build options from remaining args
                match parse_build_options(&remaining_args) {
                    Ok((paths, target, lang, cc, _, force_rebuild)) => {
                        if paths.is_empty() {
                            println!("Error: No path specified");
                            usage();
                            std::process::exit(1);
                        }
                        // Pass remaining paths as arguments to the compiled program
                        let extra_args = if paths.len() > 1 { &paths[1..] } else { &[] };
                        run_file_or_exit(&paths[0], &target, &lang, cc.as_deref(), extra_args, force_rebuild);
                    },
                    Err(err) => {
                        println!("Error: {}", err);
                        std::process::exit(1);
                    },
                }
            },
            "repl" => {
                usage();
            },
            _ => {
                println!("command '{}' not implemented.", command);
                usage();
                std::process::exit(1);
            },
        }
        return
    } else if args.len() > 1 {
        match args[1].as_str() {
            "repl" => {
                interpret_file_or_exit(&REPL_PATH.to_string(), Vec::new());
            },
            "ast" | "interpret" | "build" | "translate" | "run" |
            "help" | "-help" | "--help" | "--version" | "-v" => {
                usage();
            },
            _ => {
                interpret_file_or_exit(&args[1], Vec::new());
            },
        }
        return
    }

    // If no arguments, then repl/interactive "mode"
    interpret_file_or_exit(&REPL_PATH.to_string(), Vec::new());
}
