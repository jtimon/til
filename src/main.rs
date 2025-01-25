use std::env;
use std::io;
use std::io::Write; // <--- bring flush() into scope
use std::fs;
use std::io::ErrorKind;
use std::collections::HashMap;

// ---------- lex stuff

#[derive(Debug, Clone, PartialEq)]
enum TokenType {
    // basic
    Eof,

    // Single-character tokens.
    Minus, Plus, Slash, Star,
    LeftParen, RightParen, LeftBrace, RightBrace,
    Comma, Dot, Colon, Semicolon,

    // One or two character tokens.
    Not, NotEqual,
    Equal, EqualEqual,
    Greater, GreaterEqual,
    Lesser, LesserEqual,

    // Literals.
    Identifier, String, Number,

    // Reserved words:

    // bool
    True, False,
    // types
    // bool, i64, string, // TODO decide if parse basic types as reserved words (probably not)
    Struct, Enum,
    // function definition
    Func, Proc,
    Return, Returns,
    Throw, Throws, Try, Catch,
    // flow control
    If, Else,
    Match, While, For, In,

    // TODO implement or remove
    Mut,
    Debug , Log,

    // Errors
    Invalid,
    UnterminatedString,
    // UnterminatedComment, // TODO do nesting comments like jai and odin, shoulnd't be that hard. ideally in the lexer itself
}

#[derive(Debug, Clone)]
struct Token {
    token_type: TokenType,
    start: usize,
    end: usize,
    line: usize,
    col: usize,
}

fn get_token_str<'a>(source: &'a String, t: &'a Token) -> &'a str {
    &source[t.start..t.end]
}

fn print_lex_error(path: &String, source: &String, t: &Token, num_error: usize, msg: &str) {
    let max_symbol_len = 20;
    let mut end_symbol = t.end;
    if end_symbol - t.start > max_symbol_len {
        end_symbol = max_symbol_len;
    }
    println!("{}:{}:{} Lexical error {}: {}. Offending symbol: {}", path, t.line, t.col, num_error, msg, &source[t.start..end_symbol]);
}

fn is_literal(t: &Token) -> bool {
    match t.token_type {
        TokenType::String => true,
        TokenType::Number => true,
        TokenType::True => true,
        TokenType::False => true,
        _ => false,
    }
}

#[derive(Debug, Clone, PartialEq)]
enum ValueType {
    TBool,
    TString,
    TI64,
    TList,
    TFunc,
    TProc,
    TStruct,
    TMulti(Box<ValueType>),
    TCustom(String),
}

fn str_to_value_type(arg_type: &str) -> ValueType {
    match arg_type {
        "bool" => ValueType::TBool,
        "String" => ValueType::TString,
        "list" => ValueType::TList,
        "func" => ValueType::TFunc,
        "proc" => ValueType::TProc,
        "struct" => ValueType::TStruct,
        "i64" => ValueType::TI64,
        type_name => ValueType::TCustom(type_name.to_string()),
    }
}


#[derive(Debug, Clone, PartialEq)]
struct Declaration {
    name: String,
    value_type: ValueType,
}

#[derive(Debug, Clone, PartialEq)]
struct Assignement {
    name: String,
    value_type: ValueType,
}

#[derive(Debug, Clone, PartialEq)]
struct Arg {
    name: String,
    value_type: ValueType,
}

#[derive(Debug, Clone, PartialEq)]
struct FuncDef {
    args: Vec<Arg>,
    returns: Vec<ValueType>,
    // throws: Vec<ValueType>,
    body: Vec<Expr>,
}

#[derive(Debug, Clone, PartialEq)]
enum NodeType {
    // Mode,
    Body,
    LList,
    LString(String),
    LI64(i64),
    LBool(bool),
    // LDecimal(String),
    FCall(String),
    Identifier(String),
    Declaration(Declaration),
    Assignement(Assignement),
    FuncDef(FuncDef),
    ProcDef(FuncDef),
    StructDef,
    Return,
    If,
}

#[derive(Debug, Clone, PartialEq)]
struct Expr {
    node_type: NodeType,
    token_index: usize,
    params: Vec<Expr>,
}

#[derive(Clone)]
struct CilContext {
    symbols: HashMap<String, ValueType>,
    funcs: HashMap<String, FuncDef>,
    procs: HashMap<String, FuncDef>,
    bools: HashMap<String, bool>,
    i64s: HashMap<String, i64>,
    strings: HashMap<String, String>,
}

fn start_context() -> CilContext {
    let mut context: CilContext = CilContext {
        symbols: HashMap::new(),
        funcs: HashMap::new(),
        procs: HashMap::new(),
        bools: HashMap::new(),
        i64s: HashMap::new(),
        strings: HashMap::new(),
    };

    let args_print : Vec<Arg> = Vec::new();
    let return_types_none : Vec<ValueType> = Vec::new();
    let body : Vec<Expr> = Vec::new();
    let func_def_print = FuncDef{args: args_print, returns: return_types_none, body: body.clone()};
    context.procs.insert("print".to_string(), func_def_print.clone());
    context.procs.insert("println".to_string(), func_def_print);

    let mut args_and_or : Vec<Arg> = Vec::new();
    args_and_or.push(Arg{name: "args".to_string(), value_type: ValueType::TMulti(Box::new(ValueType::TBool))});
    let mut return_type_bool : Vec<ValueType> = Vec::new();
    return_type_bool.push(ValueType::TBool);
    let func_def_and_or = FuncDef{args: args_and_or, returns: return_type_bool.clone(), body: body.clone()};
    context.funcs.insert("and".to_string(), func_def_and_or.clone());
    context.funcs.insert("or".to_string(), func_def_and_or);

    let mut args_single_bool : Vec<Arg> = Vec::new();
    args_single_bool.push(Arg{name: "a".to_string(), value_type: ValueType::TBool});
    let func_def_not = FuncDef{args: args_single_bool.clone(), returns: return_type_bool.clone(), body: body.clone()};
    context.funcs.insert("not".to_string(), func_def_not);

    let mut args_bin_i64 : Vec<Arg> = Vec::new();
    args_bin_i64.push(Arg{name: "a".to_string(), value_type: ValueType::TI64});
    args_bin_i64.push(Arg{name: "b".to_string(), value_type: ValueType::TI64});

    let func_def_bin_i64_to_bool = FuncDef{args: args_bin_i64.clone(), returns: return_type_bool.clone(), body: body.clone()};
    context.funcs.insert("eq".to_string(), func_def_bin_i64_to_bool.clone());
    context.funcs.insert("lt".to_string(), func_def_bin_i64_to_bool.clone());
    context.funcs.insert("lteq".to_string(), func_def_bin_i64_to_bool.clone());
    context.funcs.insert("gt".to_string(), func_def_bin_i64_to_bool.clone());
    context.funcs.insert("gteq".to_string(), func_def_bin_i64_to_bool.clone());

    let mut return_type_i64 : Vec<ValueType> = Vec::new();
    return_type_i64.push(ValueType::TI64);
    let func_def_bin_i64_to_i64 = FuncDef{args: args_bin_i64, returns: return_type_i64.clone(), body: body.clone()};
    context.funcs.insert("add".to_string(), func_def_bin_i64_to_i64.clone());
    context.funcs.insert("sub".to_string(), func_def_bin_i64_to_i64.clone());
    context.funcs.insert("mul".to_string(), func_def_bin_i64_to_i64.clone());
    context.funcs.insert("div".to_string(), func_def_bin_i64_to_i64.clone());

    let return_type_single_str : Vec<ValueType> = Vec::new();
    let func_def_btoa = FuncDef{args: args_single_bool, returns: return_type_single_str.clone(), body: body.clone()};
    context.funcs.insert("btoa".to_string(), func_def_btoa);

    let mut args_single_i64 : Vec<Arg> = Vec::new();
    args_single_i64.push(Arg{name: "a".to_string(), value_type: ValueType::TI64});
    let func_def_itoa = FuncDef{args: args_single_i64, returns: return_type_single_str.clone(), body: body.clone()};
    context.funcs.insert("itoa".to_string(), func_def_itoa);

    context
}

fn value_type_func_proc(name: &str, func_def: &FuncDef) -> ValueType {
    match func_def.returns.len() {
        0 => {
            panic!("cil error: func '{}' does not return anything" , name)
        },
        1 => {
            match func_def.returns.get(0).unwrap() {
                ValueType::TBool => ValueType::TBool,
                ValueType::TI64 => ValueType::TI64,
                ValueType::TString => ValueType::TString,
                _ => panic!("cil error: func '{}' returns unsupported type {:?}" , name, func_def.returns.get(0).unwrap()),
            }
        },
        _ => {
            panic!("cil error: func '{}' returns multiple values, but that's not implemented yet." , name)
        },
    }
}

