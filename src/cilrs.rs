use std::env;
use std::io;
use std::io::Write; // <--- bring flush() into scope
use std::fs;
use std::io::ErrorKind;
use std::collections::HashMap;
use std::convert::TryInto;

// We may want to change it to rsbootstrap later when self hosting, if we get there
// or just change the name of the language
// CIL stands for Compiled Interpreted Language
// Because there is no good reason for a programming language not to be both compiled and interpreted.
const LANG_NAME: &str = "cilrs";
const DEFAULT_MODE: &str = "lib";
const INFER_TYPE: &str = "auto";
const SELF_HOSTED_PATH: &str = "src/cil.cil";
const SKIP_AST: bool = true;

// ---------- format errors

// struct RscilErr {
//     error_str: &str,
//     t: &Token,
//     level: &str,
// }

// fn init_err(t: &Token, level: &str, error_str: &str) return RscilErr {
//     return RscilErr(format!("{}:{}: {} ERROR: {}", e.line, e.col, level, error_str));
// }

// fn format_err(RscilErr: err) -> String {
//     return format!("{}:{}: {} ERROR: {}", err.e.line, err.t.col, err.level, err.error_str);
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
    Const, Var, Null,
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
    // TODO why next()? is this a bug?
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
        "throws" => TokenType::Throws, // TODO parse
        "func" => TokenType::Func,
        "proc" => TokenType::Proc,
        "macro" => TokenType::Macro, // TODO implement for real once we compile
        "ext_func" => TokenType::FuncExt, // this has to link when we compile
        "ext_proc" => TokenType::ProcExt, // this has to link when we compile

        // control flow
        "if" => TokenType::If,
        "else" => TokenType::Else,
        "while" => TokenType::While,
        "for" => TokenType::For, // TODO parse
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
        "NULL" => TokenType::Null,

        // Do we really need const fields static other than static? (ie can be different per instance, but not modified afterwards)
        // The answer is probably yet, but perhaps static is not the right answer
        // how about this? if it's in the struct body, it is const, if it is in impl, it is static, just like functions
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
            scan_push_token(&mut tokens, TokenType::Number, &source[start..pos], line, start - start_line_pos + 1);
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
                    let mut lit_string = String::new();
                    pos += 1;
                    while pos + 1 < eof_pos && &source[pos..pos+1] != "\"" {
                        if &source[pos..pos+1] == "\\" {
                            pos += 1; // if it's the escape character, skip it
                            if pos + 1 < eof_pos && &source[pos..pos+1] == "\"" {
                                lit_string.push(source.chars().nth(pos).unwrap());
                            } else if pos + 1 < eof_pos && &source[pos..pos+1] == "n" {
                                lit_string.push('\n');
                            } else if pos + 1 < eof_pos && &source[pos..pos+1] == "r" {
                                lit_string.push('\r');
                            } else if pos + 1 < eof_pos && &source[pos..pos+1] == "t" {
                                lit_string.push('\t');
                            } else if pos + 1 < eof_pos && &source[pos..pos+1] == "0" {
                                lit_string.push('\0');
                            } else if pos + 1 < eof_pos && &source[pos..pos+1] == "\\" {
                                lit_string.push('\\');
                            } else { // If it's something else, just leave it as is for now, I guess
                                lit_string.push('\\');
                                lit_string.push(source.chars().nth(pos).unwrap());
                            }
                        } else {
                            lit_string.push(source.chars().nth(pos).unwrap());
                        }
                        pos += 1;
                    }

                    if pos >= eof_pos {
                        TokenType::UnterminatedString
                    } else {
                        scan_push_token(&mut tokens, TokenType::String, &lit_string, line, start - start_line_pos + 1);
                        TokenType::String
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
            if token_type != TokenType::String {
                scan_push_token(&mut tokens, token_type, &source[start..pos + 1], line, start - start_line_pos + 1);
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
        TokenType::Null => {
            print_lex_error(&path, &t, *errors_found, "Keyword 'NULL' is not supported\nSuggestion: initialize your pointers instead");
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
            print_lex_error(&path, &t, *errors_found, "Operator '==' is not supported yet\nSuggestion: use 'I64.eq' or 'String.eq' instead");
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
            print_lex_error(&path, &t, *errors_found, "Operator '!=' is not supported yet\nSuggestion: use core funcs 'not' and 'I64.eq'/'String.eq' instead");
            *errors_found = *errors_found + 1;
        },

        _ => {},
    }
}

fn lexer_from_source(path: &String, source: String) -> Result<Lexer, String> {

    let lexer = Lexer::new(source);
    if lexer.len() < 1 {
        return Err(format!("{}:{}:{} compiler ERROR: End of file not found.", path, 1, 0));
    } else if lexer.is_eof(0) {
        return Err(format!("{}:{}:{} compiler ERROR: Nothing to be done", path, 0, 0));
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
        "list" => ValueType::TList,
        "func" => ValueType::TFunc,
        "proc" => ValueType::TProc,
        "enum" => ValueType::TEnumDef,
        "struct" => ValueType::TStructDef,
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
    throws: Vec<ValueType>,
    body: Vec<Expr>,
}

impl SFuncDef {
    fn is_proc(self: &SFuncDef) -> bool {
        match self.function_type {
            FunctionType::FTProc | FunctionType::FTProcExt => true,
            FunctionType::FTFunc | FunctionType::FTFuncExt | FunctionType::FTMacro => false,
        }
    }

    fn is_ext(self: &SFuncDef) -> bool {
        match self.function_type {
            FunctionType::FTFuncExt | FunctionType::FTProcExt => true,
            FunctionType::FTFunc | FunctionType::FTProc | FunctionType::FTMacro => false,
        }
    }
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
    Throw,
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

    fn lang_error(self: &Expr, phase: &str, msg: &str) -> String {
        if phase == "assert" || phase == "panic_type" || phase == "eval" {
            println!("{}:{}: {} {} ERROR: {}\nExplanation: This is not your fault as a user, this is a bug in the language.",
                     self.line, self.col, LANG_NAME, phase, msg);
            std::process::exit(1);
        }
        return format!("{}:{}: {} {} ERROR: {}", self.line, self.col, LANG_NAME, phase, msg)
    }

    fn todo_error(self: &Expr, phase: &str, msg: &str) -> String {
        if phase == "assert" {
            panic!("Expr.todo_error() cannot be called for phase 'assert', use Expr.lang_error() instead")
        }
        if phase == "panic_type" || phase == "eval" {
            println!("{}:{}: {} {} ERROR: {}\nExplanation: Not implemented yet, this is a missing feature in the language.",
                     self.line, self.col, LANG_NAME, phase, msg);
            std::process::exit(1);
        }
        return format!("{}:{}: {} {} ERROR: {}", self.line, self.col, LANG_NAME, phase, msg)
    }

    fn error(self: &Expr, phase: &str, msg: &str) -> String {
        if phase == "assert" {
            panic!("Expr.error() cannot be called for phase 'assert', use Expr.lang_error() instead")
        }
        if phase == "panic_type" || phase == "eval" {
            println!("{}:{}: {} ERROR: {}", self.line, self.col, phase, msg);
            std::process::exit(1);
        }
        return format!("{}:{}: {} ERROR: {}", self.line, self.col, phase, msg)
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
        return Err(format!("{}:0:0: mode '{}' is not properly supported in '{}' yet. Try mode '{}' instead", path, mode.name, LANG_NAME, "lib"));
    }
    if mode.name == "external" {
        return Err(format!("{}:0:0: mode '{}' is not properly supported in '{}' yet. Try mode '{}' instead", path, mode.name, LANG_NAME, "lib"));
    }
    if mode.name == "safe_script" {
        return Err(format!("{}:0:0: mode '{}' is not properly supported in '{}' yet. Try mode '{}' instead", path, mode.name, LANG_NAME, "script"));
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
            return Err(format!("{}:{}: {}  ERROR: Trying to parse a token that's not a literal as a literal, found {:?}.",
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
                    return Err(format!("{}:{}: parse ERROR: Unexpected ','.", list_t.line, list_t.col));
                }
            },
            _ => {
                if expect_comma {
                    return Err(format!("{}:{}: parse ERROR: Expected ')' or ',', found {:?}.", list_t.line, list_t.col, list_t.token_type));
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
        _ => Err(format!("{}:{}: parse ERROR: Expected closing parentheses.", list_t.line, list_t.col)),
    }
}

fn parse_assignment(lexer: &Lexer, current: &mut usize, t: &Token, name: &String) -> Result<Expr, String> {
    *current = *current + 1; // skip equal
    let mut params = Vec::new();
    params.push(parse_primary(&lexer, current)?);
    return Ok(Expr::new_parse(NodeType::Assignment(name.to_string()), t.clone(), params))
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
    let mut is_mut = false;
    while !(lexer.is_eof(*current) || rightparent_found) {
        match t.token_type {
            TokenType::RightParen => {
                rightparent_found = true;
                if expect_colon {
                    return Err(format!("{}:{}: parse ERROR: Expected ': Type' after arg name '{}' before ')'.", t.line, t.col, arg_name));
                }
                *current = *current + 1;
            },
            TokenType::Comma => {
                if expect_colon {
                    return Err(format!("{}:{}: parse ERROR: Expected ': Type' after arg name '{}', but found ','.", t.line, t.col, arg_name));
                }
                if expect_name {
                    return Err(format!("{}:{}: parse ERROR: Expected arg name before ','.", t.line, t.col));
                }
                if expect_comma {
                    expect_comma = false;
                    expect_colon = false;
                    expect_name = true;
                    is_mut = false;
                    *current = *current + 1;
                    t = lexer.get_token(*current)?;
                } else {
                    return Err(format!("{}:{}: parse ERROR: Unexpected ','.", t.line, t.col));
                }
            },
            TokenType::Colon => {
                if expect_colon {
                    expect_colon = false;
                    expect_name = false;
                    expect_comma = false;
                    *current = *current + 1;
                    t = lexer.get_token(*current)?;
                    match t.token_type {
                        TokenType::Identifier => {},
                        TokenType::DoubleDot => {},
                        _ => return Err(format!("{}:{}: parse ERROR: Expected type after '{}:', but found '{}'.", t.line, t.col, arg_name, t.token_str)),
                    }
                } else {
                    return Err(format!("{}:{}: parse ERROR: Unexpected ':'.", t.line, t.col));
                }
            },
            TokenType::DoubleDot => {
                if expect_colon {
                    return Err(format!("{}:{}: parse ERROR: Expected ': Type' after arg name '{}', but found '..'.", t.line, t.col, arg_name));
                }
                if expect_comma {
                    return Err(format!("{}:{}: parse ERROR: Expected ',', found {:?}.", t.line, t.col, t.token_type));
                }
                if expect_name {
                    return Err(format!("{}:{}: parse ERROR: Expected arg name, found {:?}.", t.line, t.col, t.token_type));
                }
                is_variadic = true;
                *current = *current + 1;
                t = lexer.get_token(*current)?;
            },
            TokenType::Identifier => {
                if expect_colon {
                    return Err(format!("{}:{}: parse ERROR: Expected ': Type' after arg name '{}', but found '{}'.", t.line, t.col, arg_name, t.token_str));
                }
                if expect_comma {
                    return Err(format!("{}:{}: parse ERROR: Expected ',', found identifier '{}'.", t.line, t.col, t.token_str));
                }
                if expect_name {
                    arg_name = &t.token_str;
                    expect_colon = true;
                    expect_name = false;
                } else {
                    if is_variadic {
                        args.push(Declaration {
                            name: arg_name.to_string(),
                            value_type: ValueType::TMulti(Box::new(str_to_value_type(&t.token_str))),
                            is_mut: is_mut,
                        });
                        is_variadic = false;
                    } else {
                        args.push(Declaration {
                            name: arg_name.to_string(),
                            value_type: str_to_value_type(&t.token_str),
                            is_mut: is_mut,
                        });
                    }
                    expect_comma = true;
                    is_mut = false;
                }
                *current = *current + 1;
                t = lexer.get_token(*current)?;
            },
            TokenType::Mut => {
                if !expect_name {
                    return Err(format!("{}:{}: parse ERROR: Unexpected 'mut' in argument list.", t.line, t.col));
                }
                is_mut = true;
                *current = *current + 1;
                t = lexer.get_token(*current)?;
            },
            _ => {
                return Err(format!("{}:{}: parse ERROR: Unexpected '{:?}' in func/proc args.", t.line, t.col, t.token_type));
            },
        }
    }
    match t.token_type {
        TokenType::RightParen => return Ok(args),
        _ => return Err(format!("{}:{}: parse ERROR: Expected closing parentheses.", t.line, t.col)),
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
                    return Err(format!("{}:{}: parse ERROR: Unexpected ','.", t.line, t.col));
                }
            },
            TokenType::Identifier => {
                if expect_comma {
                    return Err(format!("{}:{}: parse ERROR: Expected ',', found {:?}.", t.line, t.col, t.token_type));
                }
                return_types.push(str_to_value_type(&t.token_str));
                expect_comma = true;
                *current = *current + 1;
                t = lexer.get_token(*current)?;
            },
            _ => {
                return Err(format!("{}:{}: parse ERROR: Unexpected '{:?}' in func/proc returns.", t.line, t.col, t.token_type));
            },
        }
    }
    if end_found {
        return Ok(return_types);
    } else {
        return Err(format!("{}:{}: parse ERROR: Expected '{{' or 'throws' after return values.", t.line, t.col));
    }
}

// TODO DRY with func_proc_returns ?
fn func_proc_throws(lexer: &Lexer, current: &mut usize) -> Result<Vec<ValueType>, String> {
    let mut end_found = false;
    let mut return_types : Vec<ValueType> = Vec::new();
    *current = *current - 1;
    let mut t = lexer.get_token(*current)?;
    *current = *current + 1;
    if t.token_type != TokenType::Throws {
        return Ok(return_types);
    }
    t = lexer.get_token(*current)?;
    let mut expect_comma = false;
    while !(lexer.is_eof(*current) || end_found) {
        match t.token_type {
            TokenType::LeftBrace | TokenType::Semicolon => {
                end_found = true;
                *current = *current + 1;
            },
            TokenType::Comma => {
                if expect_comma {
                    expect_comma = false;
                    *current = *current + 1;
                    t = lexer.get_token(*current)?;
                } else {
                    return Err(format!("{}:{}: parse ERROR: Unexpected ','.", t.line, t.col));
                }
            },
            TokenType::Identifier => {
                if expect_comma {
                    return Err(format!("{}:{}: parse ERROR: Expected ',', found {:?}.", t.line, t.col, t.token_type));
                }
                return_types.push(str_to_value_type(&t.token_str));
                expect_comma = true;
                *current = *current + 1;
                t = lexer.get_token(*current)?;
            },
            _ => {
                return Err(format!("{}:{}: parse ERROR: Unexpected '{:?}' in func/proc throws.", t.line, t.col, t.token_type));
            },
        }
    }
    if end_found {
        return Ok(return_types);
    } else {
        return Err(format!("{}:{}: parse ERROR: Expected '{{' after throw values.", t.line, t.col));
    }
}

