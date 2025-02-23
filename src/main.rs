use std::env;
use std::io;
use std::io::Write; // <--- bring flush() into scope
use std::fs;
use std::io::ErrorKind;
use std::collections::HashMap;

// We may want to change it to rsbootstrap later when self hosting, if we get there
// or just change the name of the language
// CIL stands for Compiled Interpreted Language
// Because there is no good reason for a programming language not to be both compiled and interpreted.
const LANG_NAME: &str = "rscil";
const BIN_NAME: &str = "cil";
const INFER_TYPE: &str = "_Infer";
const SKIP_AST: bool = true;

// ---------- format errors

// struct RscilErr {
//     error_str: &str,
//     t: &Token,
//     level: &str,
// }

// fn init_err(t: &Token, level: &str, error_str: &str) return RscilErr {
//     return RscilErr(format!("{}:{}: {} error: {}", t.line, t.col, level, error_str));
// }

// fn format_err(RscilErr: err) -> String {
//     return format!("{}:{}: {} error: {}", err.t.line, err.t.col, err.level, err.error_str);
// }

// fn print_err(RscilErr: err) {
//     println(format_err(err))
// }

// ---------- lexer

#[derive(Debug, Clone, PartialEq)]
enum TokenType {
    // basic
    Eof,

    // Single-character tokens.
    Minus, Plus, Slash, Star,
    LeftParen, RightParen, LeftBrace, RightBrace, LeftBracket, RightBracket,
    Comma, Colon,

    // One or two character tokens.
    Dot, DoubleDot,
    Not, NotEqual,
    Equal, EqualEqual,
    Greater, GreaterEqual,
    Lesser, LesserEqual,
    Semicolon, DoubleSemicolon,

    // Literals.
    Identifier, String, Number,

    // Reserved words:
    Mut,

    // bool
    True, False,
    // type definition
    Struct, Enum,
    // function definition
    Returns, Throws,
    // flow control
    If, Else,
    While, For, In,
    Match, Switch, Default,
    Return, Throw,
    Try, Catch,

    // Special in this language:
    Func, Proc, Macro,
    Mode,

    // Errors
    Const, Var,
    Fn,
    Case,
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
        "func" => TokenType::Func,
        "proc" => TokenType::Proc,
        "macro" => TokenType::Macro,
        "return" => TokenType::Return,
        "returns" => TokenType::Returns,
        // TODO reserved words:
        "enum" => TokenType::Enum,
        "struct" => TokenType::Struct,
        "switch" => TokenType::Switch,
        "match" => TokenType::Match,
        "default" => TokenType::Default,
        "for" => TokenType::For,
        "in" => TokenType::In,
        "throw" => TokenType::Throw,
        "throws" => TokenType::Throws,
        "try" => TokenType::Try,
        "catch" => TokenType::Catch,
        "mode" => TokenType::Mode,

        // Reserved illegal words:
        // const/vars are the most abstract types, you can't even explicitly declare them
        "const" => TokenType::Const,
        "var" => TokenType::Var,
        // intentionally unsupported reserved words:
        "fn" => TokenType::Fn,
        "case" => TokenType::Case,

        // TODO intentionally unsupport more reserved words
        // TODO nicer messages for forbidden words
        // Reserved forbidden words:
        "function" => TokenType::Invalid,
        "method" => TokenType::Invalid,
        "static" => TokenType::Invalid,
        "global" => TokenType::Invalid,
        _ => TokenType::Identifier,
    }
}

fn scan_tokens(source: &String) -> Vec<Token> {
    let mut tokens : Vec<Token> = Vec::new();

    let eof_pos : usize = source.len();
    let mut pos = 0;
    let mut line = 1;
    let mut start_line_pos = 0;

    while pos < eof_pos {
        let start = pos;

        if is_digit(source, pos) {
            while pos < eof_pos && is_digit(source, pos) {
                pos += 1;
            }
            // Look for a fractional part.
            if &source[pos..pos+1] == "." && is_digit(source, pos+1) {
                pos += 1;
                while pos < eof_pos && is_digit(source, pos) {
                    pos += 1;
                }
            }
            tokens.push(Token { token_type: TokenType::Number, start: start, end: pos, line: line, col: pos - start_line_pos + 1});
        } else {

            let token_type = match &source[pos..pos+1] {
                " " => { pos += 1; continue; },
                // chars to ignore in this language:
                "\r" => { pos += 1; continue; },
                "\t" => { pos += 1; continue; },
                "\n" => {
                    pos += 1;
                    line = line + 1;
                    start_line_pos = pos;
                    continue;
                },
                // open/close. left/right
                "(" => TokenType::LeftParen,
                ")" => TokenType::RightParen,
                "{" => TokenType::LeftBrace,
                "}" => TokenType::RightBrace,
                "[" => TokenType::LeftBracket,
                "]" => TokenType::RightBracket,

                // separator for optional type before the equal in declarations or args
                ":" => TokenType::Colon,
                // separator for args
                "," => TokenType::Comma, // args can/must? have ',', otherwise the language would be too lispy when parsing from C

                // math
                "-" => TokenType::Minus,
                "+" => TokenType::Plus,
                "*" => TokenType::Star,

                // reserved for two chars in a row
                "." => if &source[pos+1..pos+2] == "." { pos += 1; TokenType::DoubleDot } else { TokenType::Dot },
                "=" => if &source[pos+1..pos+2] == "=" { pos += 1; TokenType::EqualEqual } else { TokenType::Equal },
                "<" => if &source[pos+1..pos+2] == "=" { pos += 1; TokenType::LesserEqual } else { TokenType::Lesser },
                ">" => if &source[pos+1..pos+2] == "=" { pos += 1; TokenType::GreaterEqual } else { TokenType::Greater },
                "!" => if &source[pos+1..pos+2] == "=" { pos += 1; TokenType::NotEqual } else { TokenType::Not },

                // semicolon is optional between statements, but allowed. DoubleSemicolon means empty statement
                // TODO implement better warnings
                ";" => if &source[pos+1..pos+2] == ";" { pos += 1; TokenType::DoubleSemicolon } else { TokenType::Semicolon },

                // comments:
                "#" => {
                    pos += 1;
                    while pos + 1 < eof_pos && &source[pos..pos+1] != "\n" {
                        pos += 1;
                    }
                    continue;
                },
                "/" => match &source[pos+1..pos+2] {
                    "/" => {
                        pos += 1;
                        while pos + 1 < eof_pos && &source[pos..pos+1] != "\n" {
                            pos += 1;
                        }
                        continue;
                    },
                    // TODO allow the other type of commments, allowing nesting
                    // "*" => {
                    //     // /* style of comment not allowed yet
                    //     TokenType::Invalid,
                    // },
                    _ => TokenType::Slash,
                },

                "\"" => {
                    pos += 1;
                    while pos + 1 < eof_pos && &source[pos..pos+1] != "\"" {
                        pos += 1;
                    }
                    // pos = pos - 1;
                    match &source[pos..pos+1] {
                        "\"" => TokenType::String,
                        _ => TokenType::UnterminatedString,
                    }
                },

                _ => {
                    if is_alphanumeric(source, pos){
                        pos += 1;
                        // FIX invalid characters
                        while pos < eof_pos && (is_alphanumeric(source, pos) || is_digit(source, pos)) {
                            pos += 1;
                        }
                        pos = pos - 1;
                        get_identifier_type(&source[start..pos+1])

                    } else {
                        TokenType::Invalid
                    }
                },
            }; // let match
            if token_type == TokenType::String {
                tokens.push(Token { token_type: token_type, start: start + 1, end: pos, line: line, col: pos - start_line_pos + 1});
            } else {
                tokens.push(Token { token_type: token_type, start: start, end: pos + 1, line: line, col: pos - start_line_pos + 1});
            }
            pos += 1;
        } // else

    } // while
    tokens.push(Token { token_type: TokenType::Eof, start: pos, end: pos + 1, line: line, col: 0});
    tokens
}

// ---------- parser

fn get_token_str<'a>(source: &'a String, t: &'a Token) -> &'a str {
    &source[t.start..t.end]
}

fn print_lex_error(path: &String, source: &String, t: &Token, num_error: usize, msg: &str) {
    let max_symbol_len = 20;
    let mut end_symbol = t.end;
    if end_symbol - t.start > max_symbol_len {
        end_symbol = max_symbol_len;
    }
    println!("{}:{}:{}: Lexical error {}: {}. Offending symbol: {}", path, t.line, t.col, num_error, msg, &source[t.start..end_symbol]);
}

fn print_if_lex_error(path: &String, source: &String, t: &Token, errors_found: &mut usize) {
    match t.token_type {
        TokenType::Invalid => {
            print_lex_error(&path, &source, &t, *errors_found, "Invalid character");
            *errors_found = *errors_found + 1;
        },
        TokenType::UnterminatedString => {
            print_lex_error(&path, &source, &t, *errors_found, "Unterminated String");
            *errors_found = *errors_found + 1;
        },
        TokenType::Const => {
            print_lex_error(&path, &source, &t, *errors_found, "No need to use 'const', everything is const by default unless 'mut' is used");
            *errors_found = *errors_found + 1;
        },
        TokenType::Var => {
            print_lex_error(&path, &source, &t, *errors_found, "Keyword 'var' is not supported, use 'mut' instead");
            *errors_found = *errors_found + 1;
        },
        TokenType::Fn => {
            print_lex_error(&path, &source, &t, *errors_found, "Keyword 'fn' is not supported, use 'func' or 'proc' instead");
            *errors_found = *errors_found + 1;
        },
        TokenType::Macro => {
            print_lex_error(&path, &source, &t, *errors_found, "Keyword 'macro' is not supported yet, use 'func' or 'proc' instead for now");
            *errors_found = *errors_found + 1;
        },
        TokenType::DoubleSemicolon => {
            print_lex_error(&path, &source, &t, *errors_found, "No need for ';;' (aka empty statements), try 'if true {}' instead, whatever you want that for");
            *errors_found = *errors_found + 1;
        },
        _ => {},
    }
}