fn value_type(context: &CilContext, e: &Expr) -> ValueType {
    match &e.node_type {
        NodeType::LBool(_) => ValueType::TBool,
        NodeType::LI64(_) => ValueType::TI64,
        NodeType::LString(_) => ValueType::TString,
        NodeType::LList => ValueType::TList,
        NodeType::FuncDef(_) => ValueType::TFunc,
        NodeType::ProcDef(_) => ValueType::TProc,
        NodeType::StructDef => ValueType::TStruct,
        NodeType::FCall(name) => {
            if context.funcs.contains_key(name) {
                value_type_func_proc(name, &context.funcs.get(name).unwrap())
            } else if context.procs.contains_key(name) {
                value_type_func_proc(name, &context.procs.get(name).unwrap())
            } else if is_defined_symbol(&context, name) {
                panic!("compile error: value_type: Cannot call '{}', it is not a function/procedure" , name);
            } else {
                panic!("compile error: value_type: Undefined function '{}'", name);
            }
        },
        NodeType::Identifier(name) => {
            match context.symbols.get(name) {
                Some(value_type) => value_type.clone(),
                None => {
                    panic!("cil error: Undefined symbol '{}'. This should have been caught outside 'value_type()'.", name)
                }
            }
        },
        // _ => panic!("cil error: value_type() not implement for this yet."),
       node_type => panic!("cil error: value_type() not implement for {:?} yet.", node_type),
    }
}

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

fn to_ast_str(e: &Expr) -> String {
    let mut ast_str = "".to_string();
    match &e.node_type {
        NodeType::LBool(lbool) => {
            return lbool.to_string();
        },
        NodeType::LI64(li64) => {
            return li64.to_string();
        },
        NodeType::LString(lstring) => {
            return lstring.to_string();
        },
        NodeType::Body => {
            return params_to_ast_str(true, &e)
        },
        NodeType::Declaration(decl) => {
            ast_str.push_str(&format!("(def {} {})", decl.name, to_ast_str(&e.params.get(0).unwrap())));
            return ast_str;
        },
        NodeType::Assignement(asig) => {
            ast_str.push_str(&format!("(set {} {})", asig.name, to_ast_str(&e.params.get(0).unwrap())));
            return ast_str;
        },
        NodeType::FuncDef(_func_def) => {
            return "func".to_string();
        },
        NodeType::ProcDef(_func_def) => {
            return "proc".to_string();
        },
        NodeType::StructDef => {
            return "struct".to_string();
        },
        NodeType::Identifier(id_name) => {
            return id_name.clone();
        },
        NodeType::FCall(name) => {
            ast_str.push_str(&format!("({} {})", name, params_to_ast_str(false, &e)));
            return ast_str;
        },
        NodeType::LList => {
            ast_str.push_str(&format!("({})", params_to_ast_str(false, &e)));
            return ast_str;
        },
        NodeType::If => {
            ast_str.push_str(&format!("(if {})", to_ast_str(&e.params.get(0).unwrap())));
            return ast_str;
        },
        NodeType::Return => {
            panic!("Cil error: Node_type::Return shouldn't be analized in to_ast_str().");
        },
    }
}

fn is_digit(source: &String, pos: usize) -> bool {
    match &source[pos..pos+1].chars().next().unwrap() {
        '0'..='9' => true,
        _ => false,
    }
}

fn is_alphanumeric(source: &String, pos: usize) -> bool {
    match &source[pos..pos+1].chars().next().unwrap() {
        'a'..='z' | 'A'..='Z' => true,
        '_' => true,
        _ => false,
    }
    // source[pos..pos+1].bytes().all(|b| matches!(b, b'a'..=b'z'))
    //     || source[pos..pos+1].bytes().all(|b| matches!(b, b'A'..=b'Z'))
}

fn get_identifier_type(identifier: &str) -> TokenType {
    match identifier {
        "true" => TokenType::True,
        "false" => TokenType::False,
        "mut" => TokenType::Mut,
        "if" => TokenType::If,
        "else" => TokenType::Else,
        "while" => TokenType::While,
        "for" => TokenType::For,
        "in" => TokenType::In,
        "match" => TokenType::Match,
        "enum" => TokenType::Enum,
        "struct" => TokenType::Struct,
        "func" => TokenType::Func,
        "proc" => TokenType::Proc,
        "return" => TokenType::Return,
        "returns" => TokenType::Returns,
        "throw" => TokenType::Throw,
        "throws" => TokenType::Throws,
        "try" => TokenType::Try,
        "catch" => TokenType::Catch,
        "debug" => TokenType::Debug,
        "log" => TokenType::Log,
        _ => TokenType::Identifier,
    }
}

fn increment_scan(pos: &mut usize, col: &mut usize) {
    *pos += 1;
    *col += 1;
}

// TODO FIX handle col properly
fn scan_tokens(source: &String) -> Vec<Token> {
    let mut tokens : Vec<Token> = Vec::new();

    let eof_pos : usize = source.len();
    let mut pos = 0;
    let mut line = 1;
    let mut col = 0;

    while pos < eof_pos {
        let start = pos;

        if is_digit(source, pos) {
            while pos < eof_pos && is_digit(source, pos) {
                increment_scan(&mut pos, &mut col);
            }
            // Look for a fractional part.
            if &source[pos..pos+1] == "." && is_digit(source, pos+1) {
                increment_scan(&mut pos, &mut col);
                while pos < eof_pos && is_digit(source, pos) {
                    increment_scan(&mut pos, &mut col);
                }
            }
            tokens.push(Token { token_type: TokenType::Number, start: start, end: pos, line: line, col: 0 });
        } else {

            let token_type = match &source[pos..pos+1] {
                " " => { increment_scan(&mut pos, &mut col); continue; },
                "\r" => { increment_scan(&mut pos, &mut col); continue; },
                "\t" => { increment_scan(&mut pos, &mut col); continue; },
                "\n" => {
                    increment_scan(&mut pos, &mut col);
                    line = line + 1;
                    col = 0;
                    continue;
                },
                "(" => TokenType::LeftParen,
                ")" => TokenType::RightParen,
                "{" => TokenType::LeftBrace,
                "}" => TokenType::RightBrace,
                "-" => TokenType::Minus,
                "+" => TokenType::Plus,
                "*" => TokenType::Star,
                "," => TokenType::Comma,
                "." => TokenType::Dot,
                ":" => TokenType::Colon,
                ";" => TokenType::Semicolon,
                "=" => if &source[pos+1..pos+2] == "=" { increment_scan(&mut pos, &mut col); TokenType::EqualEqual } else { TokenType::Equal },
                "<" => if &source[pos+1..pos+2] == "=" { increment_scan(&mut pos, &mut col); TokenType::LesserEqual } else { TokenType::Lesser },
                ">" => if &source[pos+1..pos+2] == "=" { increment_scan(&mut pos, &mut col); TokenType::GreaterEqual } else { TokenType::Greater },
                "!" => if &source[pos+1..pos+2] == "=" { increment_scan(&mut pos, &mut col); TokenType::NotEqual } else { TokenType::Not },

                "/" => match &source[pos+1..pos+2] {
                    "/" => {
                        increment_scan(&mut pos, &mut col);
                        while pos + 1 < eof_pos && &source[pos..pos+1] != "\n" {
                            increment_scan(&mut pos, &mut col);
                        }
                        continue;
                        // TODO allow the other type of commments, allowing nesting
                    },
                    _ => TokenType::Slash,
                },

                "\"" => {
                    increment_scan(&mut pos, &mut col);
                    while pos + 1 < eof_pos && &source[pos..pos+1] != "\"" {
                        increment_scan(&mut pos, &mut col);
                    }
                    // pos = pos - 1;
                    match &source[pos..pos+1] {
                        "\"" => TokenType::String,
                        _ => TokenType::UnterminatedString,
                    }
                },

                _ => {
                    if is_alphanumeric(source, pos){
                        increment_scan(&mut pos, &mut col);
                        // FIX invalid characters
                        while pos < eof_pos && (is_alphanumeric(source, pos) || is_digit(source, pos)) {
                            increment_scan(&mut pos, &mut col);
                        }
                        pos = pos - 1;
                        get_identifier_type(&source[start..pos+1])

                    } else {
                        TokenType::Invalid
                    }
                },
            }; // let match
            if token_type == TokenType::String {
                tokens.push(Token { token_type: token_type, start: start + 1, end: pos, line: line, col: 0 });
            } else {
                tokens.push(Token { token_type: token_type, start: start, end: pos + 1, line: line, col: 0 });
            }
            increment_scan(&mut pos, &mut col)
        } // else
    } // while
    tokens.push(Token { token_type: TokenType::Eof, start: pos, end: pos + 1, line: line, col: 0 });
    tokens
}

fn is_eof(tokens: &Vec<Token>, current: usize) -> bool {
    current > tokens.len() || match tokens.get(current).unwrap().token_type {
        TokenType::Eof => true,
        _ => false,
    }
}

