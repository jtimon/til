use std::env;
use std::io;
use std::io::Write; // <--- bring flush() into scope
use std::fs;
use std::io::ErrorKind;
use std::collections::HashMap;

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

    // Reserved words.
    True, False,
    Var,
    Struct, Enum,
    Func, Proc,
    Match, If, Else, While, For, In,
    Return, Returns, Throw, Rethrow, Throws, Catch,
    Debug,

    // Errors
    Invalid,
    UnterminatedString,
}

#[derive(Debug, Clone)]
struct Token {
    token_type: TokenType,
    start: usize,
    end: usize,
    line: usize,
}

fn get_token_str<'a>(source: &'a String, t: &'a Token) -> &'a str {
    &source[t.start..t.end]
}

fn print_lex_error(source: &String, t: &Token, num_error: usize, msg: &str) {
    let max_symbol_len = 20;
    let mut end_symbol = t.end;
    if end_symbol - t.start > max_symbol_len {
        end_symbol = max_symbol_len;
    }
    println!("Lexical error {} line {}: {}. Offending symbol: {}", num_error, t.line, msg, &source[t.start..end_symbol]);
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
    // TI64,
    TList,
    TFunc,
    TProc,
    TCustom(String),
}

fn str_to_value_type(arg_type: &str) -> ValueType {
    match arg_type {
        "bool" => ValueType::TBool,
        "String" => ValueType::TString,
        "list" => ValueType::TList,
        "func" => ValueType::TFunc,
        "proc" => ValueType::TProc,
        type_name => ValueType::TCustom(type_name.to_string()),
    }
}


#[derive(Debug, Clone, PartialEq)]
struct Declaration {
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
    Body,
    LList,
    LString,
    LNumber,
    LBool(bool),
    // LDecimal(String),
    FCall(String),
    Identifier(String),
    Declaration(Declaration),
    FuncDef(FuncDef),
    Return,
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
    bools: HashMap<String, bool>,
    funcs: HashMap<String, FuncDef>,
    procs: HashMap<String, FuncDef>,
}

fn start_context() -> CilContext {
    let mut context: CilContext = CilContext { symbols: HashMap::new(), funcs: HashMap::new(), procs: HashMap::new(), bools: HashMap::new() };

    let args : Vec<Arg> = Vec::new();
    let mut return_types : Vec<ValueType> = Vec::new();
    let body : Vec<Expr> = Vec::new();
    let func_def_print = FuncDef{args: args.clone(), returns: return_types.clone(), body: body.clone()};
    context.procs.insert("print".to_string(), func_def_print);
    return_types.push(ValueType::TBool);
    let func_def_and_or = FuncDef{args: args, returns: return_types, body: body};
    context.funcs.insert("and".to_string(), func_def_and_or.clone());
    context.funcs.insert("or" .to_string(), func_def_and_or);
    context
}