fn is_literal(t: &Token) -> bool {
    return match t.token_type {
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
    TMacro,
    TEnumDef,
    TStructDef,
    TMulti(Box<ValueType>),
    TCustom(String),
    ToInferType,
}

fn value_type_to_str(arg_type: &ValueType) -> String {
    match arg_type {
        ValueType::ToInferType => INFER_TYPE.to_string(),
        ValueType::TBool => "bool".to_string(),
        ValueType::TI64 => "i64".to_string(),
        ValueType::TString =>" String".to_string(),
        ValueType::TList => "list".to_string(),
        ValueType::TFunc => "func".to_string(),
        ValueType::TProc => "proc".to_string(),
        ValueType::TMacro => "macro".to_string(),
        ValueType::TEnumDef => "enum".to_string(),
        ValueType::TStructDef => "struct".to_string(),
        ValueType::TMulti(val_type) => format!("[]{}", value_type_to_str(val_type)).to_string(),
        ValueType::TCustom(type_name) => format!("{}", type_name),
    }
}

fn str_to_value_type(arg_type: &str) -> ValueType {
    match arg_type {
        INFER_TYPE => ValueType::ToInferType,
        "bool" => ValueType::TBool,
        "String" => ValueType::TString,
        "list" => ValueType::TList,
        "func" => ValueType::TFunc,
        "proc" => ValueType::TProc,
        "enum" => ValueType::TEnumDef,
        "struct" => ValueType::TStructDef,
        "i64" => ValueType::TI64,
        type_name => ValueType::TCustom(type_name.to_string()),
    }
}

#[derive(Debug, Clone, PartialEq)]
struct SEnumDef {
    enum_map: HashMap<String, Option<ValueType>>,
}

#[derive(Debug, Clone, PartialEq)]
struct Declaration {
    name: String,
    value_type: ValueType,
    is_mut: bool,
}

#[derive(Debug, Clone, PartialEq)]
struct SFuncDef {
    args: Vec<Declaration>,
    returns: Vec<ValueType>,
    // throws: Vec<ValueType>,
    body: Vec<Expr>,
}

// #[derive(Debug, Clone, PartialEq)]
// struct SStructDef {
//     const_members : HashMap<String, ValueType>,
//     mut_members : HashMap<String, ValueType>,
// }

#[derive(Debug, Clone, PartialEq)]
enum NodeType {
    Body,
    LList,
    LString(String),
    LI64(i64),
    LBool(bool),
    FCall(String),
    Identifier(String),
    Declaration(Declaration),
    Assignment(String),
    FuncDef(SFuncDef),
    ProcDef(SFuncDef),
    EnumDef(SEnumDef),
    StructDef,
    Return,
    If,
    While,
    Switch,
    DefaultCase,
}

#[derive(Debug, Clone, PartialEq)]
struct Expr {
    node_type: NodeType,
    token_index: usize,
    params: Vec<Expr>,
}

fn is_eof(tokens: &Vec<Token>, current: usize) -> bool {
    current > tokens.len() || match tokens.get(current).unwrap().token_type {
        TokenType::Eof => true,
        _ => false,
    }
}

#[derive(Debug, Clone, PartialEq)]
struct ModeDef {
    name: String,
    allows_base_mut: bool,
    allows_base_calls: bool,
    allows_base_anything: bool,
    needs_main_proc: bool,
}

fn mode_from_name(mode_name: &str) -> Result<ModeDef, String> {
    return match mode_name {
        "lib" => Ok(
            ModeDef{name: mode_name.to_string(),
                    allows_base_calls: false,
                    allows_base_mut: false,
                    allows_base_anything: false,
                    needs_main_proc: false,
        }),
        "external" => Ok(
            ModeDef{name: mode_name.to_string(),
                    allows_base_calls: false,
                    allows_base_mut: false,
                    allows_base_anything: false,
                    needs_main_proc: false,
        }),
        "pure" => Ok(
            ModeDef{name: mode_name.to_string(),
                    allows_base_calls: false,
                    allows_base_mut: false,
                    allows_base_anything: false,
                    needs_main_proc: false,
        }),
        "script" => Ok(
            ModeDef{name: mode_name.to_string(),
                    allows_base_calls: true,
                    allows_base_mut: true,
                    allows_base_anything: true,
                    needs_main_proc: false,
        }),
        "safe_script" => Ok(
            ModeDef{name: mode_name.to_string(),
                    allows_base_calls: true,
                    allows_base_mut: true,
                    allows_base_anything: true,
                    needs_main_proc: false,
        }),
        "cli" => Ok(
            ModeDef{name: mode_name.to_string(),
                    allows_base_calls: false,
                    allows_base_mut: true,
                    allows_base_anything: false,
                    needs_main_proc: true,
        }),
        "test" => Ok(
            ModeDef{name: mode_name.to_string(),
                    allows_base_calls: true,
                    allows_base_mut: false,
                    allows_base_anything: false,
                    needs_main_proc: false,
        }),

        _  => return Err(format!("0:0: {} interpreter implementation doesn't support mode '{}'", LANG_NAME, mode_name)),
    };
}

fn parse_mode(source: &String, tokens: &Vec<Token>, mut current: &mut usize) -> Result<ModeDef, String> {
    if &TokenType::Mode != current_token_type(&tokens, &mut current) {
        return Err(format!("0:0: 'mode' is required in the beginning of the file"));
    }
    *current = *current + 1; // Add one for mode

    if &TokenType::Identifier != current_token_type(&tokens, &mut current) {
        return Err(format!("0:0: Expected identifier after 'mode'"));
    }
    let t = current_token(&tokens, &mut current);
    let mode_name = get_token_str(source, t).to_string();
    let mode = match mode_from_name(&mode_name) {
        Ok(mode_) => mode_,
        Err(err_) => return Err(err_),
    };

    *current = *current + 1; // Add one for the identifier mode
    return Ok(mode);
}

fn parse_literal(source: &String, t: &Token, current: &mut usize) -> Result<Expr, String> {
    let params : Vec<Expr> = Vec::new();
    let node_type = match t.token_type {
        TokenType::String => NodeType::LString(get_token_str(source, t).to_string()),
        TokenType::Number => NodeType::LI64(get_token_str(source, t).parse::<i64>().unwrap()),
        TokenType::True => NodeType::LBool(true),
        TokenType::False => NodeType::LBool(false),
        _ => {
            return Err(format!("{}:{}: {}  error: Trying to parse a token that's not a literal as a literal, found {:?}.", t.line, t.col, LANG_NAME, t.token_type));
        },
    };
    let e = Expr { node_type: node_type, token_index: *current, params: params};
    *current = *current + 1;
    Ok(e)
}

fn parse_list(source: &String, tokens: &Vec<Token>, current: &mut usize) -> Result<Expr, String> {
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
                    return Err(format!("{}:{}: parse error: Unexpected ','.", list_t.line, list_t.col));
                }
            },
            _ => {
                if expect_comma {
                    return Err(format!("{}:{}: parse error: Expected ')' or ',', found {:?}.", list_t.line, list_t.col, list_t.token_type));
                }
                expect_comma = true;
                let prim = match primary(&source, &tokens, current) {
                    Ok(to_ret) => to_ret,
                    Err(err_str) => return Err(err_str),
                };
                params.push(prim);
                list_t = tokens.get(*current).unwrap();
            },
        }
    }
    match list_t.token_type {
        TokenType::RightParen => Ok(Expr { node_type: NodeType::LList, token_index: initial_current, params: params}),
        _ => Err(format!("{}:{}: parse error: Expected closing parentheses.", list_t.line, list_t.col)),
    }
}

fn parse_func_call(source: &String, tokens: &Vec<Token>, current: &mut usize) -> Result<Expr, String> {
    let t = tokens.get(*current).unwrap();
    let token_str = get_token_str(source, t);
    let initial_current = *current;
    *current = *current + 1;
    let arg_list = match parse_list(&source, &tokens, current) {
        Ok(a_list) => a_list,
        Err(err_str) => return Err(err_str),
    };
    let params : Vec<Expr> = arg_list.params;
    Ok(Expr { node_type: NodeType::FCall(token_str.to_string()), token_index: initial_current, params: params})
}

fn parse_assignment(source: &String, tokens: &Vec<Token>, current: &mut usize) -> Result<Expr, String> {
    let t = tokens.get(*current).unwrap();
    let name = get_token_str(source, t);
    let initial_current = *current;
    *current = *current + 2; // skip identifier and equal
    let mut params : Vec<Expr> = Vec::new();
    params.push(primary(&source, &tokens, current)?);
    Ok(Expr { node_type: NodeType::Assignment(name.to_string()), token_index: initial_current, params: params})
}

fn parse_func_proc_args(source: &String, tokens: &Vec<Token>, current: &mut usize) -> Result<Vec<Declaration>, String> {

    let mut rightparent_found = false;
    let mut args : Vec<Declaration> = Vec::new();
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
                if expect_colon {
                    args.push(Declaration{
                        name: arg_name.to_string(), value_type: str_to_value_type(INFER_TYPE), is_mut: false});
                }
                *current = *current + 1;
            },
            TokenType::Comma => {
                if expect_comma {
                    expect_comma = false;
                    expect_colon = false;
                    expect_name = true;
                    *current = *current + 1;
                    t = tokens.get(*current).unwrap();
                } else {
                    if expect_colon {
                        expect_colon = false;
                        args.push(Declaration{
                            name: arg_name.to_string(), value_type: str_to_value_type(INFER_TYPE), is_mut: false});
                        expect_comma = true;
                        *current = *current + 1;
                        t = tokens.get(*current).unwrap();
                    } else {
                        return Err(format!("{}:{}: parse error: Expected identifier before ','.", t.line, t.col));
                    }
                }
            },
            TokenType::Colon => {
                if expect_colon {
                    expect_colon = false;
                    expect_name = false; // expect type name then
                    expect_comma = false;
                    *current = *current + 1;
                    t = tokens.get(*current).unwrap();
                } else {
                    return Err(format!("{}:{}: parse error: Unexpected ':'.", t.line, t.col));
                }
            },
            TokenType::Identifier => {
                if expect_comma {
                    return Err(format!("{}:{}: parse error: Expected ',', found {:?}.", t.line, t.col, t.token_type));
                }
                if expect_colon {
                    return Err(format!("{}:{}: parse error: Expected ':', found {:?}.", t.line, t.col, t.token_type));
                }
                if expect_name {
                    arg_name = get_token_str(source, t);
                    expect_colon = true;
                    expect_name = false;
                } else { // expect type name then
                    args.push(Declaration{
                        name: arg_name.to_string(), value_type: str_to_value_type(get_token_str(source, t)), is_mut: false});
                    expect_comma = true;
                }
                *current = *current + 1;
                t = tokens.get(*current).unwrap();
            },
            _ => {
                return Err(format!("{}:{}: parse error: Unexpected {:?} in func/proc args.", t.line, t.col, t.token_type));
            },
        }
    }
    match t.token_type {
        TokenType::RightParen => return Ok(args),
        _ => return Err(format!("{}:{}: parse error: Expected closing parentheses.", t.line, t.col)),
    }
}

fn func_proc_returns(source: &String, tokens: &Vec<Token>, current: &mut usize) -> Result<Vec<ValueType>, String> {
    let mut end_found = false;
    let mut return_types : Vec<ValueType> = Vec::new();
    let mut t = tokens.get(*current).unwrap();
    *current = *current + 1;
    if t.token_type != TokenType::Returns {
        return Ok(return_types);
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
                    return Err(format!("{}:{}: parse error: Unexpected ','.", t.line, t.col));
                }
            },
            TokenType::Identifier => {
                if expect_comma {
                    return Err(format!("{}:{}: parse error: Expected ',', found {:?}.", t.line, t.col, t.token_type));
                }
                return_types.push(str_to_value_type(get_token_str(source, t)));
                expect_comma = true;
                *current = *current + 1;
                t = tokens.get(*current).unwrap();
            },
            _ => {
                return Err(format!("{}:{}: parse error: Unexpected {:?} in func/proc returns.", t.line, t.col, t.token_type));
            },
        }
    }
    if end_found {
        return Ok(return_types);
    } else {
        return Err(format!("{}:{}: parse error: Expected '{{' or 'throws' after return values.", t.line, t.col));
    }
}

fn parse_func_proc_definition(is_func: bool, source: &String, tokens: &Vec<Token>, current: &mut usize) -> Result<Expr, String> {
    *current = *current + 1;
    if is_eof(&tokens, *current + 1) {
        let t = tokens.get(*current).unwrap();
        return Err(format!("{}:{}: parse error: expected '(' after 'func' or 'proc', found EOF.", t.line, t.col));
    }
    let t = tokens.get(*current).unwrap();
    if t.token_type != TokenType::LeftParen {
        return Err(format!("{}:{}: parse error: expected '(' after 'func', found {:?}.", t.line, t.col, t.token_type));
    }
    let args = match parse_func_proc_args(&source, &tokens, current) {
        Ok(to_ret) => to_ret,
        Err(err_str) => return Err(err_str),
    };
    let returns = match func_proc_returns(&source, &tokens, current) {
        Ok(to_ret) => to_ret,
        Err(err_str) => return Err(err_str),
    };
    let body = match parse_body(TokenType::RightBrace, &source, tokens, current) {
        Ok(body) => body.params,
        Err(err_str) => return Err(err_str),
    };
    let func_def = SFuncDef{args: args, returns: returns, body: body};
    let params : Vec<Expr> = Vec::new();
    let e;
    match is_func {
        true => e = Expr { node_type: NodeType::FuncDef(func_def), token_index: *current, params: params},
        false => e = Expr { node_type: NodeType::ProcDef(func_def), token_index: *current, params: params},
    }
    *current = *current + 1;
    Ok(e)
}

fn enum_definition(source: &String, tokens: &Vec<Token>, current: &mut usize) -> Result<Expr, String> {
    let initial_current: usize = *current;
    *current = *current + 1;

    let t = tokens.get(*current).unwrap();
    if t.token_type != TokenType::LeftBrace {
        return Err(format!("{}:{}: parse error: Expected '{{' after 'enum'.", t.line, t.col));
    }
    if is_eof(&tokens, *current + 1) {
        let t = tokens.get(*current).unwrap();
        return Err(format!("{}:{}: parse error: expected identifier after 'enum {{', found EOF.", t.line, t.col));
    }
    *current = *current + 1;
    let mut enum_map: HashMap<String, Option<ValueType>> = HashMap::new();

    let mut end_found = false;
    while *current < tokens.len() && !end_found {
        let it_t = tokens.get(*current).unwrap();
        match it_t.token_type {
            TokenType::RightBrace => {
                end_found = true;
            },
            TokenType::Identifier => {
                let next_t = tokens.get(*current + 1).unwrap();
                let enum_val_name = get_token_str(source, it_t);
                match next_t.token_type {
                    TokenType::Identifier | TokenType::RightBrace => {
                        enum_map.insert(enum_val_name.to_string(), None);
                    },
                    TokenType::Colon => {
                        let next2_t = tokens.get(*current + 2).unwrap();
                        if next2_t.token_type != TokenType::Identifier {
                            return Err(format!("{}:{}: parse error: Expected type identifier after '{} :', found '{:?}'.", t.line, t.col, enum_val_name, next2_t.token_type));
                        }
                        let enum_val_type = get_token_str(source, next2_t);
                        enum_map.insert(enum_val_name.to_string(), Some(str_to_value_type(enum_val_type)));
                        *current = *current + 1;
                    },
                    _ => {},
                }
            },
            _ => {
                return Err(format!("{}:{}: parse error: Expected '}}' to end enum or a new identifier, found '{:?}'.", t.line, t.col, it_t.token_type));
            }
        }
        *current = *current + 1;
    }
    if !end_found {
        return Err(format!("{}:{}: parse error: Expected '}}' to end enum.", t.line, t.col));
    }
    let params : Vec<Expr> = Vec::new();
    return Ok(Expr { node_type: NodeType::EnumDef(SEnumDef{enum_map: enum_map}), token_index: initial_current, params: params});
}

fn struct_definition(source: &String, tokens: &Vec<Token>, current: &mut usize) -> Result<Expr, String> {
    *current = *current + 1;
    let t = tokens.get(*current).unwrap();
    if t.token_type != TokenType::LeftBrace {
        return Err(format!("{}:{}: parse error: Expected '{{' after 'struct'.", t.line, t.col));
    }
    if is_eof(&tokens, *current + 1) {
        let t = tokens.get(*current).unwrap();
        return Err(format!("{}:{}: parse error: expected 'identifier' after 'struct {{', found EOF.", t.line, t.col));
    }
    *current = *current + 1;
    let mut params : Vec<Expr> = Vec::new();
    let body = match parse_body(TokenType::RightBrace, &source, tokens, current) {
        Ok(body) => body,
        Err(err_str) => return Err(err_str),
    };
    params.push(body);
    *current = *current + 1;
    return Ok(Expr { node_type: NodeType::StructDef, token_index: *current, params: params});
}