fn literal(source: &String, t: &Token, current: &mut usize) -> Expr {
    let params : Vec<Expr> = Vec::new();
    let node_type = match t.token_type {
        TokenType::String => NodeType::LString(get_token_str(source, t).to_string()),
        TokenType::Number => NodeType::LI64(get_token_str(source, t).parse::<i64>().unwrap()),
        TokenType::True => NodeType::LBool(true),
        TokenType::False => NodeType::LBool(false),
        _ => panic!("{}:{} cil error: Trying to parse a token that's not a literal as a literal.", t.line, t.col),
    };
    let e = Expr { node_type: node_type, token_index: *current, params: params};
    *current = *current + 1;
    e
}

fn list(mut context: &mut CilContext, source: &String, tokens: &Vec<Token>, current: &mut usize) -> Expr {
// fn list(source: &String, tokens: &Vec<Token>, current: &mut usize) -> Result<Expr, CompilerError> {
    let mut rightparent_found = false;
    let mut params : Vec<Expr> = Vec::new();
    let initial_current = *current;
    *current = *current + 1;
    let mut list_t = tokens.get(*current).unwrap();
    // println!("primary debug LeftParen: {} {}", initial_current, *current);
    let mut expect_comma = false;
    while !(is_eof(&tokens, *current) || rightparent_found) {
        // println!("primary debug LeftParen while: {} {}", current, *current);
        match list_t.token_type {
            TokenType::RightParen => {
                rightparent_found = true;
                *current = *current + 1;
            },
            TokenType::Comma => {
                if expect_comma {
                    expect_comma = false;
                    *current = *current + 1;
                    list_t = tokens.get(*current).unwrap();
                } else {
                    panic!("{}:{} compiler error: Unexpected ','.", list_t.line, list_t.col);
                }
            },
            _ => {
                if expect_comma {
                    panic!("{}:{} compiler error: Expected ')' or ',', found {:?}.", list_t.line, list_t.col, list_t.token_type);
                }
                // TODO fix the error msg when...
                // if list_t.token_type == TokenType::Identifier {
                //     panic!("{}:{} compiler error: Expected ')' or ',', found {}.", list_t.line, list_t.col, get_token_str(source, list_t));
                // }
                expect_comma = true;
                params.push(primary(&mut context, &source, &tokens, current));
                list_t = tokens.get(*current).unwrap();
            },
        }
    }
    match list_t.token_type {
        TokenType::RightParen => Expr { node_type: NodeType::LList, token_index: initial_current, params: params},
        _ => panic!("{}:{} compiler error: Expected closing parentheses.", list_t.line, list_t.col),
    }
}

fn is_core_func(proc_name: &str) -> bool {
    match proc_name {
        "and" => true,
        "or" => true,
        "not" => true,
        "eq" => true,
        "lt" => true,
        "lteq" => true,
        "gt" => true,
        "gteq" => true,
        "add" => true,
        "sub" => true,
        "mul" => true,
        "div" => true,
        "btoa" => true,
        "itoa" => true,
        _ => false,
    }
}

fn is_core_proc(proc_name: &str) -> bool {
    match proc_name {
        "print" => true,
        "println" => true,
        "test" => true, // can be func after implementing throws
        "assert" => true, // can be func after implementing throws
        _ => false,
    }
}

fn func_call(mut context: &mut CilContext, source: &String, tokens: &Vec<Token>, current: &mut usize) -> Expr {
    let t = tokens.get(*current).unwrap();
    let token_str = get_token_str(source, t);
    let initial_current = *current;
    *current = *current + 1;
    let params : Vec<Expr> = list(&mut context, &source, &tokens, current).params;
    Expr { node_type: NodeType::FCall(token_str.to_string()), token_index: initial_current, params: params}
}

fn parse_assignment(mut context: &mut CilContext, source: &String, tokens: &Vec<Token>, current: &mut usize) -> Expr {
    let t = tokens.get(*current).unwrap();
    let name = get_token_str(source, t);
    let initial_current = *current;
    *current = *current + 2; // skip identifier and equal
    let mut params : Vec<Expr> = Vec::new();
    params.push(primary(&mut context, &source, &tokens, current));
    let e = params.get(0).unwrap();
    let value_type = value_type(&context, &e);
    let asig = Assignement{name: name.to_string(), value_type: value_type};
    Expr { node_type: NodeType::Assignement(asig), token_index: initial_current, params: params}
}

fn func_proc_args(_context: &CilContext, source: &String, tokens: &Vec<Token>, current: &mut usize) -> Vec<Arg> {

    let mut rightparent_found = false;
    let mut args : Vec<Arg> = Vec::new();
    *current = *current + 1;
    let mut t = tokens.get(*current).unwrap();
    let mut expect_comma = false;
    let mut expect_colon = false;
    let mut expect_name = true;
    let mut arg_name = "unnamed";
    while !(is_eof(&tokens, *current) || rightparent_found) {
        match t.token_type {
            TokenType::RightParen => {
                rightparent_found = true;
                *current = *current + 1;
            },
            TokenType::Comma => {
                if expect_comma {
                    expect_comma = false;
                    expect_name = true;
                    *current = *current + 1;
                    t = tokens.get(*current).unwrap();
                } else {
                    panic!("{}:{} compiler error: Unexpected ','.", t.line, t.col);
                }
            },
            TokenType::Colon => {
                if expect_colon {
                    expect_colon = false;
                    *current = *current + 1;
                    t = tokens.get(*current).unwrap();
                } else {
                    panic!("{}:{} compiler error: Unexpected ':'.", t.line, t.col);
                }
            },
            TokenType::Identifier => {
                if expect_comma {
                    panic!("{}:{} compiler error: Expected ',', found {:?}.", t.line, t.col, t.token_type);
                }
                if expect_colon {
                    panic!("{}:{} compiler error: Expected ':', found {:?}.", t.line, t.col, t.token_type);
                }
                if expect_name {
                    arg_name = get_token_str(source, t);
                    expect_colon = true;
                    expect_name = false;
                } else {
                    args.push(Arg{name: arg_name.to_string(), value_type: str_to_value_type(get_token_str(source, t))});
                    expect_comma = true;
                }
                *current = *current + 1;
                t = tokens.get(*current).unwrap();
            },
            _ => {
                panic!("{}:{} compiler error: Unexpected {:?} in func/proc args.", t.line, t.col, t.token_type);
            },
        }
    }
    match t.token_type {
        TokenType::RightParen => args,
        _ => panic!("{}:{} compiler error: Expected closing parentheses.", t.line, t.col),
    }
}

fn func_proc_returns(_context: &CilContext, source: &String, tokens: &Vec<Token>, current: &mut usize) -> Vec<ValueType> {
    let mut end_found = false;
    let mut return_types : Vec<ValueType> = Vec::new();
    let mut t = tokens.get(*current).unwrap();
    *current = *current + 1;
    if t.token_type != TokenType::Returns {
        return return_types;
    }
    t = tokens.get(*current).unwrap();
    let mut expect_comma = false;
    while !(is_eof(&tokens, *current) || end_found) {
        match t.token_type {
            TokenType::Throws | TokenType::LeftBrace => {
                end_found = true;
                *current = *current + 1;
            },
            TokenType::Comma => {
                if expect_comma {
                    expect_comma = false;
                    *current = *current + 1;
                    t = tokens.get(*current).unwrap();
                } else {
                    panic!("{}:{} compiler error: Unexpected ','.", t.line, t.col);
                }
            },
            TokenType::Identifier => {
                if expect_comma {
                    panic!("{}:{} compiler error: Expected ',', found {:?}.", t.line, t.col, t.token_type);
                }
                return_types.push(str_to_value_type(get_token_str(source, t)));
                expect_comma = true;
                *current = *current + 1;
                t = tokens.get(*current).unwrap();
            },
            _ => {
                panic!("{}:{} compiler error: Unexpected {:?} in func/proc returns.", t.line, t.col, t.token_type);
            },
        }
    }
    if end_found {
        return_types
    } else {
        panic!("{}:{} compiler error: Expected '{{' or 'throws' after return values.", t.line, t.col);
    }
}

fn func_proc_definition(is_func: bool, mut context: &mut CilContext, source: &String, tokens: &Vec<Token>, current: &mut usize) -> Expr {
    if is_eof(&tokens, *current + 1) {
        let t = tokens.get(*current).unwrap();
        panic!("{}:{} compiler error: expected '(' after 'func' or 'proc', found EOF.", t.line, t.col);
    } else {
        let t = tokens.get(*current).unwrap();
        if t.token_type == TokenType::LeftParen {
            let args = func_proc_args(&context, &source, &tokens, current);
            let returns = func_proc_returns(&context, &source, &tokens, current);
            let body = body(TokenType::RightBrace, &mut context, &source, tokens, current).params;
            let func_def = FuncDef{args: args, returns: returns, body: body};
            let params : Vec<Expr> = Vec::new();
            let e;
            match is_func {
                true => e = Expr { node_type: NodeType::FuncDef(func_def), token_index: *current, params: params},
                false => e = Expr { node_type: NodeType::ProcDef(func_def), token_index: *current, params: params},
            }
            *current = *current + 1;
            e
        } else {
            panic!("{}:{} compiler error: expected '(' after 'func', found {:?}.", t.line, t.col, t.token_type);
        }
    }
}