fn parse_func_proc_definition(lexer: &Lexer, function_type: FunctionType, do_parse_body: bool, current: &mut usize) -> Result<Expr, String> {

    *current = *current + 1;
    let t = lexer.get_token(*current)?;
    if lexer.is_eof(*current + 1) {
        return Err(format!("{}:{}: parse ERROR: expected '(' after 'func' or 'proc', found EOF.", t.line, t.col));
    }
    if t.token_type != TokenType::LeftParen {
        return Err(format!("{}:{}: parse ERROR: expected '(' after 'func', found {:?}.", t.line, t.col, t.token_type));
    }
    let args = parse_func_proc_args(&lexer, current)?;
    let returns = func_proc_returns(&lexer, current)?;
    let throws = func_proc_throws(&lexer, current)?;

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

    let func_def = SFuncDef{function_type: function_type, args: args, returns: returns, body: body, throws};
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
        return Err(format!("{}:{}: parse ERROR: Expected '{{' after 'enum'.", t.line, t.col));
    }
    if lexer.is_eof(*current + 1) {
        let t = lexer.get_token(*current)?;
        return Err(format!("{}:{}: parse ERROR: expected identifier after 'enum {{', found EOF.", t.line, t.col));
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
                let enum_val_name = &it_t.token_str;
                let next_t = lexer.get_token(*current + 1)?;
                match next_t.token_type {
                    TokenType::Colon => {
                        let next2_t = lexer.get_token(*current + 2)?;
                        if next2_t.token_type != TokenType::Identifier {
                            return Err(format!("{}:{}: parse ERROR: Expected type identifier after '{} :', found '{:?}'.", t.line, t.col, enum_val_name, next2_t.token_type));
                        }
                        let enum_val_type = &next2_t.token_str;
                        enum_map.insert(enum_val_name.to_string(), Some(str_to_value_type(enum_val_type)));
                        *current = *current + 2;
                    },
                    TokenType::Comma | TokenType::RightBrace => {
                        enum_map.insert(enum_val_name.to_string(), None);
                        if next_t.token_type == TokenType::RightBrace {
                            end_found = true;
                        }
                    },
                    _ => {
                        return Err(format!("{}:{}: parse ERROR: Expected ',' or ':' after '{}', found '{:?}'.", t.line, t.col, enum_val_name, next_t.token_type));
                    }
                }
            },
            TokenType::Comma => {
                // Skip comma
            },
            _ => {
                return Err(format!("{}:{}: parse ERROR: Expected '}}' to end enum or a new identifier, found '{:?}'.", t.line, t.col, it_t.token_type));
            }
        }
        *current = *current + 1;
    }
    if !end_found {
        return Err(format!("{}:{}: parse ERROR: Expected '}}' to end enum.", t.line, t.col));
    }
    let params : Vec<Expr> = Vec::new();
    return Ok(Expr::new_parse(NodeType::EnumDef(SEnumDef{enum_map: enum_map}), lexer.get_token(initial_current)?.clone(), params));
}

fn parse_struct_definition(lexer: &Lexer, current: &mut usize) -> Result<Expr, String> {
    *current = *current + 1;
    let t = lexer.get_token(*current)?;
    if t.token_type != TokenType::LeftBrace {
        return Err(format!("{}:{}: parse ERROR: Expected '{{' after 'struct'.", t.line, t.col));
    }
    if lexer.is_eof(*current + 1) {
        let t = lexer.get_token(*current)?;
        return Err(format!("{}:{}: parse ERROR: expected 'identifier' after 'struct {{', found EOF.", t.line, t.col));
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
                    return Err(format!("{}:{}: parse ERROR: all declarations inside struct defitions must have a value for now", t.line, t.col));
                }
            },
            _ => return Err(format!("{}:{}: parse ERROR: expected only declarations inside struct defition", t.line, t.col)),
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
            return Err(format!("{}:{}: parse ERROR: expected identifier after '{}.', found {:?}.",
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
        let arg_list = match parse_list(&lexer, current) {
            Ok(a_list) => a_list,
            Err(err_str) => return Err(err_str),
        };
        let mut params : Vec<Expr> = Vec::new();
        params.push(e);
        params.extend(arg_list.params);
        return Ok(Expr::new_parse(NodeType::FCall, lexer.get_token(initial_current)?.clone(), params))
    }
    return Ok(e);
}

fn get_combined_name(e: &Expr) -> Result<String, String> {
    let mut to_return = String::new();
    match &e.node_type {
        NodeType::Identifier(id_str_) => {
            to_return.push_str(&id_str_);
            to_return.push_str(".");
        },
        _ => {
            return Err(e.lang_error("parse", "get_combined_name() is to be called with Identifier expressions only"))
        },
    }
    for p in &e.params {
        match &p.node_type {
            NodeType::Identifier(id_str_) => {
                to_return.push_str(&id_str_);
                to_return.push_str(".");
            },
            _ => {
                return Err(e.lang_error("parse", "the params of an identifier expression must be Identifier expressions only"))
            },
        }
    }
    to_return.pop(); // Remove the last '.'
    return Ok(to_return)
}