fn primary(source: &String, tokens: &Vec<Token>, current: &mut usize) -> Result<Expr, String> {

    let initial_current = *current;
    let t = tokens.get(*current).unwrap();
    if is_literal(t) {
        return parse_literal(&source, t, current)
    } else {
        match &t.token_type {
            TokenType::Func => return parse_func_proc_definition(true, &source, &tokens, current),
            TokenType::Proc => return parse_func_proc_definition(false, &source, &tokens, current),
            TokenType::Enum => return enum_definition(&source, &tokens, current),
            TokenType::Struct => return struct_definition(&source, &tokens, current),
            TokenType::LeftParen => parse_list(&source, &tokens, current),
            TokenType::Identifier => {
                let mut next_t = tokens.get(*current + 1).unwrap();
                if TokenType::LeftParen == next_t.token_type {
                    return parse_func_call(&source, &tokens, current);
                }
                let mut current_identifier = get_token_str(source, t).to_string();
                let mut params : Vec<Expr> = Vec::new();
                while TokenType::Dot == next_t.token_type {
                    let next2_t = tokens.get(*current + 2).unwrap();
                    if TokenType::Identifier != next2_t.token_type {
                        return Err(format!("{}:{}: parse error: expected identifier after '{}.', found {:?}.",
                                           next2_t.line, next2_t.col, current_identifier, next2_t.token_type));
                    }
                    current_identifier = get_token_str(source, next2_t).to_string();
                    *current = *current + 2;
                    params.push(Expr { node_type: NodeType::Identifier(current_identifier.clone()), token_index: *current, params: Vec::new()});
                    next_t = tokens.get(*current + 1).unwrap();
                }
                let e = Expr { node_type: NodeType::Identifier(get_token_str(source, t).to_string()), token_index: initial_current, params: params};
                *current = *current + 1;
                return Ok(e);
            },
            _ => return Err(format!("{}:{}: parse error: Expected primary expression, found {:?}.", t.line, t.col, t.token_type)),
        }
    }
}

fn return_statement(source: &String, tokens: &Vec<Token>, current: &mut usize) -> Result<Expr, String> {
    let initial_current = *current;
    *current = *current + 1;
    let mut params : Vec<Expr> = Vec::new();
    let prim = match primary(&source, &tokens, current) {
        Ok(to_ret) => to_ret,
        Err(err_str) => return Err(err_str),
    };
    params.push(prim);
    Ok(Expr { node_type: NodeType::Return, token_index: initial_current, params: params})
}

fn if_statement(source: &String, tokens: &Vec<Token>, current: &mut usize) -> Result<Expr, String> {
    let initial_current = *current;
    *current = *current + 1;
    let mut params : Vec<Expr> = Vec::new();
    let prim = match primary(&source, &tokens, current) {
        Ok(to_ret) => to_ret,
        Err(err_str) => return Err(err_str),
    };
    params.push(prim);
    let mut t = tokens.get(*current).unwrap();
    if t.token_type != TokenType::LeftBrace {
        return Err(format!("{}:{}: parse error: Expected '{{' after condition in 'if' statement, found {:?}.", t.line, t.col, t.token_type));
    }
    *current = *current + 1;
    let body = match parse_body(TokenType::RightBrace, &source, tokens, current) {
        Ok(body) => body,
        Err(err_str) => return Err(err_str),
    };
    params.push(body);
    *current = *current + 1;
    t = tokens.get(*current).unwrap();
    if t.token_type == TokenType::Else {
        *current = *current + 1;
        t = tokens.get(*current).unwrap();
        if t.token_type != TokenType::LeftBrace {
            return Err(format!("{}:{}: parse error: Expected '{{' after 'else'.", t.line, t.col));
        }
        *current = *current + 1;
        let body = match parse_body(TokenType::RightBrace, &source, tokens, current) {
            Ok(body) => body,
            Err(err_str) => return Err(err_str),
        };
        params.push(body);
        *current = *current + 1;
    }
    Ok(Expr { node_type: NodeType::If, token_index: initial_current, params: params})
}

fn while_statement(source: &String, tokens: &Vec<Token>, current: &mut usize) -> Result<Expr, String> {
    let initial_current = *current;
    *current = *current + 1;
    let mut params : Vec<Expr> = Vec::new();
    let prim = match primary(&source, &tokens, current) {
        Ok(to_ret) => to_ret,
        Err(err_str) => return Err(err_str),
    };
    params.push(prim);
    let t = tokens.get(*current).unwrap();
    if t.token_type != TokenType::LeftBrace {
        return Err(format!("{}:{}: parse error: Expected '{{' after condition in 'while' statement.", t.line, t.col));
    }
    *current = *current + 1;
    let body = match parse_body(TokenType::RightBrace, &source, tokens, current) {
        Ok(body) => body,
        Err(err_str) => return Err(err_str),
    };
    params.push(body);
    *current = *current + 1;
    Ok(Expr { node_type: NodeType::While, token_index: initial_current, params: params})
}

fn current_token_type<'a>(tokens: &'a Vec<Token>, current: &'a mut usize) -> &'a TokenType {
    let next_t = &tokens.get(*current).unwrap();
    return &next_t.token_type;
}

fn current_token<'a>(tokens: &'a Vec<Token>, current: &'a mut usize) -> &'a Token {
    return &tokens.get(*current).unwrap();
}

// fn next_token_type<'a>(tokens: &'a Vec<Token>, current: &'a mut usize) -> &'a TokenType {
//     let next_t = &tokens.get(*current + 1).unwrap();
//     return &next_t.token_type;
// }

fn parse_switch_statement(source: &String, tokens: &Vec<Token>, current: &mut usize) -> Result<Expr, String> {
    let t = tokens.get(*current).unwrap();
    let initial_current = *current;
    *current = *current + 1;
    let mut params : Vec<Expr> = Vec::new();
    let prim = match primary(&source, &tokens, current) {
        Ok(to_ret) => to_ret,
        Err(err_str) => return Err(err_str),
    };
    params.push(prim);

    if &TokenType::LeftBrace != current_token_type(&tokens, current) {
        return Err(format!("{}:{}: parse error: Expected '{{' after primary expression in 'switch' statement.", t.line, t.col));
    }
    *current = *current + 1;

    let mut end_found = false;
    while *current < tokens.len() && !end_found {
        let mut next_t = tokens.get(*current).unwrap();
        if next_t.token_type != TokenType::Case {
            return Err(format!("{}:{}: parse error: Expected 'case' in switch, found {:?}", next_t.line, next_t.col, next_t.token_type));
        }

        *current = *current + 1;
        next_t = tokens.get(*current).unwrap();
        if next_t.token_type == TokenType::Colon {
            params.push(Expr{node_type: NodeType::DefaultCase, token_index: *current, params: Vec::new()});
        } else {
            let prim = match primary(&source, &tokens, current) {
                Ok(to_ret) => to_ret,
                Err(err_str) => return Err(err_str),
            };
            params.push(prim);
        }

        next_t = tokens.get(*current).unwrap();
        if next_t.token_type != TokenType::Colon {
            return Err(format!("{}:{}: parse error: Expected ':' case <primary_expr> in switch, found {:?}",
                               next_t.line, next_t.col, next_t.token_type));
        }

        *current = *current + 1;
        next_t = tokens.get(*current).unwrap();
        let mut body_params : Vec<Expr> = Vec::new();
        while *current < tokens.len() {
            if next_t.token_type == TokenType::RightBrace {
                params.push(Expr{node_type: NodeType::Body, token_index: *current, params: body_params});
                end_found = true;
                *current = *current + 1;
                break;
            }
            if next_t.token_type == TokenType::Case {
                params.push(Expr{node_type: NodeType::Body, token_index: *current, params: body_params});
                break;
            }
            let stmt = match parse_statement(&source, &tokens, current) {
                Ok(statement) => statement,
                Err(error_string) => return Err(error_string),
            };
            body_params.push(stmt);
            next_t = tokens.get(*current).unwrap();
        }
    }
    if end_found {
        return Ok(Expr { node_type: NodeType::Switch, token_index: initial_current, params: params})
    }
    return Err(format!("parse error: Expected '}}' to end switch."));
}

fn parse_declaration(source: &String, tokens: &Vec<Token>, current: &mut usize, is_mut: bool, explicit_type: &str) -> Result<Expr, String> {
    let t = tokens.get(*current).unwrap();
    let decl_name = get_token_str(source, t);
    let initial_current = *current;
    *current = *current + 3; // skip identifier, colon and equal
    if explicit_type != INFER_TYPE {
        *current = *current + 1; // skip type identifier
    }
    let mut params : Vec<Expr> = Vec::new();
    let prim = match primary(&source, &tokens, current) {
        Ok(to_ret) => to_ret,
        Err(err_str) => return Err(err_str),
    };
    params.push(prim);
    let explicit_value_type = str_to_value_type(explicit_type);
    let decl = Declaration{name: decl_name.to_string(), value_type: explicit_value_type, is_mut: is_mut};
    Ok(Expr { node_type: NodeType::Declaration(decl), token_index: initial_current, params: params})
}

fn parse_mut_declaration(source: &String, tokens: &Vec<Token>, current: &mut usize) -> Result<Expr, String> {
    let t = tokens.get(*current).unwrap();
    let mut next_t = tokens.get(*current + 1).unwrap();
    let mut next_token_type = &next_t.token_type;
    if next_token_type != &TokenType::Identifier {
        return Err(format!("{}:{}: parse error: Expected identifier after 'mut', found {:?}.", t.line, t.col, next_token_type));
    }
    let identifier = get_token_str(source, next_t);
    *current = *current + 1;
    next_t = tokens.get(*current + 1).unwrap();
    next_token_type = &next_t.token_type;
    if next_token_type != &TokenType::Colon {
        return Err(format!("{}:{}: parse error: Expected ':' after 'mut {}', found {:?}.", t.line, t.col, identifier, next_token_type));
    }
    let next_next_t = tokens.get(*current + 2).unwrap();
    let next_next_token_type = &next_next_t.token_type;
    match next_next_token_type {
        TokenType::Identifier => {
            let type_name = get_token_str(source, next_next_t);
            return parse_declaration(&source, &tokens, current, true, type_name)
        }
        TokenType::Equal => {
            return parse_declaration(&source, &tokens, current, true, INFER_TYPE)
        },
        _ => {
            Err(format!("{}:{}: parse error: Expected Type or '=' after 'mut {} :' in statement, found {:?}.", t.line, t.col, identifier, next_next_token_type))
        },
    }
}

fn parse_statement(source: &String, tokens: &Vec<Token>, current: &mut usize) -> Result<Expr, String> {
    let t = tokens.get(*current).unwrap();
    match &t.token_type {
        TokenType::For => {
            return Err(format!("{}:{}: parse error: Suggestion: use 'while' for now.\nExplanation: keyword 'for' is not supported yet,", t.line, t.col));
        },
        TokenType::Return => return return_statement(&source, &tokens, current),
        TokenType::If => return if_statement(&source, &tokens, current),
        TokenType::While => return while_statement(&source, &tokens, current),
        TokenType::Switch => return parse_switch_statement(&source, &tokens, current),
        TokenType::Mut => return parse_mut_declaration(&source, &tokens, current),
        TokenType::Identifier => {
            let next_t = tokens.get(*current + 1).unwrap();
            let next_token_type = &next_t.token_type;
            match next_token_type {
                TokenType::LeftParen => {
                    parse_func_call(&source, &tokens, current)
                },
                TokenType::Dot => {
                    Err(format!("{}:{}: parse error: '.' not allowed after the first identifier in a statement yet.", t.line, t.col))
                },
                TokenType::Equal => {
                    return parse_assignment(&source, &tokens, current)
                },
                TokenType::Colon => {
                    let next_next_t = tokens.get(*current + 2).unwrap();
                    let next_next_token_type = &next_next_t.token_type;
                    let identifier = get_token_str(source, t);
                    match next_next_token_type {
                        TokenType::Identifier => {
                            let type_name = get_token_str(source, next_next_t);
                            return parse_declaration(&source, &tokens, current, false, type_name)
                        }
                        TokenType::Equal => {
                            return parse_declaration(&source, &tokens, current, false, INFER_TYPE)
                        },
                        _ => {
                            Err(format!("{}:{}: parse error: Expected Type or '=' after '{} :' in statement, found {:?}.", t.line, t.col, identifier, next_next_token_type))
                        },
                    }

                },
                _ => {
                    Err(format!("{}:{}: parse error: Expected '(', ':' or '=' after identifier in statement, found {:?}.", t.line, t.col, next_token_type))
                },
            }
        },
        // TokenType::For => {
        //     return Err(format!("{}:{}: parse warning: keyword 'for' is not supported yet.\nSuggestion: don't use ';', no need for 'for', use while in the meantime",
        //                        t.line, t.col));
        // },
        TokenType::Semicolon => {
            *current = *current + 1;
            return parse_statement(&source, &tokens, current);
        },
        TokenType::DoubleSemicolon => {
            // TODO turn some errors into warnings
            return Err(format!("{}:{}: parse error: Suggestion: don't use ';', Explanation: no need for Double Semicolon, try 'if true' instead.\n",
                               t.line, t.col));
        },
        _ => {
            Err(format!("{}:{}: parse error: Expected statement, found {:?}.", t.line, t.col, t.token_type))
        },
    }
}