fn struct_definition(mut context: &mut CilContext, source: &String, tokens: &Vec<Token>, current: &mut usize) -> Expr {
    let t = tokens.get(*current).unwrap();
    if t.token_type != TokenType::LeftBrace {
        panic!("{}:{} compiler error: Expected '{{' after 'struct'.", t.line, t.col);
    }
    if is_eof(&tokens, *current + 1) {
        let t = tokens.get(*current).unwrap();
        panic!("{}:{} compiler error: expected '' after 'func' or 'proc', found EOF.", t.line, t.col);
    } else {
        *current = *current + 1;
        let params = body(TokenType::RightBrace, &mut context, &source, tokens, current).params;
        *current = *current + 1;
        return Expr { node_type: NodeType::StructDef, token_index: *current, params: params};
    }
}

fn primary(mut context: &mut CilContext, source: &String, tokens: &Vec<Token>, current: &mut usize) -> Expr {

    let t = tokens.get(*current).unwrap();
    if is_literal(t) {
        literal(&source, t, current)
    } else {
        match &t.token_type {
            TokenType::LeftParen => list(&mut context, &source, &tokens, current),
            TokenType::Identifier => {
                if !(is_eof(&tokens, *current + 1) || tokens.get(*current + 1).unwrap().token_type == TokenType::LeftParen) {
                    let params : Vec<Expr> = Vec::new();
                    let e = Expr { node_type: NodeType::Identifier(get_token_str(source, t).to_string()), token_index: *current, params: params};
                    *current = *current + 1;
                    e
                } else {
                    func_call(&mut context, &source, &tokens, current)
                }
            },
            TokenType::Func => {
                *current = *current + 1;
                func_proc_definition(true, &mut context, &source, &tokens, current)
            },
            TokenType::Proc => {
                *current = *current + 1;
                func_proc_definition(false, &mut context, &source, &tokens, current)
            },
            TokenType::Struct => {
                *current = *current + 1;
                struct_definition(&mut context, &source, &tokens, current)
            },
            _ => panic!("{}:{} compiler error: Expected primary expression, found {:?}.", t.line, t.col, t.token_type),
        }
    }
}

fn return_statement(mut context: &mut CilContext, source: &String, tokens: &Vec<Token>, current: &mut usize) -> Expr {
    let initial_current = *current;
    *current = *current + 1;
    let mut params : Vec<Expr> = Vec::new();
    params.push(primary(&mut context, &source, &tokens, current));
    Expr { node_type: NodeType::Return, token_index: initial_current, params: params}
}

fn if_statement(mut context: &mut CilContext, source: &String, tokens: &Vec<Token>, current: &mut usize) -> Expr {
    // TODO check EOF in this function, this is unsafe
    let initial_current = *current;
    *current = *current + 1;
    let mut params : Vec<Expr> = Vec::new();
    params.push(primary(&mut context, &source, &tokens, current));
    let mut t = tokens.get(*current).unwrap();
    if t.token_type != TokenType::LeftBrace {
        panic!("{}:{} compiler error: Expected '{{' after condition in 'if' statement.", t.line, t.col);
    }
    *current = *current + 1;
    params.push(body(TokenType::RightBrace, &mut context, &source, tokens, current));
    *current = *current + 1;
    t = tokens.get(*current).unwrap();
    if t.token_type == TokenType::Else {
        *current = *current + 1;
        t = tokens.get(*current).unwrap();
        if t.token_type != TokenType::LeftBrace {
            panic!("{}:{} compiler error: Expected '{{' after 'else'.", t.line, t.col);
        }
        *current = *current + 1;
        params.push(body(TokenType::RightBrace, &mut context, &source, tokens, current));
        *current = *current + 1;
    }
    Expr { node_type: NodeType::If, token_index: initial_current, params: params}
}

fn statement_declaration(mut context: &mut CilContext, source: &String, tokens: &Vec<Token>, current: &mut usize) -> Expr {
    let t = tokens.get(*current).unwrap();
    let decl_name = get_token_str(source, t);
    if is_defined_symbol(&context, decl_name) {
        panic!("{}:{} compiler error: '{}' already declared.", t.line, t.col, decl_name);
    }
    let initial_current = *current;
    *current = *current + 3; // skip identifier, colon and equal
    let mut params : Vec<Expr> = Vec::new();
    params.push(primary(&mut context, &source, &tokens, current));
    let e = params.get(0).unwrap();
    let value_type = value_type(&context, &e);
    match value_type {
        ValueType::TFunc => {
            match &e.node_type {
                NodeType::FuncDef(func_def) => {
                    context.funcs.insert(decl_name.to_string(), func_def.clone());
                },
                _ => {
                    panic!("{}:{} cil error: funcs/procs should have definitions. This should never happen", t.line, t.col);
                },
            }
        },
        ValueType::TProc => {
            match &e.node_type {
                NodeType::ProcDef(func_def) => {
                    context.procs.insert(decl_name.to_string(), func_def.clone());
                },
                _ => {
                    panic!("{}:{} cil error: funcs/procs should have definitions. This should never happen", t.line, t.col);
                },
            }
        },
        _ => {
            context.symbols.insert(decl_name.to_string(), value_type.clone());
        },
    }
    let decl = Declaration{name: decl_name.to_string(), value_type: value_type};
    Expr { node_type: NodeType::Declaration(decl), token_index: initial_current, params: params}
}

fn statement(mut context: &mut CilContext, source: &String, tokens: &Vec<Token>, current: &mut usize) -> Expr {
    let t = tokens.get(*current).unwrap();
    match &t.token_type {
        TokenType::Return => {
            return_statement(&mut context, &source, &tokens, current)
        },
        TokenType::If => {
            if_statement(&mut context, &source, &tokens, current)
        },
        TokenType::Mut => {
            panic!("{}:{} cil error: Mutable values not implemented yet.", t.line, t.col);
        },
        TokenType::Identifier => {
            if is_eof(&tokens, *current) {
                panic!("{}:{} compiler error: Expected '(', ':' or '=' after identifier in statement, found 'EOF'.", t.line, t.col);
            } else {
                let next_t = tokens.get(*current + 1).unwrap();
                let next_token_type = &next_t.token_type;
                match next_token_type {
                    TokenType::LeftParen => {
                        func_call(&mut context, &source, &tokens, current)
                    },
                    TokenType::Equal => {
                        parse_assignment(&mut context, &source, &tokens, current)
                    },
                    TokenType::Colon => {
                        let next_next_t = tokens.get(*current + 2).unwrap();
                        let next_next_token_type = &next_next_t.token_type;
                        match next_next_token_type {
                            TokenType::Identifier => {
                                let identifier = get_token_str(source, t);
                                let type_name = get_token_str(source, next_next_t);
                                panic!("{}:{} cil error: Suggestion: try changing '{} : {} =' for just '{} :='\nExplanation: Explicit type declaration is not allowed yet. Type inference is currently mandatory for declarations, the oposite is true for func/proc arguments. Ideally, in the future, type inference will both be allowed and not be mandatory for both arguments and declarations, for consistency (never for return types).\n ", t.line, t.col, identifier, type_name, identifier);
                            }
                            TokenType::Equal => {
                                statement_declaration(&mut context, &source, &tokens, current)
                            },
                            _ => panic!("{}:{} parse error: Expected Type or '=' after 'identifier :' in statement, found {:?}.", t.line, t.col, next_next_token_type),
                        }
                    },
                    _ => panic!("{}:{} compiler error: Expected '(', ':' or '=' after identifier in statement, found {:?}.", t.line, t.col, next_token_type),
                }
            }
        },
        _ => panic!("{}:{} compiler error: Expected statement, found {:?}.", t.line, t.col, t.token_type),
    }
}

fn body(end_token : TokenType, mut context: &mut CilContext, source: &String, tokens: &Vec<Token>, current: &mut usize) -> Expr {
    let initial_current: usize = *current;
    let mut params : Vec<Expr> = Vec::new();
    let mut end_found = false;
    while *current < tokens.len() && !end_found {
        // println!("next token: {:?}, {:?}", tokens.get(*current).unwrap().token_type, end_token);
        if tokens.get(*current).unwrap().token_type == end_token {
            end_found = true;
        } else {
            params.push(statement(&mut context, &source, &tokens, current));
        }
    }
    if end_found {
        Expr { node_type: NodeType::Body, token_index: initial_current, params: params}
    } else {
        panic!("compiler error: Expected {:?} to end body.", end_token);
    }
}

// ---------- Type checking stuff

fn is_defined_func_proc(context: &CilContext, name: &str) -> bool {
    context.funcs.contains_key(name) || context.procs.contains_key(name)
}

