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
const DEFAULT_MODE: &str = "lib";
const INFER_TYPE: &str = "auto";
const REPL_PATH: &str = "src/repl.cil";
const SKIP_AST: bool = true;

// ---------- format errors

// struct RscilErr {
//     error_str: &str,
//     t: &Token,
//     level: &str,
// }

// fn init_err(t: &Token, level: &str, error_str: &str) return RscilErr {
//     return RscilErr(format!("{}:{}: {} error: {}", e.line, e.col, level, error_str));
// }

// fn format_err(RscilErr: err) -> String {
//     return format!("{}:{}: {} error: {}", err.e.line, err.t.col, err.level, err.error_str);
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
    Mode,
    Func, Proc, Macro,
    FuncExt, ProcExt,

    // Errors
    Const, Var,
    Fn,
    Case,
    Invalid,
    UnterminatedString,
    // UnterminatedComment, // TODO do nesting comments like jai and odin, shoulnd't be that hard. ideally in the lexer itself
}

#[derive(Debug, Clone, PartialEq)]
struct Token {
    token_type: TokenType,
    token_str: String,
    line: usize,
    col: usize,
}

struct Lexer {
    tokens: Vec<Token>,
}

impl Lexer {
    fn new(source: String) -> Self {
        return Self{tokens: scan_tokens(source)};
    }

    fn len(self: &Lexer) -> usize {
        return self.tokens.len();
    }

    fn is_eof(self: &Lexer, current: usize) -> bool {
        return current >= self.tokens.len() ||
            match self.tokens.get(current) {
                Some(_t) => TokenType::Eof == _t.token_type,
                None => false,

            }
    }

    fn get_token(self: &Lexer, i: usize) -> Result<&Token, String> {
        match self.tokens.get(i) {
            Some(_t) => {
                return Ok(_t);
            },
            None => {
                return Err(format!(":: Token in pos {} is out of bounds", i));
            },
        };
    }
}

fn is_digit(source: &String, pos: usize) -> bool {
    match &source[pos..pos+1].chars().next().unwrap() {
        '0'..='9' => true,
        _ => false,
    }
}

fn is_id_start(source: &String, pos: usize) -> bool {
    match &source[pos..pos+1].chars().next().unwrap() {
        'a'..='z' | 'A'..='Z' | '_' => true,
        _ => false,
    }
}

fn scan_reserved_words(identifier: &str) -> TokenType {
    match identifier {
        "mode" => TokenType::Mode,

        // declaration/arg modifiers
        "mut" => TokenType::Mut,

        // bool literals
        "true" => TokenType::True,
        "false" => TokenType::False,

        // core data types
        "enum" => TokenType::Enum,
        "struct" => TokenType::Struct,

        // function declaration
        "returns" => TokenType::Returns,
        // Anything that can be thrown must be explicitly declared in the function via 'throws', java style.
        // Except perhaps PanicException or something like that which can be implicit, but still allowed to documment redundantly
        // or perhaps not, for that may degenerate in an extra warning option
        // perhaps just force the user to explicitly catch and exit any potential panic from the callee
        "throws" => TokenType::Throws, // TODO
        "func" => TokenType::Func,
        "proc" => TokenType::Proc,
        "macro" => TokenType::Macro, // TODO implement for real once we compile
        "ext_func" => TokenType::FuncExt, // this have to link when we compile
        "ext_proc" => TokenType::ProcExt, // this have to link when we compile

        // control flow
        "if" => TokenType::If,
        "else" => TokenType::Else,
        "while" => TokenType::While,
        "for" => TokenType::For, // TODO
        "in" => TokenType::In, // TODO, or just use semicolon reserve forbid this
        "switch" => TokenType::Switch,
        "match" => TokenType::Match, // TODO like switch but special for declarations/assignments
        "case" => TokenType::Case,
        "default" => TokenType::Default, // TODO currently using "case:", but "default:" is more traditional, grepable and overt
        "return" => TokenType::Return,
        "throw" => TokenType::Throw, // TODO
        // TODO throw should just act as a return that gets post-processed by the next catch or rethrown
        "catch" => TokenType::Catch,
        "try" => TokenType::Try, // TODO don't allow it to open contexts, just mandatory 'try:' in any line that may throw
        // or should 'try:' be optional?

        // Reserved forbidden/illegal words (intentionally unsupported reserved words)
        // TODO intentionally unsupport more reserved words
        // TODO nicer messages for forbidden words
        "fn" => TokenType::Fn,
        "function" => TokenType::Invalid,
        "method" => TokenType::Invalid,
        "global" => TokenType::Invalid, // just use mut declaration in the root of the file, but they're not allowed in all modes
        // const/vars are the most abstract types, you can't even explicitly declare them
        "const" => TokenType::Const,
        "var" => TokenType::Var,

        // Do we really need const fields static other than static? (ie can be different per instance, but not modified afterwards)
        // The answer is probably yet, but perhaps static is not the right answer
        // how about this? if it's in the struct body, it is const, if it is in impl, it is static, just like functions\
        // or do we need mut function fields too? probably yes
        "static" => TokenType::Invalid,

        _ => TokenType::Identifier,
    }
}

fn scan_push_token(tokens: &mut Vec<Token>, token_type: TokenType, token_str: &str, line: usize, col: usize) {
    tokens.push(Token{token_type: token_type, token_str: token_str.to_string(), line: line, col: col});
}

fn scan_tokens(source: String) -> Vec<Token> {
    let mut tokens : Vec<Token> = Vec::new();
    let eof_pos: usize = source.len();
    let mut pos = 0;
    let mut line = 1;
    let mut start_line_pos = 0;

    while pos < eof_pos {
        let start = pos;

        if is_digit(&source, pos) {
            while pos < eof_pos && is_digit(&source, pos) {
                pos += 1;
            }
            // Look for a fractional part.
            if &source[pos..pos+1] == "." && is_digit(&source, pos+1) {
                pos += 1;
                while pos < eof_pos && is_digit(&source, pos) {
                    pos += 1;
                }
            }
            scan_push_token(&mut tokens, TokenType::Number, &source[start..pos], line, pos - start_line_pos + 1);
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

                // literal strings
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

                _ => { // Everything else must be reserved words, identifiers or invalid
                    if is_id_start(&source, pos) {
                        pos += 1;
                        while pos < eof_pos && (is_digit(&source, pos) || is_id_start(&source, pos)) {
                            pos += 1;
                        }
                        pos = pos - 1;
                        scan_reserved_words(&source[start..pos+1])
                    } else {
                        TokenType::Invalid
                    }
                },

            }; // let match
            if token_type == TokenType::String {
                scan_push_token(&mut tokens, token_type, &source[start + 1..pos], line, pos - start_line_pos + 1);
            } else {
                scan_push_token(&mut tokens, token_type, &source[start..pos + 1], line, pos - start_line_pos + 1);
            }
            pos += 1;
        } // else
    } // while

    scan_push_token(&mut tokens, TokenType::Eof, "End of file", line, 0);
    return tokens
}

fn print_lex_error(path: &String, t: &Token, num_error: usize, msg: &str) {
    println!("{}:{}:{}: Lexical error {}: {}. Offending symbol: '{}'", path, t.line, t.col, num_error, msg, t.token_str);
}

fn print_if_lex_error(path: &String, t: &Token, errors_found: &mut usize) {
    match t.token_type {
        TokenType::Invalid => {
            print_lex_error(&path, &t, *errors_found, "Invalid character");
            *errors_found = *errors_found + 1;
        },
        TokenType::UnterminatedString => {
            print_lex_error(&path, &t, *errors_found, "Unterminated String\nSuggestion: add missing '\"'");
            *errors_found = *errors_found + 1;
        },
        TokenType::Const => {
            print_lex_error(&path, &t, *errors_found, "No need to use 'const', everything is const by default unless 'mut' is used");
            *errors_found = *errors_found + 1;
        },
        TokenType::Var => {
            print_lex_error(&path, &t, *errors_found, "Keyword 'var' is not supported\nSuggestion: use 'mut' instead");
            *errors_found = *errors_found + 1;
        },
        TokenType::Fn => {
            print_lex_error(&path, &t, *errors_found, "Keyword 'fn' is not supported\nSuggestion: use 'func' or 'proc' instead");
            *errors_found = *errors_found + 1;
        },
        TokenType::DoubleSemicolon => {
            print_lex_error(&path, &t, *errors_found, "No need for ';;' (aka empty statements)\nSuggestion: try 'if true {}' instead, whatever you want that for");
            *errors_found = *errors_found + 1;
        },
        TokenType::Plus => {
            print_lex_error(&path, &t, *errors_found, "Operator '+' is not supported yet\nSuggestion: use core func 'add' instead");
            *errors_found = *errors_found + 1;
        },
        TokenType::Minus => {
            print_lex_error(&path, &t, *errors_found, "Operator '-' is not supported yet\nSuggestion: use core func 'sub' instead");
            *errors_found = *errors_found + 1;
        },
        TokenType::Star => {
            print_lex_error(&path, &t, *errors_found, "Operator '*' is not supported yet\nSuggestion: use core func 'mul' instead");
            *errors_found = *errors_found + 1;
        },
        TokenType::Slash => {
            print_lex_error(&path, &t, *errors_found, "Operator '/' is not supported yet\nSuggestion: use core func 'div' instead");
            *errors_found = *errors_found + 1;
        },
        TokenType::EqualEqual => {
            print_lex_error(&path, &t, *errors_found, "Operator '==' is not supported yet\nSuggestion: use core func 'eq' or 'str_eq' instead");
            *errors_found = *errors_found + 1;
        },
        TokenType::Lesser => {
            print_lex_error(&path, &t, *errors_found, "Operator '<' is not supported yet\nSuggestion: use core func 'lt' instead");
            *errors_found = *errors_found + 1;
        },
        TokenType::LesserEqual => {
            print_lex_error(&path, &t, *errors_found, "Operator '<=' is not supported yet\nSuggestion: use core func 'lteq' instead");
            *errors_found = *errors_found + 1;
        },
        TokenType::Greater => {
            print_lex_error(&path, &t, *errors_found, "Operator '>' is not supported yet\nSuggestion: use core func 'gt' instead");
            *errors_found = *errors_found + 1;
        },
        TokenType::GreaterEqual => {
            print_lex_error(&path, &t, *errors_found, "Operator '>=' is not supported yet\nSuggestion: use core func 'gteq' instead");
            *errors_found = *errors_found + 1;
        },
        TokenType::Not => {
            print_lex_error(&path, &t, *errors_found, "Operator '!' is not supported yet\nSuggestion: use core func 'not' instead");
            *errors_found = *errors_found + 1;
        },
        TokenType::NotEqual => {
            print_lex_error(&path, &t, *errors_found, "Operator '!=' is not supported yet\nSuggestion: use core funcs 'not' and 'eq' instead");
            *errors_found = *errors_found + 1;
        },

        _ => {},
    }
}

fn lexer_from_source(path: &String, source: String) -> Result<Lexer, String> {

    let lexer = Lexer::new(source);
    if lexer.len() < 1 {
        return Err(format!("{}:{}:{} compiler error: End of file not found.", path, 1, 0));
    } else if lexer.is_eof(0) {
        return Err(format!("{}:{}:{} compiler error: Nothing to be done", path, 0, 0));
    }

    let mut errors_found: usize = 0;
    for t in &lexer.tokens {
        print_if_lex_error(&path, &t, &mut errors_found)
    }
    if errors_found > 0 {
        return Err(format!("Compiler errors: {} lexical errors found", errors_found));
    }
    return Ok(lexer);
}

// ---------- parser

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
    TType,
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
        ValueType::TType => "Type".to_string(),
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
        "Type" => ValueType::TType,
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
enum FunctionType {
    FTFunc,
    FTProc,
    FTMacro,
    FTFuncExt,
    FTProcExt,
}

#[derive(Debug, Clone, PartialEq)]
struct SFuncDef {
    function_type: FunctionType,
    args: Vec<Declaration>,
    returns: Vec<ValueType>,
    // throws: Vec<ValueType>,
    body: Vec<Expr>,
}

#[derive(Debug, Clone, PartialEq)]
struct SStructDef {
    members : HashMap<String, Declaration>,
    default_values : HashMap<String, Expr>,
}

#[derive(Debug, Clone, PartialEq)]
enum NodeType {
    Body,
    LList(String),
    LString(String),
    LI64(i64),
    LBool(bool),
    FCall,
    Identifier(String),
    Declaration(Declaration),
    Assignment(String),
    FuncDef(SFuncDef),
    EnumDef(SEnumDef),
    StructDef(SStructDef),
    Return,
    If,
    While,
    Switch,
    DefaultCase,
}

#[derive(Debug, Clone, PartialEq)]
struct Expr {
    node_type: NodeType,
    params: Vec<Expr>,
    line: usize,
    col: usize,
}

impl Expr {
    fn new_parse(node_type: NodeType, token: Token, params: Vec<Expr>) -> Expr {
        return Expr{
            node_type: node_type,
            params: params,
            line: token.line,
            col: token.col,
        }
    }

    fn new_explicit(node_type: NodeType, params: Vec<Expr>, line: usize, col: usize) -> Expr {
        return Expr{
            node_type: node_type,
            params: params,
            line: line,
            col: col,
        }
    }

    fn new_clone(node_type: NodeType, e: &Expr, params: Vec<Expr>) -> Expr {
        return Expr::new_explicit(node_type, params, e.line, e.col)
    }