fn value_type(context: &CilContext, e: &Expr) -> ValueType {
    match &e.node_type {
        NodeType::LBool(_) => ValueType::TBool,
        NodeType::LString => ValueType::TString,
        NodeType::LList => ValueType::TList,
        NodeType::FuncDef(_) => ValueType::TFunc,
        NodeType::FCall(name) => {
            match context.funcs.get(name) {
                Some(func_def) => {

                    match func_def.returns.len() {
                        0 => {
                            panic!("cil error: func '{}' does not return anything" , name)
                        },
                        1 => {
                            match func_def.returns.get(0).unwrap() {
                                ValueType::TBool => ValueType::TBool,
                                _ => panic!("cil error: func '{}' does not return bool" , name),
                            }
                        },
                        _ => {
                            panic!("cil error: func '{}' returns multiple values, but that's not implemented yet." , name)
                        },
                    }
                },
                None => panic!("compile error: value_type: Undefined function/procedure '{}'" , name),
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
        _ => panic!("cil error: value_type() not implement for this ValueType yet."),
    }
}

// fn is_literal_node(node_type: &NodeType) -> bool {
//     match node_type {
//         NodeType::LString => true,
//         NodeType::LNumber => true,
//         NodeType::LBool(_) => true,
//         NodeType::LList => true,
//         _ => false,
//     }
// }

// fn get_token_type<'a>(tokens: &'a Vec<Token>, e: &'a Expr) -> &'a TokenType {
//     let t = tokens.get(e.token_index).unwrap();
//     &t.token_type
// }

// enum Value {
//     b: u8,
//     l: Vec<Value>,
//     n: i64,
//     s: String,
// }

// struct Constant {
//     str_id: String,
//     value: Value,
// }

// struct Mutable {
//     str_id: String,
//     value: Value,
// }

// #[derive(Debug)]
// struct Interpreter {
//     declared_values: Vec<Constant>.
// }

// fn declare_constant(i: & mut Interpreter, str_id: String, value: Value,) {
//     i.declared_values.push();
// }

fn to_ast_str(tokens: &Vec<Token>, e: &Expr) -> String {
    let mut ast_str = "".to_string();
    if e.node_type == NodeType::Body {
        for se in e.params.iter() {
            ast_str.push_str(&format!("{}\n", to_ast_str(&tokens, &se)));
        }
        return ast_str
    }
    let t = tokens.get(e.token_index).unwrap();

    if e.params.len() > 0 {
        ast_str.push_str("(");
    }

    ast_str.push_str(&format!("{}", token_type_to_string(&t.token_type)));

    if e.params.len() > 0 {
        for se in e.params.iter() {
            ast_str.push_str(&format!(" {}", to_ast_str(&tokens, &se)));
        }

        ast_str.push_str(")");
    }
    ast_str
}

fn token_type_to_string(token_type: &TokenType) -> String {
    match token_type {
        TokenType::Eof => "Eof".to_string(),
        TokenType::Minus => "Minus".to_string(),
        TokenType::Plus => "Plus".to_string(),
        TokenType::Slash => "Slash".to_string(),
        TokenType::Star => "Star".to_string(),
        TokenType::LeftParen => "LeftParen".to_string(),
        TokenType::RightParen => "RightParen".to_string(),
        TokenType::LeftBrace => "LeftBrace".to_string(),
        TokenType::RightBrace => "RightBrace".to_string(),
        TokenType::Comma => "Comma".to_string(),
        TokenType::Dot => "Dot".to_string(),
        TokenType::Colon => "Colon".to_string(),
        TokenType::Semicolon => "Semicolon".to_string(),
        TokenType::Not => "Not".to_string(),
        TokenType::NotEqual => "NotEqual".to_string(),
        TokenType::Equal => "Equal".to_string(),
        TokenType::EqualEqual => "EqualEqual".to_string(),
        TokenType::Greater => "Greater".to_string(),
        TokenType::GreaterEqual => "GreaterEqual".to_string(),
        TokenType::Lesser => "Lesser".to_string(),
        TokenType::LesserEqual => "LesserEqual".to_string(),
        TokenType::Identifier => "Identifier".to_string(),
        TokenType::String => "String".to_string(),
        TokenType::Number => "Number".to_string(),
        TokenType::True => "True".to_string(),
        TokenType::False => "False".to_string(),
        TokenType::Var => "Var".to_string(),
        TokenType::Func => "Func".to_string(),
        TokenType::Proc => "Proc".to_string(),
        TokenType::Struct => "Struct".to_string(),
        TokenType::Enum => "Enum".to_string(),
        TokenType::Match => "Match".to_string(),
        TokenType::If => "If".to_string(),
        TokenType::Else => "Else".to_string(),
        TokenType::While => "While".to_string(),
        TokenType::For => "For".to_string(),
        TokenType::In => "In".to_string(),
        TokenType::Return => "Return".to_string(),
        TokenType::Returns => "Returns".to_string(),
        TokenType::Throw => "Throw".to_string(),
        TokenType::Rethrow => "Rethrow".to_string(),
        TokenType::Throws => "Throws".to_string(),
        TokenType::Catch => "Catch".to_string(),
        TokenType::Debug => "Debug".to_string(),
        TokenType::Invalid => "Invalid".to_string(),
        TokenType::UnterminatedString => "UnterminatedString".to_string(),
        // TokenType:: => "".to_string(),
        // _ => "Unknown".to_string(),
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
        "var" => TokenType::Var,
        "struct" => TokenType::Struct,
        "enum" => TokenType::Enum,
        "func" => TokenType::Func,
        "proc" => TokenType::Proc,
        "match" => TokenType::Match,
        "if" => TokenType::If,
        "else" => TokenType::Else,
        "while" => TokenType::While,
        "for" => TokenType::For,
        "in" => TokenType::In,
        "return" => TokenType::Return,
        "returns" => TokenType::Returns,
        "throw" => TokenType::Throw,
        "rethrow" => TokenType::Rethrow,
        "throws" => TokenType::Throws,
        "catch" => TokenType::Catch,
        "debug" => TokenType::Debug,
        _ => TokenType::Identifier,
    }
}

fn scan_tokens(source: &String) -> Vec<Token> {
    let mut tokens : Vec<Token> = Vec::new();

    let eof_pos : usize = source.len();
    let mut pos = 0;
    let mut line = 0;

    while pos < eof_pos {
        let start = pos;

        if is_digit(source, pos) {
            while pos < eof_pos && is_digit(source, pos) {
                pos = pos + 1;
            }
            // Look for a fractional part.
            if &source[pos..pos+1] == "." && is_digit(source, pos+1) {
                pos = pos + 1;
                while pos < eof_pos && is_digit(source, pos) {
                    pos = pos + 1;
                }
            }
            tokens.push(Token { token_type: TokenType::Number, start: start, end: pos + 1, line: line });
        } else {

            let token_type = match &source[pos..pos+1] {
                " " => { pos = pos + 1; continue; },
                "\r" => { pos = pos + 1; continue; },
                "\t" => { pos = pos + 1; continue; },
                "\n" => { pos = pos + 1; line = line + 1; continue; },
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
                "=" => if &source[pos+1..pos+2] == "=" { pos = pos + 1; TokenType::EqualEqual } else { TokenType::Equal },
                "<" => if &source[pos+1..pos+2] == "=" { pos = pos + 1; TokenType::LesserEqual } else { TokenType::Lesser },
                ">" => if &source[pos+1..pos+2] == "=" { pos = pos + 1; TokenType::GreaterEqual } else { TokenType::Greater },
                "!" => if &source[pos+1..pos+2] == "=" { pos = pos + 1; TokenType::NotEqual } else { TokenType::Not },

                "/" => match &source[pos+1..pos+2] {
                    "/" => {
                        pos = pos + 1;
                        while pos + 1 < eof_pos && &source[pos..pos+1] != "\n" {
                            pos = pos + 1;
                        }
                        continue;
                        // TODO allow the other type of commments, allowing nesting
                    },
                    _ => TokenType::Slash,
                },

                "\"" => {
                    pos = pos + 1;
                    while pos + 1 < eof_pos && &source[pos..pos+1] != "\"" {
                        pos = pos + 1;
                    }
                    // pos = pos - 1;
                    match &source[pos..pos+1] {
                        "\"" => TokenType::String,
                        _ => TokenType::UnterminatedString,
                    }
                },

                _ => {
                    if is_alphanumeric(source, pos){
                        pos = pos + 1;
                        // FIX invalid characters
                        while pos < eof_pos && (is_alphanumeric(source, pos) || is_digit(source, pos)) {
                            pos = pos + 1;
                        }
                        pos = pos - 1;
                        get_identifier_type(&source[start..pos+1])

                    } else {
                        TokenType::Invalid
                    }
                },
            }; // let match
            // println!("Current token line {}, start: {}, end {}, identifier type: {} identifier string: __{}__",
                     // line, start, pos+1, token_type_to_string(&token_type), &source[start..pos+1]);
            tokens.push(Token { token_type: token_type, start: start, end: pos + 1, line: line });
            pos = pos + 1;
        } // else
    } // while
    tokens.push(Token { token_type: TokenType::Eof, start: pos, end: pos + 1, line: line });
    tokens
}

// fn unary(tokens: &Vec<Token>, current: usize) -> Expr {

//     let t: Token = tokens.get(current).unwrap().clone();
//     let is_unary = match &t.token_type {
//         TokenType::Minus => true,
//         TokenType::Not => true,
//         _ => false,
//     };

//     if is_unary {
//         let mut params : Vec<Expr> = Vec::new();
//         params.push(unary(&tokens, current + 1));
//         Expr { operator: t, params: params}
//     } else {
//         primary(&tokens, current)
//     }
// }

// fn factor(tokens: &Vec<Token>, current: usize) -> Expr {
//     let expr: Expr = unary(&tokens, current);

//     let t: Token = tokens.get(current).unwrap().clone();
//     if match &t.token_type {
//         TokenType::Slash => true,
//         TokenType::Star => true,
//         _ => false,
//     } {
//         let t: Token = tokens.get(current).unwrap().clone();
//         let mut params : Vec<Expr> = Vec::new();
//         params.push(expr);
//         params.push(unary(&tokens, current + 1));
//         Expr { operator: t, params: params}
//     } else {
//         expr
//     }
// }

// fn term(tokens: &Vec<Token>, current: usize) -> Expr {
//     let expr: Expr = factor(&tokens, current);

//     let t: Token = tokens.get(current).unwrap().clone();
//     if match &t.token_type {
//         TokenType::Minus => true,
//         TokenType::Plus => true,
//         _ => false,
//     } {
//         let t: Token = tokens.get(current).unwrap().clone();
//         let mut params : Vec<Expr> = Vec::new();
//         params.push(expr);
//         params.push(factor(&tokens, current + 1));
//         Expr { operator: t, params: params}
//     } else {
//         expr
//     }
// }

// fn is_comparison(t: &Token) -> bool {
//     match &t.token_type {
//         TokenType::Greater => true,
//         TokenType::GreaterEqual => true,
//         TokenType::Lesser => true,
//         TokenType::LesserEqual => true,
//         _ => false,
//     }
// }

// fn comparison(tokens: &Vec<Token>, current: usize) -> Expr {
//     let expr: Expr = term(&tokens, current);

//     let t: Token = tokens.get(current).unwrap().clone();
//     if is_comparison(&t) {
//         let t: Token = tokens.get(current).unwrap().clone();
//         let mut params : Vec<Expr> = Vec::new();
//         params.push(expr);
//         params.push(term(&tokens, current + 1));
//         Expr { operator: t, params: params}
//     } else {
//         expr
//     }
// }

// fn equality(tokens: &Vec<Token>, current: usize) -> Expr {
//     let expr: Expr = comparison(&tokens, current);

//     let t: Token = tokens.get(current).unwrap().clone();
//     let is_equality = match &t.token_type {
//         TokenType::NotEqual => true,
//         TokenType::EqualEqual => true,
//         _ => false,
//    };
//    if is_equality {
//         let t: Token = tokens.get(current).unwrap().clone();
//         let mut params : Vec<Expr> = Vec::new();
//         params.push(expr);
//         params.push(comparison(&tokens, current + 1));
//         Expr { operator: t, params: params}
//    } else {
//        expr
//    }
// }

// fn expression(tokens: &Vec<Token>, current: usize) -> Expr {
//     let expr: Expr = equality(&tokens, current);
//     expr
// }

// enum CompilerError {
//     line: usize,
//     pos: usize,
//     col: usize,
//     msg: str,
// }

fn is_eof(tokens: &Vec<Token>, current: usize) -> bool {
    current > tokens.len() || match tokens.get(current).unwrap().token_type {
        TokenType::Eof => true,
        _ => false,
    }
}

fn literal(t: &Token, current: &mut usize) -> Expr {
    let params : Vec<Expr> = Vec::new();
    let node_type = match t.token_type {
        TokenType::String => NodeType::LString,
        TokenType::Number => NodeType::LNumber,
        TokenType::True => NodeType::LBool(true),
        TokenType::False => NodeType::LBool(false),
        _ => panic!("cil error (line {}): Trying to parse a token that's not a literal as a literal.", t.line),
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
                    panic!("compile error (line {}): Unexpected ','.", list_t.line);
                }
            },
            _ => {
                if expect_comma {
                    panic!("compile error (line {}): Expected ',', found {:?}.", list_t.line, list_t.token_type);
                }
                expect_comma = true;
                params.push(primary(&mut context, &source, &tokens, current));
                list_t = tokens.get(*current).unwrap();
            },
        }
    }
    match list_t.token_type {
        TokenType::RightParen => Expr { node_type: NodeType::LList, token_index: initial_current, params: params},
        _ => panic!("compiler error (line {}): Expected closing parentheses.", list_t.line),
    }
}