fn is_defined_symbol(context: &CilContext, name: &str) -> bool {
    is_defined_func_proc(&context, name) || context.symbols.contains_key(name)
}

fn does_func_return_bool(context: &CilContext, name: &str) -> bool {
    if context.funcs.contains_key(name) {
        let func_def = &context.funcs.get(name).unwrap();
        func_def.returns.len() == 1 && *func_def.returns.get(0).unwrap() == ValueType::TBool
    } else if context.procs.contains_key(name) {
        let func_def = &context.procs.get(name).unwrap();
        func_def.returns.len() == 1 && *func_def.returns.get(0).unwrap() == ValueType::TBool
    } else {
        false
    }
}

fn is_value_type_printable(value_type: &ValueType) -> bool {
    match value_type {
        ValueType::TBool => true,
        ValueType::TI64 => true,
        ValueType::TString => true,
        _ => false,
    }
}

fn check_all_params_printable(context: &CilContext, name: &str, source: &String, tokens: &Vec<Token>, e: &Expr) -> Vec<String> {
    let mut errors : Vec<String> = Vec::new();

    for p in e.params.iter() {
        match &p.node_type {
            NodeType::LBool(_) => {},
            NodeType::LI64(_) => {},
            NodeType::LString(_) => {},
            NodeType::LList => {
                errors.push(format!("Function '{}' cannot accept 'list' arguments", name));
            },
            NodeType::FuncDef(_) => {
                errors.push(format!("Function '{}' cannot accept 'func' arguments", name));
            },
            NodeType::StructDef => {
                errors.push(format!("Function '{}' cannot accept 'struct' arguments", name));
            },
            NodeType::ProcDef(_) => {
                errors.push(format!("Function '{}' cannot accept 'proc' arguments", name));
            },
            NodeType::Identifier(id_name) => {
                if context.symbols.contains_key(id_name) {
                    let value_type = context.symbols.get(id_name).unwrap();
                    if !is_value_type_printable(value_type) {
                        errors.push(format!("In call to '{}', expected printable arguments, but '{}' is {:?}", name, id_name, value_type));
                    }
                } else {
                    errors.push(format!("In call to '{}', undefined symbol {}", name, id_name));
                }
            }
            NodeType::FCall(func_name) => {
                if context.funcs.contains_key(name) {
                    let func_def = &context.funcs.get(name).unwrap();
                    if func_def.returns.len() != 1 {
                        errors.push(format!("func '{}' expects only calls that return single values as arguments, func '{}' returns {} values.",
                                            name, func_name, func_def.returns.len()));
                    } else {
                        let value_type = func_def.returns.get(0).unwrap();
                        if !is_value_type_printable(&value_type) {
                            errors.push(format!(
                                "func '{}' expects only printable arguments, func '{}' does not return something printable, it returns {:?}.",
                                name, func_name, value_type));
                        }
                    }

                } else if context.procs.contains_key(name) {
                    // TODO fix
                    // let func_def = &context.procs.get(name).unwrap();
                    // if func_def.returns.len() != 1 {
                    //     errors.push(format!("Function '{}' expects only calls that return single values as arguments, proc '{}' returns {} values.",
                    //                         name, func_name, func_def.returns.len()));
                    // } else {
                    //     match *func_def.returns.get(0).unwrap() {
                    //         ValueType::TBool => { continue; },
                    //         ValueType::TI64 => { continue; },
                    //         ValueType::TString => { continue; },
                    //         _ => {
                    //             errors.push(format!(
                    //                 "Function '{}' expects only printable arguments, procedure '{}' does not return something printable, it returns {:?}.",
                    //                 name, func_name, *func_def.returns.get(0).unwrap()));
                    //         },
                    //     }
                    // }
                } else {
                    errors.push(format!("Cil error: Calling '{}', undefined func/proc '{}' This should never happen", name, func_name));
                }
                errors.append(&mut check_types(&context, &source, &tokens, &p));
            }
            NodeType::Declaration(_) => {
                errors.push(format!("Cil error: Function '{}' cannot take a Declaration as an arg. This should never happen", name));
            }
            NodeType::Assignement(_) => {
                errors.push(format!("Cil error: Function '{}' cannot take a Declaration as an arg. This should never happen", name));
            }
            NodeType::Body => {
                errors.push(format!("Cil error: Function '{}' cannot take a Body as an arg. This should never happen", name));
            }
            NodeType::Return => {
                errors.push(format!("Cil error: Function '{}' cannot take a return statement as an arg. This should never happen", name));
            }
            NodeType::If => {
                errors.push(format!("Cil error: Function '{}' cannot take an if statement as an arg. This should never happen", name));
            }
        }
    }

    errors
}

fn is_expr_calling_procs(context: &CilContext, source: &String,  tokens: &Vec<Token>, e: &Expr) -> bool {
    match &e.node_type {
        NodeType::Body => {
            for se in &e.params {
                if is_expr_calling_procs(&context, &source, &tokens, &se) {
                    return true;
                }
            }
            false
        },
        NodeType::StructDef => {
            false
        },
        NodeType::LBool(_) => false,
        NodeType::LI64(_) => false,
        NodeType::LString(_) => false,
        NodeType::LList => false,
        NodeType::Identifier(_) => false,
        NodeType::FCall(call_name) => {
            context.procs.contains_key(call_name)
        },
        NodeType::Return => {
            for it_e in &e.params {
                if is_expr_calling_procs(&context, &source, &tokens, &it_e) {
                    return true;
                }
            }
            false
        },
        NodeType::Declaration(decl) => {
            assert!(e.params.len() != 1, "Cil error: while declaring {}, declarations must take exactly one value.", decl.name);
            is_expr_calling_procs(&context, &source, &tokens, &e.params.get(0).unwrap())
        },
        NodeType::Assignement(asig) => {
            assert!(e.params.len() == 1, "Cil error: while assigning {}, assignements must take exactly one value, not {}.", asig.name, e.params.len());
            is_expr_calling_procs(&context, &source, &tokens, &e.params.get(0).unwrap())
        }
        NodeType::ProcDef(func_def) => {
            for it_e in &func_def.body {
                if is_expr_calling_procs(&context, &source, &tokens, &it_e) {
                    return true;
                }
            }
            false
        },
        NodeType::FuncDef(func_def) => {
            for it_e in &func_def.body {
                if is_expr_calling_procs(&context, &source, &tokens, &it_e) {
                    return true;
                }
            }
            false
        },
        NodeType::If => {
            for it_e in &e.params {
                if is_expr_calling_procs(&context, &source, &tokens, &it_e) {
                    return true;
                }
            }
            false
        },
    }
}

fn func_proc_has_multi_arg(func_def: &FuncDef) -> bool {
    for a in &func_def.args {
        match a.value_type {
            ValueType::TMulti(_) => {
                return true;
            }
            _ => {}
        }
    }
    false
}

fn check_func_proc_types(func_def: &FuncDef, context: &CilContext, source: &String, tokens: &Vec<Token>) -> Vec<String> {
    let mut errors : Vec<String> = Vec::new();
    let mut function_context = context.clone();
    for arg in &func_def.args {
        function_context.symbols.insert(arg.name.clone(), arg.value_type.clone());
    }
    for p in func_def.body.iter() {
        errors.append(&mut check_types(&function_context, &source, &tokens, &p));
    }
    errors
}