    fn get(self: &Expr, i: usize) -> &Expr {
        return &self.params.get(i).unwrap();
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

fn can_be_imported(mode: &ModeDef) -> bool {
    return !(
        mode.needs_main_proc || // TODO think harder, why not?
        mode.allows_base_mut ||
        mode.allows_base_calls ||
        mode.allows_base_anything
    );
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

fn parse_mode(path: &String, lexer: &Lexer, mut current: &mut usize) -> Result<ModeDef, String> {
    if &TokenType::Mode != current_token_type(&lexer, &mut current) {
        return Err(format!("0:0: 'mode' is required in the beginning of the file"));
    }
    *current = *current + 1; // Add one for mode

    if &TokenType::Identifier != current_token_type(&lexer, &mut current) {
        return Err(format!("0:0: Expected identifier after 'mode'"));
    }
    let t = lexer.get_token(*current)?;
    let mode_name = &t.token_str;
    let mode = match mode_from_name(&mode_name) {
        Ok(mode_) => mode_,
        Err(err_) => return Err(err_),
    };

    if mode.name == "pure" {
        return Err(format!("{}:0:0: mode '{}' is not properly supported in '{}' yet. Try mode '{}' instead", path, mode.name, BIN_NAME, "lib"));
    }
    if mode.name == "external" {
        return Err(format!("{}:0:0: mode '{}' is not properly supported in '{}' yet. Try mode '{}' instead", path, mode.name, BIN_NAME, "lib"));
    }
    if mode.name == "safe_script" {
        return Err(format!("{}:0:0: mode '{}' is not properly supported in '{}' yet. Try mode '{}' instead", path, mode.name, BIN_NAME, "script"));
    }

    *current = *current + 1; // Add one for the identifier mode
    return Ok(mode);
}

fn parse_literal(t: &Token, current: &mut usize) -> Result<Expr, String> {
    let params : Vec<Expr> = Vec::new();
    let node_type = match t.token_type {
        TokenType::String => NodeType::LString(t.token_str.clone()),
        TokenType::Number => NodeType::LI64(t.token_str.parse::<i64>().unwrap()),
        TokenType::True => NodeType::LBool(true),
        TokenType::False => NodeType::LBool(false),
        _ => {
            return Err(format!("{}:{}: {}  error: Trying to parse a token that's not a literal as a literal, found {:?}.",
                               t.line, t.col, LANG_NAME, t.token_type));
        },
    };
    let e = Expr::new_parse(node_type, t.clone(), params);
    *current = *current + 1;
    Ok(e)
}

fn parse_list(lexer: &Lexer, current: &mut usize) -> Result<Expr, String> {
    let mut rightparent_found = false;
    let mut params : Vec<Expr> = Vec::new();
    let initial_current = *current;
    *current = *current + 1;
    let mut list_t = lexer.get_token(*current)?;
    // println!("primary debug LeftParen: {} {}", initial_current, *current);
    let mut expect_comma = false;
    while !(lexer.is_eof(*current) || rightparent_found) {
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
                    list_t = lexer.get_token(*current)?;
                } else {
                    return Err(format!("{}:{}: parse error: Unexpected ','.", list_t.line, list_t.col));
                }
            },
            _ => {
                if expect_comma {
                    return Err(format!("{}:{}: parse error: Expected ')' or ',', found {:?}.", list_t.line, list_t.col, list_t.token_type));
                }
                expect_comma = true;
                let prim = match parse_primary(&lexer, current) {
                    Ok(to_ret) => to_ret,
                    Err(err_str) => return Err(err_str),
                };
                params.push(prim);
                list_t = lexer.get_token(*current)?;
            },
        }
    }
    match list_t.token_type {
        // TODO properly parse lists besides function definition arguments
        TokenType::RightParen => Ok(Expr::new_parse(NodeType::LList("".to_string()), lexer.get_token(initial_current)?.clone(), params)),
        _ => Err(format!("{}:{}: parse error: Expected closing parentheses.", list_t.line, list_t.col)),
    }
}

fn parse_assignment(lexer: &Lexer, current: &mut usize) -> Result<Expr, String> {
    let t = lexer.get_token(*current)?;
    let name = &t.token_str;
    let initial_current = *current;
    *current = *current + 2; // skip identifier and equal
    let mut params : Vec<Expr> = Vec::new();
    params.push(parse_primary(&lexer, current)?);
    return Ok(Expr::new_parse(NodeType::Assignment(name.to_string()), lexer.get_token(initial_current)?.clone(), params))
}