fn is_core_func(proc_name: &str) -> bool {
    match proc_name {
        "and" => true,
        "or" => true,
        "add" => true,
        "eq" => true,
        "lt" => true,
        "lteq" => true,
        "gt" => true,
        "gteq" => true,
        _ => false,
    }
}

fn is_core_proc(proc_name: &str) -> bool {
    match proc_name {
        "test" => true,
        "print" => true,
        "println" => true,
        "assert" => true,
        _ => false,
    }
}

fn is_core_func_proc(proc_name: &str) -> bool {
    is_core_func(proc_name) || is_core_proc(proc_name)
}

fn func_call(mut context: &mut CilContext, source: &String, tokens: &Vec<Token>, current: &mut usize) -> Expr {
    let t = tokens.get(*current).unwrap();
    let token_str = get_token_str(source, t);

    if is_defined_func_proc(&context, token_str) {
        let initial_current = *current;
        *current = *current + 1;
        let params : Vec<Expr> = list(&mut context, &source, &tokens, current).params;
        Expr { node_type: NodeType::FCall(token_str.to_string()), token_index: initial_current, params: params}
    } else {
        panic!("compiler error (line {}): Undefined function/procedure '{}'.", t.line, get_token_str(source, t));
    }
}

// fn declaration(source: &String, tokens: &Vec<Token>, current: &mut usize) -> Result<Expr, CompilerError> {
//     let t = tokens.get(*current).unwrap();
//     let token_str = get_token_str(source, t);
//     Err(CompilerError::CompUndefFuncProc(token_str.to_string()))
// }