fn parse_body(end_token : TokenType, source: &String, tokens: &Vec<Token>, current: &mut usize) -> Result<Expr, String> {
    let initial_current: usize = *current;
    let mut params : Vec<Expr> = Vec::new();
    let mut end_found = false;
    while *current < tokens.len() && !end_found {
        // println!("next token: {:?}, {:?}", tokens.get(*current).unwrap().token_type, end_token);
        if tokens.get(*current).unwrap().token_type == end_token {
            end_found = true;
            break;
        }
        let stmt = match parse_statement(&source, &tokens, current) {
            Ok(statement) => statement,
            Err(error_string) => return Err(error_string),
        };
        params.push(stmt);
    }
    if end_found {
        return Ok(Expr { node_type: NodeType::Body, token_index: initial_current, params: params})
    }
    return Err(format!("parse error: Expected {:?} to end body.", end_token));
}

fn parse_tokens(source: &String, tokens: &Vec<Token>, current: &mut usize) -> Result<Expr, String> {

    let e: Expr = match parse_body(TokenType::Eof, &source, tokens, current) {
        Ok(expr) => expr,
        Err(error_string) => return Err(error_string),
    };
    *current = *current + 1; // Add one for the EOF

    println!("Total tokens parsed: {}/{}", current, tokens.len());
    let mut i = *current;
    let mut unparsed_tokens = 0;
    if i < tokens.len() {
        unparsed_tokens = tokens.len() - i;
    }
    while i < tokens.len() {
        let t = tokens.get(i).unwrap();
        println!("Token: {:?}", t);
        i = i + 1;
    }
    if unparsed_tokens > 0 {
        return Err(format!("Total unparsed tokens: {}/{}", unparsed_tokens, tokens.len()));
    }
    return Ok(e)
}

// ---------- Context

#[derive(Debug, Clone, PartialEq)]
struct SymbolInfo {
    value_type: ValueType,
    is_mut: bool,
}

#[derive(Debug, Clone, PartialEq)]
struct EnumVal {
    enum_type: String,
    enum_name: String,
    // enum_unsigned_val: String,
    // extra_Val: Option<Anything>,
}

#[derive(Clone)]
struct Context {
    mode: ModeDef,
    symbols: HashMap<String, SymbolInfo>,
    funcs: HashMap<String, SFuncDef>,
    procs: HashMap<String, SFuncDef>,
    macros: HashMap<String, SFuncDef>,
    enum_defs: HashMap<String, SEnumDef>,
    enums: HashMap<String, EnumVal>,
    struct_defs: HashMap<String, Expr>,
    bools: HashMap<String, bool>,
    i64s: HashMap<String, i64>,
    strings: HashMap<String, String>,
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
        "btoi" => true, // necessary for branchless arithmetics
        "btoa" => true,
        "itoa" => true,
        "str_eq" => true, // TODO implement
        _ => false,
    }
}

fn is_core_proc(proc_name: &str) -> bool {
    match proc_name {
        "exit" => true,
        "print" => true,
        "println" => true,
        // TODO implement more core procs in rust:
        "readfile" => true,
        "writefile" => true,
        "import" => true,
        "eval_to_str" => true,
        "eval_to_ast_str" => true,
        "eval_to_expr" => true,
        _ => false,
    }
}

fn start_context(mode: ModeDef) -> Context {
    let mut context: Context = Context {
        mode: mode,
        symbols: HashMap::new(),
        funcs: HashMap::new(),
        procs: HashMap::new(),
        macros: HashMap::new(),
        enum_defs: HashMap::new(),
        enums: HashMap::new(),
        struct_defs: HashMap::new(),
        bools: HashMap::new(),
        i64s: HashMap::new(),
        strings: HashMap::new(),
    };

    let body : Vec<Expr> = Vec::new();
    let return_types_none : Vec<ValueType> = Vec::new();

    let mut args_print : Vec<Declaration> = Vec::new();
    args_print.push(Declaration{name: "args".to_string(), value_type: ValueType::TMulti(Box::new(ValueType::TString)), is_mut: false});
    let func_def_print = SFuncDef{args: args_print, returns: return_types_none.clone(), body: body.clone()};
    context.procs.insert("print".to_string(), func_def_print.clone());
    context.procs.insert("println".to_string(), func_def_print);

    let mut args_single_i64 : Vec<Declaration> = Vec::new();
    args_single_i64.push(Declaration{name: "a".to_string(), value_type: ValueType::TI64, is_mut: false});
    let func_def_exit = SFuncDef{args: args_single_i64, returns: return_types_none, body: body.clone()};
    context.procs.insert("exit".to_string(), func_def_exit);

    let mut args_and_or : Vec<Declaration> = Vec::new();
    args_and_or.push(Declaration{name: "args".to_string(), value_type: ValueType::TMulti(Box::new(ValueType::TBool)), is_mut: false});
    let mut return_type_bool : Vec<ValueType> = Vec::new();
    return_type_bool.push(ValueType::TBool);
    let func_def_and_or = SFuncDef{args: args_and_or, returns: return_type_bool.clone(), body: body.clone()};
    context.funcs.insert("and".to_string(), func_def_and_or.clone());
    context.funcs.insert("or".to_string(), func_def_and_or);

    let mut args_single_bool : Vec<Declaration> = Vec::new();
    args_single_bool.push(
        Declaration{name: "a".to_string(), value_type: ValueType::TBool, is_mut: false});
    let func_def_not = SFuncDef{args: args_single_bool.clone(), returns: return_type_bool.clone(), body: body.clone()};
    context.funcs.insert("not".to_string(), func_def_not);

    let mut args_bin_i64 : Vec<Declaration> = Vec::new();
    args_bin_i64.push(Declaration{name: "a".to_string(), value_type: ValueType::TI64, is_mut: false});
    args_bin_i64.push(Declaration{name: "b".to_string(), value_type: ValueType::TI64, is_mut: false});

    let func_def_bin_i64_to_bool = SFuncDef{args: args_bin_i64.clone(), returns: return_type_bool.clone(), body: body.clone()};
    context.funcs.insert("eq".to_string(), func_def_bin_i64_to_bool.clone());
    context.funcs.insert("lt".to_string(), func_def_bin_i64_to_bool.clone());
    context.funcs.insert("lteq".to_string(), func_def_bin_i64_to_bool.clone());
    context.funcs.insert("gt".to_string(), func_def_bin_i64_to_bool.clone());
    context.funcs.insert("gteq".to_string(), func_def_bin_i64_to_bool.clone());

    let mut return_type_i64 : Vec<ValueType> = Vec::new();
    return_type_i64.push(ValueType::TI64);
    let func_def_bin_i64_to_i64 = SFuncDef{args: args_bin_i64, returns: return_type_i64.clone(), body: body.clone()};
    context.funcs.insert("add".to_string(), func_def_bin_i64_to_i64.clone());
    context.funcs.insert("sub".to_string(), func_def_bin_i64_to_i64.clone());
    context.funcs.insert("mul".to_string(), func_def_bin_i64_to_i64.clone());
    context.funcs.insert("div".to_string(), func_def_bin_i64_to_i64.clone());

    let mut return_type_single_str : Vec<ValueType> = Vec::new();
    return_type_single_str.push(ValueType::TString);
    let func_def_btoa = SFuncDef{args: args_single_bool, returns: return_type_single_str.clone(), body: body.clone()};
    context.funcs.insert("btoa".to_string(), func_def_btoa);

    let mut args_single_i64 : Vec<Declaration> = Vec::new();
    args_single_i64.push(Declaration{name: "a".to_string(), value_type: ValueType::TI64, is_mut: false});
    let func_def_itoa = SFuncDef{args: args_single_i64, returns: return_type_single_str.clone(), body: body.clone()};
    context.funcs.insert("itoa".to_string(), func_def_itoa);

    context
}

fn value_type_func_proc(t: &Token, name: &str, func_def: &SFuncDef) -> Result<ValueType, String> {
    match func_def.returns.len() {
        0 => {
            return Err(format!("{}:{}: {} error: func '{}' does not return anything", t.line, t.col, LANG_NAME, name))
        },
        1 => {
            match func_def.returns.get(0).unwrap() {
                ValueType::TBool => Ok(ValueType::TBool),
                ValueType::TI64 => Ok(ValueType::TI64),
                ValueType::TString => Ok(ValueType::TString),
                ValueType::TCustom(type_str) => Ok(ValueType::TCustom(type_str.to_string())), // TODO find a better way
                _ => return Err(format!("{}:{}: {} error: func '{}' returns unsupported type {:?}",
                                        t.line, t.col, LANG_NAME, name, func_def.returns.get(0).unwrap())),
            }
        },
        _ => {
            return Err(format!("{}:{}: {} error: func '{}' returns multiple values, but that's not implemented yet.", t.line, t.col, LANG_NAME, name));
        },
    }
}

fn get_fcall_value_type(context: &Context, tokens: &Vec<Token>, name: &str, e: &Expr) -> Result<ValueType, String> {
    let t = tokens.get(e.token_index).unwrap();
    if context.funcs.contains_key(name) {
        value_type_func_proc(t, name, &context.funcs.get(name).unwrap())
    } else if context.procs.contains_key(name) {
        value_type_func_proc(t, name, &context.procs.get(name).unwrap())
    } else if is_defined_symbol(&context, name) {
        return Err(format!("{}:{}: type error: Cannot call '{}', it is not a function/procedure", t.line, t.col, name));
    } else {
        return Err(format!("{}:{}: type error: Undefined function/procedure '{}'", t.line, t.col, name));
    }
}

fn get_value_type(context: &Context, tokens: &Vec<Token>, e: &Expr) -> Result<ValueType, String> {
    let t = tokens.get(e.token_index).unwrap();
    match &e.node_type {
        NodeType::LBool(_) => Ok(ValueType::TBool),
        NodeType::LI64(_) => Ok(ValueType::TI64),
        NodeType::LString(_) => Ok(ValueType::TString),
        NodeType::LList => Ok(ValueType::TList),
        NodeType::FuncDef(_) => Ok(ValueType::TFunc),
        NodeType::ProcDef(_) => Ok(ValueType::TProc),
        NodeType::EnumDef(_) => Ok(ValueType::TEnumDef),
        NodeType::StructDef => Ok(ValueType::TStructDef),
        NodeType::FCall(name) => get_fcall_value_type(&context, &tokens, &name, &e),
        NodeType::Identifier(name) => {
            let symbol_info = match context.symbols.get(name) {
                Some(symbol_info_m) => {
                    symbol_info_m
                },
                None => {
                    return Err(format!("{}:{}: type error: Undefined symbol '{}'", t.line, t.col, name));
                }
            };
            if e.params.len() == 0 {
                return Ok(symbol_info.value_type.clone());
            }
            let member_str = match &e.params.get(0).unwrap().node_type {
                NodeType::Identifier(member_name) => member_name,
                node_type => return Err(format!("{}:{}: {} error: identifiers can only contain identifiers, found {:?}.",
                                                LANG_NAME, t.line, t.col, node_type)),
            };

            match symbol_info.value_type {
                ValueType::TStructDef => {
                    match context.struct_defs.get(name) {
                        Some(_struct_def) => {
                            return Err(format!("{}:{}: type error: struct '{}' has no const (static) member '{}'", t.line, t.col, name, member_str))
                        },
                        None => {
                            return Err(format!("{}:{}: {} error: Undefined struct '{}'", LANG_NAME, t.line, t.col, name));
                        },
                    }
                },
                ValueType::TEnumDef => {
                    match context.enum_defs.get(name) {
                        Some(enum_def) => {
                            if enum_def.enum_map.contains_key(member_str) {
                                if e.params.len() > 1 {
                                    let extra_member_str = match &e.params.get(1).unwrap().node_type {
                                        NodeType::Identifier(member_name) => member_name,
                                        node_type => return Err(format!("{}:{}: {} error: identifiers can only contain identifiers, found {:?}.",
                                                                        t.line, t.col, LANG_NAME, node_type)),
                                    };
                                    return Err(format!("{}:{}: type error: Suggestion: remove '.{}' after '{}.{}'\nExplanation: enum value '{}.{}' cannot have members",
                                                       t.line, t.col, extra_member_str, name, member_str, name, member_str));
                                }
                                return Ok(ValueType::TCustom(name.to_string()));
                            }
                            return Err(format!("{}:{}: type error: enum '{}' has no value '{}'", t.line, t.col, name, member_str));
                        }
                        None => {
                            return Err(format!("{}:{}: {} error: Undefined enum '{}'", t.line, t.col, LANG_NAME, name));
                        }
                    }
                },
                _ => {
                    return Err(format!("{}:{}: type error: {:?} '{}' can't have members, '{}' is not a member",
                                       t.line, t.col, symbol_info.value_type, name, member_str))
                },
            }
        },
        node_type => return Err(format!("{}:{}: {} error: get_value_type() not implement for {:?} yet.", t.line, t.col, LANG_NAME, node_type)),
    }
}