fn parse_func_proc_args(lexer: &Lexer, current: &mut usize) -> Result<Vec<Declaration>, String> {

    let mut rightparent_found = false;
    let mut args : Vec<Declaration> = Vec::new();
    *current = *current + 1;
    let mut t = lexer.get_token(*current)?;
    let mut expect_comma = false;
    let mut expect_colon = false;
    let mut expect_name = true;
    let mut is_variadic = false;
    let mut arg_name = "unnamed";
    while !(lexer.is_eof(*current) || rightparent_found) {
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
                    t = lexer.get_token(*current)?;
                } else {
                    if expect_colon {
                        expect_colon = false;
                        args.push(Declaration{
                            name: arg_name.to_string(), value_type: str_to_value_type(INFER_TYPE), is_mut: false});
                        expect_comma = true;
                        *current = *current + 1;
                        t = lexer.get_token(*current)?;
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
                    t = lexer.get_token(*current)?;
                } else {
                    return Err(format!("{}:{}: parse error: Unexpected ':'.", t.line, t.col));
                }
            },
            TokenType::DoubleDot => {
                if expect_comma {
                    return Err(format!("{}:{}: parse error: Expected ',', found {:?}.", t.line, t.col, t.token_type));
                }
                if expect_colon {
                    return Err(format!("{}:{}: parse error: Expected ':', found {:?}.", t.line, t.col, t.token_type));
                }
                if expect_name {
                    return Err(format!("{}:{}: parse error: Expected arg name, found {:?}.", t.line, t.col, t.token_type));
                }
                is_variadic = true;
                *current = *current + 1;
                t = lexer.get_token(*current)?;
            },
            TokenType::Identifier => {
                if expect_comma {
                    return Err(format!("{}:{}: parse error: Expected ',', found {:?}.", t.line, t.col, t.token_type));
                }
                if expect_colon {
                    return Err(format!("{}:{}: parse error: Expected ':', found {:?}.", t.line, t.col, t.token_type));
                }
                if expect_name {
                    arg_name = &t.token_str;
                    expect_colon = true;
                    expect_name = false;
                } else { // expect type name then
                    if is_variadic {
                        args.push(Declaration{
                            name: arg_name.to_string(),
                            value_type: ValueType::TMulti(Box::new(str_to_value_type(&t.token_str))), is_mut: false});
                        is_variadic = false;
                    } else {
                        args.push(Declaration{
                            name: arg_name.to_string(),
                            value_type: str_to_value_type(&t.token_str), is_mut: false});
                    }
                    expect_comma = true;
                }
                *current = *current + 1;
                t = lexer.get_token(*current)?;
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

fn func_proc_returns(lexer: &Lexer, current: &mut usize) -> Result<Vec<ValueType>, String> {
    let mut end_found = false;
    let mut return_types : Vec<ValueType> = Vec::new();
    let mut t = lexer.get_token(*current)?;
    *current = *current + 1;
    if t.token_type != TokenType::Returns {
        return Ok(return_types);
    }
    t = lexer.get_token(*current)?;
    let mut expect_comma = false;
    while !(lexer.is_eof(*current) || end_found) {
        match t.token_type {
            TokenType::Throws | TokenType::LeftBrace | TokenType::Semicolon => {
                end_found = true;
                *current = *current + 1;
            },
            TokenType::Comma => {
                if expect_comma {
                    expect_comma = false;
                    *current = *current + 1;
                    t = lexer.get_token(*current)?;
                } else {
                    return Err(format!("{}:{}: parse error: Unexpected ','.", t.line, t.col));
                }
            },
            TokenType::Identifier => {
                if expect_comma {
                    return Err(format!("{}:{}: parse error: Expected ',', found {:?}.", t.line, t.col, t.token_type));
                }
                return_types.push(str_to_value_type(&t.token_str));
                expect_comma = true;
                *current = *current + 1;
                t = lexer.get_token(*current)?;
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

fn parse_func_proc_definition(lexer: &Lexer, function_type: FunctionType, do_parse_body: bool, current: &mut usize) -> Result<Expr, String> {

    *current = *current + 1;
    let t = lexer.get_token(*current)?;
    if lexer.is_eof(*current + 1) {
        return Err(format!("{}:{}: parse error: expected '(' after 'func' or 'proc', found EOF.", t.line, t.col));
    }
    if t.token_type != TokenType::LeftParen {
        return Err(format!("{}:{}: parse error: expected '(' after 'func', found {:?}.", t.line, t.col, t.token_type));
    }
    let args = match parse_func_proc_args(&lexer, current) {
        Ok(to_ret) => to_ret,
        Err(err_str) => return Err(err_str),
    };
    let returns = match func_proc_returns(&lexer, current) {
        Ok(to_ret) => to_ret,
        Err(err_str) => return Err(err_str),
    };

    let body = match do_parse_body {
        false => {
            *current = *current - 1; // Discount the closing brace we won't need
            Vec::new()
        },
        true => match parse_body(&lexer, current, TokenType::RightBrace) {
            Ok(body) => body.params,
            Err(err_str) => return Err(err_str),
        },
    };

    let func_def = SFuncDef{function_type: function_type, args: args, returns: returns, body: body};
    let params : Vec<Expr> = Vec::new();
    let e = Expr::new_parse(NodeType::FuncDef(func_def), t.clone(), params);
    *current = *current + 1;
    Ok(e)
}

fn enum_definition(lexer: &Lexer, current: &mut usize) -> Result<Expr, String> {
    let initial_current: usize = *current;
    *current = *current + 1;

    let t = lexer.get_token(*current)?;
    if t.token_type != TokenType::LeftBrace {
        return Err(format!("{}:{}: parse error: Expected '{{' after 'enum'.", t.line, t.col));
    }
    if lexer.is_eof(*current + 1) {
        let t = lexer.get_token(*current)?;
        return Err(format!("{}:{}: parse error: expected identifier after 'enum {{', found EOF.", t.line, t.col));
    }
    *current = *current + 1;
    let mut enum_map: HashMap<String, Option<ValueType>> = HashMap::new();

    let mut end_found = false;
    while *current < lexer.len() && !end_found {
        let it_t = lexer.get_token(*current)?;
        match it_t.token_type {
            TokenType::RightBrace => {
                end_found = true;
            },
            TokenType::Identifier => {
                let next_t = lexer.get_token(*current + 1)?;
                let enum_val_name = &it_t.token_str;
                match next_t.token_type {
                    TokenType::Identifier | TokenType::RightBrace => {
                        enum_map.insert(enum_val_name.to_string(), None);
                    },
                    TokenType::Colon => {
                        let next2_t = lexer.get_token(*current + 2)?;
                        if next2_t.token_type != TokenType::Identifier {
                            return Err(format!("{}:{}: parse error: Expected type identifier after '{} :', found '{:?}'.", t.line, t.col, enum_val_name, next2_t.token_type));
                        }
                        let enum_val_type = &next2_t.token_str;
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
    return Ok(Expr::new_parse(NodeType::EnumDef(SEnumDef{enum_map: enum_map}), lexer.get_token(initial_current)?.clone(), params));
}

fn parse_struct_definition(lexer: &Lexer, current: &mut usize) -> Result<Expr, String> {
    *current = *current + 1;
    let t = lexer.get_token(*current)?;
    if t.token_type != TokenType::LeftBrace {
        return Err(format!("{}:{}: parse error: Expected '{{' after 'struct'.", t.line, t.col));
    }
    if lexer.is_eof(*current + 1) {
        let t = lexer.get_token(*current)?;
        return Err(format!("{}:{}: parse error: expected 'identifier' after 'struct {{', found EOF.", t.line, t.col));
    }
    *current = *current + 1;
    let body = match parse_body(&lexer, current, TokenType::RightBrace) {
        Ok(body) => body,
        Err(err_str) => return Err(err_str),
    };
    let mut members = HashMap::new();
    let mut default_values = HashMap::new();
    for p in body.params {
        match p.node_type {
            NodeType::Declaration(decl) => {
                members.insert(decl.name.clone(), decl.clone());
                if p.params.len() == 1 {
                    default_values.insert(decl.name.clone(), p.params.get(0).unwrap().clone()); // TODO document what's special about this line
                } else {
                    // TODO allow not setting default values in struct members
                    return Err(format!("{}:{}: parse error: all declarations inside struct defitions must have a value for now", t.line, t.col));
                }
            },
            _ => return Err(format!("{}:{}: parse error: expected only declarations inside struct defition", t.line, t.col)),
        }
    }

    *current = *current + 1;
    return Ok(Expr::new_parse(NodeType::StructDef(SStructDef{members: members, default_values: default_values}),
                              t.clone(), Vec::new()));
}

fn parse_primary_identifier(lexer: &Lexer, current: &mut usize) -> Result<Expr, String> {

    let initial_current = *current;
    let t = lexer.get_token(*current)?;
    let mut next_t = lexer.get_token(*current + 1)?;
    let mut current_identifier = &t.token_str;
    let mut params : Vec<Expr> = Vec::new();
    while TokenType::Dot == next_t.token_type {
        let next2_t = lexer.get_token(*current + 2)?;
        if TokenType::Identifier != next2_t.token_type {
            return Err(format!("{}:{}: parse error: expected identifier after '{}.', found {:?}.",
                               next2_t.line, next2_t.col, current_identifier, next2_t.token_type));
        }

        current_identifier = &next2_t.token_str;
        *current = *current + 2;
        params.push(Expr::new_parse(NodeType::Identifier(current_identifier.clone()), t.clone(), Vec::new()));
        next_t = lexer.get_token(*current + 1)?;
    }

    let e = Expr::new_parse(NodeType::Identifier(t.token_str.clone()), lexer.get_token(initial_current)?.clone(), params);
    *current = *current + 1;

    if TokenType::LeftParen == next_t.token_type {
        let mut arg_list = match parse_list(&lexer, current) {
            Ok(a_list) => a_list,
            Err(err_str) => return Err(err_str),
        };
        let mut params : Vec<Expr> = Vec::new();
        params.push(e);
        params.append(&mut arg_list.params);
        return Ok(Expr::new_parse(NodeType::FCall, lexer.get_token(initial_current)?.clone(), params))
    }
    return Ok(e);
}

fn parse_statement_identifier(lexer: &Lexer, current: &mut usize) -> Result<Expr, String> {

    let t = lexer.get_token(*current)?;
    let next_t = lexer.get_token(*current + 1)?;
    let next_token_type = &next_t.token_type;
    match next_token_type {
        TokenType::LeftParen => {
            return parse_primary_identifier(&lexer, current)
        },
        TokenType::Dot => {
            Err(format!("{}:{}: parse error: '.' not allowed after the first identifier in a statement yet.", t.line, t.col))
        },
        TokenType::Equal => {
            return parse_assignment(&lexer, current)
        },
        TokenType::Colon => {
            let next_next_t = lexer.get_token(*current + 2)?;
            let next_next_token_type = &next_next_t.token_type;
            let identifier = &t.token_str;
            match next_next_token_type {
                TokenType::Identifier => {
                    let type_name = &next_next_t.token_str;
                    return parse_declaration(&lexer, current, false, type_name)
                }
                TokenType::Equal => {
                    return parse_declaration(&lexer, current, false, INFER_TYPE)
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
}

fn parse_primary(lexer: &Lexer, current: &mut usize) -> Result<Expr, String> {

    let t = lexer.get_token(*current)?;
    if is_literal(t) {
        return parse_literal(t, current)
    }
    match &t.token_type {
        TokenType::Func => return parse_func_proc_definition(&lexer, FunctionType::FTFunc, true, current),
        TokenType::FuncExt => return parse_func_proc_definition(&lexer, FunctionType::FTFuncExt, false, current),
        TokenType::Macro => return parse_func_proc_definition(&lexer, FunctionType::FTMacro, true, current),
        TokenType::Proc => return parse_func_proc_definition(&lexer, FunctionType::FTProc, true, current),
        TokenType::ProcExt => return parse_func_proc_definition(&lexer, FunctionType::FTProcExt, false, current),
        TokenType::Enum => return enum_definition(&lexer, current),
        TokenType::Struct => return parse_struct_definition(&lexer, current),
        TokenType::LeftParen => return parse_list(&lexer, current),
        TokenType::Identifier => return parse_primary_identifier(&lexer, current),
        _ => return Err(format!("{}:{}: parse error: Expected primary expression, found {:?}.",
                                t.line, t.col, t.token_type)),
    }
}

fn return_statement(lexer: &Lexer, current: &mut usize) -> Result<Expr, String> {
    let initial_current = *current;
    *current = *current + 1;
    let mut params : Vec<Expr> = Vec::new();
    match parse_primary(&lexer, current) {
        Ok(prim) => {
            params.push(prim);
        },
        Err(_err_str) => {},
    };
    let mut t = lexer.get_token(*current)?;
    while t.token_type == TokenType::Comma {
        *current = *current + 1;
        let prim2 = match parse_primary(&lexer, current) {
            Ok(to_ret) => to_ret,
            Err(err_str) => return Err(err_str),
        };
        params.push(prim2);
        t = lexer.get_token(*current)?;
    }
    Ok(Expr::new_parse(NodeType::Return, lexer.get_token(initial_current)?.clone(), params))
}

fn if_statement(lexer: &Lexer, current: &mut usize) -> Result<Expr, String> {
    let initial_current = *current;
    *current = *current + 1;
    let mut params : Vec<Expr> = Vec::new();
    let prim = match parse_primary(&lexer, current) {
        Ok(to_ret) => to_ret,
        Err(err_str) => return Err(err_str),
    };
    params.push(prim);
    let mut t = lexer.get_token(*current)?;
    if t.token_type != TokenType::LeftBrace {
        return Err(format!("{}:{}: parse error: Expected '{{' after condition in 'if' statement, found {:?}.", t.line, t.col, t.token_type));
    }
    *current = *current + 1;
    let body = match parse_body(&lexer, current, TokenType::RightBrace) {
        Ok(body) => body,
        Err(err_str) => return Err(err_str),
    };
    params.push(body);
    *current = *current + 1;
    t = lexer.get_token(*current)?;
    if t.token_type == TokenType::Else {
        *current = *current + 1;
        t = lexer.get_token(*current)?;
        if t.token_type != TokenType::LeftBrace {
            return Err(format!("{}:{}: parse error: Expected '{{' after 'else'.", t.line, t.col));
        }
        *current = *current + 1;
        let body = match parse_body(&lexer, current, TokenType::RightBrace) {
            Ok(body) => body,
            Err(err_str) => return Err(err_str),
        };
        params.push(body);
        *current = *current + 1;
    }
    Ok(Expr::new_parse(NodeType::If, lexer.get_token(initial_current)?.clone(), params))
}

fn while_statement(lexer: &Lexer, current: &mut usize) -> Result<Expr, String> {
    let initial_current = *current;
    *current = *current + 1;
    let mut params : Vec<Expr> = Vec::new();
    let prim = match parse_primary(&lexer, current) {
        Ok(to_ret) => to_ret,
        Err(err_str) => return Err(err_str),
    };
    params.push(prim);
    let t = lexer.get_token(*current)?;
    if t.token_type != TokenType::LeftBrace {
        return Err(format!("{}:{}: parse error: Expected '{{' after condition in 'while' statement.", t.line, t.col));
    }
    *current = *current + 1;
    let body = match parse_body(&lexer, current, TokenType::RightBrace) {
        Ok(body) => body,
        Err(err_str) => return Err(err_str),
    };
    params.push(body);
    *current = *current + 1;
    Ok(Expr::new_parse(NodeType::While, lexer.get_token(initial_current)?.clone(), params))
}

fn current_token_type<'a>(lexer: &'a Lexer, current: &'a mut usize) -> &'a TokenType {
    return &lexer.get_token(*current).unwrap().token_type;
}

fn parse_switch_statement(lexer: &Lexer, current: &mut usize) -> Result<Expr, String> {
    let t = lexer.get_token(*current)?;
    let initial_current = *current;
    *current = *current + 1;
    let mut params : Vec<Expr> = Vec::new();
    let prim = match parse_primary(&lexer, current) {
        Ok(to_ret) => to_ret,
        Err(err_str) => return Err(err_str),
    };
    params.push(prim);

    if &TokenType::LeftBrace != current_token_type(&lexer, current) {
        return Err(format!("{}:{}: parse error: Expected '{{' after primary expression in 'switch' statement.", t.line, t.col));
    }
    *current = *current + 1;

    let mut end_found = false;
    while *current < lexer.len() && !end_found {
        let mut next_t = lexer.get_token(*current)?;
        if next_t.token_type != TokenType::Case {
            return Err(format!("{}:{}: parse error: Expected 'case' in switch, found {:?}", next_t.line, next_t.col, next_t.token_type));
        }

        *current = *current + 1;
        next_t = lexer.get_token(*current)?;
        if next_t.token_type == TokenType::Colon {
            params.push(Expr::new_parse(NodeType::DefaultCase, t.clone(), Vec::new()));
        } else {
            let prim = match parse_primary(&lexer, current) {
                Ok(to_ret) => to_ret,
                Err(err_str) => return Err(err_str),
            };
            params.push(prim);
        }

        next_t = lexer.get_token(*current)?;
        if next_t.token_type != TokenType::Colon {
            return Err(format!("{}:{}: parse error: Expected ':' case <primary_expr> in switch, found {:?}",
                               next_t.line, next_t.col, next_t.token_type));
        }

        *current = *current + 1;
        next_t = lexer.get_token(*current)?;
        let mut body_params : Vec<Expr> = Vec::new();
        while *current < lexer.len() {
            if next_t.token_type == TokenType::RightBrace {
                params.push(Expr::new_parse(NodeType::Body, t.clone(), body_params));
                end_found = true;
                *current = *current + 1;
                break;
            }
            if next_t.token_type == TokenType::Case {
                params.push(Expr::new_parse(NodeType::Body, t.clone(), body_params));
                break;
            }
            let stmt = match parse_statement(&lexer, current) {
                Ok(statement) => statement,
                Err(error_string) => return Err(error_string),
            };
            body_params.push(stmt);
            next_t = lexer.get_token(*current)?;
            if next_t.token_type == TokenType::Semicolon {
                *current = *current + 1;
                next_t = lexer.get_token(*current)?;
            }
        }
    }
    if end_found {
        return Ok(Expr::new_parse(NodeType::Switch, lexer.get_token(initial_current)?.clone(), params))
    }
    return Err(format!("parse error: Expected '}}' to end switch."));
}

fn parse_declaration(lexer: &Lexer, current: &mut usize, is_mut: bool, explicit_type: &str) -> Result<Expr, String> {
    let t = lexer.get_token(*current)?;
    let decl_name = &t.token_str;
    let initial_current = *current;
    *current = *current + 3; // skip identifier, colon and equal
    if explicit_type != INFER_TYPE {
        *current = *current + 1; // skip type identifier
    }
    let mut params : Vec<Expr> = Vec::new();
    let prim = match parse_primary(&lexer, current) {
        Ok(to_ret) => to_ret,
        Err(err_str) => return Err(err_str),
    };
    params.push(prim);
    let explicit_value_type = str_to_value_type(explicit_type);
    let decl = Declaration{name: decl_name.to_string(), value_type: explicit_value_type, is_mut: is_mut};
    return Ok(Expr::new_parse(NodeType::Declaration(decl), lexer.get_token(initial_current)?.clone(), params))
}

fn parse_mut_declaration(lexer: &Lexer, current: &mut usize) -> Result<Expr, String> {
    let t = lexer.get_token(*current)?;
    let mut next_t = lexer.get_token(*current + 1)?;
    let mut next_token_type = &next_t.token_type;
    if next_token_type != &TokenType::Identifier {
        return Err(format!("{}:{}: parse error: Expected identifier after 'mut', found {:?}.", t.line, t.col, next_token_type));
    }
    let identifier = &next_t.token_str;
    *current = *current + 1;
    next_t = lexer.get_token(*current + 1)?;
    next_token_type = &next_t.token_type;
    if next_token_type != &TokenType::Colon {
        return Err(format!("{}:{}: parse error: Expected ':' after 'mut {}', found {:?}.", t.line, t.col, identifier, next_token_type));
    }
    let next_next_t = lexer.get_token(*current + 2)?;
    let next_next_token_type = &next_next_t.token_type;
    match next_next_token_type {
        TokenType::Identifier => {
            let type_name = &next_next_t.token_str;
            return parse_declaration(&lexer, current, true, type_name)
        }
        TokenType::Equal => {
            return parse_declaration(&lexer, current, true, INFER_TYPE)
        },
        _ => {
            Err(format!("{}:{}: parse error: Expected a type identifier or '=' after 'mut {} :' in statement, found {:?}.",
                        t.line, t.col, identifier, next_next_token_type))
        },
    }
}

fn parse_statement(lexer: &Lexer, current: &mut usize) -> Result<Expr, String> {
    let t = lexer.get_token(*current)?;
    match &t.token_type {
        TokenType::For => {
            return Err(format!("{}:{}: parse error: Suggestion: use 'while' for now.\nExplanation: keyword 'for' is not supported yet,", t.line, t.col));
        },
        TokenType::Return => return return_statement(&lexer, current),
        TokenType::If => return if_statement(&lexer, current),
        TokenType::While => return while_statement(&lexer, current),
        TokenType::Switch => return parse_switch_statement(&lexer, current),
        TokenType::Mut => return parse_mut_declaration(&lexer, current),
        TokenType::Identifier => return parse_statement_identifier(&lexer, current),
        _ => {
            Err(format!("{}:{}: parse error: Expected statement, found {:?}.", t.line, t.col, t.token_type))
        },
    }
}

fn parse_body(lexer: &Lexer, current: &mut usize, end_token: TokenType) -> Result<Expr, String> {

    let initial_current: usize = *current;
    let mut params : Vec<Expr> = Vec::new();
    let mut end_found = false;
    while *current < lexer.len() && !end_found {
        let token_type = &lexer.get_token(*current)?.token_type;
        if token_type == &end_token {
            end_found = true;
            break;
        }
        if token_type == &TokenType::Semicolon { // REM: TokenType::DoubleSemicolon results in a lexical error, no need to parse it
            *current = *current + 1;
            continue;
        }

        let stmt = match parse_statement(&lexer, current) {
            Ok(statement) => statement,
            Err(error_string) => return Err(error_string),
        };
        params.push(stmt);
    }
    if end_found {
        return Ok(Expr::new_parse(NodeType::Body, lexer.get_token(initial_current)?.clone(), params))
    }
    return Err(format!("parse error: Expected {:?} to end body.", end_token));
}

fn parse_tokens(lexer: Lexer, current: &mut usize) -> Result<Expr, String> {

    let e: Expr = match parse_body(&lexer, current, TokenType::Eof) {
        Ok(expr) => expr,
        Err(error_string) => return Err(error_string),
    };
    *current = *current + 1; // Add one for the EOF

    let mut i = *current;
    let mut unparsed_tokens = 0;
    let lexer_len = lexer.len();
    if i < lexer_len {
        unparsed_tokens = lexer_len - i;
    }
    if unparsed_tokens > 0 {
        println!("Total tokens parsed: {}/{}", current, lexer_len);
    }
    while i < lexer_len {
        let t = lexer.get_token(i)?;
        println!("Token: {:?}", t);
        i = i + 1;
    }
    if unparsed_tokens > 0 {
        return Err(format!("Total unparsed tokens: {}/{}", unparsed_tokens, lexer_len));
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
    funcs: HashMap<String, SFuncDef>, // REM: currently funcs are not on symbols, perhaps they should?
    enum_defs: HashMap<String, SEnumDef>,
    enums: HashMap<String, EnumVal>,
    struct_defs: HashMap<String, SStructDef>,
    bools: HashMap<String, bool>,
    i64s: HashMap<String, i64>,
    strings: HashMap<String, String>,
}

impl Context {
    fn new(mode_name: &str) -> Context {
        return Context {
            mode: mode_from_name(mode_name).unwrap(),
            symbols: HashMap::new(),
            funcs: HashMap::new(),
            enum_defs: HashMap::new(),
            enums: HashMap::new(),
            struct_defs: HashMap::new(),
            bools: HashMap::new(),
            i64s: HashMap::new(),
            strings: HashMap::new(),
        };
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
        "btoi" => true, // necessary for branchless arithmetics
        "btoa" => true,
        "itoa" => true,
        "atoi" => true,
        "str_eq" => true,
        "concat" => true,
        _ => false,
    }
}

fn is_core_proc(proc_name: &str) -> bool {
    match proc_name {
        "exit" => true,
        "print" => true,
        "println" => true, // TODO self host using print once the self escaped '\n' bug is fixed
        // TODO parse with dots like other languages, then change the direction of the slash depending on the os
        // TODO use imports in declarations:
        // example_cil: my_matrix_def := import(matrix.matrix_def)
        // example_cil: my_matrix : struct = import(matrix)
        // example_python: from matrix import matrix_def as my_matrix_def
        "import" => true,
        "runfile" => true,
        "input_read_line" => true,
        "eval_to_str" => true,
        // TODO implement more core procs in rust:
        "readfile" => true,
        "writefile" => true,
        "eval_to_ast_str" => true,
        "eval_to_expr" => true,
        _ => false,
    }
}

fn get_func_name_in_call(e: &Expr) -> String {
    assert!(e.node_type == NodeType::FCall);
    assert!(e.params.len() > 0);
    match &e.get(0).node_type {
        NodeType::Identifier(f_name) => return f_name.clone(),
        _ => panic!("panic calling get_func_name_in_call(), this should never happen."),
    }
}

fn value_type_func_proc(e: &Expr, name: &str, func_def: &SFuncDef) -> Result<ValueType, String> {
    match func_def.returns.len() {
        0 => {
            return Err(format!("{}:{}: {} error: func '{}' does not return anything", e.line, e.col, LANG_NAME, name))
        },
        1 => {
            match func_def.returns.get(0).unwrap() {
                ValueType::TBool => Ok(ValueType::TBool),
                ValueType::TI64 => Ok(ValueType::TI64),
                ValueType::TString => Ok(ValueType::TString),
                ValueType::TCustom(type_str) => Ok(ValueType::TCustom(type_str.to_string())), // TODO find a better way
                _ => return Err(format!("{}:{}: {} error: func '{}' returns unsupported type {}",
                                        e.line, e.col, LANG_NAME, name, value_type_to_str(func_def.returns.get(0).unwrap()))),
            }
        },
        _ => {
            return Err(format!("{}:{}: {} error: func '{}' returns multiple values, but that's not implemented yet.", e.line, e.col, LANG_NAME, name));
        },
    }
}

fn get_fcall_value_type(context: &Context, e: &Expr) -> Result<ValueType, String> {

    let f_name = get_func_name_in_call(&e);
    if context.funcs.contains_key(&f_name) {
        return value_type_func_proc(&e, &f_name, &context.funcs.get(&f_name).unwrap())
    } else if is_core_func(&f_name) {
        return Err(format!("{}:{}: mode '{}' error: core func '{}' is not in this context", e.line, e.col, context.mode.name, &f_name));
    } else if is_core_proc(&f_name) {
        return Err(format!("{}:{}: mode '{}' error: core proc '{}' is not in this context", e.line, e.col, context.mode.name, &f_name));
    } else if context.symbols.contains_key(&f_name) {

        let symbol = context.symbols.get(&f_name).unwrap();
        match symbol.value_type {
            ValueType::TStructDef => {
                let struct_def = match context.struct_defs.get(&f_name) {
                    Some(_struct_def) => _struct_def,
                    None => {
                        return Err(format!("{}:{}: {} error: struct '{}' not found in context", e.line, e.col, LANG_NAME, f_name));
                    },
                };
                let id_expr = e.get(0);
                let after_dot = match id_expr.params.get(0) {
                    Some(_after_dot) => _after_dot,
                    None => {
                        return Ok(ValueType::TCustom(f_name.clone()));
                    },
                };
                match &after_dot.node_type {
                    NodeType::Identifier(after_dot_name) => {
                        let member_decl = match struct_def.members.get(after_dot_name) {
                            Some(_member) => _member,
                            None => {
                                return Err(format!("{}:{}: type error: struct '{}' has no member '{}' a", e.line, e.col, f_name, after_dot_name));
                            },
                        };
                        let member_default_value = match struct_def.default_values.get(after_dot_name) {
                            Some(_member) => _member,
                            None => {
                                return Err(format!("{}:{}: type error: struct '{}' has no member '{}' b", e.line, e.col, f_name, after_dot_name));
                            },
                        };
                        match &member_default_value.node_type {
                            NodeType::FuncDef(func_def) => {
                                let combined_name = format!("{}.{}", f_name, after_dot_name);
                                return value_type_func_proc(&e, &combined_name, &func_def);
                            },
                            _  => {
                                return Err(format!("{}:{}: type error: Cannot call '{}.{}', it is not a function, it is '{}'",
                                                   e.line, e.col, f_name, after_dot_name, value_type_to_str(&member_decl.value_type)));
                            },
                        }
                    },
                    _ => {
                        return Err(format!("{}:{}: {} error: expected identifier after '{}.' found {:?}",
                                           e.line, e.col, LANG_NAME, f_name, after_dot.node_type));
                    },
                }
            },
            _ => { // For UFCS
                let id_expr = e.get(0);
                let after_dot = match id_expr.params.get(0) {
                    Some(_after_dot) => _after_dot,
                    None => {
                        return Err(format!("{}:{}: type error: Cannot call '{}', it is not a function or struct, it is a {:?}",
                                           e.line, e.col, &f_name, symbol.value_type));
                    },
                };
                match &after_dot.node_type {
                    NodeType::Identifier(after_dot_name) => {
                        if context.funcs.contains_key(after_dot_name) {
                            return value_type_func_proc(&e, &f_name, &context.funcs.get(after_dot_name).unwrap())
                        }
                        return Err(format!("{}:{}: {} error: expected function name after '{}.' found {:?}",
                                           e.line, e.col, LANG_NAME, f_name, after_dot_name));
                    },
                    _ => {
                        return Err(format!("{}:{}: {} error: expected identifier after '{}.' found {:?}",
                                           e.line, e.col, LANG_NAME, f_name, after_dot.node_type));
                    },
                }
            },
        }

    } else {
        return Err(format!("{}:{}: type error: Undefined symbol '{}'", e.line, e.col, &f_name));
    }
}

fn get_value_type(context: &Context, e: &Expr) -> Result<ValueType, String> {
    match &e.node_type {
        NodeType::LBool(_) => Ok(ValueType::TBool),
        NodeType::LI64(_) => Ok(ValueType::TI64),
        NodeType::LString(_) => Ok(ValueType::TString),
        NodeType::LList(_) => Ok(ValueType::TList),
        NodeType::FuncDef(func_def) => match func_def.function_type {
            FunctionType::FTFunc | FunctionType::FTFuncExt => Ok(ValueType::TFunc),
            FunctionType::FTProc | FunctionType::FTProcExt => Ok(ValueType::TProc),
            FunctionType::FTMacro => Ok(ValueType::TMacro),
        },
        NodeType::EnumDef(_) => Ok(ValueType::TEnumDef),
        NodeType::StructDef(_) => Ok(ValueType::TStructDef),
        NodeType::FCall => get_fcall_value_type(&context, &e),
        NodeType::Identifier(name) => {
            let symbol_info = match context.symbols.get(name) {
                Some(symbol_info_m) => {
                    symbol_info_m
                },
                None => {
                    return Err(format!("{}:{}: type error: Undefined symbol '{}'", e.line, e.col, name));
                }
            };
            if e.params.len() == 0 {
                return Ok(symbol_info.value_type.clone());
            }
            let member_str = match &e.get(0).node_type {
                NodeType::Identifier(member_name) => member_name,
                node_type => return Err(format!("{}:{}: {} error: identifiers can only contain identifiers, found {:?}.",
                                                LANG_NAME, e.line, e.col, node_type)),
            };

            match symbol_info.value_type {
                ValueType::TStructDef => {
                    match context.struct_defs.get(name) {
                        Some(struct_def) => {
                            match struct_def.members.get(member_str) {
                                Some(decl) => {
                                    if !decl.is_mut {
                                        return Ok(decl.value_type.clone());
                                    } else {
                                        return Err(format!("{}:{}: type error: struct '{}' has no const (static) member '{}', an instance is needed to access mutable members",
                                                           e.line, e.col, name, member_str));
                                    }
                                },
                                _ => {
                                    return Err(format!("{}:{}: type error: struct '{}' has no member '{}' d", e.line, e.col, name, member_str))
                                },
                            }
                        },
                        None => {
                            return Err(format!("{}:{}: {} error: Undefined struct '{}'", LANG_NAME, e.line, e.col, name));
                        },
                    }
                },
                ValueType::TEnumDef => {
                    match context.enum_defs.get(name) {
                        Some(enum_def) => {
                            if enum_def.enum_map.contains_key(member_str) {
                                if e.params.len() > 1 {
                                    let extra_member_str = match &e.get(1).node_type {
                                        NodeType::Identifier(member_name) => member_name,
                                        node_type => return Err(format!("{}:{}: {} error: identifiers can only contain identifiers, found {:?}.",
                                                                        e.line, e.col, LANG_NAME, node_type)),
                                    };
                                    return Err(format!("{}:{}: type error: Suggestion: remove '.{}' after '{}.{}'\nExplanation: enum value '{}.{}' cannot have members",
                                                       e.line, e.col, extra_member_str, name, member_str, name, member_str));
                                }
                                if name.to_string() == "Type" {
                                    return Ok(ValueType::TType);
                                }
                                return Ok(ValueType::TCustom(name.to_string()));
                            }
                            return Err(format!("{}:{}: type error: enum '{}' has no value '{}'", e.line, e.col, name, member_str));
                        }
                        None => {
                            return Err(format!("{}:{}: {} error: Undefined enum '{}'", e.line, e.col, LANG_NAME, name));
                        }
                    }
                },
                _ => {
                    return Err(format!("{}:{}: type error: '{}' of type '{}' can't have members, '{}' is not a member",
                                       e.line, e.col, value_type_to_str(&symbol_info.value_type), name, member_str))
                },
            }
        },
        node_type => return Err(format!("{}:{}: {} error: get_value_type() not implement for {:?} yet.", e.line, e.col, LANG_NAME, node_type)),
    }
}

fn init_context(context: &mut Context, e: &Expr) -> Vec<String> {
    let mut errors : Vec<String> = Vec::new();
    match &e.node_type {
        NodeType::Body => {
            for se in &e.params {
                let mut stmt_context_errors = init_context(context, &se);
                errors.append(&mut stmt_context_errors);
            }
        },
        NodeType::FCall => {
            let f_name = get_func_name_in_call(&e);
            if f_name == "import" {
                eval_core_proc_import(context, &e);
            }
        },
        NodeType::Declaration(decl) => {
                    if context.funcs.contains_key(&decl.name) || context.symbols.contains_key(&decl.name) {
                errors.push(format!("{}:{}: compiler error: '{}' already declared.", e.line, e.col, decl.name));
            }
            assert!(e.params.len() == 1, "{} error: in init_context, while declaring {}, declarations must take exactly one value.", LANG_NAME, decl.name);
            let inner_e = e.get(0);
            let value_type = match get_value_type(&context, &inner_e) {
                Ok(val_type) => val_type,
                Err(error_string) => {
                    errors.push(error_string);
                    return errors;
                },
            };
            if decl.value_type != str_to_value_type(INFER_TYPE) {
                if value_type != decl.value_type {
                    errors.push(format!("{}:{}: type error: '{}' declared of type '{}' but initialized to type '{}'.", e.line, e.col, decl.name, value_type_to_str(&decl.value_type), value_type_to_str(&value_type)));
                }
            }
            match value_type {
                ValueType::TFunc | ValueType::TProc | ValueType::TMacro => {
                    match &inner_e.node_type {
                        NodeType::FuncDef(func_def) => {
                            context.symbols.insert(decl.name.to_string(), SymbolInfo{value_type: value_type.clone(), is_mut: decl.is_mut});
                            context.funcs.insert(decl.name.to_string(), func_def.clone());
                        },
                        _ => {
                            errors.push(format!("{}:{}: {} error: {}s should have definitions", e.line, e.col, LANG_NAME, value_type_to_str(&value_type)));
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
                            errors.push(format!("{}:{}: {} error: enums should have definitions.", e.line, e.col, LANG_NAME));
                            return errors;
                        },
                    }
                },
                ValueType::TStructDef => {
                    assert!(inner_e.params.len() == 0, "{} error: while declaring {}, struct declarations must have exactly 0 params.", LANG_NAME,
                            decl.name);
                    match &inner_e.node_type {
                        NodeType::StructDef(struct_def) => {
                            context.symbols.insert(decl.name.to_string(), SymbolInfo{value_type: value_type.clone(), is_mut: decl.is_mut});
                            context.struct_defs.insert(decl.name.to_string(), struct_def.clone());
                        },
                        _ => {
                            errors.push(format!("{}:{}: {} error: enums should have definitions.", e.line, e.col, LANG_NAME));
                            return errors;
                        },
                    }
                },

                ValueType::TType | ValueType::TBool | ValueType::TI64 | ValueType::TString | ValueType::TList |
                ValueType::TMulti(_) | ValueType::TCustom(_) | ValueType::ToInferType => {
                    context.symbols.insert(decl.name.to_string(), SymbolInfo{value_type: value_type.clone(), is_mut: decl.is_mut});
                },
            }
        }
        _ => {
            if !context.mode.allows_base_anything {
                        if context.mode.allows_base_calls {
                    errors.push(format!("{}:{}: mode '{}' allows only declarations and calls in the root context, found {:?}.",
                                        e.line, e.col, context.mode.name, e.node_type));
                } else {
                    errors.push(format!("{}:{}: mode '{}' allows only declarations in the root context, found {:?}.",
                                        e.line, e.col, context.mode.name, e.node_type));
                }
            }
        },
    }
    errors
}

// ---------- Type checking

fn does_func_return_bool(context: &Context, name: &str) -> bool {
    if context.funcs.contains_key(name) {
        let func_def = &context.funcs.get(name).unwrap();
        return func_def.returns.len() == 1 && *func_def.returns.get(0).unwrap() == ValueType::TBool;
    }
    return false;
}

fn is_expr_calling_procs(context: &Context, e: &Expr) -> bool {
    match &e.node_type {
        NodeType::Body => {
            for se in &e.params {
                if is_expr_calling_procs(&context, &se) {
                    return true;
                }
            }
            false
        },
        NodeType::StructDef(_) => {
            // TODO default values could try to call procs
            false
        },
        NodeType::EnumDef(_) => {
            false
        },
        NodeType::LBool(_) => false,
        NodeType::LI64(_) => false,
        NodeType::LList(_) => false,
        NodeType::LString(_) => false,
        NodeType::DefaultCase => false,
        NodeType::Identifier(_) => false,
        NodeType::FCall => {
            let f_name = get_func_name_in_call(&e);
            return context.symbols.contains_key(&f_name) && context.symbols.get(&f_name).unwrap().value_type == ValueType::TProc
        },
        NodeType::Declaration(decl) => {
            assert!(e.params.len() == 1, "{} error: while declaring {}, declarations must take exactly one value.", LANG_NAME, decl.name);
            is_expr_calling_procs(&context, &e.get(0))
        },
        NodeType::Assignment(var_name) => {
            assert!(e.params.len() == 1, "{} error: while assigning {}, assignments must take exactly one value, not {}.", LANG_NAME, var_name, e.params.len());
            is_expr_calling_procs(&context, &e.get(0))
        }
        NodeType::FuncDef(func_def) => {
            for it_e in &func_def.body {
                if is_expr_calling_procs(&context, &it_e) {
                    return true;
                }
            }
            false
        },
        NodeType::If | NodeType::While | NodeType::Switch | NodeType::Return => {
            for it_e in &e.params {
                if is_expr_calling_procs(&context, &it_e) {
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

fn basic_mode_checks(context: &Context, e: &Expr) -> Vec<String> {
    let mut errors : Vec<String> = Vec::new();

    match &e.node_type {
        NodeType::Body => {
            for p in e.params.iter() {
                match &p.node_type {

                    NodeType::Declaration(decl) => {
                        if !context.mode.allows_base_mut && decl.is_mut {
                            errors.push(format!("{}:{}: {} error: mode {} doesn't allow mut declaration of 'mut {}'.\nSuggestion: remove 'mut' or change to mode script or cli",
                                e.line, e.col, "mode", context.mode.name, decl.name));
                        }
                    },
                    NodeType::FCall => {
                        if !context.mode.allows_base_calls {
                            let f_name = get_func_name_in_call(&e);
                            errors.push(format!("{}:{}: {} error: mode {} doesn't allow calls in the root context of the file'.\nSuggestion: remove the call to '{}' or change mode 'test' or 'script'",
                                e.line, e.col, "mode", context.mode.name, f_name));
                        }
                    },
                    _ => {},
                }
            }
        },
        _ => panic!("check_needs_main_proc() expects a body expression, this should never happen."),
    }

    if context.mode.needs_main_proc {
        match context.symbols.get("main") {
            Some(symbol_info) => {
                if symbol_info.value_type != ValueType::TProc {
                    errors.push(format!("{}:{}: mode error: mode {} requires 'main' to be defined as a proc. It was defined as a {} instead",
                                        e.line, e.col, context.mode.name, value_type_to_str(&symbol_info.value_type)));
                }
            },
            None => {
                errors.push(format!("{}:{}: mode error: mode {} requires 'main' to be defined as a proc.", e.line, e.col, context.mode.name));
            },
        };
    }
    return errors;
}

fn check_enum_def(e: &Expr, enum_def: &SEnumDef) -> Vec<String> {
    assert!(e.params.len() == 0, "{} error: in check_types(): enum declarations don't have any parameters in the tree.", LANG_NAME);
    let mut errors : Vec<String> = Vec::new();

    for (_enum_val_name, enum_opt) in &enum_def.enum_map {
        match &enum_opt {
            None => {},
            Some(value_type) => {
                match value_type {
                    ValueType::TCustom(ref custom_type_name) => {
                        errors.push(format!("{}:{}: 'enum' does not support custom types yet, found custom type '{}'.",
                                            e.line, e.col, custom_type_name));
                    },
                    _ => {},
                }
            },
        }
    }
    return errors;
}

fn check_if_statement(mut context: &mut Context, e: &Expr) -> Vec<String> {
    assert!(e.params.len() == 2 || e.params.len() == 3, "{} error: if nodes must have 2 or 3 parameters.", LANG_NAME);
    let mut errors : Vec<String> = Vec::new();

    let inner_e = e.get(0);
    let value_type = match get_value_type(&context, &inner_e) {
        Ok(val_type) => val_type,
        Err(error_string) => {
            errors.push(error_string);
            return errors;
        },
    };

    let first_is_condition = ValueType::TBool == value_type;
    if !first_is_condition {
        errors.push(format!("{}:{}: type error: 'if' can only accept a bool condition first, found {:?}.",
                            inner_e.line, inner_e.col, &inner_e.node_type));
    }
    for p in e.params.iter() {
        errors.append(&mut check_types(&mut context, &p));
    }
    return errors;
}

fn check_while_statement(mut context: &mut Context, e: &Expr) -> Vec<String> {
    assert!(e.params.len() == 2, "{} error: while nodes must have exactly 2 parameters.", LANG_NAME);
    let mut errors : Vec<String> = Vec::new();

    let inner_e = e.get(0);
    let value_type = match get_value_type(&context, &inner_e) {
        Ok(val_type) => val_type,
        Err(error_string) => {
            errors.push(error_string);
            return errors;
        },
    };
    let first_is_condition = ValueType::TBool == value_type;
    if !first_is_condition {
        errors.push(format!("{}:{}: type error: 'while' can only accept a bool condition first, found {:?}.",
                            inner_e.line, inner_e.col, &inner_e.node_type));
    }
    for p in e.params.iter() {
        errors.append(&mut check_types(&mut context, &p));
    }
    return errors;
}

fn check_fcall(context: &Context, e: &Expr) -> Vec<String> {
    let mut errors : Vec<String> = Vec::new();

    let f_name = get_func_name_in_call(&e);
    let func_def;
    if context.funcs.contains_key(&f_name) {
        func_def = context.funcs.get(&f_name).unwrap();
    } else {
        let symbol = match context.symbols.get(&f_name) {
            Some(_symbol) => _symbol,
            None => {
                errors.push(format!("{}:{}: {} error: Undefined function or struct '{}'", e.line, e.col, LANG_NAME, f_name));
                return errors;
            },
        };
        match symbol.value_type {
            ValueType::TStructDef => {
                let struct_def = match context.struct_defs.get(&f_name) {
                    Some(_struct_def) => _struct_def,
                    None => {
                        errors.push(format!("{}:{}: struct '{}' not found in context.", e.line, e.col, f_name));
                        return errors;
                    },
                };

                if e.params.len() == 0 {
                    errors.push(format!("{}:{}: {} error: struct '{}' cannot be instanciated. Constructors not implemented yet",
                                        e.line, e.col, LANG_NAME, f_name));
                    return errors;
                }

                let after_dot = e.get(0).get(0);
                match &after_dot.node_type {
                    NodeType::Identifier(after_dot_name) => {
                        let member_value = match struct_def.default_values.get(after_dot_name) {
                            Some(_member_value) => _member_value,
                            None => {
                                errors.push(format!("{}:{}: struct '{}' has no member '{}' e", e.line, e.col, f_name, after_dot_name));
                                return errors;
                            },
                        };
                        match &member_value.node_type {
                            NodeType::FuncDef(_func_def) => {
                                func_def = &_func_def;
                            },
                            _ => {
                                errors.push(format!("{}:{}: Cannot call '{}.{}', it is a '{:?}', not a function.",
                                                    e.line, e.col, f_name, after_dot_name, member_value.node_type));
                                return errors;
                            },
                        }
                    },
                    _ => {
                        errors.push(format!("{}:{}: {} error: expected identifier after '{}.' found {:?}",
                                            e.line, e.col, LANG_NAME, f_name, after_dot.node_type));
                        return errors;
                    },
                }
            },
            _ => {
                errors.push(format!("{}:{}: Cannot call '{}', it is a '{:?}', not a function nor a struct.",
                                    e.line, e.col, f_name, symbol.value_type));
                return errors;
            }
        }
    }

    let has_multi_arg = func_proc_has_multi_arg(func_def);
    if !has_multi_arg && func_def.args.len() != e.params.len() - 1 {
        errors.push(format!("{}:{}: type error: Function/procedure '{}' expects {} args, but {} were provided.", e.line, e.col, &f_name, func_def.args.len(), e.params.len()));
    }
    if has_multi_arg && func_def.args.len() > e.params.len() - 1 {
        errors.push(format!("{}:{}: type error: Function/procedure '{}' expects at least {} args, but {} were provided.", e.line, e.col, &f_name, func_def.args.len(), e.params.len()));
    }

    let max_arg_def = func_def.args.len();
    for i in 0..e.params.len()-1 {
        let arg = func_def.args.get(std::cmp::min(i, max_arg_def-1)).unwrap();
        let expected_type = match &arg.value_type {
            ValueType::TMulti(inner_type) => inner_type,
            _ => &arg.value_type,

        };
        let found_type = match get_value_type(&context, e.get(i+1)) {
            Ok(val_type) => val_type,
            Err(error_string) => {
                errors.push(error_string);
                return errors;
            },
        };
        if expected_type != &found_type {
            if expected_type == &str_to_value_type(INFER_TYPE) {
                errors.push(format!("{}:{}: type error: calling func/proc '{}' declared arg {} without type, but type inference in args is not supported yet.\n Suggestion: the arg should be '{} : {},' instead of just '{},' Found type: {:?}",
                                    e.line, e.col, &f_name, arg.name, arg.name, value_type_to_str(&found_type), arg.name, value_type_to_str(&expected_type)));
            } else {
                errors.push(format!("{}:{}: type error: calling function '{}' expects '{:?}' for arg '{}', but '{:?}' was provided.",
                                    e.line, e.col, &f_name, expected_type, arg.name, found_type));
            }
        }
    }

    return errors;
}

fn check_func_proc_types(func_def: &SFuncDef, mut context: &mut Context, e: &Expr) -> Vec<String> {
    let mut errors : Vec<String> = Vec::new();
    let mut has_variadic = false;
    for arg in &func_def.args {
        if has_variadic {
            errors.push(format!("{}:{}: type error: Variadic argument '{}' must be the last (only one variadic argument allowed).",
                                e.line, e.col, &arg.name));
        }
        match &arg.value_type {
            ValueType::TMulti(_) => {
                has_variadic = true;
            }
            ValueType::TCustom(ref custom_type_name) => {
                if !context.symbols.contains_key(custom_type_name) {
                    errors.push(format!("{}:{}: type error: Argument '{}' is of undefined type {}.", e.line, e.col, &arg.name, &custom_type_name));
                }
                let _custom_symbol = context.symbols.get(custom_type_name).unwrap();
                // TODO check more type stuff
            },
            _ => {},
        }
        context.symbols.insert(arg.name.clone(), SymbolInfo{value_type: arg.value_type.clone(), is_mut: false});
    }

    let returns_len = func_def.returns.len();
    for p in func_def.body.iter() {
        match &p.node_type {
            NodeType::Return => {
                if returns_len != p.params.len() {
                    errors.push(format!("{}:{}: type error: Returning {} values when {} were expected.", e.line, e.col, returns_len, p.params.len()));
                } else {
                    for i in 0..p.params.len() {
                        let expected_value_type = func_def.returns.get(i).unwrap();
                        match get_value_type(&context, p.params.get(i).unwrap()) {
                            Ok(actual_value_type) => {
                                if expected_value_type != &actual_value_type {
                                    errors.push(format!("{}:{}: type error: Return value in pos {} expected to be {:?}, but found {:?} instead",
                                                        e.line, e.col, i, expected_value_type, actual_value_type));
                                }
                            },
                            Err(error_string) => {
                                errors.push(error_string);
                            },
                        };
                    }
                }
            },
            _ => {},
        }
        errors.append(&mut check_types(&mut context, &p));
    }

    // TODO should macros be allowed to call procs?
    if func_def.function_type == FunctionType::FTFunc {
        for se in &func_def.body {
            if is_expr_calling_procs(&context, &se) {
                errors.push(format!("{}:{}: type error: funcs cannot call procs.", se.line, se.col));
            }
        }
    }

    return errors
}

fn check_declaration(mut context: &mut Context, e: &Expr, decl: &Declaration) -> Vec<String> {
    assert!(e.params.len() == 1, "{} error: in declaration of {} declaration nodes must exactly 1 parameter.", LANG_NAME, decl.name);
    let mut errors : Vec<String> = Vec::new();

    let inner_e = e.get(0);
    if !context.symbols.contains_key(&decl.name) {
        let mut value_type = decl.value_type.clone();
        if value_type == ValueType::ToInferType {
            value_type = match get_value_type(&context, &inner_e) {
                Ok(val_type) => val_type,
                Err(error_string) => {
                    errors.push(error_string);
                    return errors;
                },
            };
        }
        // TODO move to init_context() ? inner contexts are not persisted in init_context
        context.symbols.insert(decl.name.to_string(), SymbolInfo{value_type: value_type.clone(), is_mut: decl.is_mut});
        match value_type {
            ValueType::ToInferType => {
                errors.push(format!("{}:{} {} error: Cannot infer the declaration type of {}", e.line, e.col, LANG_NAME, decl.name));
                return errors;
            },
            ValueType::TFunc | ValueType::TProc | ValueType::TMacro => {
                match &inner_e.node_type {
                    NodeType::FuncDef(func_def) => {
                        // TODO move to init_context() ? inner contexts are not persisted in init_context
                        context.funcs.insert(decl.name.clone(), func_def.clone());
                    },
                    _ => {
                        errors.push(format!("{}:{} {} error: functions should have definitions", e.line, e.col, LANG_NAME));
                        return errors;
                    },
                }
            },
            _ => {},
        }
    }
    errors.append(&mut check_types(&mut context, &inner_e));

    return errors
}

fn check_assignment(mut context: &mut Context, e: &Expr, var_name: &str) -> Vec<String> {
    assert!(e.params.len() == 1, "{} error: in assignment to {}, assignments must take exactly one value, not {}.", LANG_NAME, var_name, e.params.len());
    let mut errors : Vec<String> = Vec::new();

    if is_core_func(&var_name) {
        errors.push(format!("{}:{}: type error: Core function '{}' cannot be assigned to.", e.line, e.col, var_name));
    } else if is_core_proc(&var_name) {
        errors.push(format!("{}:{}: type error: Core procedure '{}' cannot be assigned to.", e.line, e.col, var_name));
    } else if context.funcs.contains_key(var_name)  {
        errors.push(format!("{}:{}: type error: User defined function '{}' cannot be assigned to.", e.line, e.col, var_name));
    } else if context.symbols.contains_key(var_name) {
        let symbol_info = context.symbols.get(var_name).unwrap();
        if !symbol_info.is_mut {
            errors.push(format!("{}:{}: compiler error: Cannot assign to constant '{}', Suggestion: declare it as 'mut'.", e.line, e.col, var_name));
        }
    } else {
        errors.push(format!("{}:{}: type error: Suggestion: try changing '{} =' for '{} :='\nExplanation: Cannot assign to undefined symbol '{}'.",
                            e.line, e.col, var_name, var_name, var_name));
    }
    errors.append(&mut check_types(&mut context, &e.get(0)));
    return errors
}

fn check_types(mut context: &mut Context, e: &Expr) -> Vec<String> {
    let mut errors : Vec<String> = Vec::new();
    match &e.node_type {
        NodeType::Body => {
            for p in e.params.iter() {
                errors.append(&mut check_types(&mut context, &p));
            }
        },

        NodeType::EnumDef(enum_def) => {
            errors.append(&mut check_enum_def(&e, enum_def));
        },
        NodeType::StructDef(_struct_def) => {
            assert!(e.params.len() == 0, "{} error: in check_types(): struct declarations must take exactly 0 params.", LANG_NAME);
        },

        NodeType::If => {
            errors.append(&mut check_if_statement(&mut context, &e));
        },
        NodeType::While => {
            errors.append(&mut check_while_statement(&mut context, &e));
        },
        NodeType::Switch => {
            assert!(e.params.len() >= 3, "{} error: switch nodes must have at least 3 parameters.", LANG_NAME);
            // TODO check that the type to be switch corresponds to each case
            // TODO check that there's a body param after each case
            // TODO check that all the cases are covered
            for p in e.params.iter() {
                errors.append(&mut check_types(&mut context, &p));
            }
        },

        NodeType::FCall => {
            errors.append(&mut check_fcall(&context, &e));
        },
        NodeType::FuncDef(func_def) => {
            let mut function_context = context.clone();
            errors.append(&mut check_func_proc_types(&func_def, &mut function_context, &e));
        },
        NodeType::Identifier(name) => {
            if !(context.funcs.contains_key(name) || context.symbols.contains_key(name)) {
                errors.push(format!("{}:{}: type error: Undefined symbol {}", e.line, e.col, name));
            }
        },

        NodeType::Declaration(decl) => {
            errors.append(&mut check_declaration(&mut context, &e, decl));
        },
        NodeType::Assignment(var_name) => {
            errors.append(&mut check_assignment(&mut context, &e, var_name));
        },
        NodeType::Return => {
            for return_val in &e.params {
                errors.append(&mut check_types(&mut context, &return_val));
            }
        },

        NodeType::LI64(_) | NodeType::LString(_) | NodeType::LBool(_) | NodeType::LList(_) | NodeType::DefaultCase => {},
    }

    return errors
}

// ---------- eval repl interpreter

fn eval_call_to_bool(mut context: &mut Context, e: &Expr) -> bool {
    // TODO refactor common code with eval_func_proc_call() to reuse
    let id_expr = e.get(0);
    let mut extra_arg = false;
    let f_name = if id_expr.params.len() == 0 {
        get_func_name_in_call(&e)
    } else {
        extra_arg = true;
        match &id_expr.get(0).node_type {
            NodeType::Identifier(f_name) => f_name.clone(),
            _ => panic!("panic eval_call_to_bool(), this should never happen."),
        }
    };

    if !does_func_return_bool(&context, &f_name) {
        panic!("{} error: eval_to_bool(): Function '{}' does not return bool. This should have been caught in the compile phase.\n", LANG_NAME, f_name);
    }

    if extra_arg {
        let id_expr_name = get_func_name_in_call(&e);
        let extr_arg_e = Expr::new_clone(NodeType::Identifier(id_expr_name), &e, Vec::new());
        let mut new_args = Vec::new();
        new_args.push(extr_arg_e);
        new_args.append(&mut e.params.clone());
        let new_e = Expr::new_clone(NodeType::Identifier(f_name.clone()), e.get(0), new_args);
        return lbool_in_string_to_bool(eval_func_proc_call(&f_name, &mut context, &new_e).as_str());
    }
    return lbool_in_string_to_bool(eval_func_proc_call(&f_name, &mut context, &e).as_str());
}

fn eval_to_bool(mut context: &mut Context, e: &Expr) -> bool {

    match &e.node_type {
        NodeType::LBool(b_value) => return *b_value,
        NodeType::FCall => return eval_call_to_bool(&mut context, &e),
        NodeType::Identifier(name) => {
            if context.bools.contains_key(name) {
                return context.bools.get(name).unwrap().clone();
            }
            if context.struct_defs.contains_key(name) {
                let struct_def = context.struct_defs.get(name).unwrap();

                if e.params.len() == 0 {
                    panic!("{} error: eval_to_bool(): struct '{}' is not a bool.", LANG_NAME, name);
                }
                let after_dot = e.get(0);
                match &after_dot.node_type {
                    NodeType::Identifier(after_dot_name) => {
                        let member_decl = match struct_def.members.get(after_dot_name) {
                            Some(_member) => _member,
                            None => {
                                panic!("{} eval error: eval_to_bool(): struct '{}' has no member '{}'", LANG_NAME, name, after_dot_name);
                            },
                        };

                        let combined_name = format!("{}.{}", name, after_dot_name);
                        if context.bools.contains_key(&combined_name) {
                            return context.bools.get(&combined_name).unwrap().clone();
                        }
                        panic!("{} eval error: eval_to_bool(): '{}' is not a bool, it is a '{}'",
                               LANG_NAME, combined_name, value_type_to_str(&member_decl.value_type));
                    },

                    _ => {
                        panic!("{} eval error: eval_to_bool(): expected identifier after '{}.' found {:?}",
                               LANG_NAME, name, after_dot.node_type);
                    },
                }
            }

            panic!("{} eval error: eval_to_bool(): Identifier '{}' is not a bool.", LANG_NAME, name);
        },
        node_type => {
            panic!("{} eval error: eval_to_bool(): The only types that can be evaluated to bool are currently 'LBool', 'FCall' and 'Identifier'. Found '{:?}'",
                   LANG_NAME, node_type)
        },
    }
}

// ---------- core funcs implementations for eval

fn eval_core_func_and(mut context: &mut Context, e: &Expr) -> String {
    let mut truthfulness = true;
    for i in 1..e.params.len() {
        truthfulness = truthfulness && eval_to_bool(&mut context, &e.get(i));
    }
    truthfulness.to_string()
}

fn eval_core_func_or(mut context: &mut Context, e: &Expr) -> String {
    let mut truthfulness = false;
    for i in 1..e.params.len() {
        truthfulness = truthfulness || eval_to_bool(&mut context, &e.get(i));
    }
    truthfulness.to_string()
}

fn eval_core_func_not(mut context: &mut Context, e: &Expr) -> String {
    assert!(e.params.len() == 2, "{} Error: Core func 'not' only takes 1 argument. This should never happen.", LANG_NAME);
    (!eval_to_bool(&mut context, &e.get(1))).to_string()
}

fn eval_core_func_eq(mut context: &mut Context, e: &Expr) -> String {
    assert!(e.params.len() == 3, "{} Error: Core func 'eq' takes exactly 2 arguments. This should never happen.", LANG_NAME);
    let a = &eval_expr(&mut context, e.get(1)).parse::<i64>().unwrap();
    let b = &eval_expr(&mut context, e.get(2)).parse::<i64>().unwrap();
    (a == b).to_string()
}

fn eval_core_func_str_eq(mut context: &mut Context, e: &Expr) -> String {
    assert!(e.params.len() == 3, "{} Error: Core func 'str_eq' takes exactly 2 arguments. This should never happen.", LANG_NAME);
    let a = &eval_expr(&mut context, e.get(1));
    let b = &eval_expr(&mut context, e.get(2));
    (a == b).to_string()
}

fn eval_core_func_concat(mut context: &mut Context, e: &Expr) -> String {
    assert!(e.params.len() == 3, "{} Error: Core func 'concat' takes exactly 2 arguments. This should never happen.", LANG_NAME);
    let a = eval_expr(&mut context, e.get(1));
    let b = eval_expr(&mut context, e.get(2));
    format!("{}{}", a, b)
}

fn eval_core_func_lt(mut context: &mut Context, e: &Expr) -> String {
    assert!(e.params.len() == 3, "{} Error: Core func 'eq' takes exactly 2 arguments. This should never happen.", LANG_NAME);
    let a = &eval_expr(&mut context, e.get(1)).parse::<i64>().unwrap();
    let b = &eval_expr(&mut context, e.get(2)).parse::<i64>().unwrap();
    (a < b).to_string()
}

fn eval_core_func_lteq(mut context: &mut Context, e: &Expr) -> String {
    assert!(e.params.len() == 3, "{} Error: Core func 'eq' takes exactly 2 arguments. This should never happen.", LANG_NAME);
    let a = &eval_expr(&mut context, e.get(1)).parse::<i64>().unwrap();
    let b = &eval_expr(&mut context, e.get(2)).parse::<i64>().unwrap();
    (a <= b).to_string()
}

fn eval_core_func_gt(mut context: &mut Context, e: &Expr) -> String {
    assert!(e.params.len() == 3, "{} Error: Core func 'eq' takes exactly 2 arguments. This should never happen.", LANG_NAME);
    let a = &eval_expr(&mut context, e.get(1)).parse::<i64>().unwrap();
    let b = &eval_expr(&mut context, e.get(2)).parse::<i64>().unwrap();
    (a > b).to_string()
}

fn eval_core_func_gteq(mut context: &mut Context, e: &Expr) -> String {
    assert!(e.params.len() == 3, "{} Error: Core func 'eq' takes exactly 2 arguments. This should never happen.", LANG_NAME);
    let a = &eval_expr(&mut context, e.get(1)).parse::<i64>().unwrap();
    let b = &eval_expr(&mut context, e.get(2)).parse::<i64>().unwrap();
    (a >= b).to_string()
}

fn eval_core_func_add(mut context: &mut Context, e: &Expr) -> String {
    assert!(e.params.len() == 3, "{} Error: Core func 'eq' takes exactly 2 arguments. This should never happen.", LANG_NAME);
    let a = &eval_expr(&mut context, e.get(1)).parse::<i64>().unwrap();
    let b = &eval_expr(&mut context, e.get(2)).parse::<i64>().unwrap();
    (a + b).to_string()
}

fn eval_core_func_sub(mut context: &mut Context, e: &Expr) -> String {
    assert!(e.params.len() == 3, "{} Error: Core func 'eq' takes exactly 2 arguments. This should never happen.", LANG_NAME);
    let a = &eval_expr(&mut context, e.get(1)).parse::<i64>().unwrap();
    let b = &eval_expr(&mut context, e.get(2)).parse::<i64>().unwrap();
    (a - b).to_string()
}

fn eval_core_func_mul(mut context: &mut Context, e: &Expr) -> String {
    assert!(e.params.len() == 3, "{} Error: Core func 'eq' takes exactly 2 arguments. This should never happen.", LANG_NAME);
    let a = &eval_expr(&mut context, e.get(1)).parse::<i64>().unwrap();
    let b = &eval_expr(&mut context, e.get(2)).parse::<i64>().unwrap();
    (a * b).to_string()
}

fn eval_core_func_div(mut context: &mut Context, e: &Expr) -> String {
    assert!(e.params.len() == 3, "{} Error: Core func 'eq' takes exactly 2 arguments. This should never happen.", LANG_NAME);
    let a = &eval_expr(&mut context, e.get(1)).parse::<i64>().unwrap();
    let b = &eval_expr(&mut context, e.get(2)).parse::<i64>().unwrap();
    (a / b).to_string()
}

fn eval_core_func_btoi(mut context: &mut Context, e: &Expr) -> String {
    assert!(e.params.len() == 2, "{} Error: Core func 'btoi' takes exactly 1 argument. This should never happen.", LANG_NAME);
    if eval_to_bool(&mut context, &e.get(1)) {
        "1".to_string()
    } else {
        "0".to_string()
    }
}

fn eval_core_func_atoi(mut context: &mut Context, e: &Expr) -> String {
    assert!(e.params.len() == 2, "{} Error: Core func 'btoi' takes exactly 1 argument. This should never happen.", LANG_NAME);
    let a = &eval_expr(&mut context, &e.get(1)).parse::<i64>().unwrap();
    return a.to_string();
}

fn eval_core_func_btoa(mut context: &mut Context, e: &Expr) -> String {
    assert!(e.params.len() == 2, "{} Error: Core func 'btoa' takes exactly 1 argument. This should never happen.", LANG_NAME);
    if eval_to_bool(&mut context, &e.get(1)) {
        "true".to_string()
    } else {
        "false".to_string()
    }
}

fn eval_core_func_itoa(mut context: &mut Context, e: &Expr) -> String {
    assert!(e.params.len() == 2, "{} Error: Core func 'btoa' takes exactly 1 argument. This should never happen.", LANG_NAME);
    eval_expr(&mut context, e.get(1))
}

// ---------- core procs implementations for eval

fn lbool_in_string_to_bool(b: &str) -> bool {
    match b {
        "true" => true,
        "false" => false,
        _ => panic!("{} Error: expected string 'true' or 'false', found '{}'. this should never happen.", LANG_NAME, b)
    }
}

fn eval_core_proc_print(end_line: bool, mut context: &mut Context, e: &Expr) -> String {
    for i in 1..e.params.len() {
        print!("{}", eval_expr(&mut context, &e.get(i)));
    }
    if end_line {
        print!("\n");
    }
    io::stdout().flush().unwrap();
    "".to_string()
}

fn eval_core_proc_input_read_line(mut _context: &mut Context, e: &Expr) -> String {
    let first_param = e.get(0);
    let read_line_error_msg = match &first_param.node_type {
        NodeType::LString(error_msg_) => error_msg_.clone(),
        _ => format!("input_read_line() can only take literal strings as its single argument for an error String for now. The user, perhaps wisely, tried node type '{:?}' instead",
                     first_param.node_type).to_string(), // TODO review
    };
    let mut line = String::new();
    io::stdin()
        .read_line(&mut line)
        .expect(&read_line_error_msg);

    return line.to_string()
}

fn eval_core_proc_eval_to_str(mut context: &mut Context, e: &Expr) -> String {
    // TODO properly implement
    assert!(e.params.len() == 2, "eval_core_proc_eval_to_str expects a single parameter.");
    let path = "eval".to_string(); // TODO Bring the path down here
    let str_source = format!("mode script; {}", &eval_expr(&mut context, e.get(1)));
    return main_run(false, &mut context, &path, str_source);
}

fn eval_core_proc_runfile(mut context: &mut Context, e: &Expr) -> String {
    assert!(e.params.len() == 2, "eval_core_proc_runfile expects a single parameter.");
    let path = &eval_expr(&mut context, e.get(1));
    run_file(&path);
    return "".to_string();
}

fn eval_core_proc_import(mut context: &mut Context, e: &Expr) -> String {
    assert!(e.params.len() == 2, "eval_core_proc_import expects a single parameter.");
    let path = &eval_expr(&mut context, e.get(1));
    run_file_with_context(true, &mut context, &path);
    return "".to_string();
}

fn eval_core_exit(e: &Expr) -> String {
    assert!(e.params.len() == 2, "eval_core_exit expects a single parameter.");
    let e_exit_code = e.get(1);
    let exit_code = match &e_exit_code.node_type {
        NodeType::LI64(my_li64) => {
            my_li64.clone()
        },
        node_type => {
            panic!("{}:{} {} error: calling core proc exit, but found {:?} instead of literal int exit code.",
                   e.line, e.col, LANG_NAME, node_type);
        },
    };
    std::process::exit(exit_code as i32);
}

// ---------- generic eval things

fn eval_user_func_proc_call(func_def: &SFuncDef, name: &str, context: &Context, e: &Expr) -> String {

    let mut function_context = context.clone();
    assert!(e.params.len() - 1 == func_def.args.len(), "{} error: func '{}' expected {} args, but {} were provided. This should never happen.",
            LANG_NAME, name, func_def.args.len(), e.params.len()-1);

    let mut param_index = 1;
    for arg in &func_def.args {

        function_context.symbols.insert(arg.name.to_string(), SymbolInfo{value_type: arg.value_type.clone(), is_mut: arg.is_mut});
        match &arg.value_type {
            ValueType::TBool => {
                let bool_expr_result = lbool_in_string_to_bool(&eval_expr(&mut function_context, &e.get(param_index)));
                function_context.bools.insert(arg.name.clone(), bool_expr_result);
            },
            ValueType::TI64 =>  {
                let result = &eval_expr(&mut function_context, &e.get(param_index));
                function_context.i64s.insert(arg.name.to_string(), result.parse::<i64>().unwrap());
            },
            ValueType::TString =>  {
                let result = eval_expr(&mut function_context, &e.get(param_index));
                function_context.strings.insert(arg.name.to_string(), result);
            },
            ValueType::TCustom(ref custom_type_name) => {
                let result = eval_expr(&mut function_context, &e.get(param_index));
                let custom_symbol = function_context.symbols.get(custom_type_name).unwrap();
                match custom_symbol.value_type {
                    ValueType::TEnumDef => {
                        function_context.enums.insert(arg.name.to_string(), EnumVal{enum_type: custom_type_name.to_string(), enum_name: result});
                    },
                    _ => {
                        panic!("{}:{} {} eval error: Cannot use {} of type {:?} as an argument. Only enum custom types allowed for now.",
                               e.line, e.col, LANG_NAME, &arg.name, &arg.value_type)
                    },
                }
            },

            _ => {
                panic!("{}:{} {} error: calling func '{}'. {:?} arguments not supported.", e.line, e.col, LANG_NAME, name, arg.value_type);
            },
        }

        param_index += 1;
    }

    for se in &func_def.body {
        match se.node_type {
            NodeType::Return => {
                assert!(se.params.len() != 0, "{} error: return must currently always return exactly one value.", LANG_NAME);
                return eval_expr(&mut function_context, &se.get(0));
            },
            NodeType::If => {
                assert!(se.params.len() == 2 || se.params.len() == 3, "{} error: if nodes must have 2 or 3 parameters.", LANG_NAME);
                if eval_to_bool(&mut function_context, &se.get(0)) {
                    return eval_expr(&mut function_context, &se.get(1))
                } else if se.params.len() == 3 {
                    return eval_expr(&mut function_context, &se.get(2))
                }
            },
            _ => {
                eval_expr(&mut function_context, &se);
            }
        }
    }
    "".to_string()
}

fn eval_core_func_call(name: &str, mut context: &mut Context, e: &Expr) -> String {
    return match name {
        "and" => eval_core_func_and(&mut context, &e),
        "or" => eval_core_func_or(&mut context, &e),
        "not" => eval_core_func_not(&mut context, &e),
        "eq" => eval_core_func_eq(&mut context, &e),
        "str_eq" => eval_core_func_str_eq(&mut context, &e),
        "concat" => eval_core_func_concat(&mut context, &e),
        "lt" => eval_core_func_lt(&mut context, &e),
        "lteq" => eval_core_func_lteq(&mut context, &e),
        "gt" => eval_core_func_gt(&mut context, &e),
        "gteq" => eval_core_func_gteq(&mut context, &e),
        "add" => eval_core_func_add(&mut context, &e),
        "sub" => eval_core_func_sub(&mut context, &e),
        "mul" => eval_core_func_mul(&mut context, &e),
        "div" => eval_core_func_div(&mut context, &e),
        "btoi" => eval_core_func_btoi(&mut context, &e),
        "atoi" => eval_core_func_atoi(&mut context, &e),
        "btoa" => eval_core_func_btoa(&mut context, &e),
        "itoa" => eval_core_func_itoa(&mut context, &e),
        _ => panic!("{}:{} {} eval error: Core function '{}' not implemented.", e.line, e.col, LANG_NAME, name),
    };
}

fn eval_core_proc_call(name: &str, mut context: &mut Context, e: &Expr) -> String {
    return match name {
        "eval_to_str" => eval_core_proc_eval_to_str(&mut context, &e),
        "exit" => eval_core_exit(&e),
        "import" => "".to_string(), // Should already be imported in init_context
        "input_read_line" => eval_core_proc_input_read_line(&mut context, &e),
        "print" => eval_core_proc_print(false, &mut context, &e),
        "println" => eval_core_proc_print(true, &mut context, &e),
        "runfile" => eval_core_proc_runfile(&mut context, &e),
        _ => panic!("{}:{} {} eval error: Core procedure '{}' not implemented.", e.line, e.col, LANG_NAME, name),
    }
}

fn eval_func_proc_call(name: &str, mut context: &mut Context, e: &Expr) -> String {
    if is_core_func(&name) {
        return eval_core_func_call(&name, &mut context, &e)
    } else if is_core_proc(&name) {
        return eval_core_proc_call(&name, &mut context, &e)
    } else if context.funcs.contains_key(name) {
        let func_def = context.funcs.get(name).unwrap();
        return eval_user_func_proc_call(func_def, &name, &context, &e)
    } else if context.struct_defs.contains_key(name) {
        let struct_def = context.struct_defs.get(name).unwrap();
        let id_expr = e.get(0);
        let after_dot = match id_expr.params.get(0) {
            Some(_after_dot) => _after_dot,
            None => {
                panic!("{}:{} {} eval error: Cannot instantiate '{}'. Not implemented yet.", e.line, e.col, LANG_NAME, name);
            },
        };
        match &after_dot.node_type {
            NodeType::Identifier(after_dot_name) => {
                let _member_decl = match struct_def.members.get(after_dot_name) {
                    Some(_member) => _member,
                    None => {
                        panic!("{}:{}: eval error: struct '{}' has no member '{}' a", e.line, e.col, name, after_dot_name);
                    },
                };
                let combined_name = format!("{}.{}", name, after_dot_name);
                if !context.funcs.contains_key(&combined_name) {
                    panic!("{}:{}: eval {} error: method '{}' not found in context", e.line, e.col, LANG_NAME, combined_name);
                }

                let func_def = context.funcs.get(&combined_name).unwrap();
                return eval_user_func_proc_call(func_def, &name, &context, &e);
            },
            _ => {
                panic!("{}:{}: eval {} error: expected identifier after '{}.' found {:?}", e.line, e.col, LANG_NAME, name, after_dot.node_type);
            },
        }
    } else if context.symbols.contains_key(name) { // For UFCS
        // TODO Handle UFCS in check_types instead of waiting for invalid types to be discovered during evaluation
        let id_expr = e.get(0);
        let mut extra_arg = false;
        let f_name = if id_expr.params.len() == 0 {
            get_func_name_in_call(&e)
        } else {
            extra_arg = true;
            match &id_expr.get(0).node_type {
                NodeType::Identifier(f_name) => f_name.clone(),
                _ => panic!("panic eval_func_proc_call(), this should never happen."),
            }
        };

        if extra_arg {
            let id_expr_name = get_func_name_in_call(&e);
            let extr_arg_e = Expr::new_clone(NodeType::Identifier(id_expr_name), e, Vec::new());
            let mut new_args = Vec::new();
            new_args.push(extr_arg_e);
            new_args.append(&mut e.params.clone());
            let new_e = Expr::new_clone(NodeType::Identifier(f_name.clone()), e.get(0), new_args);
            return eval_func_proc_call(&f_name, &mut context, &new_e);
        }
        return eval_func_proc_call(&f_name, &mut context, &e);

    } else {
        panic!("{}:{} {} eval error: Cannot call '{}'. Undefined function or struct.", e.line, e.col, LANG_NAME, name);
    }
}

fn eval_declaration(declaration: &Declaration, mut context: &mut Context, e: &Expr) -> String {
    let inner_e = e.get(0);
    let value_type = match get_value_type(&context, &inner_e) {
        Ok(val_type) => val_type,
        Err(error_string) => {
            panic!("{}", error_string);
        },
    };
    if declaration.value_type != ValueType::ToInferType {
        if value_type != declaration.value_type {
            panic!("{}:{} {} eval error: '{}' declared of type {} but initialized to type {:?}.", e.line, e.col, LANG_NAME, declaration.name, value_type_to_str(&declaration.value_type), value_type_to_str(&value_type));
        }
    }
    assert!(e.params.len() == 1, "{} error: Declarations can have only one child expression. This should never happen.", LANG_NAME);
    match value_type {
        ValueType::ToInferType => {
            panic!("{}:{} {} eval error: '{}' declared of type {} but but still to infer type {:?}.", e.line, e.col, LANG_NAME, declaration.name, value_type_to_str(&declaration.value_type), value_type_to_str(&value_type));
        },
        ValueType::TBool => {
            let bool_expr_result : bool = lbool_in_string_to_bool(&eval_expr(&mut context, inner_e));
            context.bools.insert(declaration.name.to_string(), bool_expr_result);
            context.symbols.insert(declaration.name.to_string(), SymbolInfo{value_type: value_type.clone(), is_mut: declaration.is_mut});
            bool_expr_result.to_string()
        },
        ValueType::TI64 => {
            let i64_expr_result_str = &eval_expr(&mut context, inner_e);
            context.i64s.insert(declaration.name.to_string(), i64_expr_result_str.parse::<i64>().unwrap());
            context.symbols.insert(declaration.name.to_string(), SymbolInfo{value_type: value_type.clone(), is_mut: declaration.is_mut});
            i64_expr_result_str.to_string()
        },
        ValueType::TString => {
            let string_expr_result = &eval_expr(&mut context, inner_e);
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
                            e.line, e.col, LANG_NAME, &declaration.name, &declaration.value_type)
            }
        },
        ValueType::TStructDef => {
            match &inner_e.node_type {
                NodeType::StructDef(struct_def) => {
                    context.struct_defs.insert(declaration.name.to_string(), struct_def.clone());
                    context.symbols.insert(declaration.name.to_string(), SymbolInfo{value_type: value_type.clone(), is_mut: declaration.is_mut});
                    for (_, member_decl) in &struct_def.members {
                        if !member_decl.is_mut {
                            let combined_name = format!("{}.{}", declaration.name, member_decl.name);
                            let default_value = match struct_def.default_values.get(&member_decl.name) {
                                Some(_default_value) => _default_value,
                                None => {
                                    panic!("{}:{} {} eval error: Struct member '{}.{}' expected to have default value.",
                                           e.line, e.col, LANG_NAME, &declaration.name, &member_decl.name);
                                },
                            };
                            let member_value_type = match member_decl.value_type {
                                ValueType::ToInferType => {
                                    match get_value_type(&context, &default_value) {
                                        Ok(val_type) => val_type,
                                        Err(error_string) => {
                                            panic!("{}", error_string);
                                        },
                                    }
                                },
                                _ => member_decl.value_type.clone(),
                            };

                            match member_value_type {
                                ValueType::TBool => {
                                    let bool_expr_result : bool = lbool_in_string_to_bool(&eval_expr(&mut context, default_value));
                                    context.bools.insert(combined_name.to_string(), bool_expr_result);
                                },
                                ValueType::TI64 => {
                                    let i64_expr_result_str = &eval_expr(&mut context, default_value);
                                    context.i64s.insert(combined_name.to_string(), i64_expr_result_str.parse::<i64>().unwrap());
                                },
                                ValueType::TString => {
                                    let string_expr_result = &eval_expr(&mut context, default_value);
                                    context.strings.insert(combined_name.to_string(), string_expr_result.to_string());
                                },
                                ValueType::TFunc | ValueType::TProc | ValueType::TMacro => {
                                    match &default_value.node_type {
                                        NodeType::FuncDef(func_def) => {
                                            context.funcs.insert(combined_name.to_string(), func_def.clone());
                                        },
                                        _ => panic!("{}:{} {} eval error: Cannot declare '{}.{}' of type {:?}, expected {} definition.",
                                                    e.line, e.col, LANG_NAME, &declaration.name, &member_decl.name, &member_decl.value_type,
                                                    value_type_to_str(&member_decl.value_type)),
                                    }
                                },
                                ValueType::ToInferType => {
                                        panic!("{}:{} {} eval error: Cannot infer type of '{}.{}', but it should be inferred already.",
                                               e.line, e.col, LANG_NAME, &declaration.name, &member_decl.name)
                                },
                                ValueType::TType | ValueType::TList | ValueType::TEnumDef | ValueType::TStructDef | ValueType::TMulti(_)
                                    | ValueType::TCustom(_) => {
                                    panic!("{}:{} {} eval error: Cannot declare '{}.{}' of type {:?}. Not implemented yet",
                                                e.line, e.col, LANG_NAME, &declaration.name, &member_decl.name, &member_decl.value_type)
                                },

                            }

                            context.symbols.insert(combined_name.to_string(),
                                                   SymbolInfo{value_type: member_decl.value_type.clone(), is_mut: member_decl.is_mut});
                        }
                    }
                    "struct declared".to_string()
                },
                _ => panic!("{}:{} {} eval error: Cannot declare {} of type {:?}, expected struct definition.",
                            e.line, e.col, LANG_NAME, &declaration.name, &declaration.value_type)
            }
        },
        ValueType::TFunc | ValueType::TProc | ValueType::TMacro => {
            match &inner_e.node_type {
                NodeType::FuncDef(func_def) => {
                    context.funcs.insert(declaration.name.to_string(), func_def.clone());
                    context.symbols.insert(declaration.name.to_string(), SymbolInfo{value_type: value_type.clone(), is_mut: declaration.is_mut});
                    return format!("{} declared", value_type_to_str(&value_type));
                },
                _ => panic!("{}:{} {} eval error: Cannot declare {} of type {:?}, expected {} definition.",
                            e.line, e.col, LANG_NAME, &declaration.name, &declaration.value_type, value_type_to_str(&value_type))
            }
        },

        ValueType::TCustom(ref custom_type_name) => {
            context.symbols.insert(declaration.name.to_string(), SymbolInfo{value_type: value_type.clone(), is_mut: declaration.is_mut});
            let custom_symbol = context.symbols.get(custom_type_name).unwrap();
            if custom_symbol.value_type == ValueType::TEnumDef {
                let enum_expr_result_str = &eval_expr(&mut context, inner_e);
                context.enums.insert(declaration.name.to_string(), EnumVal{enum_type: custom_type_name.to_string(), enum_name: enum_expr_result_str.to_string()});
            } else {
                panic!("{}:{} {} eval error: Cannot declare {} of type {:?}. Only enum custom types allowed yet.",
                       e.line, e.col, LANG_NAME, &declaration.name, &declaration.value_type)
            }
            return format!("{} declared", custom_type_name)
        },
        ValueType::TType | ValueType::TList | ValueType::TMulti(_) => {
            panic!("{}:{} {} eval error: Cannot declare {} of type {:?}.", e.line, e.col, LANG_NAME, &declaration.name, &declaration.value_type)
        },
    }
}

fn eval_assignment(var_name: &str, mut context: &mut Context, e: &Expr) -> String {
    let symbol_info = context.symbols.get(var_name).unwrap();
    assert!(symbol_info.is_mut, "{} eval error: Assignments can only be to mut values", LANG_NAME);
    assert!(e.params.len() == 1, "{} eval error: in eval_assignment, while assigning to {}, assignments must take exactly one value.", LANG_NAME, var_name);

    let inner_e = e.get(0);
    let value_type = match get_value_type(&context, &inner_e) {
        Ok(val_type) => val_type,
        Err(error_string) => {
            panic!("{}", error_string);
        },
    };
    match value_type {
        ValueType::ToInferType => {
            panic!("{}:{} {} eval error: Cannot assign {}, type should already be inferred of type '{:?}'.", e.line, e.col, LANG_NAME, &var_name, &symbol_info.value_type);
        },

        ValueType::TBool => {
            let bool_expr_result : bool = lbool_in_string_to_bool(&eval_expr(&mut context, inner_e));
            context.bools.insert(var_name.to_string(), bool_expr_result);
            bool_expr_result.to_string()
        },
        ValueType::TI64 => {
            let i64_expr_result_str = &eval_expr(&mut context, inner_e);
            context.i64s.insert(var_name.to_string(), i64_expr_result_str.parse::<i64>().unwrap());
            i64_expr_result_str.to_string()
        },
        ValueType::TString => {
            let string_expr_result = &eval_expr(&mut context, inner_e);
            context.strings.insert(var_name.to_string(), string_expr_result.to_string());
            string_expr_result.to_string()
        },
        ValueType::TStructDef => {
            panic!("{}:{} {} eval error: Cannot assign {} of type {:?}. Not implemented yet.",
                   e.line, e.col, LANG_NAME, &var_name, &value_type);
        },
        ValueType::TFunc | ValueType::TProc | ValueType::TMacro => {
            match &inner_e.node_type {
                NodeType::FuncDef(func_def) => {
                    context.funcs.insert(var_name.to_string(), func_def.clone());
                    "func declared".to_string()
                },
                _ => panic!("{}:{} {} eval error: Cannot assign {} to function type {}.",
                            e.line, e.col, LANG_NAME, &var_name, value_type_to_str(&value_type))
            }
        },

        ValueType::TType | ValueType::TList | ValueType::TEnumDef | ValueType::TMulti(_) | ValueType::TCustom(_) => {
            panic!("{}:{} {} eval error: Cannot assign {} of type {:?}.", e.line, e.col, LANG_NAME, &var_name, &value_type);
        },
    }
}

fn eval_identifier_expr(name: &str, context: &Context, e: &Expr) -> String {

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
            ValueType::TFunc | ValueType::TProc | ValueType::TMacro => {
                return name.to_string();
            },
            ValueType::TEnumDef => {
                assert!(e.params.len() > 0, "{} eval error: enum type '{}' can't be used as a primary expression.", LANG_NAME, name);
                // let enum_def = context.enum_defs.get(name).unwrap();
                let inner_e = e.get(0);
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

            ValueType::TStructDef => {
                assert!(e.params.len() > 0, "{} eval error: struct type '{}' can't be used as a primary expression.", LANG_NAME, name);
                let struct_def = context.struct_defs.get(name).unwrap();
                let inner_e = e.get(0);
                match &inner_e.node_type {
                    NodeType::Identifier(inner_name) => {
                        match struct_def.members.get(inner_name) {
                            Some(member_decl) => {
                                match member_decl.value_type {
                                    ValueType::TString => {
                                        match context.strings.get(&format!("{}.{}", name, inner_name)) {
                                            Some(result_str) => return result_str.to_string(),
                                            None => {
                                                panic!("{}:{}: {} eval error: value not set for '{}.{}'",
                                                       e.line, e.col, LANG_NAME, name, inner_name)
                                            },
                                        }

                                    },
                                    ValueType::TI64 => {
                                        match context.i64s.get(&format!("{}.{}", name, inner_name)) {
                                            Some(result) => return result.to_string(),
                                            None => {
                                                panic!("{}:{}: {} eval error: value not set for '{}.{}'",
                                                       e.line, e.col, LANG_NAME, name, inner_name)
                                            },
                                        }

                                    },
                                    ValueType::TBool => {
                                        match context.bools.get(&format!("{}.{}", name, inner_name)) {
                                            Some(result) => return result.to_string(),
                                            None => {
                                                panic!("{}:{}: {} eval error: value not set for '{}.{}'",
                                                       e.line, e.col, LANG_NAME, name, inner_name)
                                            },
                                        }

                                    },
                                    _ => {
                                        panic!("{}:{}: {} eval error: struct '{}' has no const (static) member '{}' of value type '{:?}'",
                                               e.line, e.col, LANG_NAME, name, inner_name, member_decl.value_type)
                                    },
                                }
                            },
                            _ => {
                                panic!("{}:{}: {} eval error: struct '{}' has no const (static) member '{}'",
                                       e.line, e.col, LANG_NAME, name, inner_name)
                            },
                        }
                    },
                    _ => {
                        panic!("{} eval error: identifier '{}' should only have identifiers inside.", LANG_NAME, name)
                    },
                }
            }

            ValueType::ToInferType => {
                panic!("{} eval error: Can't infer the type of identifier '{}'.", LANG_NAME, name)
            },
            ValueType::TCustom(ref custom_type_name) => {
                if !context.symbols.contains_key(custom_type_name) {
                    // note: this error originates in the macro `format` (in Nightly builds, run with -Z macro-backtrace for more info)
                    // thank you, rust, format inside format for no reason I want to understand
                    panic!("{}", format!("{}:{}: {} eval error: : Argument '{}' is of undefined type {}.",
                                         e.line, e.col, LANG_NAME, &name, &custom_type_name)
                    );
                }
                let custom_symbol = context.symbols.get(custom_type_name).unwrap();
                match custom_symbol.value_type {
                    ValueType::TEnumDef => {
                        let enum_val = context.enums.get(name).unwrap();
                        return enum_val.enum_name.clone();
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
}

fn eval_expr(mut context: &mut Context, e: &Expr) -> String {
    match &e.node_type {
        NodeType::Body => {
            for se in e.params.iter() {
                match &se.node_type {
                    NodeType::Return => {
                        return eval_expr(&mut context, &se);
                    }
                    _ => {
                        eval_expr(&mut context, &se);
                    }
                }
            }
            return "".to_string()
        },
        NodeType::LBool(bool_value) => bool_value.to_string(),
        NodeType::LI64(li64) => li64.to_string(),
        NodeType::LString(lstring) => lstring.to_string(),
        NodeType::LList(list_str_) => {
            return list_str_.to_string()
        },
        NodeType::FCall => {
            let f_name = get_func_name_in_call(&e);
            eval_func_proc_call(&f_name, &mut context, &e)
        },
        NodeType::Declaration(declaration) => {
            eval_declaration(&declaration, &mut context, &e)
        },
        NodeType::Assignment(var_name) => {
            eval_assignment(&var_name, &mut context, &e)
        },
        NodeType::Identifier(name) => {
            return eval_identifier_expr(&name, &context, &e);
        },
        NodeType::If => {
            assert!(e.params.len() == 2 || e.params.len() == 3, "{} eval error: if nodes must have 2 or 3 parameters.", LANG_NAME);
            if eval_to_bool(&mut context, &e.get(0)) {
                eval_expr(&mut context, &e.get(1))
            } else if e.params.len() == 3 {
                eval_expr(&mut context, &e.get(2))
            } else {
                "".to_string()
            }
        },
        NodeType::While => {
            assert!(e.params.len() == 2, "{} eval error: while nodes must have exactly 2 parameters.", LANG_NAME);
            while eval_to_bool(&mut context, &e.get(0)) {
                eval_expr(&mut context, &e.get(1));
            }
            "".to_string()
        },
        NodeType::Switch => {
            assert!(e.params.len() >= 3, "{} eval error: switch nodes must have at least 3 parameters.", LANG_NAME);

            let to_switch = e.get(0);
            let value_type = match get_value_type(&context, &to_switch) {
                Ok(val_type) => val_type,
                Err(error_string) => {
                    panic!("{} eval error: {}", LANG_NAME, error_string);
                },
            };
            let mut param_it = 1;
            let result_to_switch = eval_expr(&mut context, &to_switch);
            while param_it < e.params.len() {

                let case = e.get(param_it);
                if case.node_type == NodeType::DefaultCase {
                    param_it += 1;
                    let body = e.get(param_it);
                    return eval_expr(&mut context, &body);
                }

                let case_type = match get_value_type(&context, &case) {
                    Ok(val_type) => val_type,
                    Err(error_string) => {
                        panic!("{} eval error: {}", LANG_NAME, error_string);
                    },
                };
                if value_type != case_type {
                    panic!("{} eval error: switch value type {:?}, case value type {:?}", LANG_NAME, value_type, case_type);
                }

                let result_case = eval_expr(&mut context, &case);
                param_it += 1;
                if result_to_switch == result_case {
                    let body = e.get(param_it);
                    return eval_expr(&mut context, &body);
                }
                param_it += 1;
            }
            return "".to_string();
        },
        NodeType::Return => {
            if e.params.len() == 0 {
                return "".to_string();
            } else if e.params.len() == 1 {
                return eval_expr(&mut context, &e.get(0))
            } else {
                panic!("{}:{}: {} eval error: mutltiple return values not implemented yet.", e.line, e.col, LANG_NAME);
            }
        }
        _ => {
            panic!("{}:{}: {} eval error: Not implemented, found {:?}.", e.line, e.col, LANG_NAME, e.node_type)
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
            ast_str.push_str(&format!("(def {} {})", decl.name, to_ast_str(&e.get(0))));
            return ast_str;
        },
        NodeType::Assignment(var_name) => {
            ast_str.push_str(&format!("(set {} {})", var_name, to_ast_str(&e.get(0))));
            return ast_str;
        },
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
            let f_name = get_func_name_in_call(&e);
            ast_str.push_str(&format!("({} {})", f_name, params_to_ast_str(false, &e)));
            return ast_str;
        },
        NodeType::LList(_) => {
            ast_str.push_str(&format!("({})", params_to_ast_str(false, &e)));
            return ast_str;
        },
        NodeType::If => {
            ast_str.push_str(&format!("(if {})", to_ast_str(&e.get(0))));
            return ast_str;
        },
        NodeType::While => {
            ast_str.push_str(&format!("(while {})", to_ast_str(&e.get(0))));
            return ast_str;
        },
        NodeType::Switch => {
            ast_str.push_str(&format!("(switch {})", to_ast_str(&e.get(0))));
            return ast_str;
        },
        NodeType::Return => {
            panic!("{} AST error: Node_type::Return shouldn't be analized in to_ast_str().", LANG_NAME);
        },
    }
}

// ---------- main binary

fn main_run(print_extra: bool, mut context: &mut Context, path: &String, source: String) -> String {

    let lexer = match lexer_from_source(&path, source) {
        Ok(_result) => _result,
        Err(error_string) => {
            return format!("{}:{}", &path, error_string);
        },
    };

    let mut current: usize = 0;
    let mode = match parse_mode(&path, &lexer, &mut current) {
        Ok(mode_) => mode_,
        Err(error_string) => {
            return format!("{}:{}", &path, error_string);
        },
    };
    context.mode = mode;
    if print_extra {
        println!("Mode: {}", context.mode.name);
    }

    let e: Expr = match parse_tokens(lexer, &mut current) {
        Ok(expr) => expr,
        Err(error_string) => {
            return format!("{}:{}", &path, error_string);
        },
    };
    if !SKIP_AST {
        println!("AST: \n{}", to_ast_str(&e));
    }

    let mut errors = init_context(&mut context, &e);
    if errors.len() > 0 {
        for err in &errors {
            println!("{}:{}", path, err);
        }
        return format!("Compiler errors: {} declaration errors found", errors.len());
    }

    errors.append(&mut basic_mode_checks(&context, &e));
    errors.append(&mut check_types(&mut context, &e)); // TODO remove mut from context arg

    if errors.len() > 0 {
        for err in &errors {
            println!("{}:{}", path, err);
        }
        return format!("Compiler errors: {} type errors found", errors.len());
    }

    return eval_expr(&mut context, &e);
}

// ---------- main, usage, args, etc

fn run_file(path: &String) {
    let mut context = Context::new(DEFAULT_MODE);
    let core_path = "src/core/core.cil".to_string();
    run_file_with_context(true, &mut context, &core_path);
    run_file_with_context(false, &mut context, &path);
}

fn run_file_with_context(is_import: bool, mut context: &mut Context, path: &String) {
    let previous_mode = context.mode.clone();
    if !is_import {
        println!("Running file '{}'", &path);
    }
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
    let run_result = main_run(!is_import, &mut context, &path, source);
    if run_result != "" {
        println!("{}", run_result);
    }

    if is_import && !can_be_imported(&context.mode) {
        panic!("file '{}' of mode '{}' cannot be imported", path, context.mode.name)
    }
    context.mode = previous_mode; // restore the context mode of the calling file
}

fn usage() {
    println!("Usage: {} [command] [path]\n", BIN_NAME);
    println!("Entering no arguments is equavalent to: {} repl", BIN_NAME);
    println!("Entering a single argument that's not a command is interpreted as a path, equivalent to: {} interpret <path>\n", BIN_NAME);

    println!("Commands:\n");

    println!("repl: read eval print loop.");
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
            "interpret" => {
                run_file(&args[2]);
            },
            "repl" | "build" | "run" => {
                usage();
            },
            _ => {
                usage();
            },
        }
        println!("subcommand '{}' not implemented yet.", &args[1]);
        println!("callled within valid command '{}'.", &args[0]);

    } else if args.len() > 1 {
        match args[1].as_str() {
            "repl" => {
                run_file(&REPL_PATH.to_string());
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
        run_file(&REPL_PATH.to_string()) // If not arguments, then repl/interactive "mode"
    }
}