fn check_types(context: &CilContext, source: &String, tokens: &Vec<Token>, e: &Expr) -> Vec<String> {
    let mut errors : Vec<String> = Vec::new();
    let t = tokens.get(e.token_index).unwrap();

    match &e.node_type {
        NodeType::Body => {
            for p in e.params.iter() {
                errors.append(&mut check_types(&context, &source, &tokens, &p));
            }
        },
        NodeType::StructDef => {
            for p in e.params.iter() {
                match &p.node_type {
                    NodeType::Declaration(_) => {}
                    node_type => {
                        errors.push(format!("{}:{} 'struct' can only include declarations, found {:?}.", t.line, t.col, node_type));
                    }
                }
                errors.append(&mut check_types(&context, &source, &tokens, &p));
            }
        },
        NodeType::If => {
            assert!(e.params.len() == 2 || e.params.len() == 3, "Cil error: if nodes must have 2 or 3 parameters.");
            // TODO check that the first param is of value_type bool
            for p in e.params.iter() {
                errors.append(&mut check_types(&context, &source, &tokens, &p));
            }
        },
        NodeType::FCall(name) => {
            if !is_defined_func_proc(&context, &name) {
                errors.push(format!("{}:{} Undefined function or procedure {}", t.line, t.col, name));
                return errors;
            }
            match name.as_str() {
                // TODO get rid of this special case and its special function
                "print" | "println" => { errors.append(&mut check_all_params_printable(&context, &name, &source, &tokens, &e)); },
                _ => {
                    let func_def;
                    if context.funcs.contains_key(name) {
                        func_def = context.funcs.get(name).unwrap();
                    } else if context.procs.contains_key(name) {
                        func_def = context.procs.get(name).unwrap();
                    } else {
                        panic!("cil error: Undefined function or procedure '{}'. This should have been caught in the before.\n", name);
                    }
                    let has_multi_arg = func_proc_has_multi_arg(func_def);
                    if !has_multi_arg && func_def.args.len() != e.params.len() {
                        errors.push(format!("{}:{} Function/procedure '{}' expects {} args, but {} were provided.", t.line, t.col, name, func_def.args.len(), e.params.len()));
                    }
                    if has_multi_arg && func_def.args.len() > e.params.len() {
                        errors.push(format!("{}:{} Function/procedure '{}' expects at least {} args, but {} were provided.", t.line, t.col, name, func_def.args.len(), e.params.len()));
                    }

                    let max_arg_def = func_def.args.len();
                    for i in 0..e.params.len() {
                        let arg = func_def.args.get(std::cmp::min(i, max_arg_def-1)).unwrap();
                        let expected_type = match &arg.value_type {
                            ValueType::TMulti(inner_type) => inner_type,
                            _ => &arg.value_type,

                        };
                        let found_type = value_type(&context, e.params.get(i).unwrap());
                        if expected_type != &found_type {
                            errors.push(format!("{}:{} calling func/proc '{}' expects {:?} for arg {}, but {:?} was provided.",
                                                t.line, t.col, name, expected_type, arg.name, found_type));
                        }
                    }
                },
            }
        },
        NodeType::Identifier(name) => {
            if !is_defined_symbol(&context, &name) {
                errors.push(format!("{}:{} Undefined symbol {}", t.line, t.col, name));
            }
        },
        NodeType::FuncDef(func_def) => {
            for se in &func_def.body {
                if is_expr_calling_procs(&context, &source, &tokens, &se) {
                    let proc_t = tokens.get(se.token_index).unwrap();
                    errors.push(format!("{}:{} compiler error: funcs cannot call procs.", proc_t.line, proc_t.col));
                }
            }
            errors.append(&mut check_func_proc_types(&func_def, &context, &source, &tokens));
        },
        NodeType::ProcDef(func_def) => {
            errors.append(&mut check_func_proc_types(&func_def, &context, &source, &tokens));
        },
        NodeType::Declaration(decl) => {
            assert!(e.params.len() == 1, "Cil error: in declaration of {} declaration nodes must exactly 1 parameter.", decl.name);
            errors.append(&mut check_types(&context, &source, &tokens, &e.params.get(0).unwrap()));
        },
        NodeType::Assignement(asig) => {
            assert!(e.params.len() == 1, "Cil error: in assignment to {}, assignements must take exactly one value, not {}.", asig.name, e.params.len());
            if is_core_func(&asig.name) {
                errors.push(format!("{}:{} compiler error: Core function '{}' cannot be assigned to.", t.line, t.col, asig.name));
            } else if is_core_proc(&asig.name) {
                errors.push(format!("{}:{} compiler error: Core procedure '{}' cannot be assigned to.", t.line, t.col, asig.name));
            } else if context.funcs.contains_key(&asig.name)  {
                errors.push(format!("{}:{} compiler error: User defined function '{}' cannot be assigned to.", t.line, t.col, asig.name));
            } else if context.procs.contains_key(&asig.name)  {
                errors.push(format!("{}:{} compiler error: User defined procedure '{}' cannot be assigned to.", t.line, t.col, asig.name));
            } else if context.symbols.contains_key(&asig.name)  {
                errors.push(format!("{}:{} compiler error: Cannot assign to constant '{}', declare it as 'mut'.", t.line, t.col, asig.name));
            } else {
                errors.push(format!("{}:{}: compiler error: Suggestion: try changing '{} =' for '{} :='\nExplanation: Cannot assign to undefined symbol '{}'.",
                       t.line, t.col, asig.name, asig.name, asig.name));
            }
            errors.append(&mut check_types(&context, &source, &tokens, &e.params.get(0).unwrap()));
        },
        NodeType::Return => {
            assert!(e.params.len() == 1, "Cil error: return nodes must exactly 1 parameter.");
            errors.append(&mut check_types(&context, &source, &tokens, &e.params.get(0).unwrap()));
        },
        NodeType::LI64(_) | NodeType::LString(_) | NodeType::LBool(_) | NodeType::LList => {},
    }
    errors
}

// ---------- eval repl interpreter stuff

fn eval_to_bool(mut context: &mut CilContext, source: &String, tokens: &Vec<Token>, e: &Expr) -> bool {

    match &e.node_type {
        NodeType::LBool(b_value) => *b_value,
        NodeType::FCall(f_name) => {
            if does_func_return_bool(&context, f_name) {
                lbool_in_string_to_bool(eval_func_proc_call(f_name, &mut context, &source, &tokens, &e).as_str())
            } else {
                panic!("cil error: Function '{}' does not return bool. This should have been caught in the compile phase.\n", f_name);
            }
        },
        NodeType::Identifier(name) => {
            if context.bools.contains_key(name) {
                match context.bools.get(name) {
                    Some(bool_value) => bool_value.clone(),
                    None => {
                        panic!("cil error: Undefined boolean symbol '{}'. This should have been caught in the compile phase.", name)
                    }
                }
            } else {
                panic!("cil error: The only types that can be evaluated to bool are currently 'LBool', 'FCall' and 'Identifier'");
            }
        },
        node_type => panic!("cil error: The only types that can be evaluated to bool are currently 'LBool', 'FCall' and 'Identifier'. Found '{:?}'", node_type),
    }
}

// ---------- core funcs implementations for eval

fn eval_core_func_and(mut context: &mut CilContext, source: &String, tokens: &Vec<Token>, e: &Expr) -> String {
    let mut truthfulness = true;
    for i in &e.params {
        truthfulness = truthfulness && eval_to_bool(&mut context, &source, &tokens, &i);
    }
    truthfulness.to_string()
}

fn eval_core_func_or(mut context: &mut CilContext, source: &String, tokens: &Vec<Token>, e: &Expr) -> String {
    let mut truthfulness = false;
    for i in &e.params {
        truthfulness = truthfulness || eval_to_bool(&mut context, &source, &tokens, &i);
    }
    truthfulness.to_string()
}

fn eval_core_func_not(mut context: &mut CilContext, source: &String, tokens: &Vec<Token>, e: &Expr) -> String {
    assert!(e.params.len() == 1, "Cil Error: Core func 'not' only takes 1 argument. This should never happen.");
    (!eval_to_bool(&mut context, &source, &tokens, &e.params.get(0).unwrap())).to_string()
}

fn eval_core_func_eq(mut context: &mut CilContext, source: &String, tokens: &Vec<Token>, e: &Expr) -> String {
    assert!(e.params.len() == 2, "Cil Error: Core func 'eq' takes exactly 2 arguments. This should never happen.");
    let a = &eval_expr(&mut context, &source, &tokens, e.params.get(0).unwrap()).parse::<i64>().unwrap();
    let b = &eval_expr(&mut context, &source, &tokens, e.params.get(1).unwrap()).parse::<i64>().unwrap();
    (a == b).to_string()
}

fn eval_core_func_lt(mut context: &mut CilContext, source: &String, tokens: &Vec<Token>, e: &Expr) -> String {
    assert!(e.params.len() == 2, "Cil Error: Core func 'eq' takes exactly 2 arguments. This should never happen.");
    let a = &eval_expr(&mut context, &source, &tokens, e.params.get(0).unwrap()).parse::<i64>().unwrap();
    let b = &eval_expr(&mut context, &source, &tokens, e.params.get(1).unwrap()).parse::<i64>().unwrap();
    (a < b).to_string()
}

fn eval_core_func_lteq(mut context: &mut CilContext, source: &String, tokens: &Vec<Token>, e: &Expr) -> String {
    assert!(e.params.len() == 2, "Cil Error: Core func 'eq' takes exactly 2 arguments. This should never happen.");
    let a = &eval_expr(&mut context, &source, &tokens, e.params.get(0).unwrap()).parse::<i64>().unwrap();
    let b = &eval_expr(&mut context, &source, &tokens, e.params.get(1).unwrap()).parse::<i64>().unwrap();
    (a <= b).to_string()
}

fn eval_core_func_gt(mut context: &mut CilContext, source: &String, tokens: &Vec<Token>, e: &Expr) -> String {
    assert!(e.params.len() == 2, "Cil Error: Core func 'eq' takes exactly 2 arguments. This should never happen.");
    let a = &eval_expr(&mut context, &source, &tokens, e.params.get(0).unwrap()).parse::<i64>().unwrap();
    let b = &eval_expr(&mut context, &source, &tokens, e.params.get(1).unwrap()).parse::<i64>().unwrap();
    (a > b).to_string()
}