fn init_context(context: &mut Context, source: &String, tokens: &Vec<Token>, e: &Expr) -> Vec<String> {
    let mut errors : Vec<String> = Vec::new();
    match &e.node_type {
        NodeType::Body => {
            for se in &e.params {
                let mut stmt_context_errors = init_context(context, &source, &tokens, &se);
                errors.append(&mut stmt_context_errors);
            }
        },
        NodeType::FCall(_) => { },
        NodeType::Declaration(decl) => {
            let t = tokens.get(e.token_index).unwrap();
            if is_defined_symbol(&context, &decl.name) {
                errors.push(format!("{}:{}: compiler error: '{}' already declared.", t.line, t.col, decl.name));
            }
            assert!(e.params.len() == 1, "{} error: in init_context, while declaring {}, declarations must take exactly one value.", LANG_NAME, decl.name);
            let inner_e = e.params.get(0).unwrap();
            let value_type = match get_value_type(&context, &tokens, &inner_e) {
                Ok(val_type) => val_type,
                Err(error_string) => {
                    errors.push(error_string);
                    return errors;
                },
            };
            if decl.value_type != str_to_value_type(INFER_TYPE) {
                if value_type != decl.value_type {
                    errors.push(format!("{}:{}: type error: '{}' declared of type {} but initialized to type {:?}.", t.line, t.col, decl.name, value_type_to_str(&decl.value_type), value_type_to_str(&value_type)));
                }
            }
            match value_type {
                ValueType::TFunc => {
                    match &inner_e.node_type {
                        NodeType::FuncDef(func_def) => {
                            context.symbols.insert(decl.name.to_string(), SymbolInfo{value_type: value_type.clone(), is_mut: decl.is_mut});
                            context.funcs.insert(decl.name.to_string(), func_def.clone());
                        },
                        _ => {
                            errors.push(format!("{}:{}: {} error: funcs should have definitions", t.line, t.col, LANG_NAME));
                            return errors;
                        },
                    }
                },
                ValueType::TProc => {
                    match &inner_e.node_type {
                        NodeType::ProcDef(func_def) => {
                            context.symbols.insert(decl.name.to_string(), SymbolInfo{value_type: value_type.clone(), is_mut: decl.is_mut});
                            context.procs.insert(decl.name.to_string(), func_def.clone());
                        },
                        _ => {
                            errors.push(format!("{}:{}: {} error: procs should have definitions", t.line, t.col, LANG_NAME));
                            return errors;
                        },
                    }
                },
                ValueType::TMacro => {
                    match &inner_e.node_type {
                        NodeType::ProcDef(func_def) => {
                            context.symbols.insert(decl.name.to_string(), SymbolInfo{value_type: value_type.clone(), is_mut: decl.is_mut});
                            context.macros.insert(decl.name.to_string(), func_def.clone());
                        },
                        _ => {
                            errors.push(format!("{}:{}: {} error: procs should have definitions", t.line, t.col, LANG_NAME));
                            return errors;
                        },
                    }
                },

                ValueType::TEnumDef => {
                    assert!(inner_e.params.len() == 0, "{} error: while declaring {}: enum declarations don't have any parameters in the tree.", LANG_NAME,
                            decl.name);
                    match &inner_e.node_type {
                        NodeType::EnumDef(enum_def) => {
                            context.symbols.insert(decl.name.to_string(), SymbolInfo{value_type: value_type.clone(), is_mut: decl.is_mut});
                            context.enum_defs.insert(decl.name.to_string(), enum_def.clone());
                        },
                        _ => {
                            errors.push(format!("{}:{}: {} error: enums should have definitions.", t.line, t.col, LANG_NAME));
                            return errors;
                        },
                    }
                },
                ValueType::TStructDef => {
                    assert!(inner_e.params.len() == 1, "{} error: while declaring {}, struct declarations must take exactly one body.", LANG_NAME,
                            decl.name);
                    let inner_e = e.params.get(0).unwrap();
                    context.symbols.insert(decl.name.to_string(), SymbolInfo{value_type: value_type.clone(), is_mut: decl.is_mut});
                    context.struct_defs.insert(decl.name.to_string(), inner_e.clone());
                },
                ValueType::TBool | ValueType::TI64 | ValueType::TString | ValueType::TList |
                ValueType::TMulti(_) | ValueType::TCustom(_) | ValueType::ToInferType => {
                    context.symbols.insert(decl.name.to_string(), SymbolInfo{value_type: value_type.clone(), is_mut: decl.is_mut});
                },
            }
        }
        _ => {
            if !context.mode.allows_base_anything {
            let t = tokens.get(e.token_index).unwrap();
                if context.mode.allows_base_calls {
                    errors.push(format!("{}:{}: mode '{}' allows only declarations and calls in the root context, found {:?}.",
                                        t.line, t.col, context.mode.name, e.node_type));
                } else {
                    errors.push(format!("{}:{}: mode '{}' allows only declarations in the root context, found {:?}.",
                                        t.line, t.col, context.mode.name, e.node_type));
                }
            }
        },
    }
    errors
}

// ---------- Type checking

fn is_defined_func_proc(context: &Context, name: &str) -> bool {
    context.funcs.contains_key(name) || context.procs.contains_key(name)
}

fn is_defined_symbol(context: &Context, name: &str) -> bool {
    is_defined_func_proc(&context, name) || context.symbols.contains_key(name)
}

fn does_func_return_bool(context: &Context, name: &str) -> bool {
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

fn is_expr_calling_procs(context: &Context, source: &String,  tokens: &Vec<Token>, e: &Expr) -> bool {
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
            // TODO default values could try to call procs
            false
        },
        NodeType::EnumDef(_) => {
            false
        },
        NodeType::LBool(_) => false,
        NodeType::LI64(_) => false,
        NodeType::LString(_) => false,
        NodeType::DefaultCase => false,
        NodeType::LList => false,
        NodeType::Identifier(_) => false,
        NodeType::FCall(call_name) => {
            context.symbols.contains_key(call_name) && context.symbols.get(call_name).unwrap().value_type == ValueType::TProc
        },
        NodeType::Declaration(decl) => {
            assert!(e.params.len() != 1, "{} error: while declaring {}, declarations must take exactly one value.", LANG_NAME, decl.name);
            is_expr_calling_procs(&context, &source, &tokens, &e.params.get(0).unwrap())
        },
        NodeType::Assignment(var_name) => {
            assert!(e.params.len() == 1, "{} error: while assigning {}, assignments must take exactly one value, not {}.", LANG_NAME, var_name, e.params.len());
            is_expr_calling_procs(&context, &source, &tokens, &e.params.get(0).unwrap())
        }
        NodeType::ProcDef(func_def) | NodeType::FuncDef(func_def) => {
            for it_e in &func_def.body {
                if is_expr_calling_procs(&context, &source, &tokens, &it_e) {
                    return true;
                }
            }
            false
        },
        NodeType::If | NodeType::While | NodeType::Switch | NodeType::Return => {
            for it_e in &e.params {
                if is_expr_calling_procs(&context, &source, &tokens, &it_e) {
                    return true;
                }
            }
            false
        },
    }
}

