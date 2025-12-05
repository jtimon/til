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
}
use rs::lexer::LANG_NAME;
use rs::parser::{Expr, NodeType, FunctionType, Literal};
use rs::interpreter::run_file;

const SELF_HOSTED_PATH     : &str = "src/til.til";
const SKIP_AST             : bool = true;

// ---------- AST to string conversion

fn params_to_ast_str(end_line: bool, e: &Expr) -> String {
    let mut ast_str = "".to_string();
    for se in e.params.iter() {
        if end_line {
            ast_str.push_str(&format!("{}\n", to_ast_str(&se)));
        } else {
            ast_str.push_str(&format!("{} ", to_ast_str(&se)));
        }
    }
    return ast_str;
}

// TODO test this function again and maintain it, but in the self hosting side directly, perhaps
fn to_ast_str(e: &Expr) -> String {
    let mut ast_str = "".to_string();
    match &e.node_type {
        NodeType::LLiteral(Literal::Number(li64)) => {
            return li64.to_string();
        },
        NodeType::LLiteral(Literal::Str(lstring)) => {
            return lstring.to_string();
        },
        NodeType::DefaultCase => {
            return "default_case".to_string();
        }
        NodeType::Body => {
            return params_to_ast_str(true, &e)
        },
        // NodeType::Declaration(decl) => {
        //     ast_str.push_str(&format!("(def {} {})", decl.name, to_ast_str(&e.get(0))));
        //     return ast_str;
        // },
        // NodeType::Assignment(var_name) => {
        //     ast_str.push_str(&format!("(set {} {})", var_name, to_ast_str(&e.get(0))));
        //     return ast_str;
        // },
        NodeType::FuncDef(func_def) => {
            match func_def.function_type {
                FunctionType::FTFunc => return "(func)".to_string(),
                FunctionType::FTProc => return "(proc)".to_string(),
                FunctionType::FTMacro => return "(macro)".to_string(),
                FunctionType::FTFuncExt => return "(ext_func)".to_string(),
                FunctionType::FTProcExt => return "(ext_proc)".to_string(),
            }
        },
        NodeType::EnumDef(_) => {
            return "(enum)".to_string();
        },
        NodeType::StructDef(_) => {
            return "(struct)".to_string();
        },
        NodeType::Identifier(id_name) => {
            return id_name.clone();
        },
        NodeType::FCall => {
            let f_name = rs::init::get_func_name_in_call(&e);
            ast_str.push_str(&format!("({} {})", f_name, params_to_ast_str(false, &e)));
            return ast_str;
        },
        NodeType::LLiteral(Literal::List(_)) => {
            ast_str.push_str(&format!("({})", params_to_ast_str(false, &e)));
            return ast_str;
        },
        // NodeType::If => {
        //     ast_str.push_str(&format!("(if {})", to_ast_str(&e.get(0))));
        //     return ast_str;
        // },
        // NodeType::While => {
        //     ast_str.push_str(&format!("(while {})", to_ast_str(&e.get(0))));
        //     return ast_str;
        // },
        // NodeType::Switch => {
        //     ast_str.push_str(&format!("(switch {})", to_ast_str(&e.get(0))));
        //     return ast_str;
        // },
        _ => todo!(),
    }
}

// ---------- main, usage, args, etc

fn usage() {
    println!("Usage: {} [command] [path]\n", LANG_NAME);
    println!("Entering no arguments is equavalent to: {} repl", LANG_NAME);
    println!("Entering a single argument that's not a command is interpreted as a path, equivalent to: {} interpret <path>\n", LANG_NAME);

    println!("Commands:\n");

    println!("repl: read eval print loop.");
    println!("interpret: reads a file in provided <path> and evaluates it.");
    // println!("ast: reads a file in provided <path> and prints its abstract syntax tree (aka (lisp-like-syntax ast-from-now-on ) ).");
    // println!("build: reads a file in provided <path> and compiles it. Not implemented yet.");
    // println!("run: reads a file in provided <path> and runs it if it compiles. Not implemented yet.");
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
            "repl" | "build" | "run" => {
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