fn eval_core_func_gteq(mut context: &mut CilContext, source: &String, tokens: &Vec<Token>, e: &Expr) -> String {
    assert!(e.params.len() == 2, "Cil Error: Core func 'eq' takes exactly 2 arguments. This should never happen.");
    let a = &eval_expr(&mut context, &source, &tokens, e.params.get(0).unwrap()).parse::<i64>().unwrap();
    let b = &eval_expr(&mut context, &source, &tokens, e.params.get(1).unwrap()).parse::<i64>().unwrap();
    (a >= b).to_string()
}

fn eval_core_func_add(mut context: &mut CilContext, source: &String, tokens: &Vec<Token>, e: &Expr) -> String {
    assert!(e.params.len() == 2, "Cil Error: Core func 'eq' takes exactly 2 arguments. This should never happen.");
    let a = &eval_expr(&mut context, &source, &tokens, e.params.get(0).unwrap()).parse::<i64>().unwrap();
    let b = &eval_expr(&mut context, &source, &tokens, e.params.get(1).unwrap()).parse::<i64>().unwrap();
    (a + b).to_string()
}

fn eval_core_func_sub(mut context: &mut CilContext, source: &String, tokens: &Vec<Token>, e: &Expr) -> String {
    assert!(e.params.len() == 2, "Cil Error: Core func 'eq' takes exactly 2 arguments. This should never happen.");
    let a = &eval_expr(&mut context, &source, &tokens, e.params.get(0).unwrap()).parse::<i64>().unwrap();
    let b = &eval_expr(&mut context, &source, &tokens, e.params.get(1).unwrap()).parse::<i64>().unwrap();
    (a - b).to_string()
}

fn eval_core_func_mul(mut context: &mut CilContext, source: &String, tokens: &Vec<Token>, e: &Expr) -> String {
    assert!(e.params.len() == 2, "Cil Error: Core func 'eq' takes exactly 2 arguments. This should never happen.");
    let a = &eval_expr(&mut context, &source, &tokens, e.params.get(0).unwrap()).parse::<i64>().unwrap();
    let b = &eval_expr(&mut context, &source, &tokens, e.params.get(1).unwrap()).parse::<i64>().unwrap();
    (a * b).to_string()
}

fn eval_core_func_div(mut context: &mut CilContext, source: &String, tokens: &Vec<Token>, e: &Expr) -> String {
    assert!(e.params.len() == 2, "Cil Error: Core func 'eq' takes exactly 2 arguments. This should never happen.");
    let a = &eval_expr(&mut context, &source, &tokens, e.params.get(0).unwrap()).parse::<i64>().unwrap();
    let b = &eval_expr(&mut context, &source, &tokens, e.params.get(1).unwrap()).parse::<i64>().unwrap();
    (a / b).to_string()
}

fn eval_core_func_btoa(mut context: &mut CilContext, source: &String, tokens: &Vec<Token>, e: &Expr) -> String {
    assert!(e.params.len() == 1, "Cil Error: Core func 'btoa' takes exactly 1 argument. This should never happen.");
    if eval_to_bool(&mut context, &source, &tokens, &e.params.get(0).unwrap()) {
        "true".to_string()
    } else {
        "true".to_string()
    }
}

fn eval_core_func_itoa(mut context: &mut CilContext, source: &String, tokens: &Vec<Token>, e: &Expr) -> String {
    assert!(e.params.len() == 1, "Cil Error: Core func 'btoa' takes exactly 1 argument. This should never happen.");
    eval_expr(&mut context, &source, &tokens, e.params.get(0).unwrap())
}

// ---------- core procs implementations for eval

fn lbool_in_string_to_bool(b: &str) -> bool {
    match b {
        "true" => true,
        "false" => false,
        _ => panic!("Cil Error: expected string 'true' or 'false', this should never happen.")
    }
}

fn eval_core_proc_print(end_line: bool, mut context: &mut CilContext, source: &String, tokens: &Vec<Token>, e: &Expr) -> String {
    for it in &e.params {
        print!("{}", eval_expr(&mut context, &source, &tokens, &it));
    }
    if end_line {
        print!("\n");
    }
    io::stdout().flush().unwrap();
    "".to_string()
}

// ---------- generic eval things

fn eval_user_func_proc_call(func_def: &FuncDef, name: &str, context: &CilContext, source: &String, tokens: &Vec<Token>, e: &Expr) -> String {
    let t = tokens.get(e.token_index).unwrap();

    let mut function_context = context.clone();
    assert!(e.params.len() == func_def.args.len(), "Cil error: func '{}' expected {} args, but {} were provided. This should never happen.",
            name, func_def.args.len(), e.params.len());

    let mut param_index = 0;
    for arg in &func_def.args {
        if arg.value_type == ValueType::TBool {
            let bool_expr_result = lbool_in_string_to_bool(&eval_expr(&mut function_context, &source, &tokens, e.params.get(param_index).unwrap()));
            function_context.symbols.insert(arg.name.clone(), ValueType::TBool);
            function_context.bools.insert(arg.name.clone(), bool_expr_result);
            param_index += 1;
        } else if arg.value_type == ValueType::TI64 {
            let result = &eval_expr(&mut function_context, &source, &tokens, e.params.get(param_index).unwrap());
            function_context.symbols.insert(arg.name.clone(), ValueType::TI64);
            function_context.i64s.insert(arg.name.clone(), result.parse::<i64>().unwrap());
            param_index += 1;
        } else if arg.value_type == ValueType::TString {
            let result = eval_expr(&mut function_context, &source, &tokens, e.params.get(param_index).unwrap());
            function_context.symbols.insert(arg.name.clone(), ValueType::TString);
            function_context.strings.insert(arg.name.clone(), result);
            param_index += 1;
        } else {
            panic!("{}:{} cil error: calling func '{}'. {:?} arguments not supported.", t.line, t.col, name, arg.value_type);
        }

    }

    for se in &func_def.body {
        match se.node_type {
            NodeType::Return => {
                assert!(e.params.len() != 0, "Cil error: return must currently always return exactly one value.");
                return eval_expr(&mut function_context, &source, &tokens, &se.params.get(0).unwrap());
            },
            NodeType::If => {
                assert!(se.params.len() == 2 || se.params.len() == 3, "Cil error: if nodes must have 2 or 3 parameters.");
                if eval_to_bool(&mut function_context, &source, &tokens, &se.params.get(0).unwrap()) {
                    return eval_expr(&mut function_context, &source, &tokens, &se.params.get(1).unwrap())
                } else if se.params.len() == 3 {
                    return eval_expr(&mut function_context, &source, &tokens, &se.params.get(2).unwrap())
                }
            },
            _ => {
                eval_expr(&mut function_context, &source, &tokens, &se);
            }
        }
    }
    "".to_string()
}

fn eval_func_proc_call(name: &str, mut context: &mut CilContext, source: &String, tokens: &Vec<Token>, e: &Expr) -> String {
    let t = tokens.get(e.token_index).unwrap();
    if is_core_func(&name) {
        match name {
            "and" => eval_core_func_and(&mut context, &source, &tokens, &e),
            "or" => eval_core_func_or(&mut context, &source, &tokens, &e),
            "not" => eval_core_func_not(&mut context, &source, &tokens, &e),
            "eq" => eval_core_func_eq(&mut context, &source, &tokens, &e),
            "lt" => eval_core_func_lt(&mut context, &source, &tokens, &e),
            "lteq" => eval_core_func_lteq(&mut context, &source, &tokens, &e),
            "gt" => eval_core_func_gt(&mut context, &source, &tokens, &e),
            "gteq" => eval_core_func_gteq(&mut context, &source, &tokens, &e),
            "add" => eval_core_func_add(&mut context, &source, &tokens, &e),
            "sub" => eval_core_func_sub(&mut context, &source, &tokens, &e),
            "mul" => eval_core_func_mul(&mut context, &source, &tokens, &e),
            "div" => eval_core_func_div(&mut context, &source, &tokens, &e),
            "btoa" => eval_core_func_btoa(&mut context, &source, &tokens, &e),
            "itoa" => eval_core_func_itoa(&mut context, &source, &tokens, &e),
            _ => panic!("{}:{} cil error: Core function '{}' not implemented.", t.line, t.col, name),
        }
    } else if is_core_proc(&name) {
        match name {
            "print" => eval_core_proc_print(false, &mut context, &source, &tokens, &e),
            "println" => eval_core_proc_print(true, &mut context, &source, &tokens, &e),
            _ => panic!("{}:{} cil error: Core procedure '{}' not implemented.", t.line, t.col, name),
        }
    } else if context.funcs.contains_key(name) {
        let func_def = context.funcs.get(name).unwrap();
        eval_user_func_proc_call(func_def, &name, &context, &source, &tokens, &e)
    } else if context.procs.contains_key(name) {
        let func_def = context.procs.get(name).unwrap();
        eval_user_func_proc_call(func_def, &name, &context, &source, &tokens, &e)
    } else {
        panic!("{}:{} cil error: Cannot call '{}'. Undefined function. This should never happen.", t.line, t.col, name);
    }
}