fn func_proc_has_multi_arg(func_def: &SFuncDef) -> bool {
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

fn check_func_proc_types(func_def: &SFuncDef, mut context: &mut Context, source: &String, tokens: &Vec<Token>, t: &Token) -> Vec<String> {
    let mut errors : Vec<String> = Vec::new();
    for arg in &func_def.args {
        match &arg.value_type {
            ValueType::TCustom(ref custom_type_name) => {
                if !context.symbols.contains_key(custom_type_name) {
                    errors.push(format!("{}:{}: type error: Argument '{}' is of undefined type {}.", t.line, t.col, &arg.name, &custom_type_name));
                }
                let _custom_symbol = context.symbols.get(custom_type_name).unwrap();
                // TODO check more type stuff
            },
            _ => {},
        }
        context.symbols.insert(arg.name.clone(), SymbolInfo{value_type: arg.value_type.clone(), is_mut: false});
    }
    for p in func_def.body.iter() {
        errors.append(&mut check_types(&mut context, &source, &tokens, &p));
    }
    errors
}

fn check_types(mut context: &mut Context, source: &String, tokens: &Vec<Token>, e: &Expr) -> Vec<String> {
    let mut errors : Vec<String> = Vec::new();
    let t = tokens.get(e.token_index).unwrap();

    if context.mode.needs_main_proc {
        if !context.symbols.contains_key("main") {
            errors.push(format!("{}:{}: mode {} requires 'main' to be defined as a proc.",
                                t.line, t.col, context.mode.name));
            return errors;
        }
        let main_type : ValueType = match context.symbols.get("main") {
            Some(main_type_) => main_type_.value_type.clone(),
            None => panic!("main proc not provided in mode '{}'", context.mode.name),
            // ValueType::TProc => ValueType::TProc,
        };
        if main_type != ValueType::TProc {
            errors.push(format!("{}:{}: mode {} requires 'main' to be defined as a proc. It was defined as a {:?} instead",
                                t.line, t.col, context.mode.name, main_type));
            return errors;
        }
    }

    match &e.node_type {
        NodeType::Body => {
            for p in e.params.iter() {
                errors.append(&mut check_types(&mut context, &source, &tokens, &p));
            }
        },
        NodeType::EnumDef(enum_def) => {
            assert!(e.params.len() == 0, "{} error: in check_types(): enum declarations don't have any parameters in the tree.", LANG_NAME);

            for (_enum_val_name, enum_opt) in &enum_def.enum_map {
                match &enum_opt {
                    None => {},
                    Some(value_type) => {
                        match value_type {
                            ValueType::TCustom(ref custom_type_name) => {
                                errors.push(format!("{}:{}: 'enum' does not support custom types yet, found custom type '{}'.",
                                                    t.line, t.col, custom_type_name));
                            },
                            _ => {},
                        }
                    },
                }
            }
        },
        NodeType::StructDef => {
            assert!(e.params.len() == 1, "{} error: in check_types(): struct declarations must take exactly one param.", LANG_NAME);
            let inner_e = e.params.get(0).unwrap();
            assert!(inner_e.node_type == NodeType::Body, "{} error: in check_types(): struct declarations must take exactly one body.", LANG_NAME);
            for p in inner_e.params.iter() {
                match &p.node_type {
                    NodeType::Declaration(_) => {}
                    node_type => {
                        errors.push(format!("{}:{}: 'struct' can only include declarations, found {:?}.", t.line, t.col, node_type));
                    }
                }
                errors.append(&mut check_types(&mut context, &source, &tokens, &p));
            }
        },
        NodeType::If => {
            assert!(e.params.len() == 2 || e.params.len() == 3, "{} error: if nodes must have 2 or 3 parameters.", LANG_NAME);
            let inner_e = e.params.get(0).unwrap();
            let value_type = match get_value_type(&context, &tokens, &inner_e) {
                Ok(val_type) => val_type,
                Err(error_string) => {
                    errors.push(error_string);
                    return errors;
                },
            };
            let first_is_condition = ValueType::TBool == value_type;
            if !first_is_condition {
                let next_t = tokens.get(inner_e.token_index).unwrap();
                errors.push(format!("{}:{}: 'if' can only accept a bool condition first, found {:?}.", next_t.line, next_t.col, &inner_e.node_type));
            }
            for p in e.params.iter() {
                errors.append(&mut check_types(&mut context, &source, &tokens, &p));
            }
        },
        NodeType::While => {
            assert!(e.params.len() == 2, "{} error: while nodes must have exactly 2 parameters.", LANG_NAME);
            let inner_e = e.params.get(0).unwrap();
            let value_type = match get_value_type(&context, &tokens, &inner_e) {
                Ok(val_type) => val_type,
                Err(error_string) => {
                    errors.push(error_string);
                    return errors;
                },
            };
            let first_is_condition = ValueType::TBool == value_type;
            if !first_is_condition {
                let next_t = tokens.get(inner_e.token_index).unwrap();
                errors.push(format!("{}:{}: 'while' can only accept a bool condition first, found {:?}.", next_t.line, next_t.col, &inner_e.node_type));
            }
            for p in e.params.iter() {
                errors.append(&mut check_types(&mut context, &source, &tokens, &p));
            }
        },
        NodeType::Switch => {
            assert!(e.params.len() >= 3, "{} error: switch nodes must have at least 3 parameters.", LANG_NAME);
            // TODO check that the type to be switch corresponds to each case
            // TODO check that there's a body param after each case
            // TODO check that all the cases are covered
            for p in e.params.iter() {
                errors.append(&mut check_types(&mut context, &source, &tokens, &p));
            }
        },
        NodeType::FCall(name) => {
            if !is_defined_func_proc(&context, &name) {
                errors.push(format!("{}:{}: Undefined function or procedure {}", t.line, t.col, name));
                return errors;
            }
            match name.as_str() {
                _ => {
                    let func_def;
                    if context.funcs.contains_key(name) {
                        func_def = context.funcs.get(name).unwrap();
                    } else if context.procs.contains_key(name) {
                        func_def = context.procs.get(name).unwrap();
                    } else {
                        errors.push(format!("{}:{}: {} error: Undefined function or procedure '{}'", t.line, t.col, LANG_NAME, name));
                        return errors;
                    }
                    let has_multi_arg = func_proc_has_multi_arg(func_def);
                    if !has_multi_arg && func_def.args.len() != e.params.len() {
                        errors.push(format!("{}:{}: Function/procedure '{}' expects {} args, but {} were provided.", t.line, t.col, name, func_def.args.len(), e.params.len()));
                    }
                    if has_multi_arg && func_def.args.len() > e.params.len() {
                        errors.push(format!("{}:{}: Function/procedure '{}' expects at least {} args, but {} were provided.", t.line, t.col, name, func_def.args.len(), e.params.len()));
                    }

                    let max_arg_def = func_def.args.len();
                    for i in 0..e.params.len() {
                        let arg = func_def.args.get(std::cmp::min(i, max_arg_def-1)).unwrap();
                        let expected_type = match &arg.value_type {
                            ValueType::TMulti(inner_type) => inner_type,
                            _ => &arg.value_type,

                        };
                        let found_type = match get_value_type(&context, &tokens, e.params.get(i).unwrap()) {
                            Ok(val_type) => val_type,
                            Err(error_string) => {
                                errors.push(error_string);
                                return errors;
                            },
                        };
                        if expected_type != &found_type {
                            if expected_type == &str_to_value_type(INFER_TYPE) {
                                errors.push(format!("{}:{}: calling func/proc '{}' declared arg {} without type, but type inference in args is not supported yet.\n Suggestion: the arg should be '{} : {},' instead of just '{},' Found type: {:?}",
                                                    t.line, t.col, name, arg.name, arg.name, value_type_to_str(&found_type), arg.name, value_type_to_str(&expected_type)));
                            } else {
                                errors.push(format!("{}:{}: calling func/proc '{}' expects {:?} for arg {}, but {:?} was provided.",
                                                    t.line, t.col, name, expected_type, arg.name, found_type));
                            }
                        }
                    }
                },
            }
        },

        NodeType::Identifier(name) => {
            if !is_defined_symbol(&context, &name) {
                errors.push(format!("{}:{}: Undefined symbol {}", t.line, t.col, name));
            }
        },

        NodeType::FuncDef(func_def) => {
            let mut function_context = context.clone();
            errors.append(&mut check_func_proc_types(&func_def, &mut function_context, &source, &tokens, &t));
            for se in &func_def.body {
                if is_expr_calling_procs(&function_context, &source, &tokens, &se) {
                    let proc_t = tokens.get(se.token_index).unwrap();
                    errors.push(format!("{}:{}: compiler error: funcs cannot call procs.", proc_t.line, proc_t.col));
                }
            }
        },
        NodeType::ProcDef(func_def) => {
            let mut function_context = context.clone();
            errors.append(&mut check_func_proc_types(&func_def, &mut function_context, &source, &tokens, &t));
        },

        NodeType::Declaration(decl) => {
            assert!(e.params.len() == 1, "{} error: in declaration of {} declaration nodes must exactly 1 parameter.", LANG_NAME, decl.name);
            let inner_e = e.params.get(0).unwrap();
            if !context.symbols.contains_key(&decl.name) {
                let mut value_type = decl.value_type.clone();
                if value_type == ValueType::ToInferType {
                    value_type = match get_value_type(&context, &tokens, &inner_e) {
                        Ok(val_type) => val_type,
                        Err(error_string) => {
                            errors.push(error_string);
                            return errors;
                        },
                    };
                }
                context.symbols.insert(decl.name.to_string(), SymbolInfo{value_type: value_type.clone(), is_mut: decl.is_mut});
                match value_type {
                    ValueType::ToInferType => {
                        errors.push(format!("{}:{} {} error: Cannot infer the declaration type of {}", t.line, t.col, LANG_NAME, decl.name));
                        return errors;
                    },
                    ValueType::TFunc | ValueType::TProc => {
                        match &inner_e.node_type {
                            NodeType::FuncDef(func_def) => {
                                context.funcs.insert(decl.name.clone(), func_def.clone());
                            },
                            NodeType::ProcDef(func_def) => {
                                context.procs.insert(decl.name.clone(), func_def.clone());
                            },
                            _ => {
                                errors.push(format!("{}:{} {} error: funcs/procs should have definitions", t.line, t.col, LANG_NAME));
                                return errors;
                            },
                        }
                    },
                    _ => {},
                }
            }
            errors.append(&mut check_types(&mut context, &source, &tokens, &inner_e));
        },

        NodeType::Assignment(var_name) => {
            assert!(e.params.len() == 1, "{} error: in assignment to {}, assignments must take exactly one value, not {}.", LANG_NAME, var_name, e.params.len());
            if is_core_func(&var_name) {
                errors.push(format!("{}:{}: compiler error: Core function '{}' cannot be assigned to.", t.line, t.col, var_name));
            } else if is_core_proc(&var_name) {
                errors.push(format!("{}:{}: compiler error: Core procedure '{}' cannot be assigned to.", t.line, t.col, var_name));
            } else if context.funcs.contains_key(var_name)  {
                errors.push(format!("{}:{}: compiler error: User defined function '{}' cannot be assigned to.", t.line, t.col, var_name));
            } else if context.procs.contains_key(var_name)  {
                errors.push(format!("{}:{}: compiler error: User defined procedure '{}' cannot be assigned to.", t.line, t.col, var_name));
            } else if context.symbols.contains_key(var_name) {
                let symbol_info = context.symbols.get(var_name).unwrap();
                if !symbol_info.is_mut {
                    errors.push(format!("{}:{}: compiler error: Cannot assign to constant '{}', Suggestion: declare it as 'mut'.", t.line, t.col, var_name));
                }
            } else {
                errors.push(format!("{}:{}: compiler error: Suggestion: try changing '{} =' for '{} :='\nExplanation: Cannot assign to undefined symbol '{}'.",
                       t.line, t.col, var_name, var_name, var_name));
            }
            errors.append(&mut check_types(&mut context, &source, &tokens, &e.params.get(0).unwrap()));
        },
        NodeType::Return => {
            assert!(e.params.len() == 1, "{} error: return nodes must exactly 1 parameter.", LANG_NAME);
            errors.append(&mut check_types(&mut context, &source, &tokens, &e.params.get(0).unwrap()));
        },
        NodeType::LI64(_) | NodeType::LString(_) | NodeType::LBool(_) | NodeType::DefaultCase | NodeType::LList => {},
    }
    errors
}

// ---------- eval repl interpreter

fn eval_to_bool(mut context: &mut Context, source: &String, tokens: &Vec<Token>, e: &Expr) -> bool {

    match &e.node_type {
        NodeType::LBool(b_value) => *b_value,
        NodeType::FCall(f_name) => {
            if does_func_return_bool(&context, f_name) {
                lbool_in_string_to_bool(eval_func_proc_call(f_name, &mut context, &source, &tokens, &e).as_str())
            } else {
                panic!("{} error: Function '{}' does not return bool. This should have been caught in the compile phase.\n", LANG_NAME, f_name);
            }
        },
        NodeType::Identifier(name) => {
            if context.bools.contains_key(name) {
                match context.bools.get(name) {
                    Some(bool_value) => bool_value.clone(),
                    None => {
                        panic!("{} error: Undefined boolean symbol '{}'. This should have been caught in the compile phase.", LANG_NAME, name)
                    }
                }
            } else {
                panic!("{} error: The only types that can be evaluated to bool are currently 'LBool', 'FCall' and 'Identifier'", LANG_NAME);
            }
        },
        node_type => panic!("{} error: The only types that can be evaluated to bool are currently 'LBool', 'FCall' and 'Identifier'. Found '{:?}'", LANG_NAME, node_type),
    }
}

// ---------- core funcs implementations for eval

fn eval_core_func_and(mut context: &mut Context, source: &String, tokens: &Vec<Token>, e: &Expr) -> String {
    let mut truthfulness = true;
    for i in &e.params {
        truthfulness = truthfulness && eval_to_bool(&mut context, &source, &tokens, &i);
    }
    truthfulness.to_string()
}

fn eval_core_func_or(mut context: &mut Context, source: &String, tokens: &Vec<Token>, e: &Expr) -> String {
    let mut truthfulness = false;
    for i in &e.params {
        truthfulness = truthfulness || eval_to_bool(&mut context, &source, &tokens, &i);
    }
    truthfulness.to_string()
}

fn eval_core_func_not(mut context: &mut Context, source: &String, tokens: &Vec<Token>, e: &Expr) -> String {
    assert!(e.params.len() == 1, "{} Error: Core func 'not' only takes 1 argument. This should never happen.", LANG_NAME);
    (!eval_to_bool(&mut context, &source, &tokens, &e.params.get(0).unwrap())).to_string()
}

fn eval_core_func_eq(mut context: &mut Context, source: &String, tokens: &Vec<Token>, e: &Expr) -> String {
    assert!(e.params.len() == 2, "{} Error: Core func 'eq' takes exactly 2 arguments. This should never happen.", LANG_NAME);
    let a = &eval_expr(&mut context, &source, &tokens, e.params.get(0).unwrap()).parse::<i64>().unwrap();
    let b = &eval_expr(&mut context, &source, &tokens, e.params.get(1).unwrap()).parse::<i64>().unwrap();
    (a == b).to_string()
}

fn eval_core_func_lt(mut context: &mut Context, source: &String, tokens: &Vec<Token>, e: &Expr) -> String {
    assert!(e.params.len() == 2, "{} Error: Core func 'eq' takes exactly 2 arguments. This should never happen.", LANG_NAME);
    let a = &eval_expr(&mut context, &source, &tokens, e.params.get(0).unwrap()).parse::<i64>().unwrap();
    let b = &eval_expr(&mut context, &source, &tokens, e.params.get(1).unwrap()).parse::<i64>().unwrap();
    (a < b).to_string()
}

fn eval_core_func_lteq(mut context: &mut Context, source: &String, tokens: &Vec<Token>, e: &Expr) -> String {
    assert!(e.params.len() == 2, "{} Error: Core func 'eq' takes exactly 2 arguments. This should never happen.", LANG_NAME);
    let a = &eval_expr(&mut context, &source, &tokens, e.params.get(0).unwrap()).parse::<i64>().unwrap();
    let b = &eval_expr(&mut context, &source, &tokens, e.params.get(1).unwrap()).parse::<i64>().unwrap();
    (a <= b).to_string()
}

fn eval_core_func_gt(mut context: &mut Context, source: &String, tokens: &Vec<Token>, e: &Expr) -> String {
    assert!(e.params.len() == 2, "{} Error: Core func 'eq' takes exactly 2 arguments. This should never happen.", LANG_NAME);
    let a = &eval_expr(&mut context, &source, &tokens, e.params.get(0).unwrap()).parse::<i64>().unwrap();
    let b = &eval_expr(&mut context, &source, &tokens, e.params.get(1).unwrap()).parse::<i64>().unwrap();
    (a > b).to_string()
}

fn eval_core_func_gteq(mut context: &mut Context, source: &String, tokens: &Vec<Token>, e: &Expr) -> String {
    assert!(e.params.len() == 2, "{} Error: Core func 'eq' takes exactly 2 arguments. This should never happen.", LANG_NAME);
    let a = &eval_expr(&mut context, &source, &tokens, e.params.get(0).unwrap()).parse::<i64>().unwrap();
    let b = &eval_expr(&mut context, &source, &tokens, e.params.get(1).unwrap()).parse::<i64>().unwrap();
    (a >= b).to_string()
}

fn eval_core_func_add(mut context: &mut Context, source: &String, tokens: &Vec<Token>, e: &Expr) -> String {
    assert!(e.params.len() == 2, "{} Error: Core func 'eq' takes exactly 2 arguments. This should never happen.", LANG_NAME);
    let a = &eval_expr(&mut context, &source, &tokens, e.params.get(0).unwrap()).parse::<i64>().unwrap();
    let b = &eval_expr(&mut context, &source, &tokens, e.params.get(1).unwrap()).parse::<i64>().unwrap();
    (a + b).to_string()
}

fn eval_core_func_sub(mut context: &mut Context, source: &String, tokens: &Vec<Token>, e: &Expr) -> String {
    assert!(e.params.len() == 2, "{} Error: Core func 'eq' takes exactly 2 arguments. This should never happen.", LANG_NAME);
    let a = &eval_expr(&mut context, &source, &tokens, e.params.get(0).unwrap()).parse::<i64>().unwrap();
    let b = &eval_expr(&mut context, &source, &tokens, e.params.get(1).unwrap()).parse::<i64>().unwrap();
    (a - b).to_string()
}

fn eval_core_func_mul(mut context: &mut Context, source: &String, tokens: &Vec<Token>, e: &Expr) -> String {
    assert!(e.params.len() == 2, "{} Error: Core func 'eq' takes exactly 2 arguments. This should never happen.", LANG_NAME);
    let a = &eval_expr(&mut context, &source, &tokens, e.params.get(0).unwrap()).parse::<i64>().unwrap();
    let b = &eval_expr(&mut context, &source, &tokens, e.params.get(1).unwrap()).parse::<i64>().unwrap();
    (a * b).to_string()
}

fn eval_core_func_div(mut context: &mut Context, source: &String, tokens: &Vec<Token>, e: &Expr) -> String {
    assert!(e.params.len() == 2, "{} Error: Core func 'eq' takes exactly 2 arguments. This should never happen.", LANG_NAME);
    let a = &eval_expr(&mut context, &source, &tokens, e.params.get(0).unwrap()).parse::<i64>().unwrap();
    let b = &eval_expr(&mut context, &source, &tokens, e.params.get(1).unwrap()).parse::<i64>().unwrap();
    (a / b).to_string()
}

fn eval_core_func_btoi(mut context: &mut Context, source: &String, tokens: &Vec<Token>, e: &Expr) -> String {
    assert!(e.params.len() == 1, "{} Error: Core func 'btoi' takes exactly 1 argument. This should never happen.", LANG_NAME);
    if eval_to_bool(&mut context, &source, &tokens, &e.params.get(0).unwrap()) {
        "1".to_string()
    } else {
        "0".to_string()
    }
}

fn eval_core_func_btoa(mut context: &mut Context, source: &String, tokens: &Vec<Token>, e: &Expr) -> String {
    assert!(e.params.len() == 1, "{} Error: Core func 'btoa' takes exactly 1 argument. This should never happen.", LANG_NAME);
    if eval_to_bool(&mut context, &source, &tokens, &e.params.get(0).unwrap()) {
        "true".to_string()
    } else {
        "true".to_string()
    }
}

fn eval_core_func_itoa(mut context: &mut Context, source: &String, tokens: &Vec<Token>, e: &Expr) -> String {
    assert!(e.params.len() == 1, "{} Error: Core func 'btoa' takes exactly 1 argument. This should never happen.", LANG_NAME);
    eval_expr(&mut context, &source, &tokens, e.params.get(0).unwrap())
}

// ---------- core procs implementations for eval

fn lbool_in_string_to_bool(b: &str) -> bool {
    match b {
        "true" => true,
        "false" => false,
        _ => panic!("{} Error: expected string 'true' or 'false', this should never happen.", LANG_NAME)
    }
}

fn eval_core_proc_print(end_line: bool, mut context: &mut Context, source: &String, tokens: &Vec<Token>, e: &Expr) -> String {
    for it in &e.params {
        print!("{}", eval_expr(&mut context, &source, &tokens, &it));
    }
    if end_line {
        print!("\n");
    }
    io::stdout().flush().unwrap();
    "".to_string()
}

fn eval_core_exit(tokens: &Vec<Token>, e: &Expr) -> String {
    assert!(e.params.len() == 1, "eval_core_exit expects a single parameter.");
    let e_exit_code = e.params.get(0).unwrap();
    let exit_code = match &e_exit_code.node_type {
        NodeType::LI64(my_li64) => {
            my_li64.clone()
        },
        node_type => {
            let t = tokens.get(e.token_index).unwrap();
            panic!("{}:{} {} error: calling core proc exit, but found {:?} instead of exit code.", t.line, t.col, LANG_NAME, node_type);
        },
    };
    std::process::exit(exit_code as i32);
}

// ---------- generic eval things

fn eval_user_func_proc_call(func_def: &SFuncDef, name: &str, context: &Context, source: &String, tokens: &Vec<Token>, e: &Expr) -> String {
    let t = tokens.get(e.token_index).unwrap();

    let mut function_context = context.clone();
    assert!(e.params.len() == func_def.args.len(), "{} error: func '{}' expected {} args, but {} were provided. This should never happen.",
            LANG_NAME, name, func_def.args.len(), e.params.len());

    let mut param_index = 0;
    for arg in &func_def.args {

        function_context.symbols.insert(arg.name.to_string(), SymbolInfo{value_type: arg.value_type.clone(), is_mut: arg.is_mut});
        match &arg.value_type {
            ValueType::TBool => {
                let bool_expr_result = lbool_in_string_to_bool(&eval_expr(&mut function_context, &source, &tokens, e.params.get(param_index).unwrap()));
                function_context.bools.insert(arg.name.clone(), bool_expr_result);
            },
            ValueType::TI64 =>  {
                let result = &eval_expr(&mut function_context, &source, &tokens, e.params.get(param_index).unwrap());
                function_context.i64s.insert(arg.name.to_string(), result.parse::<i64>().unwrap());
            },
            ValueType::TString =>  {
                let result = eval_expr(&mut function_context, &source, &tokens, e.params.get(param_index).unwrap());
                function_context.strings.insert(arg.name.to_string(), result);
            },
            ValueType::TCustom(ref custom_type_name) => {
                let result = eval_expr(&mut function_context, &source, &tokens, e.params.get(param_index).unwrap());
                let custom_symbol = function_context.symbols.get(custom_type_name).unwrap();
                match custom_symbol.value_type {
                    ValueType::TEnumDef => {
                        function_context.enums.insert(arg.name.to_string(), EnumVal{enum_type: custom_type_name.to_string(), enum_name: result});
                    },
                    _ => {
                        panic!("{}:{} {} eval error: Cannot use {} of type {:?} as an argument. Only enum custom types allowed for now.",
                               t.line, t.col, LANG_NAME, &arg.name, &arg.value_type)
                    },
                }
            },

            _ => {
                panic!("{}:{} {} error: calling func '{}'. {:?} arguments not supported.", t.line, t.col, LANG_NAME, name, arg.value_type);
            },
        }

        param_index += 1;
    }

    for se in &func_def.body {
        match se.node_type {
            NodeType::Return => {
                assert!(se.params.len() != 0, "{} error: return must currently always return exactly one value.", LANG_NAME);
                return eval_expr(&mut function_context, &source, &tokens, &se.params.get(0).unwrap());
            },
            NodeType::If => {
                assert!(se.params.len() == 2 || se.params.len() == 3, "{} error: if nodes must have 2 or 3 parameters.", LANG_NAME);
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

fn eval_func_proc_call(name: &str, mut context: &mut Context, source: &String, tokens: &Vec<Token>, e: &Expr) -> String {
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
            "btoi" => eval_core_func_btoi(&mut context, &source, &tokens, &e),
            "btoa" => eval_core_func_btoa(&mut context, &source, &tokens, &e),
            "itoa" => eval_core_func_itoa(&mut context, &source, &tokens, &e),
            _ => panic!("{}:{} {} eval error: Core function '{}' not implemented.", t.line, t.col, LANG_NAME, name),
        }
    } else if is_core_proc(&name) {
        match name {
            "print" => eval_core_proc_print(false, &mut context, &source, &tokens, &e),
            "println" => eval_core_proc_print(true, &mut context, &source, &tokens, &e),
            // "import" => eval_core_proc_import(false, &mut context, &source, &tokens, &e),
            "exit" => eval_core_exit(&tokens, &e),
            _ => panic!("{}:{} {} eval error: Core procedure '{}' not implemented.", t.line, t.col, LANG_NAME, name),
        }
    } else if context.funcs.contains_key(name) {
        let func_def = context.funcs.get(name).unwrap();
        eval_user_func_proc_call(func_def, &name, &context, &source, &tokens, &e)
    } else if context.procs.contains_key(name) {
        let func_def = context.procs.get(name).unwrap();
        eval_user_func_proc_call(func_def, &name, &context, &source, &tokens, &e)
    } else {
        panic!("{}:{} {} eval error: Cannot call '{}'. Undefined function.", t.line, t.col, LANG_NAME, name);
    }
}

fn eval_declaration(declaration: &Declaration, mut context: &mut Context, source: &String, tokens: &Vec<Token>, e: &Expr) -> String {
    let t = tokens.get(e.token_index).unwrap();
    let inner_e = e.params.get(0).unwrap();
    let value_type = match get_value_type(&context, &tokens, &inner_e) {
        Ok(val_type) => val_type,
        Err(error_string) => {
            panic!("{}", error_string);
        },
    };
    if declaration.value_type != ValueType::ToInferType {
        if value_type != declaration.value_type {
            panic!("{}:{} {} eval error: '{}' declared of type {} but initialized to type {:?}.", t.line, t.col, LANG_NAME, declaration.name, value_type_to_str(&declaration.value_type), value_type_to_str(&value_type));
        }
    }
    assert!(e.params.len() == 1, "{} error: Declarations can have only one child expression. This should never happen.", LANG_NAME);
    match value_type {
        ValueType::ToInferType => {
            panic!("{}:{} {} eval error: '{}' declared of type {} but but still to infer type {:?}.", t.line, t.col, LANG_NAME, declaration.name, value_type_to_str(&declaration.value_type), value_type_to_str(&value_type));
        },
        ValueType::TBool => {
            let bool_expr_result : bool = lbool_in_string_to_bool(&eval_expr(&mut context, &source, &tokens, inner_e));
            context.bools.insert(declaration.name.to_string(), bool_expr_result);
            context.symbols.insert(declaration.name.to_string(), SymbolInfo{value_type: value_type.clone(), is_mut: declaration.is_mut});
            bool_expr_result.to_string()
        },
        ValueType::TI64 => {
            let i64_expr_result_str = &eval_expr(&mut context, &source, &tokens, inner_e);
            context.i64s.insert(declaration.name.to_string(), i64_expr_result_str.parse::<i64>().unwrap());
            context.symbols.insert(declaration.name.to_string(), SymbolInfo{value_type: value_type.clone(), is_mut: declaration.is_mut});
            i64_expr_result_str.to_string()
        },
        ValueType::TString => {
            let string_expr_result = &eval_expr(&mut context, &source, &tokens, inner_e);
            context.strings.insert(declaration.name.to_string(), string_expr_result.to_string());
            context.symbols.insert(declaration.name.to_string(), SymbolInfo{value_type: value_type.clone(), is_mut: declaration.is_mut});
            string_expr_result.to_string()
        },
        ValueType::TEnumDef => {
            match &inner_e.node_type {
                NodeType::EnumDef(enum_def) => {
                    context.enum_defs.insert(declaration.name.clone(), enum_def.clone());
                    context.symbols.insert(declaration.name.to_string(), SymbolInfo{value_type: value_type.clone(), is_mut: declaration.is_mut});
                    "enum declared".to_string()
                },
                _ => panic!("{}:{} {} eval error: Cannot declare {} of type {:?}, expected enum definition.",
                            t.line, t.col, LANG_NAME, &declaration.name, &declaration.value_type)
            }
        },
        ValueType::TStructDef => {
            match &inner_e.node_type {
                NodeType::StructDef => {
                    context.struct_defs.insert(declaration.name.to_string(), inner_e.clone());
                    context.symbols.insert(declaration.name.to_string(), SymbolInfo{value_type: value_type.clone(), is_mut: declaration.is_mut});
                    "struct declared".to_string()
                },
                _ => panic!("{}:{} {} eval error: Cannot declare {} of type {:?}, expected struct definition.",
                            t.line, t.col, LANG_NAME, &declaration.name, &declaration.value_type)
            }
        },
        ValueType::TFunc => {
            match &inner_e.node_type {
                NodeType::FuncDef(func_def) => {
                    context.funcs.insert(declaration.name.to_string(), func_def.clone());
                    context.symbols.insert(declaration.name.to_string(), SymbolInfo{value_type: value_type.clone(), is_mut: declaration.is_mut});
                    "func declared".to_string()
                },
                _ => panic!("{}:{} {} eval error: Cannot declare {} of type {:?}, expected function definition.",
                            t.line, t.col, LANG_NAME, &declaration.name, &declaration.value_type)
            }
        },
        ValueType::TProc => {
            match &inner_e.node_type {
                NodeType::ProcDef(func_def) => {
                    context.procs.insert(declaration.name.clone(), func_def.clone());
                    context.symbols.insert(declaration.name.to_string(), SymbolInfo{value_type: value_type.clone(), is_mut: declaration.is_mut});
                    "proc declared".to_string()
                },
                _ => panic!("{}:{} {} eval error: Cannot declare {} of type {:?}, expected procedure definition.",
                            t.line, t.col, LANG_NAME, &declaration.name, &declaration.value_type)
            }
        },
        ValueType::TCustom(ref custom_type_name) => {
            context.symbols.insert(declaration.name.to_string(), SymbolInfo{value_type: value_type.clone(), is_mut: declaration.is_mut});
            let custom_symbol = context.symbols.get(custom_type_name).unwrap();
            if custom_symbol.value_type == ValueType::TEnumDef {
                let enum_expr_result_str = &eval_expr(&mut context, &source, &tokens, inner_e);
                context.enums.insert(declaration.name.to_string(), EnumVal{enum_type: custom_type_name.to_string(), enum_name: enum_expr_result_str.to_string()});
            } else {
                panic!("{}:{} {} eval error: Cannot declare {} of type {:?}. Only enum custom types allowed yet.",
                       t.line, t.col, LANG_NAME, &declaration.name, &declaration.value_type)
            }
            return format!("{} declared", custom_type_name)
        },
        _ => panic!("{}:{} {} eval error: Cannot declare {} of type {:?}.", t.line, t.col, LANG_NAME, &declaration.name, &declaration.value_type)
    }
}

fn eval_assignment(var_name: &str, mut context: &mut Context, source: &String, tokens: &Vec<Token>, e: &Expr) -> String {
    let t = tokens.get(e.token_index).unwrap();
    let symbol_info = context.symbols.get(var_name).unwrap();
    assert!(symbol_info.is_mut, "{} eval error: Assignments can only be to mut values", LANG_NAME);
    assert!(e.params.len() == 1, "{} eval error: in eval_assignment, while assigning to {}, assignments must take exactly one value.", LANG_NAME, var_name);

    let inner_e = e.params.get(0).unwrap();
    let value_type = match get_value_type(&context, &tokens, &inner_e) {
        Ok(val_type) => val_type,
        Err(error_string) => {
            panic!("{}", error_string);
        },
    };
    match value_type {
        ValueType::TBool => {
            let bool_expr_result : bool = lbool_in_string_to_bool(&eval_expr(&mut context, &source, &tokens, inner_e));
            context.bools.insert(var_name.to_string(), bool_expr_result);
            bool_expr_result.to_string()
        },
        ValueType::TI64 => {
            let i64_expr_result_str = &eval_expr(&mut context, &source, &tokens, inner_e);
            context.i64s.insert(var_name.to_string(), i64_expr_result_str.parse::<i64>().unwrap());
            i64_expr_result_str.to_string()
        },
        ValueType::TString => {
            let string_expr_result = &eval_expr(&mut context, &source, &tokens, inner_e);
            context.strings.insert(var_name.to_string(), string_expr_result.to_string());
            string_expr_result.to_string()
        },
        ValueType::TStructDef => {
            panic!("{}:{} {} eval error: Cannot assign {} of type {:?}. Not implemented yet.",
                   t.line, t.col, LANG_NAME, &var_name, &value_type);
        },
        ValueType::TFunc => {
            match &inner_e.node_type {
                NodeType::FuncDef(func_def) => {
                    context.funcs.insert(var_name.to_string(), func_def.clone());
                    "func declared".to_string()
                },
                _ => panic!("{}:{} {} eval error: Cannot assign {} of type {:?}.",
                            t.line, t.col, LANG_NAME, &var_name, &value_type)
            }
        },
        ValueType::TProc => {
            match &inner_e.node_type {
                NodeType::ProcDef(func_def) => {
                    context.procs.insert(var_name.to_string(), func_def.clone());
                    "proc declared".to_string()
                },
                _ => panic!("{}:{} {} eval error: Cannot assign {} of type {:?}.",
                            t.line, t.col, LANG_NAME, &var_name, &value_type)
            }
        },
        _ => panic!("{}:{} {} eval error: Cannot assign {} of type {:?}.", t.line, t.col, LANG_NAME, &var_name, &value_type)
    }
}

fn eval_expr(mut context: &mut Context, source: &String, tokens: &Vec<Token>, e: &Expr) -> String {
    let t = tokens.get(e.token_index).unwrap();
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
            let token_str = get_token_str(source, t);
            token_str.to_string()
        },
        NodeType::FCall(name) => {
            eval_func_proc_call(&name, &mut context, &source, &tokens, &e)
        },
        NodeType::Declaration(declaration) => {
            eval_declaration(&declaration, &mut context, &source, &tokens, &e)
        },
        NodeType::Assignment(var_name) => {
            eval_assignment(&var_name, &mut context, &source, &tokens, &e)
        },
        NodeType::Identifier(name) => {

            match context.symbols.get(name) {
                Some(symbol_info) => match symbol_info.value_type {
                    ValueType::TBool => {
                        context.bools.get(name).unwrap().to_string()
                    },
                    ValueType::TI64 => {
                        context.i64s.get(name).unwrap().to_string()
                    },
                    ValueType::TString => {
                        context.strings.get(name).unwrap().to_string()
                    },
                    ValueType::TEnumDef => {
                        assert!(e.params.len() > 0, "{} eval error: enum type '{}' can't be used as a primary expression.", LANG_NAME, name);
                        // let enum_def = context.enum_defs.get(name).unwrap();
                        let inner_e = e.params.get(0).unwrap();
                        match &inner_e.node_type {
                            NodeType::Identifier(inner_name) => {
                                // TODO check that inner_name is in enum_def
                                // TODO check if that inner_name has an optional type
                                return format!("{}.{}", name, inner_name);
                            },
                            _ => {
                                panic!("{} eval error: identifier '{}' should only have identifiers inside.", LANG_NAME, name)
                            },
                        }
                    },
                    ValueType::ToInferType => {
                        panic!("{} eval error: Can't infer the type of identifier '{}'.", LANG_NAME, name)
                    },
                    ValueType::TCustom(ref custom_type_name) => {
                        if !context.symbols.contains_key(custom_type_name) {
                            // note: this error originates in the macro `format` (in Nightly builds, run with -Z macro-backtrace for more info)
                            // thank you, rust, format inside format for no reason I want to understand
                            panic!("{}", format!("{}:{}: {} eval error: : Argument '{}' is of undefined type {}.",
                                                 t.line, t.col, LANG_NAME, &name, &custom_type_name)
                            );
                        }
                        let custom_symbol = context.symbols.get(custom_type_name).unwrap();
                        match custom_symbol.value_type {
                            ValueType::TEnumDef => {
                                return format!("TODO: can't eval enum values yet");
                                // function_context.enums.insert(arg.name.to_string(), EnumVal{enum_type: custom_type_name.to_string(), enum_name: result});
                            },

                            _ => {
                                panic!("{} eval error: TODO Can't eval '{}' of custom type {}.", LANG_NAME, name, custom_type_name)
                            },
                        }
                    },
                    _ => {
                        panic!("{} eval error: Can't use identifier '{}'. Type {:?} not supported yet.", LANG_NAME, name, symbol_info.value_type)
                    },
                }
                None => {
                    panic!("{} eval error: Undefined symbol '{}'. This should have been caught in the compile phase.", LANG_NAME, name)
                },
            }
        },
        NodeType::If => {
            assert!(e.params.len() == 2 || e.params.len() == 3, "{} eval error: if nodes must have 2 or 3 parameters.", LANG_NAME);
            if eval_to_bool(&mut context, &source, &tokens, &e.params.get(0).unwrap()) {
                eval_expr(&mut context, &source, &tokens, &e.params.get(1).unwrap())
            } else if e.params.len() == 3 {
                eval_expr(&mut context, &source, &tokens, &e.params.get(2).unwrap())
            } else {
                "".to_string()
            }
        },
        NodeType::While => {
            assert!(e.params.len() == 2, "{} eval error: while nodes must have exactly 2 parameters.", LANG_NAME);
            while eval_to_bool(&mut context, &source, &tokens, &e.params.get(0).unwrap()) {
                eval_expr(&mut context, &source, &tokens, &e.params.get(1).unwrap());
            }
            "".to_string()
        },
        NodeType::Switch => {
            assert!(e.params.len() >= 3, "{} eval error: switch nodes must have at least 3 parameters.", LANG_NAME);

            let to_switch = e.params.get(0).unwrap();
            let value_type = match get_value_type(&context, &tokens, &to_switch) {
                Ok(val_type) => val_type,
                Err(error_string) => {
                    panic!("{} eval error: {}", LANG_NAME, error_string);
                },
            };
            let mut param_it = 1;
            let result_to_switch = eval_expr(&mut context, &source, &tokens, &to_switch);
            while param_it < e.params.len() {

                let case = e.params.get(param_it).unwrap();
                if case.node_type == NodeType::DefaultCase {
                    param_it += 1;
                    let body = e.params.get(param_it).unwrap();
                    return eval_expr(&mut context, &source, &tokens, &body);
                }

                let case_type = match get_value_type(&context, &tokens, &case) {
                    Ok(val_type) => val_type,
                    Err(error_string) => {
                        panic!("{} eval error: {}", LANG_NAME, error_string);
                    },
                };
                if value_type != case_type {
                    panic!("{} eval error: switch value type {:?}, vase value type {:?}", LANG_NAME, value_type, case_type);
                }

                let result_case = eval_expr(&mut context, &source, &tokens, &case);
                param_it += 1;
                if result_to_switch == result_case {
                    let body = e.params.get(param_it).unwrap();
                    return eval_expr(&mut context, &source, &tokens, &body);
                }
                param_it += 1;
            }
            return "".to_string();
        },
        NodeType::Return => {
            assert!(e.params.len() == 1, "{} eval error: return nodes must have exactly 1 parameter.", LANG_NAME);
            eval_expr(&mut context, &source, &tokens, &e.params.get(0).unwrap())
        }
        _ => {
            panic!("{}:{}: {} eval error: Not implemented, found {}.", t.line, t.col, LANG_NAME, get_token_str(source, t))
        },
    }
}

// ---------- to ast (aka code_gen lisp-like syntax)

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
        NodeType::DefaultCase => {
            return "default_case".to_string();
        }
        NodeType::Body => {
            return params_to_ast_str(true, &e)
        },
        NodeType::Declaration(decl) => {
            ast_str.push_str(&format!("(def {} {})", decl.name, to_ast_str(&e.params.get(0).unwrap())));
            return ast_str;
        },
        NodeType::Assignment(var_name) => {
            ast_str.push_str(&format!("(set {} {})", var_name, to_ast_str(&e.params.get(0).unwrap())));
            return ast_str;
        },
        NodeType::FuncDef(_func_def) => {
            return "(func)".to_string();
        },
        NodeType::ProcDef(_func_def) => {
            return "(proc)".to_string();
        },
        NodeType::EnumDef(_) => {
            return "(enum)".to_string();
        },
        NodeType::StructDef => {
            return "(struct)".to_string();
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
        NodeType::While => {
            ast_str.push_str(&format!("(while {})", to_ast_str(&e.params.get(0).unwrap())));
            return ast_str;
        },
        NodeType::Switch => {
            ast_str.push_str(&format!("(switch {})", to_ast_str(&e.params.get(0).unwrap())));
            return ast_str;
        },
        NodeType::Return => {
            panic!("{} AST error: Node_type::Return shouldn't be analized in to_ast_str().", LANG_NAME);
        },
    }
}