// fn compiler_error_to_string()(ce: CompilerError) -> String {
//     let mut e_str = "".to_string();
//     match ce {

//     }

// }

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
                    panic!("compile error (line {}): Unexpected ','.", t.line);
                }
            },
            TokenType::Colon => {
                if expect_colon {
                    expect_colon = false;
                    *current = *current + 1;
                    t = tokens.get(*current).unwrap();
                } else {
                    panic!("compile error (line {}): Unexpected ':'.", t.line);
                }
            },
            TokenType::Identifier => {
                if expect_comma {
                    panic!("compile error (line {}): Expected ',', found {:?}.", t.line, t.token_type);
                }
                if expect_colon {
                    panic!("compile error (line {}): Expected ':', found {:?}.", t.line, t.token_type);
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
                panic!("compile error (line {}): Unexpected {:?} in func/proc args.", t.line, t.token_type);
            },
        }
    }
    match t.token_type {
        TokenType::RightParen => args,
        _ => panic!("compiler error (line {}): Expected closing parentheses.", t.line),
    }
}

fn func_proc_returns(_context: &CilContext, source: &String, tokens: &Vec<Token>, current: &mut usize) -> Vec<ValueType> {
    let mut end_found = false;
    let mut return_types : Vec<ValueType> = Vec::new();
    *current = *current + 1;
    let mut t = tokens.get(*current).unwrap();
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
                    panic!("compile error (line {}): Unexpected ','.", t.line);
                }
            },
            TokenType::Identifier => {
                if expect_comma {
                    panic!("compile error (line {}): Expected ',', found {:?}.", t.line, t.token_type);
                }
                return_types.push(str_to_value_type(get_token_str(source, t)));
                expect_comma = true;
                *current = *current + 1;
                t = tokens.get(*current).unwrap();
            },
            _ => {
                panic!("compile error (line {}): Unexpected {:?} in func/proc args.", t.line, t.token_type);
            },
        }
    }
    if end_found {
        return_types
    } else {
        panic!("compiler error (line {}): Expected '{{' or 'throws' after return values.", t.line);
    }
}

