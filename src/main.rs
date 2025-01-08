use std::env;
use std::io;
use std::io::Write; // <--- bring flush() into scope
use std::fs;
use std::io::ErrorKind;
// use std::collections::HashMap;

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
    Const, Var,
    Struct, Enum,
    Fn, Proc,
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

#[derive(Debug, Clone, PartialEq)]
enum NodeType {
    RootNode,
    LList,
    LString,
    LUnsigned,
    LBool(bool),
    // LDecimal(String),
    FCall,
}

#[derive(Clone)]
struct Expr {
    node_type: NodeType,
    token_index: usize,
    params: Vec<Expr>,
}

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

// Type inference lets us omit an explicit type signature (which
// would be `HashMap<String, String>` in this example).
// let mut book_reviews = HashMap::new();

// // Review some books.
// book_reviews.insert(
//     "Adventures of Huckleberry Finn".to_string(),
//     "My favorite book.".to_string(),
// );


// #[derive(Debug)]
// struct Interpreter {
//     declared_values: Vec<Constant>.
// }

// fn declare_constant(i: & mut Interpreter, str_id: String, value: Value,) {
//     i.declared_values.push();
// }

fn to_ast_str(tokens: &Vec<Token>, e: &Expr) -> String {
    let mut ast_str = "".to_string();
    if e.node_type == NodeType::RootNode {
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
        TokenType::Const => "Const".to_string(),
        TokenType::Var => "Var".to_string(),
        TokenType::Fn => "Fn".to_string(),
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
    // println!("Identifier literal {}", identifier);
    match identifier {
        "true" => TokenType::True,
        "false" => TokenType::False,
        "const" => TokenType::Const,
        "var" => TokenType::Var,
        "struct" => TokenType::Struct,
        "enum" => TokenType::Enum,
        "fn" => TokenType::Fn,
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

// fn is_literal_boolean(tokens: &Vec<Token>, current: usize) -> bool {
//     let t = tokens.get(current).unwrap();
//     match t.token_type {
//         TokenType::True => true,
//         TokenType::False => true,
//         _  => false,
//     }
// }

// fn boolean(tokens: &Vec<Token>, current: usize) -> Expr {
//     let t: Token = tokens.get(current).unwrap().clone();
//     let mut params : Vec<Expr> = Vec::new();

//     match t.token_type {
//         TokenType::True => Expr { operator: t, params: params},
//         TokenType::False => Expr { operator: t, params: params},
//         _  => false,
//     }
// }

enum CompilerError {
    // CompExpectedRightParen{
    //     line: usize,
    //     pos: usize,
    // },
    CompUndefFuncProc(String),
}

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
        TokenType::Number => NodeType::LUnsigned,
        TokenType::True => NodeType::LBool(true),
        TokenType::False => NodeType::LBool(false),
        _ => panic!("cil error (line {}): Trying to parse a token that's not a literal as a literal.", t.line),
    };
    let e = Expr { node_type: node_type, token_index: *current, params: params};
    *current = *current + 1;
    e
}

fn list(source: &String, tokens: &Vec<Token>, current: &mut usize) -> Expr {
// fn list(source: &String, tokens: &Vec<Token>, current: &mut usize) -> Result<Expr, CompilerError> {
    let mut rightparent_found = false;
    let mut params : Vec<Expr> = Vec::new();
    let initial_current = *current;
    *current = *current + 1;
    let mut list_t = tokens.get(*current).unwrap();
    // println!("primary debug LeftParen: {} {}", initial_current, *current);
    while !(is_eof(&tokens, *current) || rightparent_found) {
        // println!("primary debug LeftParen while: {} {}", current, *current);
        match list_t.token_type {
            TokenType::RightParen => {
                rightparent_found = true;
                *current = *current + 1;
            },
            _ => {
                params.push(primary(&source, &tokens, current));
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
        "let" => true,
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

fn func_call(source: &String, tokens: &Vec<Token>, current: &mut usize) -> Result<Expr, CompilerError> {
    let t = tokens.get(*current).unwrap();
    let token_str = get_token_str(source, t);
    if is_core_func_proc(token_str) {
        let initial_current = *current;
        *current = *current + 1;
        let params : Vec<Expr> = list(&source, &tokens, current).params;
        Ok(Expr { node_type: NodeType::FCall, token_index: initial_current, params: params})
    } else {
        Err(CompilerError::CompUndefFuncProc(token_str.to_string()))
    }
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

// fn compiler_error_to_string()(ce: CompilerError) -> String {
//     let mut e_str = "".to_string();
//     match ce {

//     }

// }

fn primary(source: &String, tokens: &Vec<Token>, current: &mut usize) -> Expr {

    // println!("primary debug: {}", current);
    let t = tokens.get(*current).unwrap();
    if is_literal(t) {
        literal(t, current)
    } else {
        match &t.token_type {
            TokenType::LeftParen => list(&source, &tokens, current),
            TokenType::Identifier => {
                if is_eof(&tokens, *current) || tokens.get(*current + 1).unwrap().token_type == TokenType::LeftParen {
                    match func_call(&source, &tokens, current) {
                        Ok(e) => e,
                        Err(_e) => {panic!("compiler error (line {}): Undefined function/procedure '{}'.", t.line, get_token_str(source, t));}
                    }
                } else {
                    literal(t, current)
                }
            },
            _ => panic!("compiler error (line {}): Expected primary expression, found {:?}.", t.line, t.token_type),
        }
    }
}

fn statement(source: &String, tokens: &Vec<Token>, current: &mut usize) -> Expr {
    let t = tokens.get(*current).unwrap();
    match &t.token_type {
        TokenType::Identifier => {
            if is_eof(&tokens, *current) || tokens.get(*current + 1).unwrap().token_type == TokenType::LeftParen {
                match func_call(&source, &tokens, current) {
                    Ok(e) => e,
                    Err(_e) => {panic!("compiler error (line {}): Undefined function/procedure '{}'.", t.line, get_token_str(source, t));}
                }
            } else {
                literal(t, current)
            }
        },
        _ => panic!("compiler error (line {}): Expected statement, found {:?}.", t.line, t.token_type),
    }

}

fn root_body(source: &String, tokens: &Vec<Token>, current: &mut usize) -> Expr {
    let mut params : Vec<Expr> = Vec::new();
    while !is_eof(&tokens, *current) {
        params.push(statement(&source, &tokens, current));
    }

    Expr { node_type: NodeType::RootNode, token_index: *current, params: params}
}

fn eval_func_to_bool(source: &String, tokens: &Vec<Token>, e: &Expr) -> bool {
    let t = tokens.get(e.token_index).unwrap();
    let token_str = get_token_str(source, t);
    if e.node_type == NodeType::FCall {
        match token_str {
            "and" => eval_and_func(&source, &tokens, e),
            "or" => eval_or_func(&source, &tokens, e),
            _ => panic!("cil error: The only functions that can be evaluated to bool are currently 'and' and 'or'. Found '{}'" , token_str)
        }
    } else {
        panic!("cil error: Only NodeType::FCall should be eval to bool as func. Found '{}'" , token_str)
    }
}

fn eval_to_bool(source: &String, tokens: &Vec<Token>, e: &Expr) -> bool {

    let t = tokens.get(e.token_index).unwrap();
    match e.node_type {
        NodeType::LBool(b_value) => b_value,
        NodeType::FCall => eval_func_to_bool(&source, &tokens, &e),
        _ => {
            let token_str = get_token_str(source, t);
            panic!("cil error: 'and' and 'or' should fail at compile time if non boolean args are provided. Found '{}'" , token_str)
        },
    }
}

fn eval_and_func(source: &String, tokens: &Vec<Token>, e: &Expr) -> bool {
    let mut truthfulness = true;
    for i in &e.params {
        truthfulness = truthfulness && eval_to_bool(&source, &tokens, &i);
    }
    truthfulness
}

fn eval_or_func(source: &String, tokens: &Vec<Token>, e: &Expr) -> bool {
    let mut truthfulness = false;
    for i in &e.params {
        truthfulness = truthfulness || eval_to_bool(&source, &tokens, &i);
    }
    truthfulness
}

fn bool_to_string(b: bool) -> String {
    if b {
        "true".to_string()
    } else {
        "false".to_string()
    }
}

fn let_to_string() -> String {
    "funny string".to_string()
}

fn eval_expr(source: &String, tokens: &Vec<Token>, e: &Expr) -> String {
    if e.node_type == NodeType::RootNode {
        let mut result_str = "".to_string();
        for se in e.params.iter() {
            result_str.push_str(&format!("{}\n", eval_expr(&source, &tokens, &se)));
        }
        return result_str
    }
    let t = tokens.get(e.token_index).unwrap();

    let token_str = get_token_str(source, t);
    if is_literal(t) {
        token_str.to_string()
    } else if is_core_func(token_str) {
        match token_str {
            "and" | "or" => bool_to_string(eval_func_to_bool(&source, &tokens, &e)),
            "let" => let_to_string(),
            _ => { panic!("cil error (line {}): Core function '{}' not implemented.", t.line, token_str); },
        }

    } else {
        panic!("cil error (line {}): Not implemented, found {:?}.", t.line, t.token_type);
    }
}

fn parse_tokens(source: &String, tokens: &Vec<Token>) -> Expr {
    let mut current: usize = 0;

    let e: Expr = root_body(&source, tokens, &mut current);
    current = current + 1; // Add olne for the EOF

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

// struct ParseError {
//     error_msg = String,
//     line: usize,
// }

// fn print_parse_error(error: ParseError) {
// }

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

    let e: Expr = parse_tokens(&source, &tokens);
    println!("AST: {}", to_ast_str(&tokens, &e));

    eval_expr(&source, &tokens, &e)
}

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