// ---------- main binary

fn main_run(path: &String, source: &String) -> String {
    let tokens: Vec<Token> = scan_tokens(&source);
    if tokens.len() < 1 {
        return format!("{}:{}:{} compiler error: End of file not found.", path, 1, 0);
    } else if is_eof(&tokens, 0) {
        return format!("{}:{}:{} compiler error: Nothing to be done", path, tokens.get(0).unwrap().line, 0);
    }

    let mut errors_found : usize = 0;
    for t in &tokens {
        print_if_lex_error(&path, &source, &t, &mut errors_found)
    }
    if errors_found > 0 {
        return format!("Compiler errors: {} lexical errors found", errors_found);
    }

    let mut current: usize = 0;
    let mode = match parse_mode(&source, &tokens, &mut current) {
        Ok(mode_) => mode_,
        Err(error_string) => {
            return format!("{}:{}", &path, error_string);
        },
    };
    println!("Mode: {}", mode.name);

    if mode.name == "pure" {
        return format!("{}:0:0: mode '{}' is not properly supported in {} yet. Try mode {} instead", path, mode.name, BIN_NAME, "lib");
    }
    if mode.name == "external" {
        return format!("{}:0:0: mode '{}' is not properly supported in {} yet. Try mode {} instead", path, mode.name, BIN_NAME, "lib");
    }
    if mode.name == "safe_script" {
        return format!("{}:0:0: mode '{}' is not properly supported in {} yet. Try mode {} instead", path, mode.name, BIN_NAME, "script");
    }

    let mut e: Expr = match parse_tokens(&source, &tokens, &mut current) {
        Ok(expr) => expr,
        Err(error_string) => {
            return format!("{}:{}", &path, error_string);
        },
    };
    if !SKIP_AST {
        println!("AST: \n{}", to_ast_str(&e));
    }

    let mut context = start_context(mode);
    let mut errors = init_context(&mut context, &source, &tokens, &e);
    if errors.len() > 0 {
        for err in &errors {
            println!("{}:{}", path, err);
        }
        return format!("Compiler errors: {} declaration errors found", errors.len());
    }

    match &e.node_type {
        NodeType::Body => {
            for p in e.params.iter() {
                match &p.node_type {

                    NodeType::Declaration(decl) => {
                        if !context.mode.allows_base_mut && decl.is_mut {
                            let t = tokens.get(p.token_index).unwrap();
                            errors.push(format!("{}:{}: {} error: mode {} doesn't allow mut declaration of 'mut {}'.\nSuggestion: remove 'mut' or change to mode script or cli",
                                t.line, t.col, "mode", context.mode.name, decl.name));
                        }
                    },
                    NodeType::FCall(name) => {
                        if !context.mode.allows_base_calls {
                            let t = tokens.get(p.token_index).unwrap();
                            errors.push(format!("{}:{}: {} error: mode {} doesn't allow calls in the root context of the file'.\nSuggestion: remove the call to '{}' or change mode 'test' or 'script'",
                                t.line, t.col, "mode", context.mode.name, name));
                        }
                    }
                    _ => {},
                }
            }
        },
        _ => {},
    }
    if errors.len() > 0 {
        for err in &errors {
            println!("{}:{}", path, err);
        }
        return format!("Mode errors: {} type errors found", errors.len());
    }
    if context.mode.needs_main_proc {
        e.params.push(Expr{node_type: NodeType::FCall("main".to_string()), token_index: 0, params: Vec::new()});
    }

    let errors = check_types(&mut context, &source, &tokens, &e);
    if errors.len() > 0 {
        for err in &errors {
            println!("{}:{}", path, err);
        }
        return format!("Compiler errors: {} type errors found", errors.len());
    }

    eval_expr(&mut context, &source, &tokens, &e)
}