fn func_proc_definition(is_func: bool, mut context: &mut CilContext, source: &String, tokens: &Vec<Token>, current: &mut usize) -> Expr {
    if !is_func {
        let t = tokens.get(*current).unwrap();
        panic!("cil error (line {}): proc definition not implemented yet.", t.line);
    }
    if is_eof(&tokens, *current + 1) {
        let t = tokens.get(*current).unwrap();
        panic!("compiler error (line {}): expected '(' after 'func', found EOF.", t.line);
    } else {
        let t = tokens.get(*current).unwrap();
        if t.token_type == TokenType::LeftParen {
            let args = func_proc_args(&context, &source, &tokens, current);
            let returns = func_proc_returns(&context, &source, &tokens, current);
            let body = body(TokenType::RightBrace, &mut context, &source, tokens, current).params;
            let func_def = FuncDef{args: args, returns: returns, body: body};
            let params : Vec<Expr> = Vec::new();
            let e = Expr { node_type: NodeType::FuncDef(func_def), token_index: *current, params: params};
            *current = *current + 1;
            e
        } else {
            panic!("compiler error (line {}): expected '(' after 'func', found {:?}.", t.line, t.token_type);
        }
    }
}

fn primary(mut context: &mut CilContext, source: &String, tokens: &Vec<Token>, current: &mut usize) -> Expr {

    let t = tokens.get(*current).unwrap();
    if is_literal(t) {
        literal(t, current)
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
            _ => panic!("compiler error (line {}): Expected primary expression, found {:?}.", t.line, t.token_type),
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

fn statement(mut context: &mut CilContext, source: &String, tokens: &Vec<Token>, current: &mut usize) -> Expr {
    let t = tokens.get(*current).unwrap();
    match &t.token_type {
        TokenType::Return => {
            return_statement(&mut context, &source, &tokens, current)
        },
        TokenType::Identifier => {
            if is_eof(&tokens, *current) {
                panic!("compiler error (line {}): Expected '(' or ':' after identifier in statement, found 'EOF'.", t.line);
            } else {
                let next_token_type = &tokens.get(*current + 1).unwrap().token_type;
                match next_token_type {
                    TokenType::LeftParen => {
                        func_call(&mut context, &source, &tokens, current)
                    },
                    TokenType::Colon => {
                        if is_eof(&tokens, *current + 1) {
                            panic!("compiler error (line {}): Expected Type or '=' after 'identifier :' in statement, found 'EOF'.", t.line);
                        } else {
                            let next_next_token_type = &tokens.get(*current + 2).unwrap().token_type;
                            match next_next_token_type {
                                TokenType::Equal => {
                                    let initial_current = *current;
                                    *current = *current + 3;
                                    let mut params : Vec<Expr> = Vec::new();
                                    params.push(primary(&mut context, &source, &tokens, current));
                                    let decl_name = get_token_str(source, t);
                                    let e = params.get(0).unwrap();
                                    let value_type = value_type(&context, &e);
                                    if is_defined_symbol(&context, decl_name) {
                                        panic!("compiler error (line {}): '{}' already declared.", t.line, decl_name);
                                    } else {
                                        match value_type {
                                            ValueType::TFunc => {
                                                match &e.node_type {
                                                    NodeType::FuncDef(func_def) => {
                                                        context.funcs.insert(decl_name.to_string(), func_def.clone());
                                                    },
                                                    _ => {
                                                        panic!("cil error (line {}): funcs should have definitions. This should never happen", t.line);
                                                    }

                                                }
                                            },
                                            ValueType::TProc => {
                                                panic!("cil error (line {}): proc declarations not implemented yet.", t.line);
                                            },
                                            _ => {
                                                context.symbols.insert(decl_name.to_string(), value_type.clone());
                                            },
                                        }
                                    }
                                    let decl = Declaration{name: decl_name.to_string(), value_type: value_type};
                                    Expr { node_type: NodeType::Declaration(decl), token_index: initial_current, params: params}
                                },
                                TokenType::Identifier => {
                                    panic!("cil error (line {}): Explicit types in declarations not implemented yet.", t.line);
                                }
                                _ => panic!("compiler error (line {}): Expected Type or '=' after 'identifier :' in statement, found {:?}.", t.line, t.token_type),
                            }
                            // match declaration(&source, &tokens, current) {
                            //     Ok(e) => e,
                            //     Err(_e) => {panic!("compiler error (line {}): error in declaration '{}'.", t.line, get_token_str(source, t));}
                            // }
                        }
                    },
                    _ => panic!("compiler error (line {}): Expected '(' or ':' after identifier in statement, found {:?}.", t.line, t.token_type),
                }
            }
        },
        _ => panic!("compiler error (line {}): Expected statement, found {:?}.", t.line, t.token_type),
    }
}

fn body(end_token : TokenType, mut context: &mut CilContext, source: &String, tokens: &Vec<Token>, current: &mut usize) -> Expr {
    let initial_current: usize = *current;
    let mut params : Vec<Expr> = Vec::new();
    let mut end_found = false;
    while *current < tokens.len() && !end_found {
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
    is_core_func_proc(name) || context.funcs.contains_key(name) || context.procs.contains_key(name)
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

// fn check_call(source: &String, tokens: &Vec<Token>, e: &Expr) -> Vec<String> {
// }

fn check_all_params_bool(context: &CilContext, name: &str, source: &String, tokens: &Vec<Token>, e: &Expr) -> Vec<String> {
    let mut errors : Vec<String> = Vec::new();

    for p in e.params.iter() {
        match &p.node_type {
            NodeType::LBool(_) => {
                continue;
            },
            NodeType::LList => {
                errors.push(format!("Function '{}' expects only bool arguments, found 'list'", name));
            },
            NodeType::LString => {
                errors.push(format!("Function '{}' expects only bool arguments, found 'string'", name));
            },
            NodeType::LNumber => {
                errors.push(format!("Function '{}' expects only bool arguments, found 'number'", name));
            },
            NodeType::FuncDef(_) => {
                errors.push(format!("Function '{}' expects only bool arguments, found 'func'", name));
            }
            NodeType::Identifier(id_name) => {
                if context.symbols.contains_key(id_name) {
                    let value_type = context.symbols.get(id_name).unwrap();
                    match value_type {
                        ValueType::TBool => { continue; }
                        _ => { errors.push(format!("In call to '{}', expected bool, but '{}' is {:?}", name, id_name, value_type)); }
                    }
                } else {
                    errors.push(format!("In call to '{}', undefined symbol {}", name, id_name));
                }
            }
            NodeType::FCall(func_name) => {
                if !does_func_return_bool(&context, func_name) {
                    errors.push(format!("Function '{}' expects only bool arguments, '{}' does not return bool\n", name, func_name));
                }
                errors.append(&mut check_types(&context, &source, &tokens, &p));
            }
            NodeType::Declaration(_) => {
                errors.push(format!("Cil error: Function '{}' cannot take a Declaration as an arg. This should never happen", name));
            }
            NodeType::Body => {
                errors.push(format!("Cil error: Function '{}' cannot take a Body as an arg. This should never happen", name));
            }
            NodeType::Return => {
                errors.push(format!("Cil error: Function '{}' cannot take a return statement as an arg. This should never happen", name));
            }
        }
    }

    errors
}

fn check_types(context: &CilContext, source: &String, tokens: &Vec<Token>, e: &Expr) -> Vec<String> {
    let mut errors : Vec<String> = Vec::new();

    match &e.node_type {
        NodeType::Body => {
            for p in e.params.iter() {
                errors.append(&mut check_types(&context, &source, &tokens, &p));
            }
        },
        NodeType::FCall(name) => {
            if !is_defined_func_proc(&context, &name) {
                errors.push(format!("Undefined function {}", name));
            }
            match name.as_str() {
                "and" | "or" => { errors.append(&mut check_all_params_bool(&context, &name, &source, &tokens, &e)); },
                "print" => {
                    // TODO check print args are printable
                },
                _ => {
                    let func_def = context.funcs.get(name).unwrap();
                    if func_def.args.len() != e.params.len() {
                        errors.push(format!("Function/procedure '{}' expects {} args, but {} were provided.", name, func_def.args.len(), e.params.len()));
                    }
                    for i in 0..func_def.args.len() {
                        let arg = func_def.args.get(i).unwrap();
                        let expected_type = &arg.value_type;
                        let found_type = value_type(&context, e.params.get(i).unwrap());
                        if expected_type != &found_type {
                            errors.push(format!("calling func/proc '{}' expects {:?} for arg {}, but {:?} was provided.",
                                                name, expected_type, arg.name, found_type));
                        }
                    }
                },
            }
        },
        NodeType::Identifier(name) => {
            if !is_defined_symbol(&context, &name) {
                errors.push(format!("Undefined symbol {}", name));
            }
        }
        _ => {},
    }
    errors
}

// ---------- eval repl interpreter stuff

fn eval_to_bool(mut context: &mut CilContext, source: &String, tokens: &Vec<Token>, e: &Expr) -> bool {

    match &e.node_type {
        NodeType::LBool(b_value) => *b_value,
        NodeType::FCall(f_name) => {
            match f_name.as_str() {
                "and" => eval_and_func(&mut context, &source, &tokens, e),
                "or" => eval_or_func(&mut context, &source, &tokens, e),
                _ => {
                    if does_func_return_bool(&context, f_name) {
                        lbool_in_string_to_bool(eval_func_proc_call(f_name, &mut context, &source, &tokens, &e).as_str())
                    } else {
                        panic!("Compiler error: Function '{}' does not return bool\n", f_name);
                    }
                }
            }
        },
        NodeType::Identifier(name) => {
            match context.bools.get(name) {
                Some(bool_value) => bool_value.clone(),
                None => {
                    panic!("cil error: Undefined boolean symbol '{}'. This should have been caught in the compile phase.", name)
                }
            }
        },
        _ => panic!("cil error: The only types that can be evaluated to bool are currently 'LBool', 'FCall' and 'Identifier'. Found 'SOMETHING_ELSE'"),
    }
}

fn eval_and_func(mut context: &mut CilContext, source: &String, tokens: &Vec<Token>, e: &Expr) -> bool {
    let mut truthfulness = true;
    for i in &e.params {
        truthfulness = truthfulness && eval_to_bool(&mut context, &source, &tokens, &i);
    }
    truthfulness
}

fn eval_or_func(mut context: &mut CilContext, source: &String, tokens: &Vec<Token>, e: &Expr) -> bool {
    let mut truthfulness = false;
    for i in &e.params {
        truthfulness = truthfulness || eval_to_bool(&mut context, &source, &tokens, &i);
    }
    truthfulness
}


fn lbool_in_string_to_bool(b: &str) -> bool {
    match b {
        "true" => true,
        "false" => false,
        _ => panic!("Cil Error: expected string 'true' or 'false', this should never happen.")
    }
}

fn bool_to_string(b: &bool) -> String {
    if *b {
        "true".to_string()
    } else {
        "false".to_string()
    }
}

fn eval_core_proc_print(mut context: &mut CilContext, source: &String, tokens: &Vec<Token>, e: &Expr) -> String {
    for it in &e.params {
        print!("{}", eval_expr(&mut context, &source, &tokens, &it));
    }
    io::stdout().flush().unwrap();
    "".to_string()
}

fn eval_func_proc_call(name: &str, mut context: &mut CilContext, source: &String, tokens: &Vec<Token>, e: &Expr) -> String {
    let t = tokens.get(e.token_index).unwrap();
    if is_core_func(&name) {
        match name {
            "and" | "or" => bool_to_string(&eval_to_bool(&mut context, &source, &tokens, &e)),
            _ => panic!("cil error (line {}): Core function '{}' not implemented.", t.line, name),
        }
    } else if is_core_proc(&name) {
        match name {
            "print" => eval_core_proc_print(&mut context, &source, &tokens, &e),
            _ => panic!("cil error (line {}): Core procedure '{}' not implemented.", t.line, name),
        }
    } else if context.funcs.contains_key(name) {
        let func_def = context.funcs.get(name).unwrap();

        let mut function_context = context.clone();
        assert!(e.params.len() == func_def.args.len(), "Cil error: func '{}' expected {} args, but {} were provided. This should never happen.",
                name, func_def.args.len(), e.params.len());

        let mut param_index = 0;
        for arg in &func_def.args {
            if arg.value_type == ValueType::TBool {
                let bool_expr_result = lbool_in_string_to_bool(&eval_expr(&mut function_context, &source, &tokens, e.params.get(param_index).unwrap()));
                function_context.bools.insert(arg.name.clone(), bool_expr_result);
                param_index += 1;
            } else {
                panic!("cil error (line {}): calling func '{}'. Only bool arguments allowed for now.", t.line, name);
            }

        }

        let mut result_str = "".to_string();
        for se in &func_def.body {
            match se.node_type {
                NodeType::Return => {
                    assert!(e.params.len() != 0, "Cil error: return must currently always return exactly one value.");
                    result_str.push_str(&format!("{}", eval_expr(&mut function_context, &source, &tokens, &se.params.get(0).unwrap())));
                    break;
                },
                _ => {
                    println!("In func {}: {}", name, eval_expr(&mut function_context, &source, &tokens, &se));
                }
            }
        }
        result_str
    } else if context.procs.contains_key(name) {
        panic!("cil error (line {}): Cannot call '{}'. Custom procedures not implemented yet.", t.line, name);
    } else {
        panic!("cil error (line {}): Cannot call '{}'. Undefined function. This should never happen.", t.line, name);
    }
}

fn eval_expr(mut context: &mut CilContext, source: &String, tokens: &Vec<Token>, e: &Expr) -> String {
    match &e.node_type {
        NodeType::Body => {
            let mut result_str = "".to_string();
            for se in e.params.iter() {
                result_str.push_str(&format!("{}\n", eval_expr(&mut context, &source, &tokens, &se)));
            }
            result_str
        },
        NodeType::LBool(bool_value) => bool_to_string(&bool_value),
        NodeType::LString | NodeType::LNumber | NodeType::LList => {
            let t = tokens.get(e.token_index).unwrap();
            let token_str = get_token_str(source, t);
            token_str.to_string()
        },
        NodeType::FCall(name) => {
            eval_func_proc_call(&name, &mut context, &source, &tokens, &e)
        },
        NodeType::Declaration(declaration) => {
            let t = tokens.get(e.token_index).unwrap();
            match declaration.value_type {
                ValueType::TBool => {
                    assert!(e.params.len() == 1, "Declarations can have only one child expression. This should never happen.");
                    let bool_expr_result : bool = lbool_in_string_to_bool(&eval_expr(&mut context, &source, &tokens, e.params.get(0).unwrap()));
                    context.bools.insert(declaration.name.clone(), bool_expr_result);
                    bool_expr_result.to_string()
                },
                ValueType::TFunc => {
                    assert!(e.params.len() == 1, "Declarations can have only one child expression. This should never happen.");
                    match &e.params.get(0).unwrap().node_type {
                        NodeType::FuncDef(func_def) => {
                            context.funcs.insert(declaration.name.clone(), func_def.clone());
                            "func declared".to_string()
                        },
                        _ => panic!("cil error (line {}): Cannot declare {} of type {:?}. This should never happen", t.line, &declaration.name, &declaration.value_type)
                    }
                },
                ValueType::TProc => {
                    assert!(e.params.len() == 1, "Declarations can have only one child expression. This should never happen.");
                    match &e.params.get(0).unwrap().node_type {
                        NodeType::FuncDef(func_def) => {
                            context.funcs.insert(declaration.name.clone(), func_def.clone());
                            "proc declared".to_string()
                        },
                        _ => panic!("cil error (line {}): Cannot declare {} of type {:?}. This should never happen", t.line, &declaration.name, &declaration.value_type)
                    }
                },
                _ => panic!("cil error (line {}): Cannot declare {} of type {:?}.", t.line, &declaration.name, &declaration.value_type)
            }
        },

        NodeType::Identifier(name) => {
            match context.bools.get(name) {
                Some(bool_value) => bool_to_string(bool_value),
                None => {
                    panic!("cil error: Undefined boolean symbol '{}'. This should have been caught in the compile phase.", name)
                }
            }
        },
        _ => {
            let t = tokens.get(e.token_index).unwrap();
            panic!("cil error (line {}): Not implemented, found {}.", t.line, get_token_str(source, t))
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

fn run(source: &String) -> String {
    let tokens: Vec<Token> = scan_tokens(&source);
    if tokens.len() < 1 {
        panic!("compiler error (line {}): End of file not found.", 0);
    } else if is_eof(&tokens, 0) {
        panic!("compiler error (line {}): Nothing to be done", tokens.get(0).unwrap().line);
    }

    let mut errors_found : usize = 0;
    for t in &tokens {
        match t.token_type {
            TokenType::Invalid => {
                print_lex_error(&source, &t, errors_found, "Invalid character");
                errors_found = errors_found + 1;
            },
            TokenType::UnterminatedString => {
                print_lex_error(&source, &t, errors_found, "Unterminated String");
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

    let errors = check_types(&context, &source, &tokens, &e);
    if errors.len() > 0 {
        for err in &errors {
            println!("Type error: {}", err);
        }
        panic!("Compiler errors: {} type errors found", errors.len());
    }

    println!("AST: {}", to_ast_str(&tokens, &e));
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
    println!("eval: {}", run(&source));
}

fn run_prompt() {
    loop {
        print!("cil> ");
        io::stdout().flush().unwrap();

        let mut line = String::new();
        io::stdin()
            .read_line(&mut line)
            .expect("Failed to read line");

        if line.len() == 1 { break; }

        println!("{}", run(&line));
    }
}

fn main() {
    let args: Vec<String> = env::args().collect();

    // test();
    if args.len() > 2 {
        println!("Usage: cargo run [pathToScript]");
    } else if args.len() > 1 {
        run_file(&args[1]);
    } else {
        run_prompt();
    }
}
