use std::env;
use std::fs;
use std::io::ErrorKind;

mod rs {
    pub mod lexer;
    pub mod mode;
    pub mod parser;
    pub mod init;
    pub mod typer;
    pub mod interpreter;
    pub mod ext;
}
use rs::lexer::{LANG_NAME, lexer_from_source};
use rs::mode::{can_be_imported, parse_mode};
use rs::parser::{
    Expr, NodeType, FunctionType, SFuncDef, Literal,
    parse_tokens,
};
use rs::init::Context;
use rs::interpreter::EvalResult;

const DEFAULT_MODE         : &str = "lib";
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

// ---------- main binary

fn main_run(print_extra: bool, skip_init_and_typecheck: bool, context: &mut Context, path: &String, source: String, main_args: Vec<String>) -> Result<EvalResult, String> {

    let mut lexer = match lexer_from_source(&path, source) {
        Ok(_result) => _result,
        Err(error_string) => {
            return Err(format!("{}:{}", &path, error_string));
        },
    };

    let mode = parse_mode(&path, &mut lexer)?;
    context.mode_def = mode;
    if print_extra {
        println!("Mode: {}", context.mode_def.name);
    }

    for import_str in context.mode_def.imports.clone() {
        let import_func_name_expr = Expr{node_type: NodeType::Identifier("import".to_string()), params: Vec::new(), line: 0, col: 0};
        let import_path_expr = Expr{node_type: NodeType::LLiteral(Literal::Str(import_str.to_string())), params: Vec::new(), line: 0, col: 0};
        let import_fcall_expr = Expr{node_type: NodeType::FCall, params: vec![import_func_name_expr, import_path_expr], line: 0, col: 0};
        match rs::ext::proc_import(context, &import_fcall_expr) {
            Ok(_) => {},
            Err(error_string) => {
                return Err(format!("{}:{}", &path, error_string));
            },
        }
    }

    let mut e: Expr = match parse_tokens(&mut lexer) {
        Ok(expr) => expr,
        Err(error_string) => {
            return Err(format!("{}:{}", &path, error_string));
        },
    };
    if !SKIP_AST {
        println!("AST: \n{}", to_ast_str(&e));
    }

    // Skip init and type checking if this is Phase 2 of a two-phase import
    // (declarations already registered in Phase 1)
    if !skip_init_and_typecheck {
        let mut errors = rs::init::init_context(context, &e);
        if errors.len() > 0 {
            for err in &errors {
                println!("{}:{}", path, err);
            }
            return Err(format!("Compiler errors: {} declaration errors found", errors.len()));
        }
        errors.extend(rs::typer::basic_mode_checks(&context, &e));

        // For modes that require a main proc, add an implicit call to main
        if context.mode_def.needs_main_proc {
            let mut main_params = Vec::new();
            main_params.push(Expr{node_type: NodeType::Identifier("main".to_string()), line: 0, col: 0, params: Vec::new()});
            for str_arg in main_args {
                main_params.push(Expr{node_type: NodeType::LLiteral(Literal::Str(str_arg)), line: 0, col: 0, params: Vec::new()});
            }
            e.params.push(Expr{node_type: NodeType::FCall, line: 0, col: 0, params: main_params});
        }
        errors.extend(rs::typer::check_types(context, &e));

        // Check throw/catch and return things in the root body of the file (for modes script and test, for example)
        let func_def = SFuncDef{args: vec![], body: vec![], function_type: FunctionType::FTProc, return_types: vec![], throw_types: vec![], source_path: path.clone()};
        let mut thrown_type_strs: Vec<String> = vec![];
        let mut thrown_type_msgs: Vec<String> = vec![];
        let mut return_found = false;
        errors.extend(rs::typer::check_body_returns_throws(context, &e, &func_def, e.params.as_slice(), &mut thrown_type_strs, &mut thrown_type_msgs, &mut return_found));

        if return_found {
            errors.push(e.error(&path, "type", "Cannot return from the root of the file"));
        }
        for error_msg in &thrown_type_msgs {
            errors.push(error_msg.to_string());
        }

        if errors.len() > 0 {
            for err in &errors {
                println!("{}:{}", path, err);
            }
            return Err(format!("Compiler errors: {} type errors found", errors.len()));
        }

        // Clear import cache between init and eval phases so imports are actually evaluated
        context.imports_done.clear();
    }

    return match rs::interpreter::eval_expr(context, &e) {
        Ok(eval_result) => Ok(eval_result),
        Err(err) => Err(format!("{}:{}", path, err)),
    }
}

// ---------- main, usage, args, etc

fn run_file(path: &String, main_args: Vec<String>) -> Result<EvalResult, String> {
    let mut context = Context::new(path, DEFAULT_MODE)?;
    if path != "src/core/core.til" {
        // Automatically import core.til (needs full init and eval, skip_init=false)
        let core_path = "src/core/core.til".to_string();
        run_file_with_context(true, false, &mut context, &core_path, Vec::new())?;
    }
    return run_file_with_context(false, false, &mut context, &path, main_args)
}

fn run_file_with_context(is_import: bool, skip_init: bool, context: &mut Context, path: &String, main_args: Vec<String>) -> Result<EvalResult, String> {
    let previous_mode = context.mode_def.clone();
    if !is_import {
        println!("Running file '{}'", &path);
    }
    let source: String = match fs::read_to_string(path) {
        Ok(file) => file,
        Err(error) => match error.kind() {
            ErrorKind::NotFound => {
                return Err(format!("File '{path}' not found."))
            },
            other_error => {
                return Err(format!("Problem opening the file '{path}': {other_error:?}"))
            },
        },
    };
    let run_result = main_run(!is_import, skip_init, context, &path, source, main_args)?;

    if is_import && !can_be_imported(&context.mode_def) {
        return Err(format!("file '{path}' of mode '{}' cannot be imported", context.mode_def.name))
    }
    context.mode_def = previous_mode; // restore the context mode of the calling file
    return Ok(run_result)
}

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