// ---------- main, usage, args, etc

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
    println!("eval: {}", main_run(&path, &source));
}

fn run_repl() {
    loop {
        print!("{}> ", LANG_NAME);
        io::stdout().flush().unwrap();

        let mut line = String::new();
        io::stdin()
            .read_line(&mut line)
            .expect("repl error: Failed to read line");

        if line.len() == 1 { break; }

        let path = "repl".to_string();
        println!("{}", main_run(&path, &line));
    }
}

fn usage() {
    println!("Usage: {} [command] [path]\n", BIN_NAME);
    println!("Entering no arguments is equavalent to: {} repl", BIN_NAME);
    println!("Entering a single argument that's not a command is interpreted as a path, equivalent to: {} interpret <path>\n", BIN_NAME);

    println!("Commands:\n");

    println!("repl: read eval print loop. TODO FIX");
    println!("interpret: reads a file in provided <path> and evaluates it.");
    // println!("ast: reads a file in provided <path> and prints its abstract syntax tree (aka (lisp-like-syntax ast-from-now-on ) ).");
    // println!("build: reads a file in provided <path> and compiles it. Not implemented yet.");
    // println!("run: reads a file in provided <path> and runs it if it compiles. Not implemented yet.");
    println!("help: Prints this.\n");
}

fn main() {
    env::set_var("RUST_BACKTRACE", "1");
    let args: Vec<String> = env::args().collect();

    if args.len() > 3 {
        usage();
    } else if args.len() > 2 {
        match args[1].as_str() {
            "repl" => {
                usage();
            },
            "interpret" => {
                run_file(&args[2]);
            },
            "build" | "run" => {
                usage();
            },
            _ => {
                usage();
            },
        }
        println!("command '{}' not implemented yet.", &args[1]);
        println!("in valid command '{}'.", &args[1]);
    } else if args.len() > 1 {
        match args[1].as_str() {
            "repl" => {
                run_repl();
            },
            "ast" | "interpret" | "build" | "run" |
            "help" | "-help" | "--help"=> {
                usage();
            },
            _ => {
                run_file(&args[1]);
            },
        }
    } else {
        run_repl();
    }
}
