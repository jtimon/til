use std::env;

mod rs {
    pub mod lexer;
    pub mod mode;
    pub mod target;
    pub mod parser;
    pub mod init;
    pub mod typer;
    pub mod precomp;
    pub mod scavenger;
    pub mod arena;
    pub mod interpreter;
    pub mod ext;
    pub mod ccodegen;
    pub mod builder;
}
use rs::lexer::LANG_NAME;
use rs::interpreter::run_file;
use rs::builder;
use rs::arena::Arena;
use rs::target::{Target, Lang, target_from_str, lang_from_str, detect_current_target, default_lang_for_target};

const SELF_HOSTED_PATH     : &str = "src/til.til";

// Parse --target=X and --lang=X options from args, return (remaining_args, target, lang, translate_only)
fn parse_build_options(args: &[String]) -> Result<(Vec<String>, Target, Lang, bool), String> {
    let mut remaining = Vec::new();
    let mut target: Option<Target> = None;
    let mut lang: Option<Lang> = None;
    let mut translate_only = false;

    for arg in args {
        if arg.starts_with("--target=") {
            let value = &arg[9..];
            target = Some(target_from_str(value)?);
        } else if arg.starts_with("--lang=") {
            let value = &arg[7..];
            lang = Some(lang_from_str(value)?);
        } else if arg == "--translate" {
            translate_only = true;
        } else {
            remaining.push(arg.clone());
        }
    }

    // Default target is current platform
    let final_target = target.unwrap_or_else(detect_current_target);
    // Default lang is determined by target
    let final_lang = lang.unwrap_or_else(|| default_lang_for_target(&final_target));

    Ok((remaining, final_target, final_lang, translate_only))
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
    println!("                  Supported: c\n");
}

fn interpret_file_or_exit(path: &String, args: Vec<String>) {
    match run_file(path, args) {
        Ok(_) => {},
        Err(err) => {
            println!("ERROR: While running file {path}:\n{err}");
            std::process::exit(1);
        },
    };
    if path.ends_with("tests.til") {
        println!("Total memory used by interpreted program: {} bytes", Arena::g().len());
    }
}

fn build_file_or_exit(path: &String, target: &Target, lang: &Lang, translate_only: bool) {
    match builder::build(path, target, lang, translate_only) {
        Ok(output_path) => {
            if translate_only {
                println!("Generated: {}", output_path);
            }
        },
        Err(err) => {
            println!("Build error: {}", err);
            std::process::exit(1);
        },
    };
}

fn run_file_or_exit(path: &String, target: &Target, lang: &Lang, extra_args: &[String]) {
    let exe_path = match builder::build(path, target, lang, false) {
        Ok(exe) => exe,
        Err(err) => {
            println!("Build error: {}", err);
            std::process::exit(1);
        },
    };

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
                    Ok((paths, target, lang, translate_flag)) => {
                        if paths.is_empty() {
                            println!("Error: No path specified");
                            usage();
                            std::process::exit(1);
                        }
                        let translate_only = command == "translate" || translate_flag;
                        build_file_or_exit(&paths[0], &target, &lang, translate_only);
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
                    Ok((paths, target, lang, _)) => {
                        if paths.is_empty() {
                            println!("Error: No path specified");
                            usage();
                            std::process::exit(1);
                        }
                        // Pass remaining paths as arguments to the compiled program
                        let extra_args = if paths.len() > 1 { &paths[1..] } else { &[] };
                        run_file_or_exit(&paths[0], &target, &lang, extra_args);
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
                let mut repl_temp : Vec<String> = Vec::new();
                repl_temp.push("repl".to_string());
                interpret_file_or_exit(&SELF_HOSTED_PATH.to_string(), repl_temp);
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

    // If not arguments, then repl/interactive "mode"
    let mut repl_temp : Vec<String> = Vec::new();
    repl_temp.push("repl".to_string());
    interpret_file_or_exit(&SELF_HOSTED_PATH.to_string(), repl_temp);
}