fn parse_statement_identifier(lexer: &Lexer, current: &mut usize) -> Result<Expr, String> {

    let t = lexer.get_token(*current)?;
    let mut next_t = lexer.get_token(*current + 1)?;
    let mut next_token_type = &next_t.token_type;
    match next_token_type {
        TokenType::LeftParen => {
            return parse_primary_identifier(&lexer, current)
        },
        TokenType::Dot => {
            let e = parse_primary_identifier(&lexer, current)?;
            match &e.node_type {
                NodeType::FCall => return Ok(e),
                NodeType::Identifier(_) => {},
                _ => {
                    return Err(format!("{}:{}: {} parse ERROR: a series of is and dots should have been parsed as identifier or function call", t.line, t.col, LANG_NAME))
                },
            }
            next_t = lexer.get_token(*current)?;
            next_token_type = &next_t.token_type;
            match next_token_type {
                TokenType::Equal => {
                    let name = get_combined_name(&e)?;
                    return parse_assignment(&lexer, current, t, &name)
                },
                _ => {
                    return Err(format!("{}:{}: {} parse ERROR: While parsing a '.', this should never happen", t.line, t.col, LANG_NAME))
                },
            }
        },
        TokenType::Equal => {
            *current = *current + 1; // skip identifier
            return parse_assignment(&lexer, current, t, &t.token_str)
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
                    Err(format!("{}:{}: parse ERROR: Expected Type or '=' after '{} :' in statement, found {:?}.", t.line, t.col, identifier, next_next_token_type))
                },
            }

        },
        _ => {
            Err(format!("{}:{}: parse ERROR: Expected '(', ':' or '=' after identifier in statement, found {:?}.", t.line, t.col, next_token_type))
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
        _ => return Err(format!("{}:{}: parse ERROR: Expected primary expression, found {:?}.",
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

fn parse_throw_statement(lexer: &Lexer, current: &mut usize) -> Result<Expr, String> {
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
    Ok(Expr::new_parse(NodeType::Throw, lexer.get_token(initial_current)?.clone(), params))
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
        return Err(format!("{}:{}: parse ERROR: Expected '{{' after condition in 'if' statement, found {:?}.", t.line, t.col, t.token_type));
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
            return Err(format!("{}:{}: parse ERROR: Expected '{{' after 'else'.", t.line, t.col));
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
        return Err(format!("{}:{}: parse ERROR: Expected '{{' after condition in 'while' statement.", t.line, t.col));
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
        return Err(format!("{}:{}: parse ERROR: Expected '{{' after primary expression in 'switch' statement.", t.line, t.col));
    }
    *current = *current + 1;

    let mut end_found = false;
    while *current < lexer.len() && !end_found {
        let mut next_t = lexer.get_token(*current)?;
        if next_t.token_type != TokenType::Case {
            return Err(format!("{}:{}: parse ERROR: Expected 'case' in switch, found {:?}", next_t.line, next_t.col, next_t.token_type));
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
            return Err(format!("{}:{}: parse ERROR: Expected ':' case <primary_expr> in switch, found {:?}",
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
    return Err(format!("parse ERROR: Expected '}}' to end switch."));
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
        return Err(format!("{}:{}: parse ERROR: Expected identifier after 'mut', found {:?}.", t.line, t.col, next_token_type));
    }
    let identifier = &next_t.token_str;
    *current = *current + 1;
    next_t = lexer.get_token(*current + 1)?;
    next_token_type = &next_t.token_type;
    if next_token_type != &TokenType::Colon {
        return Err(format!("{}:{}: parse ERROR: Expected ':' after 'mut {}', found {:?}.", t.line, t.col, identifier, next_token_type));
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
            Err(format!("{}:{}: parse ERROR: Expected a type identifier or '=' after 'mut {} :' in statement, found {:?}.",
                        t.line, t.col, identifier, next_next_token_type))
        },
    }
}

fn parse_statement(lexer: &Lexer, current: &mut usize) -> Result<Expr, String> {
    let t = lexer.get_token(*current)?;
    match &t.token_type {
        TokenType::For => {
            return Err(format!("{}:{}: parse ERROR: Suggestion: use 'while' for now.\nExplanation: keyword 'for' is not supported yet,", t.line, t.col));
        },
        TokenType::Return => return return_statement(&lexer, current),
        TokenType::Throw => return parse_throw_statement(&lexer, current),
        TokenType::If => return if_statement(&lexer, current),
        TokenType::While => return while_statement(&lexer, current),
        TokenType::Switch => return parse_switch_statement(&lexer, current),
        TokenType::Mut => return parse_mut_declaration(&lexer, current),
        TokenType::Identifier => return parse_statement_identifier(&lexer, current),
        _ => {
            Err(format!("{}:{}: parse ERROR: Expected statement, found {:?}.", t.line, t.col, t.token_type))
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
    return Err(format!("parse ERROR: Expected {:?} to end body.", end_token));
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
    // TODO implement tagged unions
    // payload: Option<String>,
}

impl EnumVal {
    // Serialize EnumVal to bytes
    fn to_bytes(&self) -> Vec<u8> {
        let mut result = Vec::new();
        result.extend_from_slice(self.enum_type.as_bytes());
        result.push(0); // null byte separator
        result.extend_from_slice(self.enum_name.as_bytes());
        result.push(0); // null byte separator
        result
    }

    // Deserialize bytes back to EnumVal
    fn from_bytes(bytes: &[u8]) -> Option<Self> {
        let mut parts = bytes.splitn(2, |&b| b == 0);
        let enum_type_bytes = parts.next()?;
        let rest = parts.next()?;
        let mut parts2 = rest.splitn(2, |&b| b == 0);
        let enum_name_bytes = parts2.next()?;

        let enum_type = String::from_utf8(enum_type_bytes.to_vec()).ok()?;
        let enum_name = String::from_utf8(enum_name_bytes.to_vec()).ok()?;

        Some(EnumVal { enum_type, enum_name })
    }
}

#[derive(Clone)]
struct Context {
    path: String,
    mode: ModeDef,
    symbols: HashMap<String, SymbolInfo>,
    funcs: HashMap<String, SFuncDef>, // REM: currently funcs are not on symbols, perhaps they should?
    enum_defs: HashMap<String, SEnumDef>,
    struct_defs: HashMap<String, SStructDef>,
    arena: Vec<u8>, // REM: heap/arena memory (starts at 1 to avoid NULL confusion)
    arena_index: HashMap<String, usize>, // stores offsets
}

impl Context {
    fn new(path: &String, mode_name: &str) -> Context {
        return Context {
            path: path.to_string(),
            mode: mode_from_name(mode_name).unwrap(),
            symbols: HashMap::new(),
            funcs: HashMap::new(),
            enum_defs: HashMap::new(),
            struct_defs: HashMap::new(),
            arena: vec![0], // REM: first address 0 is reserved (invalid), malloc always >0
            arena_index: HashMap::new(),
        };
    }

    fn get_i64(self: &Context, id: &str) -> Option<i64> {
        return match self.arena_index.get(id) {
            Some(&offset) => Some(i64::from_ne_bytes(self.arena[offset..offset + 8].try_into().unwrap())),
            None => None,
        }
    }

    fn insert_i64(self: &mut Context, id: &str, i64_str: &String) -> Option<i64> {
        let v = i64_str.parse::<i64>().unwrap();
        let offset = self.arena.len();
        self.arena.extend_from_slice(&v.to_ne_bytes());
        return match self.arena_index.insert(id.to_string(), offset) {
            Some(old_offset) => Some(i64::from_ne_bytes(self.arena[old_offset..old_offset + 8].try_into().unwrap())),
            None => None,
        }
    }

    fn get_u8(self: &Context, id: &str) -> Option<u8> {
        return match self.arena_index.get(id) {
            Some(&offset) => Some(self.arena[offset]),
            None => None,
        }
    }

    fn insert_u8(self: &mut Context, id: &str, u8_str: &String) -> Option<u8> {
        let v = u8_str.parse::<u8>().unwrap();
        let offset = self.arena.len();
        self.arena.push(v);
        return match self.arena_index.insert(id.to_string(), offset) {
            Some(old_offset) => Some(self.arena[old_offset]),
            None => None,
        }
    }

    fn get_bool(self: &Context, id: &str) -> Option<bool> {
        return match self.arena_index.get(id) {
            Some(&offset) => Some(self.arena[offset] == 0),
            None => None,
        }
    }

    fn insert_bool(self: &mut Context, id: &str, bool_str: &String) -> Option<bool> {
        let bool_to_insert = lbool_in_string_to_bool(bool_str);
        let stored = if bool_to_insert { 0 } else { 1 };
        let offset = self.arena.len();
        self.arena.push(stored);
        return match self.arena_index.insert(id.to_string(), offset) {
            Some(_old_offset) => Some(bool_to_insert),
            None => None,
        }
    }

    fn insert_struct_field(self: &mut Context, id: &str, struct_def: &SStructDef, decl: &Declaration, is_mut: bool) -> bool {
        let default_value = match struct_def.default_values.get(&decl.name) {
            Some(_e_) => eval_expr(self, _e_),
            None => {
                println!("Cannot insert field '{}' in struct '{}' \nTODO: insert_struct_field: allow fields without default values",
                         decl.name, id);
                return false
            },
        };
        return self.insert_struct_field_with_value(id, &decl, is_mut, &default_value);
    }

    fn insert_struct_field_with_value(self: &mut Context, id: &str, decl: &Declaration, is_mut: bool, value: &String) -> bool {
        let combined_name = format!("{}.{}", id, &decl.name);
        match &decl.value_type {
            ValueType::TCustom(type_name) => {
                match type_name.as_str() {
                    "U8" => {
                        self.insert_u8(&combined_name, value);
                    },
                    "I64" => {
                        self.insert_i64(&combined_name, value);
                    },
                    "Bool" => {
                        self.insert_bool(&combined_name, value);
                    },
                    "String" => {
                        self.insert_string(&combined_name, value);
                    },
                    _ => {
                        if self.enum_defs.contains_key(type_name) {
                            self.insert_enum(&combined_name, type_name, &value);
                        } else {
                            println!("ERROR: Cannot insert field '{}' in struct '{}'\n Context.insert_struct_field: TODO: allow fields of custom struct type '{}'",
                                     decl.name, id, value_type_to_str(&decl.value_type));
                            return false
                        }
                    },
                }
            },
            _ => {
                println!("ERROR: Cannot insert field '{}' in struct '{}'\n Context.insert_struct_field: TODO: allow fields of type '{}'",
                         decl.name, id, value_type_to_str(&decl.value_type));
                return false;
            },
        }
        self.symbols.insert(combined_name, SymbolInfo{value_type: decl.value_type.clone(), is_mut: is_mut});
        return true;
    }

    fn get_field_value(self: &mut Context, custom_type_name: &str, id: &str, decl: &Declaration) -> Option<String> {
        let combined_name = format!("{}.{}", id, &decl.name);
        match &decl.value_type {
            ValueType::TCustom(type_name) => {
                match type_name.as_str() {
                    "I64" => {
                        return self.get_i64(&combined_name).map(|value| value.to_string())
                    },
                    "U8" => {
                        return self.get_u8(&combined_name).map(|value| value.to_string())
                    },
                    "Bool" => {
                        return self.get_bool(&combined_name).map(|value| value.to_string())
                    },
                    "String" => {
                        return self.get_string(&combined_name)
                    },
                    _ => {
                        println!("ERROR: Cannot get field '{}' from struct '{}'\n Context.get_struct_field: TODO: allow fields of custom struct type '{}'",
                                 decl.name, id, value_type_to_str(&decl.value_type));
                        return None;
                    },
                }
            }
            _ => {
                println!("ERROR: Cannot get field '{}' in struct '{}'\n Context.get_struct_field: TODO: allow fields of type '{}'",
                         decl.name, custom_type_name, value_type_to_str(&decl.value_type));
                return None
            },
        }
    }

    // TODO all args should be passed as pointers/references and we wouldn't need this
    fn copy_fields(self: &mut Context, custom_type_name: &str, src: &str, dest: &str) -> bool {
        // Search the struct def and add all mut values as fields in order
        let struct_def = match self.struct_defs.get(custom_type_name) {
            Some(struct_def_) => struct_def_.clone(),
            None => return false,
        };

        let is_mut = match self.symbols.get(dest) {
            Some(symbol_info_) => symbol_info_.is_mut,
            None => return false,
        };
        for (_member_name, decl) in struct_def.members.iter() {
            if decl.is_mut {
                let src_value = match self.get_field_value(custom_type_name, src, &decl) {
                    Some(val_) => val_,
                    None => return false,
                };
                if !self.insert_struct_field_with_value(dest, &decl, is_mut, &src_value) {
                    return false;
                }
            }
        }

        return true
    }

    fn insert_struct(self: &mut Context, id: &str, custom_type_name: &str) -> bool {
        // Search the struct def and add all mut values as fields in order
        let struct_def = match self.struct_defs.get(custom_type_name) {
            Some(struct_def_) => struct_def_.clone(),
            None => return false,
        };

        let is_mut = match self.symbols.get(id) {
            Some(symbol_info_) => symbol_info_.is_mut,
            None => return false,
        };
        for (_member_name, decl) in struct_def.members.iter() {
            if decl.is_mut {
                if !self.insert_struct_field(&id, &struct_def, &decl, is_mut) {
                    return false;
                }
            }
        }

        return true
        // TODO insert the struct as a whole in the same buffer and access the fields with offsets
    }

    fn get_string(self: &Context, id: &str) -> Option<String> {
        return match self.arena_index.get(id) {
            Some(&offset) => {
                let mut end = offset;
                while end < self.arena.len() && self.arena[end] != 0 {
                    end += 1;
                }
                // Include everything before null terminator
                Some(String::from_utf8_lossy(&self.arena[offset..end]).to_string())
            },
            None => None,
        }
    }

    fn insert_string(self: &mut Context, id: &str, value_str: &String) -> Option<String> {
        let offset = self.arena.len();
        self.arena.extend_from_slice(value_str.as_bytes());
        self.arena.push(0); // Null terminator
        return match self.arena_index.insert(id.to_string(), offset) {
            Some(old_offset) => {
                let mut end = old_offset;
                while end < self.arena.len() && self.arena[end] != 0 {
                    end += 1;
                }
                Some(String::from_utf8_lossy(&self.arena[old_offset..end]).to_string())
            },
            None => None,
        }
    }

    fn get_enum(self: &Context, id: &str) -> Option<EnumVal> {
        return self.arena_index.get(id).and_then(|&offset| EnumVal::from_bytes(&self.arena[offset..]));
    }

    fn insert_enum(self: &mut Context, id: &str, enum_type: &str, enum_name: &str) -> Option<EnumVal> {
        let enum_val = EnumVal {
            enum_type: enum_type.to_string(),
            enum_name: enum_name.to_string(),
        };
        let serialized = enum_val.to_bytes();
        let offset = self.arena.len();
        self.arena.extend(&serialized);
        return self.arena_index.insert(id.to_string(), offset).and_then(|_old_offset| EnumVal::from_bytes(&self.arena[offset..]));
    }
}

fn get_func_name_in_call(e: &Expr) -> String {
    assert!(e.node_type == NodeType::FCall);
    assert!(e.params.len() > 0);
    match &e.get(0).node_type {
        NodeType::Identifier(f_name) => return f_name.clone(),
        _ => return e.lang_error("panic_type", &format!("panic calling get_func_name_in_call(), this should never happen.")),
    }
}

fn value_type_func_proc(e: &Expr, name: &str, func_def: &SFuncDef) -> Result<ValueType, String> {
    match func_def.returns.len() {
        0 => {
            return Err(e.error("type", &format!("func '{}' does not return anything", name)));
        },
        1 => {
            match func_def.returns.get(0).unwrap() {
                ValueType::TCustom(type_str) => Ok(ValueType::TCustom(type_str.to_string())), // TODO find a better way
                _ => return Err(e.error("type", &format!("func '{}' returns unsupported type {}",
                                                         name, value_type_to_str(func_def.returns.get(0).unwrap())))),
            }
        },
        _ => {
            return Err(e.todo_error("type", &format!("func '{}' returns multiple values", name)));
        },
    }
}

fn get_ufcs_fcall_value_type(context: &Context, e: &Expr, f_name: &String, id_expr: &Expr, symbol: &SymbolInfo) -> Result<ValueType, String> {
    let after_dot = match id_expr.params.get(0) {
        Some(_after_dot) => _after_dot,
        None => {
            return Err(e.error("type", &format!("Cannot call '{}', it is not a function or struct, it is a '{}'",
                                                &f_name, value_type_to_str(&symbol.value_type))));
        },
    };

    match &after_dot.node_type {
        NodeType::Identifier(after_dot_name) => {
            if context.funcs.contains_key(after_dot_name) {
                return value_type_func_proc(&e, &f_name, &context.funcs.get(after_dot_name).unwrap())
            }
            return Err(e.lang_error("type", &format!("expected function name after '{}.' found '{}'", f_name, after_dot_name)));
        },
        _ => {
            return Err(e.error("type", &format!("expected identifier after '{}.' found '{:?}'", f_name, after_dot.node_type)));
        },
    }
}

fn get_fcall_value_type(context: &Context, e: &Expr) -> Result<ValueType, String> {

    let f_name = get_func_name_in_call(&e);
    if context.funcs.contains_key(&f_name) {
        return value_type_func_proc(&e, &f_name, &context.funcs.get(&f_name).unwrap())
    } else if context.symbols.contains_key(&f_name) {

        let symbol = context.symbols.get(&f_name).unwrap();
        let id_expr = e.get(0);
        match &symbol.value_type {
            ValueType::TStructDef => {
                let struct_def = match context.struct_defs.get(&f_name) {
                    Some(_struct_def) => _struct_def,
                    None => {
                        return Err(e.lang_error("type", &format!("struct '{}' not found in context", f_name)));
                    },
                };
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
                                return Err(e.error("type", &format!("struct '{}' has no member '{}' a", f_name, after_dot_name)));
                            },
                        };
                        let member_default_value = match struct_def.default_values.get(after_dot_name) {
                            Some(_member) => _member,
                            None => {
                                return Err(e.error("type", &format!("struct '{}' has no member '{}' b", f_name, after_dot_name)));
                            },
                        };
                        match &member_default_value.node_type {
                            NodeType::FuncDef(func_def) => {
                                let combined_name = format!("{}.{}", f_name, after_dot_name);
                                return value_type_func_proc(&e, &combined_name, &func_def);
                            },
                            _  => {
                                return Err(e.error("type", &format!("Cannot call '{}.{}', it is not a function, it is '{}'",
                                                                    f_name, after_dot_name, value_type_to_str(&member_decl.value_type))));
                            },
                        }
                    },
                    _ => {
                        return Err(e.lang_error("type", &format!("Expected identifier after '{}.' found '{:?}'", f_name, after_dot.node_type)));
                    },
                }
            },
            ValueType::TCustom(custom_type_name) => { // TODO handle enums too
                let struct_def = match context.struct_defs.get(custom_type_name) {
                    Some(_struct_def) => _struct_def,
                    None => {
                        return Err(e.lang_error("type", &format!("struct '{}' not found in context", f_name)));
                    },
                };
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
                                match get_ufcs_fcall_value_type(&context, &e, &f_name, id_expr, symbol) {
                                    Ok(ok_val) => return Ok(ok_val),
                                    Err(error_string) => {
                                        println!("{}", error_string);
                                        return Err(e.error("type", &format!("struct '{}' has no member '{}' c", custom_type_name, after_dot_name)));
                                    },
                                }
                            },
                        };
                        let member_default_value = match struct_def.default_values.get(after_dot_name) {
                            Some(_member) => _member,
                            None => {
                                return Err(e.error("type", &format!("struct '{}' has no member '{}' d", custom_type_name, after_dot_name)));
                            },
                        };
                        match &member_default_value.node_type {
                            NodeType::FuncDef(func_def) => {
                                let combined_name = format!("{}.{}", custom_type_name, after_dot_name);
                                return value_type_func_proc(&e, &combined_name, &func_def);
                            },
                            _  => {
                                return Err(e.error("type", &format!("Cannot call '{}.{}', it is not a function, it is '{}'",
                                                                    f_name, after_dot_name, value_type_to_str(&member_decl.value_type))));
                            },
                        }
                    },
                    _ => {
                        return Err(e.lang_error("type", &format!("Expected identifier after '{}.' found '{:?}'", f_name, after_dot.node_type)));
                    },
                }
            },
            _ => {
                return get_ufcs_fcall_value_type(&context, &e, &f_name, id_expr, symbol)
            },
        }

    } else {
        return Err(e.error("type", &format!("Undefined symbol '{}'", &f_name)));
    }
}

fn get_value_type(context: &Context, e: &Expr) -> Result<ValueType, String> {
    match &e.node_type {
        NodeType::LI64(_) => Ok(ValueType::TCustom("I64".to_string())),
        NodeType::LBool(_) => Ok(ValueType::TCustom("Bool".to_string())),
        NodeType::LString(_) => Ok(ValueType::TCustom("String".to_string())),
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
                    return Err(e.error("type", &format!("Undefined symbol '{}'", &name)));
                }
            };
            if e.params.len() == 0 {
                return Ok(symbol_info.value_type.clone());
            }
            let member_str = match &e.get(0).node_type {
                NodeType::Identifier(member_name) => member_name,
                node_type => return Err(e.lang_error("type", &format!("identifiers can only contain identifiers, found '{:?}'.", node_type))),
            };

            match &symbol_info.value_type {
                ValueType::TStructDef => {
                    match context.struct_defs.get(name) {
                        Some(struct_def) => {
                            match struct_def.members.get(member_str) {
                                Some(decl) => {
                                    if !decl.is_mut {
                                        return Ok(decl.value_type.clone());
                                    } else {
                                        return Err(e.error("type", &format!("struct '{}' has no const (static) member '{}', an instance is needed to access mutable members",
                                                                            name, member_str)));
                                    }
                                },
                                _ => {
                                    return Err(e.error("type", &format!("struct '{}' has no member '{}' d", name, member_str)))
                                },
                            }
                        },
                        None => {
                            return Err(e.error("type", &format!("Undefined struct '{}'", name)));
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
                                        node_type => return Err(e.error("type", &format!("identifiers can only contain identifiers, found '{:?}'",
                                                                        node_type))),
                                    };
                                    return Err(e.error("type", &format!("Suggestion: remove '.{}' after '{}.{}'\nExplanation: enum value '{}.{}' cannot have members",
                                                                        extra_member_str, name, member_str, name, member_str)));
                                }
                                return Ok(ValueType::TCustom(name.to_string()));
                            }
                            return Err(e.error("type", &format!("enum '{}' has no value '{}'", name, member_str)));
                        }
                        None => {
                            return Err(e.error("type", &format!("Undefined enum '{}'", name)));
                        }
                    }
                },
                ValueType::TCustom(custom_type_name) => {
                    match context.struct_defs.get(custom_type_name) {
                        Some(struct_def) => {
                            match struct_def.members.get(member_str) {
                                Some(decl) => {
                                    return Ok(decl.value_type.clone());
                                },
                                None => {
                                    return Err(e.error("type", &format!("struct '{}' has no member '{}' d", name, member_str)))
                                },
                            }
                        },
                        None => {
                            return Err(e.error("type", &format!("Undefined struct '{}'", name)));
                        },
                    }
                },
                _ => {
                    return Err(e.error("type", &format!("'{}' of type '{}' can't have members, '{}' is not a member",
                                       name, value_type_to_str(&symbol_info.value_type), member_str)))
                },
            }
        },
        node_type => return Err(format!("{}:{}: {} ERROR: get_value_type() not implement for {:?} yet.", e.line, e.col, LANG_NAME, node_type)),
    }
}

