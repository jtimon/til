use std::env;

mod rs {
    pub mod lexer;
    pub mod mode;
    pub mod parser;
    pub mod init;
    pub mod typer;
    pub mod arena;
    pub mod interpreter;
    pub mod ext;
    pub mod codegen_c;
    pub mod builder;
}
use rs::lexer::LANG_NAME;
use rs::interpreter::run_file;
use rs::builder;

const SELF_HOSTED_PATH     : &str = "src/til.til";

// ---------- main, usage, args, etc

fn usage() {
    println!("Usage: {} [command] [path]\n", LANG_NAME);
    println!("Entering no arguments is equavalent to: {} repl", LANG_NAME);
    println!("Entering a single argument that's not a command is interpreted as a path, equivalent to: {} interpret <path>\n", LANG_NAME);

    println!("Commands:\n");

    println!("repl: read eval print loop.");
    println!("interpret: reads a file in provided <path> and evaluates it.");
    // println!("ast: reads a file in provided <path> and prints its abstract syntax tree (aka (lisp-like-syntax ast-from-now-on ) ).");
    println!("build: reads a file in provided <path> and compiles it to C.");
    println!("run: reads a file in provided <path>, compiles and runs it.");
    println!("help: Prints this.\n");
}

fn interpret_file_or_exit(path: &String, args: Vec<String>) {
    match run_file(path, args) {
        Ok(_) => {},
        Err(err) => {
            println!("ERROR: While running file {path}:\n{err}");
            std::process::exit(1);
        },
    };
}

fn build_file_or_exit(path: &String) {
    match builder::build(path) {
        Ok(_) => {},
        Err(err) => {
            println!("Build error: {}", err);
            std::process::exit(1);
        },
    };
}

fn run_file_or_exit(path: &String) {
    build_file_or_exit(path);
    // TODO: run compiled binary
    println!("TODO: run compiled binary not implemented");
}

fn main() {
    env::set_var("RUST_BACKTRACE", "1");
    let args: Vec<String> = env::args().collect();


    if args.len() > 2 {
        let mut main_args = Vec::new();
        let mut i = 0;
        for arg in &args {
            if i > 2 {
                main_args.push(arg.clone());
            }
            i += 1;
        }
        match args[1].as_str() {
            "interpret" => {
                interpret_file_or_exit(&args[2], main_args);
            },
            "build" => {
                build_file_or_exit(&args[2]);
            },
            "run" => {
                run_file_or_exit(&args[2]);
            },
            "repl" => {
                usage();
            },
            _ => {
                println!("command '{}' not implemented.", &args[1]);
                usage();
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
            "ast" | "interpret" | "build" | "run" |
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