fn eval_declaration(declaration: &Declaration, mut context: &mut CilContext, source: &String, tokens: &Vec<Token>, e: &Expr) -> String {
    let t = tokens.get(e.token_index).unwrap();
    match declaration.value_type {
        ValueType::TBool => {
            assert!(e.params.len() == 1, "Declarations can have only one child expression. This should never happen.");
            let bool_expr_result : bool = lbool_in_string_to_bool(&eval_expr(&mut context, &source, &tokens, e.params.get(0).unwrap()));
            context.bools.insert(declaration.name.clone(), bool_expr_result);
            bool_expr_result.to_string()
        },
        ValueType::TI64 => {
            assert!(e.params.len() == 1, "Declarations can have only one child expression. This should never happen.");
            let i64_expr_result_str = &eval_expr(&mut context, &source, &tokens, e.params.get(0).unwrap());
            context.i64s.insert(declaration.name.clone(), i64_expr_result_str.parse::<i64>().unwrap());
            i64_expr_result_str.to_string()
        },
        ValueType::TString => {
            assert!(e.params.len() == 1, "Declarations can have only one child expression. This should never happen.");
            let string_expr_result = &eval_expr(&mut context, &source, &tokens, e.params.get(0).unwrap());
            context.strings.insert(declaration.name.clone(), string_expr_result.to_string());
            string_expr_result.to_string()
        },
        ValueType::TStruct => {
            panic!("{}:{} cil error: Cannot declare {} of type {:?}. Not implemented yet.",
                   t.line, t.col, &declaration.name, &declaration.value_type);
        },
        ValueType::TFunc => {
            assert!(e.params.len() == 1, "Declarations can have only one child expression. This should never happen.");
            match &e.params.get(0).unwrap().node_type {
                NodeType::FuncDef(func_def) => {
                    context.funcs.insert(declaration.name.clone(), func_def.clone());
                    "func declared".to_string()
                },
                _ => panic!("{}:{} cil error: Cannot declare {} of type {:?}. This should never happen",
                            t.line, t.col, &declaration.name, &declaration.value_type)
            }
        },
        ValueType::TProc => {
            assert!(e.params.len() == 1, "Declarations can have only one child expression. This should never happen.");
            match &e.params.get(0).unwrap().node_type {
                NodeType::ProcDef(func_def) => {
                    context.procs.insert(declaration.name.clone(), func_def.clone());
                    "proc declared".to_string()
                },
                _ => panic!("{}:{} cil error: Cannot declare {} of type {:?}. This should never happen",
                            t.line, t.col, &declaration.name, &declaration.value_type)
            }
        },
        _ => panic!("{}:{} cil error: Cannot declare {} of type {:?}.", t.line, t.col, &declaration.name, &declaration.value_type)
    }
}

fn eval_expr(mut context: &mut CilContext, source: &String, tokens: &Vec<Token>, e: &Expr) -> String {
    match &e.node_type {
        NodeType::Body => {
            for se in e.params.iter() {
                match &se.node_type {
                    NodeType::Return => {
                        return eval_expr(&mut context, &source, &tokens, &se);
                    }
                    _ => {
                        eval_expr(&mut context, &source, &tokens, &se);
                    }
                }
            }
            "".to_string()
        },
        NodeType::LBool(bool_value) => bool_value.to_string(),
        NodeType::LI64(li64) => li64.to_string(),
        NodeType::LString(lstring) => lstring.to_string(),
        NodeType::LList => {
            let t = tokens.get(e.token_index).unwrap();
            let token_str = get_token_str(source, t);
            token_str.to_string()
        },
        NodeType::FCall(name) => {
            eval_func_proc_call(&name, &mut context, &source, &tokens, &e)
        },
        NodeType::Declaration(declaration) => {
            eval_declaration(&declaration, &mut context, &source, &tokens, &e)
        },
        NodeType::Identifier(name) => {

            match context.symbols.get(name) {
                Some(value_type) => match value_type {
                    ValueType::TBool => {
                        context.bools.get(name).unwrap().to_string()
                    },
                    ValueType::TI64 => {
                        context.i64s.get(name).unwrap().to_string()
                    },
                    ValueType::TString => {
                        context.strings.get(name).unwrap().to_string()
                    },
                    _ => {
                        panic!("cil error: Can't use identifier '{}'. Type {:?} not supported yet.", name, value_type)
                    },
                }
                None => {
                    panic!("cil error: Undefined symbol '{}'. This should have been caught in the compile phase.", name)
                },
            }
        },
        NodeType::If => {
            assert!(e.params.len() == 2 || e.params.len() == 3, "Cil error: if nodes must have 2 or 3 parameters.");
            if eval_to_bool(&mut context, &source, &tokens, &e.params.get(0).unwrap()) {
                eval_expr(&mut context, &source, &tokens, &e.params.get(1).unwrap())
            } else if e.params.len() == 3 {
                eval_expr(&mut context, &source, &tokens, &e.params.get(2).unwrap())
            } else {
                "".to_string()
            }
        },
        NodeType::Return => {
            assert!(e.params.len() == 1, "Cil error: return nodes must have exactly 1 parameter.");
            eval_expr(&mut context, &source, &tokens, &e.params.get(0).unwrap())
        }
        _ => {
            let t = tokens.get(e.token_index).unwrap();
            panic!("{}:{} cil error: Not implemented, found {}.", t.line, t.col, get_token_str(source, t))
        },
    }
}

fn parse_tokens(mut context: &mut CilContext, source: &String, tokens: &Vec<Token>) -> Expr {
    let mut current: usize = 0;

    let e: Expr = body(TokenType::Eof, &mut context, &source, tokens, &mut current);
    current = current + 1; // Add one for the EOF

    println!("Total tokens parsed: {}/{}", current, tokens.len());
    let mut i = current;
    if i < tokens.len() {
        println!("Unparsed tokens ({}):", tokens.len() - i);
    }
    while i < tokens.len() {
        let t = tokens.get(i).unwrap();
        println!("Token: {:?}", t);
        i = i + 1;
    }
    e
}

fn run(path: &String, source: &String) -> String {
    let tokens: Vec<Token> = scan_tokens(&source);
    if tokens.len() < 1 {
        panic!("{}:{}:{} compiler error: End of file not found.", path, 1, 0);
    } else if is_eof(&tokens, 0) {
        panic!("{}:{}:{} compiler error: Nothing to be done", path, tokens.get(0).unwrap().line, 0);
    }

    let mut errors_found : usize = 0;
    for t in &tokens {
        match t.token_type {
            TokenType::Invalid => {
                print_lex_error(&path, &source, &t, errors_found, "Invalid character");
                errors_found = errors_found + 1;
            },
            TokenType::UnterminatedString => {
                print_lex_error(&path, &source, &t, errors_found, "Unterminated String");
                errors_found = errors_found + 1;
            },
            _ => {},
        }
    }
    if errors_found > 0 {
        panic!("Compiler errors: {} lexical errors found", errors_found);
    }

    let mut context = start_context();
    let e: Expr = parse_tokens(&mut context, &source, &tokens);
    println!("AST:\n{}", to_ast_str(&e));

    let errors = check_types(&context, &source, &tokens, &e);
    if errors.len() > 0 {
        for err in &errors {
            println!("{}:{}", path, err);
        }
        panic!("Compiler errors: {} type errors found", errors.len());
    }

    eval_expr(&mut context, &source, &tokens, &e)
}

// ---------- main stuff, usage, args, etc

fn run_file(path: &String) {
    let source: String = match fs::read_to_string(path) {
        Ok(file) => file,
        Err(error) => match error.kind() {
            ErrorKind::NotFound => {
                panic!("File {} not found.", path);
            },
            other_error => {
                panic!("Problem opening the file: {other_error:?}");
            },
        },
    };
    println!("eval: {}", run(&path, &source));
}

fn run_prompt() {
    loop {
        print!("cil> ");
        io::stdout().flush().unwrap();

        let mut line = String::new();
        io::stdin()
            .read_line(&mut line)
            .expect("repl error: Failed to read line");

        if line.len() == 1 { break; }

        let path = "repl".to_string();
        println!("{}", run(&path, &line));
    }
}

fn usage() {
    // TODO document this properly
    println!("Usage: Zero arguments for the repl mode:");
    println!("example> cil");
    println!("Usage: for the interpreted mode. running scripts: a single arg that's a path:");
    println!("example> cil src/demo.cil");
    println!("Usage: for the nasm mode. This is compiled:");
    println!("example> cil build src/demo.cil");
    println!("Usage: if you want to run what you just compiled:");
    println!("example> cil run src/demo.cil");
}

fn main() {
    let args: Vec<String> = env::args().collect();

    if args.len() > 3 {
        usage();
    } else if args.len() > 2 {
        println!("subcommand {} not implemented yet.", &args[1]);
    } else if args.len() > 1 {
        run_file(&args[1]);
    } else {
        run_prompt();
    }
}