fn init_context(context: &mut Context, e: &Expr) -> Vec<String> {
    let mut errors : Vec<String> = Vec::new();
    match &e.node_type {
        NodeType::Body => {
            for se in &e.params {
                errors.extend(init_context(context, &se));
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
                errors.push(format!("{}:{}: compiler ERROR: '{}' already declared.", e.line, e.col, decl.name));
            }
            assert!(e.params.len() == 1, "{} ERROR: in init_context, while declaring {}, declarations must take exactly one value.", LANG_NAME, decl.name);
            let inner_e = e.get(0);
            let mut value_type = match get_value_type(&context, &inner_e) {
                Ok(val_type) => val_type,
                Err(error_string) => {
                    errors.push(error_string);
                    return errors;
                },
            };
            if decl.value_type != str_to_value_type(INFER_TYPE) {
                if decl.value_type == ValueType::TCustom("U8".to_string()) && value_type == ValueType::TCustom("I64".to_string()) {
                    value_type = decl.value_type.clone();
                } else if value_type != decl.value_type {
                    errors.push(e.error("type", &format!("'{}' declared of type '{}' but initialized to type '{}'.",
                                                         decl.name, value_type_to_str(&decl.value_type), value_type_to_str(&value_type))));
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
                            errors.push(format!("{}:{}: {} ERROR: {}s should have definitions", e.line, e.col, LANG_NAME, value_type_to_str(&value_type)));
                            return errors;
                        },
                    }
                },

                ValueType::TEnumDef => {
                    assert!(inner_e.params.len() == 0, "{} ERROR: while declaring {}: enum declarations don't have any parameters in the tree.", LANG_NAME,
                            decl.name);
                    match &inner_e.node_type {
                        NodeType::EnumDef(enum_def) => {
                            context.symbols.insert(decl.name.to_string(), SymbolInfo{value_type: value_type.clone(), is_mut: decl.is_mut});
                            context.enum_defs.insert(decl.name.to_string(), enum_def.clone());
                        },
                        _ => {
                            errors.push(format!("{}:{}: {} ERROR: enums should have definitions.", e.line, e.col, LANG_NAME));
                            return errors;
                        },
                    }
                },
                ValueType::TStructDef => {
                    assert!(inner_e.params.len() == 0, "{} ERROR: while declaring {}, struct declarations must have exactly 0 params.", LANG_NAME,
                            decl.name);
                    match &inner_e.node_type {
                        NodeType::StructDef(struct_def) => {
                            context.symbols.insert(decl.name.to_string(), SymbolInfo{value_type: value_type.clone(), is_mut: decl.is_mut});
                            context.struct_defs.insert(decl.name.to_string(), struct_def.clone());
                        },
                        _ => {
                            errors.push(format!("{}:{}: {} ERROR: enums should have definitions.", e.line, e.col, LANG_NAME));
                            return errors;
                        },
                    }
                },

                ValueType::TList |
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
            // TODO the arguments of a function call can also call procedures
            let f_name = get_func_name_in_call(&e);
            return context.funcs.contains_key(&f_name) && context.funcs.get(&f_name).unwrap().is_proc()
        },
        NodeType::Declaration(decl) => {
            assert!(e.params.len() == 1, "{} ERROR: while declaring {}, declarations must take exactly one value.", LANG_NAME, decl.name);
            is_expr_calling_procs(&context, &e.get(0))
        },
        NodeType::Assignment(var_name) => {
            assert!(e.params.len() == 1, "{} ERROR: while assigning {}, assignments must take exactly one value, not {}.", LANG_NAME, var_name, e.params.len());
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
        NodeType::If | NodeType::While | NodeType::Switch | NodeType::Return | NodeType::Throw => {
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
    return false
}

fn basic_mode_checks(context: &Context, e: &Expr) -> Vec<String> {
    let mut errors : Vec<String> = Vec::new();

    match &e.node_type {
        NodeType::Body => {
            for p in e.params.iter() {
                match &p.node_type {

                    NodeType::Declaration(decl) => {
                        if !context.mode.allows_base_mut && decl.is_mut {
                            errors.push(e.error("mode", &format!("mode {} doesn't allow mut declarations of 'mut {}'.\nSuggestion: remove 'mut' or change to mode script or cli",
                                                                 context.mode.name, decl.name)));
                        }
                    },
                    NodeType::FCall => {
                        if !context.mode.allows_base_calls {
                            let f_name = get_func_name_in_call(&p);
                            if f_name != "import" {
                                errors.push(e.error("mode", &format!("mode {} doesn't allow calls in the root context of the file'.\nSuggestion: remove the call to '{}' or change mode 'test' or 'script'",
                                                                     context.mode.name, f_name)));
                            }
                        }
                    },
                    _ => {},
                }
            }
        },
        _ => {
            errors.push(e.lang_error("mode", "basic_mode_checks() expects a body expression, this should never happen."))
        },
    }

    if context.mode.needs_main_proc {
        match context.symbols.get("main") {
            Some(symbol_info) => {
                if symbol_info.value_type != ValueType::TProc {
                    errors.push(e.error("mode", &format!("mode {} requires 'main' to be defined as a proc. It was defined as a {} instead",
                                                         context.mode.name, value_type_to_str(&symbol_info.value_type))));
                }
            },
            None => {
                errors.push(format!("{}:{}: mode ERROR: mode {} requires 'main' to be defined as a proc.", e.line, e.col, context.mode.name));
            },
        };
    }
    return errors;
}

fn check_enum_def(e: &Expr, enum_def: &SEnumDef) -> Vec<String> {
    assert!(e.params.len() == 0, "{} ERROR: in check_types(): enum declarations don't have any parameters in the tree.", LANG_NAME);
    let mut errors : Vec<String> = Vec::new();

    for (_enum_val_name, enum_opt) in &enum_def.enum_map {
        match &enum_opt {
            None => {},
            Some(value_type) => {
                match value_type {
                    ValueType::TCustom(ref custom_type_name) => match custom_type_name.as_str() {
                        "I64" | "Bool" | "U8" | "String" => {},
                        _ => {
                            errors.push(e.todo_error("type", &format!("{}:{}: 'enum' does not support custom types yet, found custom type '{}'.",
                                                                      e.line, e.col, custom_type_name)));
                        },
                    },
                    _ => {},
                }
            },
        }
    }
    return errors;
}

fn check_if_statement(mut context: &mut Context, e: &Expr) -> Vec<String> {
    assert!(e.params.len() == 2 || e.params.len() == 3, "{} ERROR: if nodes must have 2 or 3 parameters.", LANG_NAME);
    let mut errors : Vec<String> = Vec::new();

    let inner_e = e.get(0);
    let value_type = match get_value_type(&context, &inner_e) {
        Ok(val_type) => val_type,
        Err(error_string) => {
            errors.push(error_string);
            return errors;
        },
    };

    let first_is_condition = match value_type {
        ValueType::TCustom(type_name) => match type_name.as_str() {
            "Bool" => true,
            _ => false,
        },
        _ => false,
    };
    if !first_is_condition {
        errors.push(inner_e.error("type", &format!("'if' can only accept a bool condition first, found {:?}.", &inner_e.node_type)));
    }
    for p in e.params.iter() {
        errors.extend(check_types(&mut context, &p));
    }
    return errors;
}

fn check_while_statement(mut context: &mut Context, e: &Expr) -> Vec<String> {
    assert!(e.params.len() == 2, "{} ERROR: while nodes must have exactly 2 parameters.", LANG_NAME);
    let mut errors : Vec<String> = Vec::new();

    let inner_e = e.get(0);
    let value_type = match get_value_type(&context, &inner_e) {
        Ok(val_type) => val_type,
        Err(error_string) => {
            errors.push(error_string);
            return errors;
        },
    };

    let first_is_condition = match value_type {
        ValueType::TCustom(type_name) => match type_name.as_str() {
            "Bool" => true,
            _ => false,
        },
        _ => false,
    };
    if !first_is_condition {
        errors.push(inner_e.error("type", &format!("'while' can only accept a bool condition first, found {:?}.", &inner_e.node_type)));
    }
    for p in e.params.iter() {
        errors.extend(check_types(&mut context, &p));
    }
    return errors;
}

fn check_fcall(context: &Context, e: &Expr) -> Vec<String> {
    let mut errors: Vec<String> = Vec::new();
    let f_name = get_func_name_in_call(e);
    let func_def;

    if context.funcs.contains_key(&f_name) {
        func_def = context.funcs.get(&f_name).unwrap();
    } else if let Some(symbol) = context.symbols.get(&f_name) {
        match &symbol.value_type {
            ValueType::TStructDef => {
                let struct_def = match context.struct_defs.get(&f_name) {
                    Some(def) => def,
                    None => {
                        errors.push(e.error("type", &format!("struct '{}' not found in context", f_name)));
                        return errors;
                    },
                };

                assert!(e.params.len() > 0);
                if e.params.get(0).unwrap().params.len() == 0 {
                    return errors; // NOTE: This is to allow struct instantiation with no arguments
                }

                let after_dot = e.get(0).get(0);
                match &after_dot.node_type {
                    NodeType::Identifier(after_dot_name) => {
                        let member_value = match struct_def.default_values.get(after_dot_name) {
                            Some(val) => val,
                            None => {
                                errors.push(e.error("type", &format!("struct '{}' has no member '{}'", f_name, after_dot_name)));
                                return errors;
                            },
                        };
                        match &member_value.node_type {
                            NodeType::FuncDef(f) => {
                                func_def = f;
                            },
                            _ => {
                                errors.push(e.error("type", &format!("Cannot call '{}.{}', it is a '{:?}', not a function.",
                                    f_name, after_dot_name, member_value.node_type)));
                                return errors;
                            },
                        }
                    },
                    _ => {
                        errors.push(e.error("type", &format!("expected identifier after '{}.' found '{:?}'", f_name, after_dot.node_type)));
                        return errors;
                    },
                }
            },
            ValueType::TCustom(type_name) => {
                let struct_def = match context.struct_defs.get(type_name) {
                    Some(def) => def,
                    None => {
                        errors.push(e.error("type", &format!("type '{}' not found in context", type_name)));
                        return errors;
                    },
                };

                let after_dot = e.get(0).get(0);
                match &after_dot.node_type {
                    NodeType::Identifier(after_dot_name) => {
                        let member_value = match struct_def.default_values.get(after_dot_name) {
                            Some(val) => val,
                            None => {
                                errors.push(e.error("type", &format!("struct '{}' has no member '{}'", type_name, after_dot_name)));
                                return errors;
                            },
                        };
                        match &member_value.node_type {
                            NodeType::FuncDef(_) => {
                                let full_name = format!("{}.{}", type_name, after_dot_name);
                                match context.funcs.get(&full_name) {
                                    Some(_func_def_) => {
                                        let id_expr = Expr::new_clone(NodeType::Identifier(full_name.clone()), e.get(0), vec![]);
                                        let mut new_params = vec![Expr::new_clone(NodeType::Identifier(f_name.clone()), e, vec![])];
                                        new_params.extend(e.params[1..].iter().cloned());
                                        let mut new_e = Expr::new_clone(NodeType::FCall, e, new_params);
                                        new_e.params.insert(0, id_expr);
                                        return check_fcall(context, &new_e);
                                    },
                                    None => {
                                        errors.push(e.error("type", &format!("method '{}' not found in context", full_name)));
                                        return errors;
                                    },
                                }
                            },
                            _ => {
                                errors.push(e.error("type", &format!("Cannot call '{}.{}', it is a '{:?}', not a function.",
                                    type_name, after_dot_name, member_value.node_type)));
                                return errors;
                            },
                        }
                    },
                    _ => {
                        errors.push(e.error("type", &format!("expected identifier after '{}.' found {:?}", f_name, after_dot.node_type)));
                        return errors;
                    },
                }
            },
            _ => {
                errors.push(e.error("type", &format!("Cannot call '{}', it is a '{:?}', not a function nor a struct.", f_name, symbol.value_type)));
                return errors;
            },
        }
    } else {
        errors.push(e.error("type", &format!("Undefined function or struct '{}'", f_name)));
        return errors;
    }

    if func_def.args.len() == 0 && e.params.len() - 1 > 0 {
        errors.push(e.error("type", &format!("Function/procedure '{}' expects 0 args, but {} were provided.", f_name, e.params.len() - 1)));
        return errors;
    }
    let has_multi_arg = func_proc_has_multi_arg(func_def);
    if !has_multi_arg && func_def.args.len() != e.params.len() - 1 {
        errors.push(e.error("type", &format!("Function/procedure '{}' expects {} args, but {} were provided.",
            f_name, func_def.args.len(), e.params.len() - 1)));
    }
    if has_multi_arg && func_def.args.len() > e.params.len() - 1 {
        errors.push(e.error("type", &format!("Function/procedure '{}' expects at least {} args, but {} were provided.",
            f_name, func_def.args.len(), e.params.len() - 1)));
    }

    let max_arg_def = func_def.args.len();
    for i in 0..e.params.len() - 1 {
        let arg = func_def.args.get(std::cmp::min(i, max_arg_def - 1)).unwrap();
        let expected_type = match &arg.value_type {
            ValueType::TMulti(inner_type) => inner_type,
            _ => &arg.value_type,
        };
        let found_type = match get_value_type(&context, e.get(i + 1)) {
            Ok(val_type) => val_type,
            Err(error_string) => {
                errors.push(error_string);
                return errors;
            },
        };
        if expected_type != &found_type {
            if expected_type == &str_to_value_type(INFER_TYPE) {
                errors.push(e.error("type", &format!("calling func/proc '{}' declared arg {} without type, but type inference in args is not supported yet.\n Suggestion: the arg should be '{} : {},' instead of just '{},' Found type: {:?}",
                    f_name, arg.name, arg.name, value_type_to_str(&found_type), arg.name, value_type_to_str(&expected_type))));
            } else {
                errors.push(e.error("type", &format!("calling function '{}' expects '{}' for arg '{}', but '{}' was provided.",
                    f_name, value_type_to_str(expected_type), arg.name, value_type_to_str(&found_type))));
            }
        }
    }

    return errors
}

fn check_func_proc_types(func_def: &SFuncDef, mut context: &mut Context, e: &Expr) -> Vec<String> {
    let mut errors : Vec<String> = Vec::new();
    let mut has_variadic = false;
    for arg in &func_def.args {
        if has_variadic {
            errors.push(e.error("type", &format!("Variadic argument '{}' must be the last (only one variadic argument allowed).", &arg.name)));
        }
        match &arg.value_type {
            ValueType::TMulti(_) => {
                has_variadic = true;
            }
            ValueType::TCustom(ref custom_type_name) => {
                let _custom_symbol = match context.symbols.get(custom_type_name) {
                    Some(custom_symbol_) => custom_symbol_,
                    None => {
                        errors.push(e.error("type", &format!("Argument '{}' is of undefined type '{}'.", &arg.name, &custom_type_name)));
                        return errors
                    },
                };
                // TODO check more type stuff
            },
            _ => {},
        }
        context.symbols.insert(arg.name.clone(), SymbolInfo{value_type: arg.value_type.clone(), is_mut: arg.is_mut});
    }

    // Don't check the bodies of external functions
    if func_def.is_ext() {
        return errors;
    }

    let returns_len = func_def.returns.len();
    // let mut return_found = false;
    for p in func_def.body.iter() {
        match &p.node_type {
            NodeType::Return => {
                // return_found = true;
                if returns_len != p.params.len() {
                    errors.push(e.error("type", &format!("Returning {} values when {} were expected.", returns_len, p.params.len())));
                } else {
                    for i in 0..p.params.len() {
                        let expected_value_type = func_def.returns.get(i).unwrap();
                        match get_value_type(&context, p.params.get(i).unwrap()) {
                            Ok(actual_value_type) => {
                                if expected_value_type != &actual_value_type {
                                    errors.push(e.error("type", &format!("Return value in pos {} expected to be {:?}, but found {:?} instead",
                                                                         i, expected_value_type, actual_value_type)));
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
        errors.extend(check_types(&mut context, &p));
    }
    // TODO More complete checks for return values inside if statements and the like
    // if !return_found && returns_len > 0 {
    //     errors.push(e.error("type", &format!("No return statments found in function that returns ", e.line, e.col));
    // }

    if func_def.function_type == FunctionType::FTFunc || func_def.function_type == FunctionType::FTFuncExt {
        if func_def.returns.len() == 0 && func_def.throws.len() == 0 {
            errors.push(e.error("type", "funcs must return or throw something, use a proc instead"));
        }
    }
    // TODO should macros be allowed to call procs?
    if func_def.function_type == FunctionType::FTFunc {
        for se in &func_def.body {
            if is_expr_calling_procs(&context, &se) {
                errors.push(se.error("type", "funcs cannot call procs."));
            }
        }
    }

    return errors
}

fn check_declaration(mut context: &mut Context, e: &Expr, decl: &Declaration) -> Vec<String> {
    assert!(e.params.len() == 1, "{} ERROR: in declaration of {} declaration nodes must exactly 1 parameter.", LANG_NAME, decl.name);
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
                errors.push(format!("{}:{} {} ERROR: Cannot infer the declaration type of {}", e.line, e.col, LANG_NAME, decl.name));
                return errors;
            },
            ValueType::TCustom(custom_type) => {
                match context.struct_defs.get(&custom_type) {
                    Some(_struct_def) => {
                        context.insert_struct(&decl.name, &custom_type);
                    },
                    _ => {}, // If it's enum, don't do anything
                }
            }
            ValueType::TFunc | ValueType::TProc | ValueType::TMacro => {
                match &inner_e.node_type {
                    NodeType::FuncDef(func_def) => {
                        // TODO move to init_context() ? inner contexts are not persisted in init_context
                        context.funcs.insert(decl.name.clone(), func_def.clone());
                    },
                    _ => {
                        errors.push(format!("{}:{} {} ERROR: functions should have definitions", e.line, e.col, LANG_NAME));
                        return errors;
                    },
                }
            },
            _ => {},
        }
    }
    errors.extend(check_types(&mut context, &inner_e));

    return errors
}

fn check_assignment(mut context: &mut Context, e: &Expr, var_name: &str) -> Vec<String> {
    assert!(e.params.len() == 1, "{} ERROR: in assignment to {}, assignments must take exactly one value, not {}.", LANG_NAME, var_name, e.params.len());
    let mut errors : Vec<String> = Vec::new();

    if context.funcs.contains_key(var_name)  {
        errors.push(e.error("type", &format!("function '{}' cannot be assigned to.", var_name)));
    } else if context.symbols.contains_key(var_name) {
        let symbol_info = context.symbols.get(var_name).unwrap();
        if !symbol_info.is_mut {
            errors.push(e.error("type", &format!("Cannot assign to constant '{}', Suggestion: declare it as 'mut'.", var_name)));
        }
    } else {
        errors.push(e.error("type", &format!("Suggestion: try changing '{} =' for '{} :='\nExplanation: Cannot assign to undefined symbol '{}'.",
                                             var_name, var_name, var_name)));
    }
    errors.extend(check_types(&mut context, &e.get(0)));
    return errors
}

fn check_switch_statement(context: &mut Context, e: &Expr) -> Vec<String> {
    let mut errors: Vec<String> = Vec::new();

    let switch_expr_type = match get_value_type(context, e.get(0)) {
        Ok(t) => t,
        Err(err) => {
            errors.push(err);
            return errors
        }
    };

    let mut case_found = false;
    let mut default_found = false;

    let mut i = 1;
    while i < e.params.len() {
        let case_expr = &e.params[i];

        match &case_expr.node_type {
            NodeType::DefaultCase => {
                if default_found {
                    errors.push(case_expr.error("type", "Duplicate default case in switch"));
                }
                default_found = true;
                case_found = true;
            }
            _ => {
                case_found = true;
            }
        }

        i += 1;

        if i >= e.params.len() {
            errors.push(e.error("type", "Switch case missing body expression"));
            return errors
        }

        let body_expr = &e.params[i];
        errors.extend(check_types(context, body_expr));

        i += 1;
    }

    if !case_found {
        errors.push(e.error("type", "Switch must have at least one case"));
    }

    // Exhaustiveness check only for enums
    if let ValueType::TCustom(enum_name) = switch_expr_type {
        if let Some(enum_def) = context.enum_defs.get(&enum_name) {
            let mut matched_variants: Vec<String> = Vec::new();

            let mut j = 1;
            while j < e.params.len() {
                let case_expr = &e.params[j];
                match &case_expr.node_type {
                    NodeType::Identifier(name) => {
                        if case_expr.params.is_empty() {
                            // case A
                            matched_variants.push(name.clone());
                        } else {
                            // case ExampleEnum.A
                            let variant_expr = &case_expr.params[0];
                            if let NodeType::Identifier(variant) = &variant_expr.node_type {
                                if name != &enum_name {
                                    errors.push(case_expr.error("type", &format!("Mismatched enum type '{}', expected '{}'.", name, enum_name)));
                                }
                                matched_variants.push(variant.clone());
                            } else {
                                errors.push(case_expr.error("type", "Invalid enum case syntax"));
                            }
                        }
                    }
                    NodeType::DefaultCase => {
                        default_found = true;
                    }
                    _ => {}
                }
                j += 2;
            }

            if !default_found {
                for variant in enum_def.enum_map.keys() {
                    if !matched_variants.contains(variant) {
                        errors.push(e.error("type", &format!("Switch is missing case for variant '{}'", variant)));
                    }
                }
            }
        }
    }

    return errors
}

fn check_types(mut context: &mut Context, e: &Expr) -> Vec<String> {
    let mut errors : Vec<String> = Vec::new();
    match &e.node_type {
        NodeType::Body => {
            for p in e.params.iter() {
                errors.extend(check_types(&mut context, &p));
            }
        },

        NodeType::EnumDef(enum_def) => {
            errors.extend(check_enum_def(&e, enum_def));
        },
        NodeType::StructDef(_struct_def) => {
            assert!(e.params.len() == 0, "{} ERROR: in check_types(): struct declarations must take exactly 0 params.", LANG_NAME);
        },

        NodeType::If => {
            errors.extend(check_if_statement(&mut context, &e));
        },
        NodeType::While => {
            errors.extend(check_while_statement(&mut context, &e));
        },
        NodeType::Switch => {
            errors.extend(check_switch_statement(&mut context, &e));
        },

        NodeType::FCall => {
            errors.extend(check_fcall(&context, &e));
        },
        NodeType::FuncDef(func_def) => {
            let mut function_context = context.clone();
            errors.extend(check_func_proc_types(&func_def, &mut function_context, &e));
        },
        NodeType::Identifier(name) => {
            if !(context.funcs.contains_key(name) || context.symbols.contains_key(name)) {
                errors.push(e.error("type", &format!("Undefined symbol {}", name)));
            }
        },

        NodeType::Declaration(decl) => {
            errors.extend(check_declaration(&mut context, &e, decl));
        },
        NodeType::Assignment(var_name) => {
            errors.extend(check_assignment(&mut context, &e, var_name));
        },
        NodeType::Return | NodeType::Throw => {
            for return_val in &e.params {
                errors.extend(check_types(&mut context, &return_val));
            }
        },

        NodeType::LI64(_) | NodeType::LString(_) | NodeType::LBool(_) | NodeType::LList(_) | NodeType::DefaultCase => {},
    }

    return errors
}

// ---------- core funcs implementations for eval

fn eval_core_func_loc(context: &mut Context, e: &Expr) -> String {
    let file = context.path.clone();
    let line = e.line;
    let col = e.col;

    return format!("{}:{}:{}:", file, line, col)
}

// ---------- eval memory

fn eval_core_func_malloc(mut context: &mut Context, e: &Expr) -> String {
    assert!(e.params.len() == 2, "{} ERROR: Core func 'malloc' takes exactly 1 argument. This should never happen.", LANG_NAME);

    let size_str = eval_expr(&mut context, e.get(1));
    let size = size_str.parse::<usize>().unwrap();

    let offset = context.arena.len(); // take *current* end of arena

    if size > 0 {
        context.arena.resize(offset + size, 0); // extend safely
    }

    return offset.to_string();
}

fn eval_core_func_free(mut context: &mut Context, e: &Expr) -> String {
    assert!(e.params.len() == 2, "{} ERROR: Core func 'free' takes exactly 1 argument. This should never happen.", LANG_NAME);

    let _ptr_str = eval_expr(&mut context, e.get(1));
    // NOTE: Free does nothing in arena model (for now).

    return "".to_string()
}

fn eval_core_func_memset(context: &mut Context, e: &Expr) -> String {
    assert!(
        e.params.len() == 4,
        "{} ERROR: Core func 'memset' takes exactly 3 arguments. This should never happen.",
        LANG_NAME
    );

    let dest_str = eval_expr(context, e.get(1));
    let value_str = eval_expr(context, e.get(2));
    let size_str = eval_expr(context, e.get(3));

    let dest = match dest_str.trim().parse::<i64>() {
        Ok(v) => v as usize,
        Err(err) => return e.error("eval", &format!("Invalid dest (I64): '{}': {}", dest_str, err)),
    };

    let value = match value_str.trim().parse::<u8>() {
        Ok(v) => v,
        Err(err) => return e.error("eval", &format!("Invalid value (U8): '{}': {}", value_str, err)),
    };

    let size = match size_str.trim().parse::<i64>() {
        Ok(v) => v as usize,
        Err(err) => return e.error("eval", &format!("Invalid size (I64): '{}': {}", size_str, err)),
    };

    if dest + size > context.arena.len() {
        return e.error("eval", &format!(
            "memset out of bounds: dest={} size={} arena_len={}",
            dest, size, context.arena.len()
        ));
    }

    for i in 0..size {
        context.arena[dest + i] = value;
    }

    "".to_string()
}

fn eval_core_func_memcpy(mut context: &mut Context, e: &Expr) -> String {
    assert!(e.params.len() == 4, "{} ERROR: Core func 'memcpy' takes exactly 3 arguments. This should never happen.", LANG_NAME);

    let dest_str = eval_expr(&mut context, e.get(1));
    let src_str = eval_expr(&mut context, e.get(2));
    let size_str = eval_expr(&mut context, e.get(3));

    let dest = dest_str.parse::<usize>().unwrap();
    let src = src_str.parse::<usize>().unwrap();
    let size = size_str.parse::<usize>().unwrap();

    if dest + size > context.arena.len() || src + size > context.arena.len() {
        return e.error("eval", &format!(
            "memcpy out of bounds: src={} dest={} size={} arena_len={}",
            src, dest, size, context.arena.len()
        ));
    }

    for i in 0..size {
        context.arena[dest + i] = context.arena[src + i];
    }

    return "".to_string()
}

// ---------- eval str

fn eval_core_func_str_eq(mut context: &mut Context, e: &Expr) -> String {
    assert!(e.params.len() == 3, "{} ERROR: Core func 'str_eq' takes exactly 2 arguments. This should never happen.", LANG_NAME);
    let a = &eval_expr(&mut context, e.get(1));
    let b = &eval_expr(&mut context, e.get(2));
    return (a == b).to_string()
}

fn eval_core_func_concat(mut context: &mut Context, e: &Expr) -> String {
    assert!(e.params.len() == 3, "{} ERROR: Core func 'concat' takes exactly 2 arguments. This should never happen.", LANG_NAME);
    let a = eval_expr(&mut context, e.get(1));
    let b = eval_expr(&mut context, e.get(2));
    return format!("{}{}", a, b)
}

fn eval_core_func_str_len(mut context: &mut Context, e: &Expr) -> String {
    assert!(e.params.len() == 2, "{} ERROR: Core func 'concat' takes exactly 1 argument. This should never happen.", LANG_NAME);
    let a = eval_expr(&mut context, e.get(1));
    return format!("{}", a.len())
}

fn eval_core_func_str_get_substr(mut context: &mut Context, e: &Expr) -> String {
    assert!(e.params.len() == 4, "{} ERROR: Core func 'concat' takes exactly 3 arguments. This should never happen.", LANG_NAME);
    let a = eval_expr(&mut context, e.get(1));
    let start = &eval_expr(&mut context, e.get(2)).parse::<i64>().unwrap();
    let end = &eval_expr(&mut context, e.get(3)).parse::<i64>().unwrap();
    return format!("{}", &a[*start as usize..*end as usize]);
}

fn eval_core_func_lt(mut context: &mut Context, e: &Expr) -> String {
    assert!(e.params.len() == 3, "{} ERROR: Core func 'eq' takes exactly 2 arguments. This should never happen.", LANG_NAME);
    let a = &eval_expr(&mut context, e.get(1)).parse::<i64>().unwrap();
    let b = &eval_expr(&mut context, e.get(2)).parse::<i64>().unwrap();
    (a < b).to_string()
}

fn eval_core_func_gt(mut context: &mut Context, e: &Expr) -> String {
    assert!(e.params.len() == 3, "{} ERROR: Core func 'eq' takes exactly 2 arguments. This should never happen.", LANG_NAME);
    let a = &eval_expr(&mut context, e.get(1)).parse::<i64>().unwrap();
    let b = &eval_expr(&mut context, e.get(2)).parse::<i64>().unwrap();
    (a > b).to_string()
}

fn eval_core_func_add(mut context: &mut Context, e: &Expr) -> String {
    assert!(e.params.len() == 3, "{} ERROR: Core func 'eq' takes exactly 2 arguments. This should never happen.", LANG_NAME);
    let a = &eval_expr(&mut context, e.get(1)).parse::<i64>().unwrap();
    let b = &eval_expr(&mut context, e.get(2)).parse::<i64>().unwrap();
    (a + b).to_string()
}

fn eval_core_func_sub(mut context: &mut Context, e: &Expr) -> String {
    assert!(e.params.len() == 3, "{} ERROR: Core func 'eq' takes exactly 2 arguments. This should never happen.", LANG_NAME);
    let a = &eval_expr(&mut context, e.get(1)).parse::<i64>().unwrap();
    let b = &eval_expr(&mut context, e.get(2)).parse::<i64>().unwrap();
    (a - b).to_string()
}

fn eval_core_func_mul(mut context: &mut Context, e: &Expr) -> String {
    assert!(e.params.len() == 3, "{} ERROR: Core func 'eq' takes exactly 2 arguments. This should never happen.", LANG_NAME);
    let a = &eval_expr(&mut context, e.get(1)).parse::<i64>().unwrap();
    let b = &eval_expr(&mut context, e.get(2)).parse::<i64>().unwrap();
    (a * b).to_string()
}

fn eval_core_func_div(mut context: &mut Context, e: &Expr) -> String {
    assert!(e.params.len() == 3, "{} ERROR: Core func 'eq' takes exactly 2 arguments. This should never happen.", LANG_NAME);
    let a = &eval_expr(&mut context, e.get(1)).parse::<i64>().unwrap();
    let b = &eval_expr(&mut context, e.get(2)).parse::<i64>().unwrap();
    (a / b).to_string()
}

fn eval_core_func_str_to_i64(mut context: &mut Context, e: &Expr) -> String {
    assert!(e.params.len() == 2, "{} ERROR: Core func 'str_to_i64' takes exactly 1 argument. This should never happen.", LANG_NAME);
    let a = &eval_expr(&mut context, &e.get(1)).parse::<i64>().unwrap();
    return a.to_string();
}

fn eval_core_func_i64_to_str(mut context: &mut Context, e: &Expr) -> String {
    assert!(e.params.len() == 2, "{} ERROR: Core func 'i64_to_str' takes exactly 1 argument. This should never happen.", LANG_NAME);
    eval_expr(&mut context, e.get(1))
}

fn eval_core_func_u8_to_i64(mut context: &mut Context, e: &Expr) -> String {
    assert!(e.params.len() == 2, "{} ERROR: Core func 'u8_to_i64' takes exactly 1 argument. This should never happen.", LANG_NAME);
    let a = &eval_expr(&mut context, &e.get(1)).parse::<i64>().unwrap();
    return a.to_string();
}

fn eval_core_func_i64_to_u8(mut context: &mut Context, e: &Expr) -> String {
    assert!(e.params.len() == 2, "{} ERROR: Core func 'i64_to_u8' takes exactly 1 argument. This should never happen.", LANG_NAME);
    eval_expr(&mut context, e.get(1))
}

// ---------- core procs implementations for eval

fn lbool_in_string_to_bool(b: &str) -> bool {
    match b {
        "true" => true,
        "false" => false,
        _ => panic!("{} ERROR: expected string 'true' or 'false', found '{}'. this should never happen.", LANG_NAME, b)
    }
}

fn eval_to_bool(mut context: &mut Context, e: &Expr) -> bool {
    let result = &eval_expr(&mut context, &e);
    return lbool_in_string_to_bool(result)
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
    return main_run(false, &mut context, &path, str_source, Vec::new());
}

fn eval_core_proc_runfile(mut context: &mut Context, e: &Expr) -> String {
    assert!(e.params.len() >= 2, "eval_core_proc_runfile expects at least 1 parameter.");
    let path = &eval_expr(&mut context, e.get(1));
    let mut main_args = Vec::new();
    for i in 2..e.params.len() {
        main_args.push(eval_expr(&mut context, e.get(i)));
    }
    match run_file(&path, main_args) {
        Ok(_) => {},
        Err(error_string) => {
            println!("ERROR: While running file {path}");
            return e.error("eval", &error_string);
        },
    };
    return "".to_string();
}

fn eval_core_proc_import(mut context: &mut Context, e: &Expr) -> String {
    assert!(e.params.len() == 2, "eval_core_proc_import expects a single parameter.");

    let path = format!("{}{}", &eval_expr(&mut context, e.get(1)), ".cil");
    match run_file_with_context(true, &mut context, &path, Vec::new()) {
        Ok(_) => {},
        Err(error_string) => {
            println!("ERROR: While trying to import {path}");
            return e.error("eval", &error_string);
        },
    };
    return "".to_string();
}

fn eval_core_proc_readfile(mut context: &mut Context, e: &Expr) -> String {
    assert!(e.params.len() == 2, "eval_core_proc_readfile expects a single parameter.");
    let path = &eval_expr(&mut context, e.get(1));
    let source: String = match fs::read_to_string(path) {
        Ok(file) => file,
        Err(error) => match error.kind() {
            ErrorKind::NotFound => {
                return e.error("eval", &format!("File '{}' not found.", path))
            },
            other_error_ => {
                return e.error("eval", &format!("Problem reading file '{}'\n : '{}'", path, other_error_))
            },
        },
    };
    return source;
}

fn eval_core_exit(e: &Expr) -> String {
    assert!(e.params.len() == 2, "eval_core_exit expects a single parameter.");
    let e_exit_code = e.get(1);
    let exit_code = match &e_exit_code.node_type {
        NodeType::LI64(my_li64) => {
            my_li64.clone()
        },
        node_type => {
            return e.lang_error("eval", &format!("calling core proc exit, but found {:?} instead of literal i64 exit code.",
                   node_type));
        },
    };
    std::process::exit(exit_code as i32);
}

// ---------- generic eval things

fn eval_user_func_proc_call(func_def: &SFuncDef, name: &str, mut context: &mut Context, e: &Expr) -> String {

    let mut function_context = context.clone();
    let has_multi_arg = func_proc_has_multi_arg(func_def);
    assert!(!(!has_multi_arg && func_def.args.len() != e.params.len() - 1),
            "{} ERROR: func '{}' expected {} args, but {} were provided. This should never happen.",
            LANG_NAME, name, func_def.args.len(), e.params.len()-1);
    assert!(!(has_multi_arg && func_def.args.len() > e.params.len() - 1),
            "{} ERROR: func '{}' expected at least {} args, but {} were provided. This should never happen.",
            LANG_NAME, name, func_def.args.len(), e.params.len()-1);

    let mut param_index = 1;
    let mut mut_args: Vec<(String, String, ValueType)> = Vec::new(); // (arg_name, source_name, type)

    for arg in &func_def.args {

        function_context.symbols.insert(arg.name.to_string(), SymbolInfo{value_type: arg.value_type.clone(), is_mut: arg.is_mut});
        match &arg.value_type {
            ValueType::TMulti(ref _multi_value_type) => {
                return e.todo_error("eval", &format!("Cannot use '{}' of type '{}' as an argument. Variadic arguments for user defined functions not supported yet.",
                                                     &arg.name, value_type_to_str(&arg.value_type)))
            },
            ValueType::TCustom(ref custom_type_name) => {
                let current_arg = e.get(param_index);
                let result = eval_expr(&mut context, &current_arg);

                if arg.is_mut {
                    match &current_arg.node_type {
                        NodeType::Identifier(id_) => {
                            mut_args.push((arg.name.clone(), id_.clone(), arg.value_type.clone()));
                        },
                        _ => {
                            return e.error("eval", "mut arguments must be passed as identifiers");
                        }
                    }
                }

                match custom_type_name.as_str() {
                    "I64" => {
                        function_context.insert_i64(&arg.name, &result);
                    },
                    "U8" => {
                        function_context.insert_u8(&arg.name, &result);
                    },
                    "Bool" => {
                        function_context.insert_bool(&arg.name, &result);
                    },
                    "String" => {
                        function_context.insert_string(&arg.name, &result);
                    },
                    _ => {
                        let custom_symbol = function_context.symbols.get(custom_type_name).unwrap();
                        match custom_symbol.value_type {
                            ValueType::TEnumDef => {
                                function_context.insert_enum(&arg.name, &custom_type_name, &result);
                            },
                            ValueType::TStructDef => {
                                if !function_context.insert_struct(&arg.name, &custom_type_name) {
                                    return e.lang_error("eval", &format!("Cannot use '{}' of type '{}' as an argument.", &arg.name, &custom_type_name))
                                }
                                if current_arg.params.len() > 0 {
                                    return e.todo_error("eval", &format!("Cannot use '{}' of type '{}' as an argument. Only name of struct instances allowed for struct arguments for now. ", &arg.name, &custom_type_name))
                                }
                                match &current_arg.node_type {
                                    NodeType::Identifier(id_) => {
                                        if !function_context.copy_fields(&custom_type_name, &id_, &arg.name) {
                                            return e.todo_error("eval", &format!("While copying fields from '{}' to '{}' of type '{}'",
                                                                                 &id_, &arg.name, &custom_type_name))
                                        }
                                    },
                                    _ => {
                                        return e.todo_error("eval", &format!("Cannot use '{}' of type '{}' as an argument. Only names of struct instances allowed for struct arguments for now. ",
                                                                             &arg.name, &custom_type_name))
                                    },
                                }
                            },
                            _ => {
                                return e.lang_error("eval", &format!("Cannot use '{}' of type '{}' as an argument. Custom types can only be struct or enum.",
                                                                     &arg.name, &custom_type_name))
                            },
                        }
                    },
                }

            },

            _ => {
                return e.todo_error("eval", &format!("Cannot use '{}' of type '{}' as an argument. Only enum custom types allowed for now.",
                                                     &arg.name, &value_type_to_str(&arg.value_type)))
            },
        }

        param_index += 1;
    }

    let result = eval_body(&mut function_context, &func_def.body);

    for (arg_name, source_name, value_type) in mut_args {
        match value_type {
            ValueType::TCustom(ref type_name) if type_name == "I64" => {
                let val = function_context.get_i64(&arg_name).unwrap();
                context.insert_i64(&source_name, &val.to_string());
            },
            ValueType::TCustom(ref type_name) if type_name == "U8" => {
                let val = function_context.get_u8(&arg_name).unwrap();
                context.insert_u8(&source_name, &val.to_string());
            },
            ValueType::TCustom(ref type_name) if type_name == "Bool" => {
                let val = function_context.get_bool(&arg_name).unwrap();
                context.insert_bool(&source_name, &val.to_string());
            },
            ValueType::TCustom(ref type_name) if type_name == "String" => {
                let val = function_context.get_string(&arg_name).unwrap();
                context.insert_string(&source_name, &val);
            },
            _ => {
                // TODO: support struct mutation copying later
            }
        }
    }

    return result;
}

fn eval_core_func_proc_call(name: &str, mut context: &mut Context, e: &Expr, is_proc: bool) -> String {
    return match name {
        "loc" => return eval_core_func_loc(&mut context, e),
        "malloc" => eval_core_func_malloc(&mut context, &e),
        "free" => eval_core_func_free(&mut context, &e),
        "memset" => eval_core_func_memset(&mut context, &e),
        "memcpy" => eval_core_func_memcpy(&mut context, &e),
        "str_eq" => eval_core_func_str_eq(&mut context, &e),
        "concat" => eval_core_func_concat(&mut context, &e),
        "str_len" => eval_core_func_str_len(&mut context, &e),
        "str_get_substr" => eval_core_func_str_get_substr(&mut context, &e),
        "lt" => eval_core_func_lt(&mut context, &e),
        "gt" => eval_core_func_gt(&mut context, &e),
        "add" => eval_core_func_add(&mut context, &e),
        "sub" => eval_core_func_sub(&mut context, &e),
        "mul" => eval_core_func_mul(&mut context, &e),
        "div" => eval_core_func_div(&mut context, &e),
        "str_to_i64" => eval_core_func_str_to_i64(&mut context, &e),
        "i64_to_str" => eval_core_func_i64_to_str(&mut context, &e),
        "u8_to_i64" => eval_core_func_u8_to_i64(&mut context, &e),
        "i64_to_u8" => eval_core_func_i64_to_u8(&mut context, &e),
        "eval_to_str" => eval_core_proc_eval_to_str(&mut context, &e),
        "exit" => eval_core_exit(&e),
        "import" => "".to_string(), // Should already be imported in init_context
        "input_read_line" => eval_core_proc_input_read_line(&mut context, &e),
        "print" => eval_core_proc_print(false, &mut context, &e),
        "println" => eval_core_proc_print(true, &mut context, &e),
        "readfile" => eval_core_proc_readfile(&mut context, &e),
        "runfile" => eval_core_proc_runfile(&mut context, &e),
        _ => {
            if is_proc {
                return e.lang_error("eval", &format!("Core procedure '{}' not implemented.", name))
            } else {
                return e.lang_error("eval", &format!("Core function '{}' not implemented.", name))
            }
        },
    }
}

fn eval_func_proc_call_try_ufcs(mut context: &mut Context, e: &Expr) -> String {
    // TODO Handle UFCS in check_types instead of waiting for invalid types to be discovered during evaluation
    let id_expr = e.get(0);
    let name = get_func_name_in_call(&e);
    if id_expr.params.len() == 0 { // TODO Do we really need this check?
        return e.lang_error("eval", &format!("Cannot call '{}'. Undefined function or struct.", name));
    }
    let after_dot = match id_expr.params.get(0) {
        Some(_after_dot) => _after_dot,
        None => return e.lang_error("eval", &format!("Cannot call '{}'. Undefined function or struct.", name)),
    };
    let after_dot_name = match &after_dot.node_type {
        NodeType::Identifier(f_name_) => f_name_.clone(),
        _ => return e.lang_error("eval", &format!("Cannot call '{}'. Undefined function or struct.", name)),
    };

    let id_expr_name = format!("{}.{}", name, after_dot_name);

    let new_e = Expr::new_clone(NodeType::Identifier(after_dot_name.clone()), e.get(0), Vec::new());
    let extra_arg_e = Expr::new_clone(NodeType::Identifier(name.to_string()), e, Vec::new());
    let mut new_args = Vec::new();
    new_args.push(new_e);
    new_args.push(extra_arg_e);
    new_args.extend(e.params[1..].to_vec());
    let new_fcall_e = Expr::new_clone(NodeType::FCall, e.get(0), new_args);
    let func_def = match context.funcs.get(&after_dot_name) {
        Some(func_def_) => func_def_.clone(),
        None => return after_dot.lang_error("eval", &format!("Cannot call '{}'. Undefined function.", after_dot_name)),
    };
    return eval_user_func_proc_call(&func_def, &id_expr_name, &mut context, &new_fcall_e);
}

fn eval_func_proc_call(name: &str, mut context: &mut Context, e: &Expr) -> String {
    if context.funcs.contains_key(name) {
        let func_def = &context.funcs.get(name).unwrap().clone();
        if func_def.is_ext() {
            let is_proc = func_def.is_proc();
            return eval_core_func_proc_call(&name, &mut context, &e, is_proc)
        }
        return eval_user_func_proc_call(func_def, &name, &mut context, &e)
    } else if context.struct_defs.contains_key(name) {
        let struct_def = context.struct_defs.get(name).unwrap();
        let id_expr = e.get(0);
        let after_dot = match id_expr.params.get(0) {
            Some(_after_dot) => _after_dot,
            None => {
                return e.todo_error("eval", &format!("Cannot instantiate '{}'. Not implemented yet.", name))
            },
        };
        match &after_dot.node_type {
            NodeType::Identifier(after_dot_name) => {
                let _member_decl = match struct_def.members.get(after_dot_name) {
                    Some(_member) => _member,
                    None => {
                        return e.lang_error("eval", &format!("struct '{}' has no member '{}' a", name, after_dot_name))
                    },
                };
                let combined_name = format!("{}.{}", name, after_dot_name);
                if !context.funcs.contains_key(&combined_name) {
                    return e.lang_error("eval", &format!("method '{}' not found in context", combined_name))
                }

                let func_def = &context.funcs.get(&combined_name).unwrap().clone();
                return eval_user_func_proc_call(func_def, &name, &mut context, &e);
            },
            _ => {
                return e.lang_error("eval", &format!("expected identifier after '{}.' found {:?}", name, after_dot.node_type))
            },
        }
    } else if context.symbols.contains_key(name) {
        let symbol = context.symbols.get(name).unwrap();
        match &symbol.value_type {
            ValueType::TCustom(custom_type_name) => {
                let struct_def = match context.struct_defs.get(custom_type_name) {
                    Some(_struct_def) => _struct_def,
                    None => {
                        return eval_func_proc_call_try_ufcs(&mut context, &e)
                    },
                };

                let id_expr = e.get(0);
                let after_dot = match id_expr.params.get(0) {
                    Some(_after_dot) => _after_dot,
                    None => {
                        return eval_func_proc_call_try_ufcs(&mut context, &e)
                    },
                };

                let after_dot_name = match &after_dot.node_type {
                    NodeType::Identifier(f_name_) => f_name_.clone(),
                    _ => return eval_func_proc_call_try_ufcs(&mut context, &e),
                };

                let member_default_value = match struct_def.default_values.get(&after_dot_name) {
                    Some(_member) => _member,
                    None => {
                        return eval_func_proc_call_try_ufcs(&mut context, &e)
                    },
                };

                // check that the function is a method in the struct, and if not try regular UFCS
                let id_expr_name = match &member_default_value.node_type {
                    NodeType::FuncDef(_func_def) => {
                        format!("{}.{}", custom_type_name, after_dot_name)
                    },
                    _  => {
                        return eval_func_proc_call_try_ufcs(&mut context, &e)
                    },
                };

                let new_e = Expr::new_clone(NodeType::Identifier(id_expr_name.clone()), e.get(0), Vec::new());
                let extra_arg_e = Expr::new_clone(NodeType::Identifier(name.to_string()), e, Vec::new());
                let mut new_args = Vec::new();
                new_args.push(new_e);
                new_args.push(extra_arg_e);
                new_args.extend(e.params[1..].to_vec());
                let new_fcall_e = Expr::new_clone(NodeType::FCall, e.get(0), new_args);
                let func_def = &context.funcs.get(&id_expr_name).unwrap().clone();
                return eval_user_func_proc_call(func_def, &id_expr_name, &mut context, &new_fcall_e);
            },
            _ => {
                return eval_func_proc_call_try_ufcs(&mut context, &e)
            },
        }

    } else {
        return e.lang_error("eval", &format!("Cannot call '{}'. Undefined function or struct.", name));
    }
}

fn eval_declaration(declaration: &Declaration, mut context: &mut Context, e: &Expr) -> String {
    let inner_e = e.get(0);
    let mut value_type = match get_value_type(&context, &inner_e) {
        Ok(val_type) => val_type,
        Err(error_string) => {
            return e.lang_error("eval", &error_string);
        },
    };
    if declaration.value_type != ValueType::ToInferType {
        if declaration.value_type == ValueType::TCustom("U8".to_string()) && value_type == ValueType::TCustom("I64".to_string()) {
            value_type = declaration.value_type.clone();
        } else if value_type != declaration.value_type {
            return e.lang_error("eval", &format!("'{}' declared of type {} but initialized to type {:?}.", declaration.name, value_type_to_str(&declaration.value_type), value_type_to_str(&value_type)));
        }
    }
    assert!(e.params.len() == 1, "{} ERROR: Declarations can have only one child expression. This should never happen.", LANG_NAME);
    match value_type {
        ValueType::ToInferType => {
            return e.lang_error("eval", &format!("'{}' declared of type '{}' but still to infer type '{}'",
                                                 declaration.name, value_type_to_str(&declaration.value_type), value_type_to_str(&value_type)));
        },
        ValueType::TEnumDef => {
            match &inner_e.node_type {
                NodeType::EnumDef(enum_def) => {
                    context.enum_defs.insert(declaration.name.clone(), enum_def.clone());
                    context.symbols.insert(declaration.name.to_string(), SymbolInfo{value_type: value_type.clone(), is_mut: declaration.is_mut});
                    return "".to_string()
                },
                _ => return e.lang_error("eval", &format!("Cannot declare '{}' of type '{}', expected enum definition.",
                                                          &declaration.name, value_type_to_str(&declaration.value_type))),
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
                                    return e.lang_error("eval", &format!("Struct member '{}.{}' expected to have default value.",
                                                                         &declaration.name, &member_decl.name));
                                },
                            };
                            let member_value_type = match member_decl.value_type {
                                ValueType::ToInferType => {
                                    match get_value_type(&context, &default_value) {
                                        Ok(val_type) => val_type,
                                        Err(error_string) => {
                                            return e.lang_error("eval", &error_string);
                                        },
                                    }
                                },
                                _ => member_decl.value_type.clone(),
                            };

                            match member_value_type {
                                ValueType::TCustom(type_name) => {
                                    match type_name.as_str() {
                                        "I64" => {
                                            let expr_result_str = eval_expr(&mut context, default_value);
                                            context.insert_i64(&combined_name, &expr_result_str);
                                        },
                                        "U8" => {
                                            let expr_result_str = eval_expr(&mut context, default_value);
                                            context.insert_u8(&combined_name, &expr_result_str);
                                        },
                                        "Bool" => {
                                            let expr_result_str = eval_expr(&mut context, default_value);
                                            context.insert_bool(&combined_name, &expr_result_str);
                                        },
                                        "String" => {
                                            let expr_result_str = eval_expr(&mut context, default_value);
                                            context.insert_string(&combined_name, &expr_result_str);
                                        },
                                        _ => {
                                            return e.todo_error("eval", &format!("Cannot declare '{}.{}' of custom type '{}'",
                                                                                 &declaration.name,
                                                                                 &member_decl.name,
                                                                                 type_name))
                                        },
                                    }
                                },
                                ValueType::TFunc | ValueType::TProc | ValueType::TMacro => {
                                    match &default_value.node_type {
                                        NodeType::FuncDef(func_def) => {
                                            context.funcs.insert(combined_name.to_string(), func_def.clone());
                                        },
                                        _ => {
                                            return e.lang_error("eval", &format!("Cannot declare '{}.{}' of type '{}', expected '{}' definition.",
                                                                                 &declaration.name,
                                                                                 &member_decl.name,
                                                                                 value_type_to_str(&member_value_type),
                                                                                 value_type_to_str(&member_decl.value_type)))
                                        },
                                    }
                                },
                                ValueType::ToInferType => {
                                    return e.lang_error("eval", &format!("Cannot infer type of '{}.{}', but it should be inferred already.",
                                                                         &declaration.name, &member_decl.name))
                                },
                                ValueType::TList | ValueType::TEnumDef | ValueType::TStructDef | ValueType::TMulti(_) => {
                                        return e.todo_error("eval", &format!("Cannot declare '{}.{}' of type '{}'",
                                                                             &declaration.name,
                                                                             &member_decl.name,
                                                                             value_type_to_str(&member_decl.value_type)))
                                    },

                            }

                            context.symbols.insert(combined_name.to_string(),
                                                   SymbolInfo{value_type: member_decl.value_type.clone(), is_mut: member_decl.is_mut});
                        }
                    }
                    return "".to_string()
                },
                _ => return e.lang_error("eval", &format!("Cannot declare {} of type {:?}, expected struct definition.",
                                                         &declaration.name, &declaration.value_type))
            }
        },
        ValueType::TFunc | ValueType::TProc | ValueType::TMacro => {
            match &inner_e.node_type {
                NodeType::FuncDef(func_def) => {
                    context.funcs.insert(declaration.name.to_string(), func_def.clone());
                    context.symbols.insert(declaration.name.to_string(), SymbolInfo{value_type: value_type.clone(), is_mut: declaration.is_mut});
                    return "".to_string();
                },

                _ => e.error("eval", &format!("Cannot declare '{}' of type '{}', expected '{}' definition.",
                                              &declaration.name, value_type_to_str(&declaration.value_type), value_type_to_str(&value_type))),
            }
        },

        ValueType::TCustom(ref custom_type_name) => {
            match custom_type_name.as_str() {
                "I64" => {
                    let expr_result_str = eval_expr(&mut context, inner_e);
                    context.insert_i64(&declaration.name, &expr_result_str);
                    context.symbols.insert(declaration.name.to_string(), SymbolInfo{value_type: value_type.clone(), is_mut: declaration.is_mut});
                    return "".to_string()
                },
                "U8" => {
                    let expr_result_str = eval_expr(&mut context, inner_e);
                    context.insert_u8(&declaration.name, &expr_result_str);
                    context.symbols.insert(declaration.name.to_string(), SymbolInfo{value_type: value_type.clone(), is_mut: declaration.is_mut});
                    return "".to_string()
                },
                "Bool" => {
                    let expr_result_str = eval_expr(&mut context, inner_e);
                    context.insert_bool(&declaration.name, &expr_result_str);
                    context.symbols.insert(declaration.name.to_string(), SymbolInfo{value_type: value_type.clone(), is_mut: declaration.is_mut});
                    return "".to_string()
                },
                "String" => {
                    let expr_result_str = eval_expr(&mut context, inner_e);
                    context.insert_string(&declaration.name, &expr_result_str);
                    context.symbols.insert(declaration.name.to_string(), SymbolInfo{value_type: value_type.clone(), is_mut: declaration.is_mut});
                    return "".to_string()
                },
                _ => {
                    context.symbols.insert(declaration.name.to_string(), SymbolInfo{value_type: value_type.clone(), is_mut: declaration.is_mut});
                    let custom_symbol = context.symbols.get(custom_type_name).unwrap();
                    if custom_symbol.value_type == ValueType::TEnumDef {
                        let enum_expr_result_str = &eval_expr(&mut context, inner_e);
                        context.insert_enum(&declaration.name, custom_type_name, enum_expr_result_str);
                    } else if custom_symbol.value_type == ValueType::TStructDef {
                        if !context.insert_struct(&declaration.name, custom_type_name) {
                            return e.error("eval", &format!("Failure trying to declare '{}' of struct type '{}'", &declaration.name, custom_type_name))
                        }
                    } else {
                        return e.error("eval", &format!("Cannot declare '{}' of type '{}'. Only 'enum' and 'struct' custom types allowed.",
                                                        &declaration.name, value_type_to_str(&custom_symbol.value_type)))
                    }
                    return "".to_string()
                },
            }
        },
        ValueType::TList | ValueType::TMulti(_) => {
            e.error("eval", &format!("Cannot declare '{}' of type '{}'",
                                     &declaration.name, value_type_to_str(&declaration.value_type)))
        },
    }
}

fn eval_assignment(var_name: &str, mut context: &mut Context, e: &Expr) -> String {
    let symbol_info = context.symbols.get(var_name).unwrap();
    assert!(symbol_info.is_mut, "{} eval ERROR: Assignments can only be to mut values", LANG_NAME);
    assert!(e.params.len() == 1, "{} eval ERROR: in eval_assignment, while assigning to {}, assignments must take exactly one value.", LANG_NAME, var_name);

    let inner_e = e.get(0);
    let value_type = match get_value_type(&context, &inner_e) {
        Ok(val_type) => val_type,
        Err(error_string) => {
            return e.lang_error("eval", &error_string);
        },
    };
    match value_type {
        ValueType::ToInferType => {
            return e.lang_error("eval", &format!("Cannot assign {}, type should already be inferred of type '{:?}'.", &var_name, &symbol_info.value_type));
        },

        ValueType::TCustom(ref custom_type_name) => {
            match custom_type_name.as_str() {
                "I64" => {
                    let expr_result_str = eval_expr(&mut context, inner_e);
                    context.insert_i64(var_name, &expr_result_str);
                    return "".to_string()
                },
                "U8" => {
                    let expr_result_str = eval_expr(&mut context, inner_e);
                    context.insert_u8(var_name, &expr_result_str);
                    return "".to_string()
                },
                "Bool" => {
                    let expr_result_str = eval_expr(&mut context, inner_e);
                    context.insert_bool(var_name, &expr_result_str);
                    return "".to_string()
                },
                "String" => {
                    let expr_result_str = eval_expr(&mut context, inner_e);
                    context.insert_string(var_name, &expr_result_str);
                    return "".to_string()
                },
                _ => {
                    return e.lang_error("eval", &format!("Cannot assign '{}' of custom type '{}'.", &var_name, custom_type_name))
                },
            }
        },
        ValueType::TStructDef => {
            return e.todo_error("eval", &format!("Cannot assign '{}' of type '{}'", &var_name, value_type_to_str(&value_type)))
        },
        ValueType::TFunc | ValueType::TProc | ValueType::TMacro => {
            match &inner_e.node_type {
                NodeType::FuncDef(func_def) => {
                    context.funcs.insert(var_name.to_string(), func_def.clone());
                    "".to_string()
                },
                _ => return e.lang_error("eval", &format!("Cannot assign '{}' to function type '{}'",
                                                          &var_name, value_type_to_str(&value_type))),
            }
        },

        ValueType::TList | ValueType::TEnumDef | ValueType::TMulti(_) => {
            return e.lang_error("eval", &format!("Cannot assign '{}' of type '{}'.", &var_name, value_type_to_str(&value_type)))
        },
    }
}

fn eval_identifier_expr_struct_member(name: &str, inner_name: &str, context: &Context, inner_e: &Expr, member_decl: &Declaration) -> String {
    match member_decl.value_type {
        ValueType::TCustom(ref custom_type_name) => {

            match custom_type_name.as_str() {
                "I64" => {
                    match context.get_i64(&format!("{}.{}", name, inner_name)) {
                        Some(result) => return result.to_string(),
                        None => {
                            return inner_e.lang_error("eval", &format!("value not set for '{}.{}'", name, inner_name))
                        },
                    }
                },
                "U8" => {
                    match context.get_u8(&format!("{}.{}", name, inner_name)) {
                        Some(result) => return result.to_string(),
                        None => {
                            return inner_e.lang_error("eval", &format!("value not set for '{}.{}'", name, inner_name))
                        },
                    }
                },
                "Bool" => {
                    match context.get_bool(&format!("{}.{}", name, inner_name)) {
                        Some(result) => return result.to_string(),
                        None => {
                            return inner_e.lang_error("eval", &format!("value not set for '{}.{}'", name, inner_name))
                        },
                    }
                },
                "String" => {
                    match context.get_string(&format!("{}.{}", name, inner_name)) {
                        Some(result_str) => return result_str.to_string(),
                        None => {
                            return inner_e.lang_error("eval", &format!("value not set for '{}.{}'", name, inner_name))
                        },
                    }
                },
                _ => {
                    return inner_e.lang_error("eval", &format!("evaluating member '{}.{}' of custom type '{}' is not supported yet",
                                                               name,
                                                               inner_name,
                                                               value_type_to_str(&member_decl.value_type)))
                },
            }
        },

        _ => {
            return inner_e.lang_error("eval", &format!("struct '{}' has no const (static) member '{}' of struct value type '{}'",
                                                       name,
                                                       inner_name,
                                                       value_type_to_str(&member_decl.value_type)))
        },
    }
}

fn eval_identifier_expr_struct(name: &str, context: &Context, e: &Expr) -> String {
    assert!(e.params.len() > 0, "{} eval ERROR: struct type '{}' can't be used as a primary expression.", LANG_NAME, name);

    let struct_def = context.struct_defs.get(name).unwrap();
    let inner_e = e.get(0);
    match &inner_e.node_type {
        NodeType::Identifier(inner_name) => {
            match struct_def.members.get(inner_name) {
                Some(member_decl) => {
                    return eval_identifier_expr_struct_member(name, inner_name, &context, &inner_e, &member_decl)
                },
                None => {
                    return e.lang_error("eval", &format!("struct '{}' has no member '{}'", name, inner_name))
                },
            }
        },
        _ => {
            return e.lang_error("eval", &format!("identifier '{}' should only have identifiers inside.", name))
        },
    }
}

fn eval_custom_expr(e: &Expr, context: &Context, name: &str, custom_type_name: &str) -> String {
    if !context.symbols.contains_key(custom_type_name) {
        return e.lang_error("eval", &format!("Argument '{}' is of undefined type {}.", &name, &custom_type_name))
    }
    let custom_symbol = context.symbols.get(custom_type_name).unwrap();
    match custom_symbol.value_type {
        ValueType::TEnumDef => {
            let enum_val = context.get_enum(name).unwrap();
            return enum_val.enum_name.clone();
        },

        ValueType::TStructDef => {
            let struct_def = context.struct_defs.get(custom_type_name).unwrap();
            if e.params.len() == 0 {
                return name.to_string() // This is an ugly hack
            }
            let inner_e = e.get(0);
            match &inner_e.node_type {
                NodeType::Identifier(inner_name) => {
                    match struct_def.members.get(inner_name) {
                        Some(member_decl) => {
                            match member_decl.value_type {

                                ValueType::TCustom(ref custom_type_name) => {
                                    match custom_type_name.as_str() {
                                        "I64" => {
                                            match context.get_i64(&format!("{}.{}", name, inner_name)) {
                                                Some(result) => return result.to_string(),
                                                None => {
                                                    return inner_e.lang_error("eval", &format!("value not set for field '{}.{}'", name, inner_name))
                                                },
                                            }
                                        },
                                        "U8" => {
                                            match context.get_u8(&format!("{}.{}", name, inner_name)) {
                                                Some(result) => return result.to_string(),
                                                None => {
                                                    return inner_e.lang_error("eval", &format!("value not set for field '{}.{}'", name, inner_name))
                                                },
                                            }
                                        },
                                        "Bool" => {
                                            match context.get_bool(&format!("{}.{}", name, inner_name)) {
                                                Some(result) => return result.to_string(),
                                                None => {
                                                    return inner_e.lang_error("eval", &format!("value not set for field '{}.{}'", name, inner_name))
                                                },
                                            }
                                        },
                                        "String" => {
                                            match context.get_string(&format!("{}.{}", name, inner_name)) {
                                                Some(result) => return result.to_string(),
                                                None => {
                                                    return inner_e.lang_error("eval", &format!("value not set for field '{}.{}'", name, inner_name))
                                                },
                                            }
                                        },
                                        _ => {
                                            return inner_e.todo_error("eval", &format!("Cannot access '{}.{}'. Fields of custom type '{}' not implemented",
                                                                                       name, inner_name, custom_type_name))
                                        },
                                    }
                                },

                                _ => {
                                    return inner_e.todo_error("eval", &format!("Cannot access '{}.{}'. Fields of type '{}' not implemented",
                                                                               name, inner_name, value_type_to_str(&member_decl.value_type)))
                                },
                            }
                        },
                        _ => {
                            return e.lang_error("eval", &format!("struct '{}' has no const (static) member '{}'", name, inner_name))
                        },
                    }
                },
                _ => {
                    return e.lang_error("eval", &format!("identifier '{}' should only have identifiers inside.", name))
                },
            }
        },

        _ => {
            return e.lang_error("eval", &format!("'{}' of type: '{}': custom types are supposed to be struct or enum, found '{}'.",
                                                 name, custom_type_name, value_type_to_str(&custom_symbol.value_type)))
        },
    }
}

fn eval_identifier_expr(name: &str, context: &Context, e: &Expr) -> String {

    match context.symbols.get(name) {
        Some(symbol_info) => match symbol_info.value_type {
            ValueType::TFunc | ValueType::TProc | ValueType::TMacro => {
                return name.to_string();
            },
            ValueType::TEnumDef => {
                assert!(e.params.len() > 0, "{} eval ERROR: enum type '{}' can't be used as a primary expression.", LANG_NAME, name);
                // let enum_def = context.enum_defs.get(name).unwrap();
                let inner_e = e.get(0);
                match &inner_e.node_type {
                    NodeType::Identifier(inner_name) => {
                        // TODO check that inner_name is in enum_def
                        // TODO check if that inner_name has an optional type
                        return format!("{}.{}", name, inner_name);
                    },
                    _ => {
                        return e.lang_error("eval", &format!("identifier '{}' should only have identifiers inside.", name))
                    },
                }
            },

            ValueType::TStructDef => {
                return eval_identifier_expr_struct(name, context, e)
            }

            ValueType::ToInferType => {
                return e.lang_error("eval", &format!("Can't infer the type of identifier '{}'.", name))
            },
            ValueType::TCustom(ref custom_type_name) => {
                match custom_type_name.as_str() {
                    "I64" => {
                        return context.get_i64(name).unwrap().to_string()
                    },
                    "U8" => {
                        return context.get_u8(name).unwrap().to_string()
                    },
                    "Bool" => {
                        return context.get_bool(name).unwrap().to_string()
                    },
                    "String" => {
                        return context.get_string(name).unwrap().to_string()
                    },
                    _ => {
                        let to_return = eval_custom_expr(&e, &context, &name, &custom_type_name);
                        return to_return
                    },
                }
            },
            _ => {
                return e.todo_error("eval", &format!("Can't use identifier '{}'. Type {:?} not supported yet.", name, symbol_info.value_type))
            },
        }
        None => {
            return e.lang_error("eval", &format!("Undefined symbol '{}'. This should have been caught in the compile phase.", name))
        },
    }
}

fn eval_body(mut context: &mut Context, statements: &Vec<Expr>) -> String {
    for se in statements.iter() {
        match &se.node_type {
            NodeType::Return => {
                if se.params.len() == 0 {
                    return "".to_string() // TODO this still should handle all nested cases of empty returns
                } else if se.params.len() > 1 {
                    return se.todo_error("eval", "Multiple return values not implemented yet")
                }
                return eval_expr(&mut context, &se.get(0));
            },
            NodeType::Throw => {
                if se.params.len() != 1 {
                    return se.lang_error("eval", "Throw can only return one value. This should have been caught before")
                }
                return eval_expr(&mut context, &se.get(0));
            },
            _ => {
                let stmt_result = eval_expr(&mut context, &se);
                if stmt_result != "" {
                    return stmt_result
                }
            }
        }
    }
    return "".to_string()
}

fn eval_expr(mut context: &mut Context, e: &Expr) -> String {
    match &e.node_type {
        NodeType::Body => {
            return eval_body(&mut context, &e.params);
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
            assert!(e.params.len() == 2 || e.params.len() == 3, "{} eval ERROR: if nodes must have 2 or 3 parameters.", LANG_NAME);
            if eval_to_bool(&mut context, &e.get(0)) {
                eval_expr(&mut context, &e.get(1))
            } else if e.params.len() == 3 {
                eval_expr(&mut context, &e.get(2))
            } else {
                "".to_string()
            }
        },
        NodeType::While => {
            assert!(e.params.len() == 2, "{} eval ERROR: while nodes must have exactly 2 parameters.", LANG_NAME);
            while eval_to_bool(&mut context, &e.get(0)) {
                eval_expr(&mut context, &e.get(1));
            }
            "".to_string()
        },
        NodeType::Switch => {
            assert!(e.params.len() >= 3, "{} eval ERROR: switch nodes must have at least 3 parameters.", LANG_NAME);

            let to_switch = e.get(0);
            let value_type = match get_value_type(&context, &to_switch) {
                Ok(val_type) => val_type,
                Err(error_string) => {
                    return e.lang_error("eval", &error_string)
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
                        return e.lang_error("eval", &error_string)
                    },
                };
                if value_type != case_type {
                    return e.lang_error("eval", &format!("switch value type {:?}, case value type {:?}", value_type, case_type))
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
            } else if e.params.len() > 1 {
                return e.lang_error("eval", "multiple return values not implemented yet")
            }
            return eval_expr(&mut context, &e.get(0))
        },
        NodeType::Throw => {
            if e.params.len() != 1 {
                return e.lang_error("eval", "Throw can only return one value. This should have been caught before")
            }
            return eval_expr(&mut context, &e.get(0))
        },
        _ => {
            return e.lang_error("eval", &format!("Not implemented yet, found node type {:?}.", e.node_type))
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
        // TODO why not? this whole function is out of date and untested anyway
        NodeType::Return => {
            panic!("{} AST ERROR: Node_type::Return shouldn't be analized in to_ast_str().", LANG_NAME);
        },
        NodeType::Throw => {
            panic!("{} AST ERROR: Node_type::Throw shouldn't be analized in to_ast_str().", LANG_NAME);
        },
    }
}

// ---------- main binary

// TODO return Result<String, String>, so that imports that fail can be treated accordingly
fn main_run(print_extra: bool, mut context: &mut Context, path: &String, source: String, main_args: Vec<String>) -> String {

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

    if context.mode.name == "test" {
        match run_file_with_context(true, &mut context, &"src/core/modes/test.cil".to_string(), Vec::new()) {
            Ok(_) => {},
            Err(error_string) => {
                return format!("{}:{}", &path, error_string);
            },
        }
    }

    let mut e: Expr = match parse_tokens(lexer, &mut current) {
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
    errors.extend(basic_mode_checks(&context, &e));

    // For modes that require a main proc, add an implicit call to main
    if context.mode.needs_main_proc {
        let mut main_params = Vec::new();
        main_params.push(Expr{node_type: NodeType::Identifier("main".to_string()), line: 0, col: 0, params: Vec::new()});
        for str_arg in main_args {
            main_params.push(Expr{node_type: NodeType::LString(str_arg), line: 0, col: 0, params: Vec::new()});
        }
        e.params.push(Expr{node_type: NodeType::FCall, line: 0, col: 0, params: main_params});
    }
    errors.extend(check_types(&mut context, &e)); // TODO remove mut from context arg

    if errors.len() > 0 {
        for err in &errors {
            println!("{}:{}", path, err);
        }
        return format!("Compiler errors: {} type errors found", errors.len());
    }

    return eval_expr(&mut context, &e);
}

// ---------- main, usage, args, etc

fn run_file(path: &String, main_args: Vec<String>) -> Result<(), String> {
    let mut context = Context::new(path, DEFAULT_MODE);
    run_file_with_context(true, &mut context, &"src/core/core.cil".to_string(), Vec::new())?;
    run_file_with_context(true, &mut context, &"src/core/std.cil".to_string(), Vec::new())?;
    run_file_with_context(false, &mut context, &path, main_args)?;
    return Ok(())
}

fn run_file_with_context(is_import: bool, mut context: &mut Context, path: &String, main_args: Vec<String>) -> Result<(), String> {
    let previous_mode = context.mode.clone();
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
    let run_result = main_run(!is_import, &mut context, &path, source, main_args);
    if run_result != "" {
        println!("{}", run_result);
    }

    if is_import && !can_be_imported(&context.mode) {
        return Err(format!("file '{path}' of mode '{}' cannot be imported", context.mode.name))
    }
    context.mode = previous_mode; // restore the context mode of the calling file
    return Ok(())
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

fn run_file_or_exit(path: &String, args: Vec<String>) {
    match run_file(path, args) {
        Ok(_) => {},
        Err(error_string) => {
            println!("ERROR: While running file {path}");
            println!("{error_string}");
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
                run_file_or_exit(&args[2], main_args);
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
                run_file_or_exit(&SELF_HOSTED_PATH.to_string(), repl_temp);
            },
            "ast" | "interpret" | "build" | "run" |
            "help" | "-help" | "--help" | "--version" | "-v" => {
                usage();
            },
            _ => {
                run_file_or_exit(&args[1], Vec::new());
            },
        }
        return
    }

    // If not arguments, then repl/interactive "mode"
    let mut repl_temp : Vec<String> = Vec::new();
    repl_temp.push("repl".to_string());
    run_file_or_exit(&SELF_HOSTED_PATH.to_string(), repl_temp);
}
