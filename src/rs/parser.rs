use std::collections::HashMap;
use std::io::Write; // <--- bring flush() into scope
use std::io;

use rs::lexer::{LANG_NAME, TokenType, Token, Lexer};

pub const INFER_TYPE : &str = "auto";

#[derive(Debug, Clone, PartialEq)]
pub struct SEnumDef {
    pub enum_map: HashMap<String, Option<ValueType>>,
}

#[derive(Debug, Clone, PartialEq)]
pub struct Declaration {
    pub name: String,
    pub value_type: ValueType,
    pub is_mut: bool,
}

#[derive(Debug, Clone, PartialEq)]
pub enum FunctionType {
    FTFunc,
    FTProc,
    FTMacro,
    FTFuncExt,
    FTProcExt,
}

#[derive(Debug, Clone, PartialEq)]
pub struct SFuncDef {
    pub function_type: FunctionType,
    pub args: Vec<Declaration>,
    pub returns: Vec<ValueType>,
    pub throws: Vec<ValueType>,
    pub body: Vec<Expr>,
}

impl SFuncDef {
    pub fn is_proc(self: &SFuncDef) -> bool {
        match self.function_type {
            FunctionType::FTProc | FunctionType::FTProcExt => true,
            FunctionType::FTFunc | FunctionType::FTFuncExt | FunctionType::FTMacro => false,
        }
    }

    pub fn is_ext(self: &SFuncDef) -> bool {
        match self.function_type {
            FunctionType::FTFuncExt | FunctionType::FTProcExt => true,
            FunctionType::FTFunc | FunctionType::FTProc | FunctionType::FTMacro => false,
        }
    }
}

#[derive(Debug, Clone, PartialEq)]
pub struct SStructDef {
    pub members : HashMap<String, Declaration>,
    pub default_values : HashMap<String, Expr>,
}

#[derive(Debug, Clone, PartialEq)]
pub enum Literal {
    Number(String), // TODO support more kinds of numbers
    Str(String),
    Bool(String),
    List(String), // TODO You can call it tupple too. who cares? it's not even tested yet, just parsed
}

#[derive(Debug, Clone, PartialEq)]
pub enum NodeType {
    Body,
    LLiteral(Literal),
    FCall,
    Identifier(String),
    Declaration(Declaration),
    Assignment(String),
    FuncDef(SFuncDef),
    EnumDef(SEnumDef),
    StructDef(SStructDef),
    Return,
    Throw,
    Catch,
    If,
    While,
    Switch,
    DefaultCase,
    Range,
}

#[derive(Debug, Clone, PartialEq)]
pub struct Expr {
    pub node_type: NodeType,
    pub params: Vec<Expr>,
    pub line: usize,
    pub col: usize,
}

impl Expr {
    pub fn new_parse(node_type: NodeType, token: Token, params: Vec<Expr>) -> Expr {
        return Expr{
            node_type: node_type,
            params: params,
            line: token.line,
            col: token.col,
        }
    }

    pub fn new_explicit(node_type: NodeType, params: Vec<Expr>, line: usize, col: usize) -> Expr {
        return Expr{
            node_type: node_type,
            params: params,
            line: line,
            col: col,
        }
    }

    pub fn new_clone(node_type: NodeType, e: &Expr, params: Vec<Expr>) -> Expr {
        return Expr::new_explicit(node_type, params, e.line, e.col)
    }

    pub fn get(self: &Expr, i: usize) -> Result<&Expr, String> {
        match self.params.get(i) {
            Some(expr) => Ok(expr),
            None => Err(self.lang_error("assert", &format!("Expr index {} out of bounds (len: {}).", i, self.params.len()))),
        }
     }

    pub fn exit_error(self: &Expr, phase: &str, msg: &str) -> String {
        if phase == "warning" {
            println!("{}:{}: {} WARNING: {}\nExplanation: This should never happen, this is a bug in the language.",
                     self.line, self.col, LANG_NAME, msg);
        } else {
            println!("{}:{}: {} {} ERROR: {}\nExplanation: This should never happen, this is a bug in the language.",
                     self.line, self.col, LANG_NAME, phase, msg);
        }
        let _ = io::stdout().flush(); // Disregard flush errors, don't unwrap
        std::process::exit(1);
    }

    pub fn lang_error(self: &Expr, phase: &str, msg: &str) -> String {
        if phase == "warning" {
            return format!("{}:{}: {} WARNING: {}\nExplanation: This should never happen, this is a bug in the language.", self.line, self.col, LANG_NAME, msg);
        }
        return format!("{}:{}: {} {} ERROR: {}\nExplanation: This should never happen, this is a bug in the language.",
                       self.line, self.col, LANG_NAME, phase, msg)
    }

    pub fn todo_error(self: &Expr, phase: &str, msg: &str) -> String {
        if phase == "warning" {
            return format!("{}:{}: {} WARNING: {}\nExplanation: Not implemented yet, this is a missing feature in the language.", self.line, self.col, LANG_NAME, msg);
        }
        return format!("{}:{}: {} {} ERROR: {}\nExplanation: Not implemented yet, this is a missing feature in the language.",
                       self.line, self.col, LANG_NAME, phase, msg)
    }

    pub fn error(self: &Expr, phase: &str, msg: &str) -> String {
        if phase == "warning" {
            return format!("{}:{}: WARNING: {}", self.line, self.col, msg);
        }
        return format!("{}:{}: {} ERROR: {}", self.line, self.col, phase, msg)
    }
}

fn is_literal(t: &Token) -> bool {
    return match t.token_type {
        TokenType::String => true,
        TokenType::Number => true,
        TokenType::True => true,
        _ => false,
    }
}

#[derive(Debug, Clone, PartialEq)]
pub enum TTypeDef {
    TEnumDef,
    TStructDef,
}

#[derive(Debug, Clone, PartialEq)]
pub enum ValueType {
    TFunction(FunctionType),
    TType(TTypeDef),
    TCustom(String),
    TMulti(String),
}

pub fn value_type_to_str(arg_type: &ValueType) -> String {
    match arg_type {
        ValueType::TType(TTypeDef::TEnumDef) => "enum".to_string(),
        ValueType::TType(TTypeDef::TStructDef) => "struct".to_string(),
        ValueType::TFunction(ftype) => match ftype {
            FunctionType::FTFunc | FunctionType::FTFuncExt => "func".to_string(),
            FunctionType::FTProc | FunctionType::FTProcExt => "proc".to_string(),
            FunctionType::FTMacro => "macro".to_string(),
        },
        ValueType::TMulti(type_name) => format!("{}", type_name),
        ValueType::TCustom(type_name) => format!("{}", type_name),
    }
}

pub fn str_to_value_type(arg_type: &str) -> ValueType {
    match arg_type {
        "func" => ValueType::TFunction(FunctionType::FTFunc),
        "proc" => ValueType::TFunction(FunctionType::FTProc),
        "macro" => ValueType::TFunction(FunctionType::FTMacro),
        "enum" => ValueType::TType(TTypeDef::TEnumDef),
        "struct" => ValueType::TType(TTypeDef::TStructDef),
        type_name => ValueType::TCustom(type_name.to_string()),
    }
}

#[derive(Debug, Clone, PartialEq)]
pub struct ModeDef {
    pub name: String,
    pub allows_procs: bool,
    pub allows_base_mut: bool,
    pub allows_base_calls: bool,
    pub allows_base_anything: bool,
    pub needs_main_proc: bool,
    pub imports: Vec<String>,
}

pub fn can_be_imported(mode: &ModeDef) -> bool {
    return !(
        mode.needs_main_proc || // TODO think harder, why not?
        mode.allows_base_mut ||
        mode.allows_base_calls ||
        mode.allows_base_anything
    );
}

pub fn mode_from_name(mode_name: &str) -> Result<ModeDef, String> {
    return match mode_name {
        "lib" => Ok(
            ModeDef{name                 : mode_name.to_string(),
                    allows_procs         : true,
                    allows_base_calls    : false,
                    allows_base_mut      : false,
                    allows_base_anything : false,
                    needs_main_proc      : false,
                    imports              : vec![],
        }),
        "pure" => Ok(
            ModeDef{name                 : mode_name.to_string(),
                    allows_procs         : false,
                    allows_base_calls    : false,
                    allows_base_mut      : false,
                    allows_base_anything : false,
                    needs_main_proc      : false,
                    imports              : vec![],
        }),
        "script" => Ok(
            ModeDef{name                 : mode_name.to_string(),
                    allows_procs         : true,
                    allows_base_calls    : true,
                    allows_base_mut      : true,
                    allows_base_anything : true,
                    needs_main_proc      : false,
                    imports              : vec![],
        }),
        "safe_script" => Ok(
            ModeDef{name                 : mode_name.to_string(),
                    allows_procs         : true,
                    allows_base_calls    : true,
                    allows_base_mut      : true,
                    allows_base_anything : true,
                    needs_main_proc      : false,
                    imports              : vec![],
        }),
        "cli" => Ok(
            ModeDef{name                 : mode_name.to_string(),
                    allows_procs         : true,
                    allows_base_calls    : false,
                    allows_base_mut      : true,
                    allows_base_anything : false,
                    needs_main_proc      : true,
                    imports              : vec![],
        }),
        "test" => Ok(
            ModeDef{name                 : mode_name.to_string(),
                    allows_procs         : true,
                    allows_base_calls    : true,
                    allows_base_mut      : true,
                    allows_base_anything : false,
                    needs_main_proc      : false,
                    imports              : vec!["src/core/modes/test".to_string()],
        }),

        _  => return Err(format!("0:0: {} interpreter implementation doesn't support mode '{}'", LANG_NAME, mode_name)),
    };
}

pub fn parse_mode(path: &String, lexer: &mut Lexer) -> Result<ModeDef, String> {
    lexer.expect(TokenType::Mode)?; // Add one for mode

    if TokenType::Identifier != lexer.peek().token_type {
        return Err(format!("0:0: Expected identifier after 'mode'"));
    }
    let t = lexer.peek();
    let mode_name = &t.token_str;
    let mode = match mode_from_name(&mode_name) {
        Ok(mode_) => mode_,
        Err(err_) => return Err(err_),
    };

    if mode.name == "safe_script" {
        return Err(format!("{}:0:0: mode '{}' is not properly supported in '{}' yet. Try mode '{}' instead", path, mode.name, LANG_NAME, "script"));
    }

    lexer.expect(TokenType::Identifier)?; // Add one for the identifier of the mode
    return Ok(mode);
}

fn parse_literal(lexer: &mut Lexer, t: &Token) -> Result<Expr, String> {
    let params : Vec<Expr> = Vec::new();
    let node_type = match t.token_type {
        TokenType::String => NodeType::LLiteral(Literal::Str(t.token_str.clone())),
        TokenType::Number => {
            let number = t.token_str.parse::<i64>()
                .map_err(|e| t.lang_error(&format!("Invalid number literal '{}': {}", t.token_str, e)))?;
            NodeType::LLiteral(Literal::Number(number.to_string()))
        },
        TokenType::True => NodeType::LLiteral(Literal::Bool(t.token_str.clone())),
        _ => {
            return Err(t.lang_error(&format!("Trying to parse a token that's not a literal as a literal, found '{:?}'.", t.token_type)));
        },
    };
    let e = Expr::new_parse(node_type, t.clone(), params);
    lexer.advance(1)?;
    Ok(e)
}

fn parse_list(lexer: &mut Lexer) -> Result<Expr, String> {
    let mut rightparent_found = false;
    let mut params : Vec<Expr> = Vec::new();
    let initial_current = lexer.current;
    lexer.expect(TokenType::LeftParen)?;
    let mut list_t = lexer.peek();
    // println!("primary debug LeftParen: {} {}", initial_current, *current);
    let mut expect_comma = false;
    while !(lexer.is_eof(0) || rightparent_found) {
        // println!("primary debug LeftParen while: {} {}", current, *current);
        match list_t.token_type {
            TokenType::RightParen => {
                lexer.expect(TokenType::RightParen)?;
                rightparent_found = true;
            },
            TokenType::Comma => {
                if expect_comma {
                    lexer.expect(TokenType::Comma)?;
                    expect_comma = false;
                    list_t = lexer.peek();
                } else {
                    return Err(list_t.error("Unexpected ','."));
                }
            },
            _ => {
                if expect_comma {
                    return Err(list_t.error(&format!("Expected ')' or ',', found '{:?}'.", list_t.token_type)));
                }
                expect_comma = true;
                let prim = match parse_primary(lexer) {
                    Ok(to_ret) => to_ret,
                    Err(err_str) => return Err(err_str),
                };
                params.push(prim);
                list_t = lexer.peek();
            },
        }
    }
    match list_t.token_type {
        // TODO properly parse lists besides function definition arguments
        TokenType::RightParen => Ok(Expr::new_parse(NodeType::LLiteral(Literal::List("".to_string())), lexer.get_token(initial_current)?.clone(), params)),
        _ => Err(list_t.error("Expected closing parentheses.")),
    }
}

fn parse_assignment(lexer: &mut Lexer, t: &Token, name: &String) -> Result<Expr, String> {
    lexer.expect(TokenType::Equal)?;
    let mut params = Vec::new();
    params.push(parse_primary(lexer)?);
    return Ok(Expr::new_parse(NodeType::Assignment(name.to_string()), t.clone(), params))
}

fn parse_func_proc_args(lexer: &mut Lexer) -> Result<Vec<Declaration>, String> {
    lexer.expect(TokenType::LeftParen)?;
    let mut rightparent_found = false;
    let mut args : Vec<Declaration> = Vec::new();
    let mut t = lexer.peek();
    let mut expect_comma = false;
    let mut expect_colon = false;
    let mut expect_name = true;
    let mut is_variadic = false;
    let mut arg_name = "unnamed".to_string();
    let mut is_mut = false;
    while !(lexer.is_eof(0) || rightparent_found) {
        match t.token_type {
            TokenType::RightParen => {
                rightparent_found = true;
                if expect_colon {
                    return Err(t.error(&format!("Expected ': Type' after arg name '{}' before ')'.", arg_name)));
                }
                lexer.advance(1)?;
            },
            TokenType::Comma => {
                if expect_colon {
                    return Err(t.error(&format!("Expected ': Type' after arg name '{}', but found ','.", arg_name)));
                }
                if expect_name {
                    return Err(t.error("Expected arg name before ','."));
                }
                if expect_comma {
                    expect_comma = false;
                    expect_colon = false;
                    expect_name = true;
                    is_mut = false;
                    lexer.expect(TokenType::Comma)?;
                    t = lexer.peek();
                } else {
                    return Err(t.error("Unexpected ','."));
                }
            },
            TokenType::Colon => {
                if expect_colon {
                    expect_colon = false;
                    expect_name = false;
                    expect_comma = false;
                    lexer.advance(1)?;
                    t = lexer.peek();
                    match t.token_type {
                        TokenType::Identifier => {},
                        TokenType::DoubleDot => {},
                        _ => return Err(t.error(&format!("Expected type after '{}:', but found '{}'.", arg_name, t.token_str))),
                    }
                } else {
                    return Err(t.error("Unexpected ':'."));
                }
            },
            TokenType::DoubleDot => {
                if expect_colon {
                    return Err(t.error(&format!("Expected ': Type' after arg name '{}', but found '..'.", arg_name)));
                }
                if expect_comma {
                    return Err(t.error(&format!("Expected ',', found '{:?}'.", t.token_type)));
                }
                if expect_name {
                    return Err(t.error(&format!("Expected arg name, found '{:?}'.", t.token_type)));
                }
                is_variadic = true;
                lexer.advance(1)?;
                t = lexer.peek();
            },
            TokenType::Identifier => {
                if expect_colon {
                    return Err(t.error(&format!("Expected ': Type' after arg name '{}', but found '{}'.", arg_name, t.token_str)));
                }
                if expect_comma {
                    return Err(t.error(&format!("Expected ',', found identifier '{}'.", t.token_str)));
                }
                if expect_name {
                    arg_name = t.token_str.to_string();
                    expect_colon = true;
                    expect_name = false;
                } else {
                    if is_variadic {
                        args.push(Declaration {
                            name: arg_name.to_string(),
                            value_type: ValueType::TMulti(t.token_str.clone()),
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
                lexer.advance(1)?;
                t = lexer.peek();
            },
            TokenType::Mut => {
                if !expect_name {
                    return Err(t.error("Unexpected 'mut' in argument list."));
                }
                is_mut = true;
                lexer.advance(1)?;
                t = lexer.peek();
            },
            _ => {
                return Err(t.error(&format!("Unexpected '{:?}' in func/proc args.", t.token_type)));
            },
        }
    }
    match t.token_type {
        TokenType::RightParen => return Ok(args),
        _ => return Err(t.error("Expected closing parentheses.")),
    }
}

fn func_proc_returns(lexer: &mut Lexer) -> Result<Vec<ValueType>, String> {
    let mut end_found = false;
    let mut return_types : Vec<ValueType> = Vec::new();
    let mut t = lexer.peek();
    lexer.advance(1)?;
    if t.token_type != TokenType::Returns {
        return Ok(return_types);
    }
    t = lexer.peek();
    let mut expect_comma = false;
    while !(lexer.is_eof(0) || end_found) {
        match t.token_type {
            TokenType::Throws | TokenType::LeftBrace | TokenType::Semicolon => {
                end_found = true;
                lexer.advance(1)?;
            },
            TokenType::Comma => {
                if expect_comma {
                    lexer.expect(TokenType::Comma)?;
                    expect_comma = false;
                    t = lexer.peek();
                } else {
                    return Err(t.error("Unexpected ','."));
                }
            },
            TokenType::Identifier => {
                if expect_comma {
                    return Err(t.error(&format!("Expected ',', found '{:?}'.", t.token_type)));
                }
                return_types.push(str_to_value_type(&t.token_str));
                expect_comma = true;
                lexer.advance(1)?;
                t = lexer.peek();
            },
            _ => {
                return Err(t.error(&format!("Unexpected '{:?}' in func/proc returns.", t.token_type)));
            },
        }
    }
    if end_found {
        return Ok(return_types);
    } else {
        return Err(t.error("Expected '{{' or 'throws' after return values."));
    }
}

// TODO DRY with func_proc_returns ?
fn func_proc_throws(lexer: &mut Lexer) -> Result<Vec<ValueType>, String> {
    let mut end_found = false;
    let mut return_types : Vec<ValueType> = Vec::new();
    let mut t = lexer.previous()?;
    if t.token_type != TokenType::Throws {
        return Ok(return_types);
    }
    t = lexer.peek();
    let mut expect_comma = false;
    while !(lexer.is_eof(0) || end_found) {
        match t.token_type {
            TokenType::LeftBrace | TokenType::Semicolon => {
                end_found = true;
                lexer.advance(1)?;
            },
            TokenType::Comma => {
                if expect_comma {
                    expect_comma = false;
                    lexer.advance(1)?;
                    t = lexer.peek();
                } else {
                    return Err(t.error("Unexpected ','."));
                }
            },
            TokenType::Identifier => {
                if expect_comma {
                    return Err(t.error(&format!("Expected ',', found '{:?}'.", t.token_type)));
                }
                return_types.push(str_to_value_type(&t.token_str));
                expect_comma = true;
                lexer.advance(1)?;
                t = lexer.peek();
            },
            _ => {
                return Err(t.error(&format!("Unexpected '{:?}' in func/proc throws.", t.token_type)));
            },
        }
    }
    if end_found {
        return Ok(return_types);
    } else {
        return Err(t.error("Expected '{{' after throw values."));
    }
}

fn parse_func_proc_definition(lexer: &mut Lexer, function_type: FunctionType, do_parse_body: bool) -> Result<Expr, String> {

    lexer.advance(1)?;
    let t = lexer.peek();
    if lexer.is_eof(1) {
        return Err(t.error("expected '(' after 'func' or 'proc', found EOF."));
    }
    if t.token_type != TokenType::LeftParen {
        return Err(t.error(&format!("expected '(' after 'func', found '{:?}'.", t.token_type)));
    }
    let args = parse_func_proc_args(lexer)?;
    let returns = func_proc_returns(lexer)?;
    let throws = func_proc_throws(lexer)?;

    let body = match do_parse_body {
        false => {
            lexer.go_back(1)?; // Discount the closing brace we won't need
            Vec::new()
        },
        true => match parse_body(lexer, TokenType::RightBrace) {
            Ok(body) => body.params,
            Err(err_str) => return Err(err_str),
        },
    };

    let func_def = SFuncDef{function_type: function_type, args: args, returns: returns, body: body, throws};
    let params : Vec<Expr> = Vec::new();
    let e = Expr::new_parse(NodeType::FuncDef(func_def), t.clone(), params);
    Ok(e)
}

fn enum_definition(lexer: &mut Lexer) -> Result<Expr, String> {
    let initial_current: usize = lexer.current;
    lexer.advance(1)?;

    let t = lexer.peek();
    if t.token_type != TokenType::LeftBrace {
        return Err(t.error("Expected '{{' after 'enum'."));
    }
    if lexer.is_eof(1) {
        let t = lexer.peek();
        return Err(t.error("expected identifier after 'enum {{', found EOF."));
    }
    lexer.advance(1)?;
    let mut enum_map: HashMap<String, Option<ValueType>> = HashMap::new();

    let mut end_found = false;
    while lexer.current < lexer.len() && !end_found {
        let it_t = lexer.peek();
        match it_t.token_type {
            TokenType::RightBrace => {
                end_found = true;
            },
            TokenType::Identifier => {
                let enum_val_name = &it_t.token_str;
                let next_t = lexer.next()?;
                match next_t.token_type {
                    TokenType::Colon => {
                        let next2_t = lexer.peek_ahead(2)?;
                        if next2_t.token_type != TokenType::Identifier {
                            return Err(next2_t.error(&format!("Expected type identifier after '{} :', found '{:?}'.",
                                                              enum_val_name, next2_t.token_type)));
                        }
                        let enum_val_type = &next2_t.token_str;
                        enum_map.insert(enum_val_name.to_string(), Some(str_to_value_type(enum_val_type)));
                        lexer.advance(2)?;
                    },
                    TokenType::Comma | TokenType::RightBrace => {
                        enum_map.insert(enum_val_name.to_string(), None);
                        if next_t.token_type == TokenType::RightBrace {
                            end_found = true;
                        }
                    },
                    _ => {
                        return Err(next_t.error(&format!("Expected ',' or ':' after '{}', found '{:?}'.",
                                                         enum_val_name, next_t.token_type)));
                    }
                }
            },
            TokenType::Comma => {
                // Skip comma
            },
            _ => {
                return Err(it_t.error(&format!("Expected '}}' to end enum or a new identifier, found '{:?}'.",
                                               it_t.token_type)));
            }
        }
        lexer.advance(1)?;
    }
    if !end_found {
        return Err(t.error("Expected '}}' to end enum."));
    }
    let params : Vec<Expr> = Vec::new();
    return Ok(Expr::new_parse(NodeType::EnumDef(SEnumDef{enum_map: enum_map}), lexer.get_token(initial_current)?.clone(), params));
}

fn parse_struct_definition(lexer: &mut Lexer) -> Result<Expr, String> {
    lexer.expect(TokenType::Struct)?;
    let t = lexer.peek();
    if t.token_type != TokenType::LeftBrace {
        return Err(t.error("Expected '{{' after 'struct'."));
    }
    if lexer.is_eof(1) {
        let t = lexer.peek();
        return Err(t.error("expected 'identifier' after 'struct {{', found EOF."));
    }
    lexer.advance(1)?;
    let body = match parse_body(lexer, TokenType::RightBrace) {
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
                    match p.params.get(0) {
                        Some(val) => {
                            default_values.insert(decl.name.clone(), val.clone());
                        },
                        None => return Err(t.error("expected value in struct member declaration")),
                    }
                } else {
                    // TODO allow not setting default values in struct members
                    return Err(t.error("all declarations inside struct definitions must have a value for now"));
                }
            },
            _ => return Err(t.error("expected only declarations inside struct definition")),
        }
    }

    return Ok(Expr::new_parse(NodeType::StructDef(SStructDef{members: members, default_values: default_values}),
                              t.clone(), Vec::new()));
}

fn parse_primary_identifier(lexer: &mut Lexer) -> Result<Expr, String> {

    let initial_current = lexer.current;
    let t = lexer.peek();
    let mut next_t = lexer.next()?;
    let mut current_identifier = t.token_str.to_string();
    let mut params : Vec<Expr> = Vec::new();
    while TokenType::Dot == next_t.token_type {
        let next2_t = lexer.peek_ahead(2)?;
        if TokenType::Identifier != next2_t.token_type {
            return Err(next2_t.error(&format!("expected identifier after '{}.', found '{:?}'.", current_identifier, next2_t.token_type)));
        }

        current_identifier = next2_t.token_str.to_string();
        lexer.advance(2)?;
        params.push(Expr::new_parse(NodeType::Identifier(current_identifier.clone()), t.clone(), Vec::new()));
        next_t = lexer.next()?;
    }

    let e = Expr::new_parse(NodeType::Identifier(t.token_str.clone()), lexer.get_token(initial_current)?.clone(), params);
    lexer.advance(1)?;

    if TokenType::LeftParen == next_t.token_type {
        let arg_list = match parse_list(lexer) {
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

fn parse_statement_identifier(lexer: &mut Lexer) -> Result<Expr, String> {

    let t = lexer.peek();
    let mut next_t = lexer.next()?;
    let mut next_token_type = &next_t.token_type;
    match next_token_type {
        TokenType::LeftParen => {
            return parse_primary_identifier(lexer)
        },
        TokenType::Dot => {
            let e = parse_primary_identifier(lexer)?;
            match &e.node_type {
                NodeType::FCall => return Ok(e),
                NodeType::Identifier(_) => {},
                _ => {
                    return Err(t.lang_error("a series of identifiers and dots should have been parsed as identifier or function call"));
                },
            }
            next_t = lexer.peek();
            next_token_type = &next_t.token_type;
            match next_token_type {
                TokenType::Equal => {
                    let name = get_combined_name(&e)?;
                    return parse_assignment(lexer, &t, &name)
                },
                _ => {
                    return Err(t.lang_error("While parsing a '.', this should never happen"));
                },
            }
        },
        TokenType::Equal => {
            lexer.advance(1)?; // skip identifier
            return parse_assignment(lexer, &t, &t.token_str)
        },
        TokenType::Colon => {
            let next_next_t = lexer.peek_ahead(2)?;
            let next_next_token_type = &next_next_t.token_type;
            let identifier = &t.token_str;
            match next_next_token_type {
                TokenType::Identifier => {
                    let type_name = &next_next_t.token_str;
                    return parse_declaration(lexer, false, type_name)
                }
                TokenType::Equal => {
                    return parse_declaration(lexer, false, INFER_TYPE)
                },
                _ => {
                    Err(t.error(&format!("Expected Type or '=' after '{} :' in statement, found '{:?}'.", identifier, next_next_token_type)))
                },
            }

        },
        _ => {
            Err(t.error(&format!("Expected '(', ':' or '=' after identifier in statement, found '{:?}'.", next_token_type)))
        },
    }
}

fn parse_primary(lexer: &mut Lexer) -> Result<Expr, String> {

    let t = lexer.peek();
    if is_literal(&t) {
        return parse_literal(lexer, &t)
    }
    match &t.token_type {
        TokenType::Func => return parse_func_proc_definition(lexer, FunctionType::FTFunc, true),
        TokenType::FuncExt => return parse_func_proc_definition(lexer, FunctionType::FTFuncExt, false),
        TokenType::Macro => return parse_func_proc_definition(lexer, FunctionType::FTMacro, true),
        TokenType::Proc => return parse_func_proc_definition(lexer, FunctionType::FTProc, true),
        TokenType::ProcExt => return parse_func_proc_definition(lexer, FunctionType::FTProcExt, false),
        TokenType::Enum => return enum_definition(lexer),
        TokenType::Struct => return parse_struct_definition(lexer),
        TokenType::LeftParen => return parse_list(lexer),
        TokenType::Identifier => return parse_primary_identifier(lexer),
        _ => return Err(t.error(&format!("Expected primary expression, found '{:?}'.", t.token_type))),
    }
}

fn return_statement(lexer: &mut Lexer) -> Result<Expr, String> {
    let initial_current = lexer.current;
    lexer.advance(1)?;
    let mut params : Vec<Expr> = Vec::new();
    match parse_primary(lexer) {
        Ok(prim) => {
            params.push(prim);
        },
        Err(_err_str) => {},
    };
    let mut t = lexer.peek();
    while t.token_type == TokenType::Comma {
        lexer.advance(1)?;
        let prim2 = match parse_primary(lexer) {
            Ok(to_ret) => to_ret,
            Err(err_str) => return Err(err_str),
        };
        params.push(prim2);
        t = lexer.peek();
    }
    Ok(Expr::new_parse(NodeType::Return, lexer.get_token(initial_current)?.clone(), params))
}

fn parse_throw_statement(lexer: &mut Lexer) -> Result<Expr, String> {
    let initial_current = lexer.current;
    lexer.advance(1)?;
    let mut params : Vec<Expr> = Vec::new();
    match parse_primary(lexer) {
        Ok(prim) => {
            params.push(prim);
        },
        Err(_err_str) => {},
    };
    let mut t = lexer.peek();
    while t.token_type == TokenType::Comma {
        lexer.advance(1)?;
        let prim2 = match parse_primary(lexer) {
            Ok(to_ret) => to_ret,
            Err(err_str) => return Err(err_str),
        };
        params.push(prim2);
        t = lexer.peek();
    }
    Ok(Expr::new_parse(NodeType::Throw, lexer.get_token(initial_current)?.clone(), params))
}

fn parse_catch_statement(lexer: &mut Lexer) -> Result<Expr, String> {
    let initial_current = lexer.current;
    lexer.advance(1)?; // consume 'catch'

    lexer.expect(TokenType::LeftParen)?; // expect '('

    // Parse the error variable name
    let name_token = lexer.expect(TokenType::Identifier)?;
    let name = name_token.token_str.clone();
    let name_expr = Expr::new_parse(
        NodeType::Identifier(name.clone()),
        name_token.clone(),
        vec![],
    );

    lexer.expect(TokenType::Colon)?; // expect ':'

    // Parse the exception type
    let type_token = lexer.expect(TokenType::Identifier)?;
    let type_expr = Expr::new_parse(
        NodeType::Identifier(type_token.token_str.clone()),
        type_token.clone(),
        vec![],
    );

    lexer.expect(TokenType::RightParen)?; // expect ')'

    lexer.expect(TokenType::LeftBrace)?; // expect '{'
    let body_expr = parse_body(lexer, TokenType::RightBrace)?;

    Ok(Expr::new_parse(
        NodeType::Catch,
        lexer.get_token(initial_current)?.clone(),
        vec![name_expr, type_expr, body_expr],
    ))
}

fn if_statement(lexer: &mut Lexer) -> Result<Expr, String> {
    let initial_current = lexer.current;
    lexer.advance(1)?;
    let mut params : Vec<Expr> = Vec::new();
    let prim = match parse_primary(lexer) {
        Ok(to_ret) => to_ret,
        Err(err_str) => return Err(err_str),
    };
    params.push(prim);
    let t = lexer.peek();
    if t.token_type != TokenType::LeftBrace {
        return Err(t.error(&format!("Expected '{{' after condition in 'if' statement, found '{:?}'.", t.token_type)));
    }
    lexer.advance(1)?;
    let body = match parse_body(lexer, TokenType::RightBrace) {
        Ok(body) => body,
        Err(err_str) => return Err(err_str),
    };
    params.push(body);

    let t = lexer.peek();
    if t.token_type == TokenType::Else {
        lexer.advance(1)?;
        let next = lexer.peek();
        if next.token_type == TokenType::If {
            let nested_if = if_statement(lexer)?;
            params.push(nested_if);
        } else if next.token_type == TokenType::LeftBrace {
            lexer.advance(1)?;
            let else_body = match parse_body(lexer, TokenType::RightBrace) {
                Ok(body) => body,
                Err(err_str) => return Err(err_str),
            };
            params.push(else_body);
        } else {
            return Err(t.error(&format!("Expected '{{' or 'if' after 'else', found '{:?}'.", next.token_type)));
        }
    }

    Ok(Expr::new_parse(NodeType::If, lexer.get_token(initial_current)?.clone(), params))
}

fn while_statement(lexer: &mut Lexer) -> Result<Expr, String> {
    let initial_current = lexer.current;
    lexer.advance(1)?;
    let mut params : Vec<Expr> = Vec::new();
    let prim = match parse_primary(lexer) {
        Ok(to_ret) => to_ret,
        Err(err_str) => return Err(err_str),
    };
    params.push(prim);
    let t = lexer.peek();
    if t.token_type != TokenType::LeftBrace {
        return Err(t.error("Expected '{{' after condition in 'while' statement."));
    }
    lexer.advance(1)?;
    let body = match parse_body(lexer, TokenType::RightBrace) {
        Ok(body) => body,
        Err(err_str) => return Err(err_str),
    };
    params.push(body);
    Ok(Expr::new_parse(NodeType::While, lexer.get_token(initial_current)?.clone(), params))
}

fn parse_for_statement(lexer: &mut Lexer) -> Result<Expr, String> {
    let initial_token = lexer.peek();
    lexer.advance(1)?; // consume 'for'

    // Expect loop variable name
    let ident_token = lexer.expect(TokenType::Identifier)?;
    let loop_var_name = ident_token.token_str.clone();

    lexer.expect(TokenType::In)?;

    // Parse the range expression (e.g., 1..10)
    let range_expr = parse_case_expr(lexer)?;
    if range_expr.node_type != NodeType::Range {
        return Err(ident_token.error("Expected range expression (start..end) after 'in'"));
    }
    let start_expr = range_expr.get(0)?.clone();
    let end_expr = range_expr.get(1)?.clone();

    lexer.expect(TokenType::LeftBrace)?;
    let body_expr = parse_body(lexer, TokenType::RightBrace)?;

    // let loop_var := <start_expr>
    let decl = Declaration {
        name: loop_var_name.clone(),
        value_type: str_to_value_type(INFER_TYPE),
        is_mut: true,
    };
    let decl_expr = Expr::new_parse(NodeType::Declaration(decl), initial_token.clone(), vec![start_expr.clone()]);

    // while <loop_var> < <end_expr> {
    let cond_expr = Expr::new_explicit(
        NodeType::FCall,
        vec![
            Expr::new_parse(
                NodeType::Identifier(loop_var_name.clone()),
                initial_token.clone(),
                vec![
                    Expr::new_parse(
                        NodeType::Identifier("lt".to_string()),
                        initial_token.clone(),
                        vec![],
                    ),
                ],
            ),
            end_expr.clone(),
        ],
        initial_token.line,
        initial_token.col,
    );

    let inc_expr = Expr::new_explicit(
        NodeType::FCall,
        vec![
            Expr::new_parse(NodeType::Identifier(loop_var_name.clone()), initial_token.clone(), vec![
                Expr::new_parse(NodeType::Identifier("inc".to_string()), initial_token.clone(), vec![]),
            ]),
        ],
        initial_token.line,
        initial_token.col,
    );

    let mut while_body_params = body_expr.params.clone();
    while_body_params.push(inc_expr);
    let while_body = Expr::new_explicit(NodeType::Body, while_body_params, body_expr.line, body_expr.col);

    let while_expr = Expr::new_explicit(NodeType::While, vec![cond_expr, while_body], initial_token.line, initial_token.col);

    Ok(Expr::new_explicit(NodeType::Body, vec![decl_expr, while_expr], initial_token.line, initial_token.col))
}

fn parse_case_expr(lexer: &mut Lexer) -> Result<Expr, String> {
    let left = parse_primary(lexer)?;
    let t = lexer.peek();
    if t.token_type == TokenType::DoubleDot {
        lexer.advance(1)?;
        let right = parse_primary(lexer)?;
        return Ok(Expr::new_parse(NodeType::Range, t, vec![left, right]));
    }
    Ok(left)
}

fn parse_switch_statement(lexer: &mut Lexer) -> Result<Expr, String> {
    let t = lexer.peek();
    let initial_current = lexer.current;
    lexer.advance(1)?;
    let mut params : Vec<Expr> = Vec::new();
    let prim = match parse_primary(lexer) {
        Ok(to_ret) => to_ret,
        Err(err_str) => return Err(err_str),
    };
    params.push(prim);

    if TokenType::LeftBrace != lexer.peek().token_type {
        return Err(t.error("Expected '{{' after primary expression in 'switch' statement."));
    }
    lexer.advance(1)?;

    let mut end_found = false;
    while lexer.current < lexer.len() && !end_found {
        let mut next_t = lexer.peek();
        if next_t.token_type != TokenType::Case {
            return Err(next_t.error(&format!("Expected 'case' in switch, found '{:?}'", next_t.token_type)));
        }

        lexer.advance(1)?;
        next_t = lexer.peek();
        if next_t.token_type == TokenType::Colon {
            params.push(Expr::new_parse(NodeType::DefaultCase, t.clone(), Vec::new()));
        } else {
            let prim = match parse_case_expr(lexer) {
                Ok(to_ret) => to_ret,
                Err(err_str) => return Err(err_str),
            };
            params.push(prim);
        }

        next_t = lexer.peek();
        if next_t.token_type != TokenType::Colon {
            return Err(next_t.error(&format!("Expected ':' case <primary_expr> in switch, found '{:?}'", next_t.token_type)));
        }

        lexer.advance(1)?;
        next_t = lexer.peek();
        let mut body_params : Vec<Expr> = Vec::new();
        while lexer.current < lexer.len() {
            if next_t.token_type == TokenType::RightBrace {
                params.push(Expr::new_parse(NodeType::Body, t.clone(), body_params));
                end_found = true;
                lexer.advance(1)?;
                break;
            }
            if next_t.token_type == TokenType::Case {
                params.push(Expr::new_parse(NodeType::Body, t.clone(), body_params));
                break;
            }
            let stmt = match parse_statement(lexer) {
                Ok(statement) => statement,
                Err(error_string) => return Err(error_string),
            };
            body_params.push(stmt);
            next_t = lexer.peek();
            if next_t.token_type == TokenType::Semicolon {
                lexer.advance(1)?;
                next_t = lexer.peek();
            }
        }
    }
    if end_found {
        return Ok(Expr::new_parse(NodeType::Switch, lexer.get_token(initial_current)?.clone(), params))
    }
    return Err(t.error("Expected '}}' to end switch."));
}

fn parse_declaration(lexer: &mut Lexer, is_mut: bool, explicit_type: &str) -> Result<Expr, String> {
    let t = lexer.peek();
    let decl_name = &t.token_str;
    let initial_current = lexer.current;

    lexer.advance(3)?; // skip identifier, colon and equal
    if explicit_type != INFER_TYPE {
        lexer.advance(1)?; // skip type identifier
    }

    let mut params : Vec<Expr> = Vec::new();
    params.push(parse_primary(lexer)?);

    let decl = Declaration{name: decl_name.to_string(), value_type: str_to_value_type(explicit_type), is_mut: is_mut};

    return Ok(Expr::new_parse(NodeType::Declaration(decl), lexer.get_token(initial_current)?.clone(), params))
}

fn parse_mut_declaration(lexer: &mut Lexer) -> Result<Expr, String> {
    let t = lexer.peek();
    let mut next_t = lexer.next()?;
    let mut next_token_type = &next_t.token_type;
    if next_token_type != &TokenType::Identifier {
        return Err(t.error(&format!("Expected identifier after 'mut', found '{:?}'.", next_token_type)));
    }
    let identifier = &next_t.token_str.to_string();
    lexer.advance(1)?;
    next_t = lexer.next()?;
    next_token_type = &next_t.token_type;
    if next_token_type != &TokenType::Colon {
        return Err(t.error(&format!("Expected ':' after 'mut {}', found '{:?}'.", identifier, next_token_type)));
    }
    let next_next_t = lexer.peek_ahead(2)?;
    let next_next_token_type = &next_next_t.token_type;
    match next_next_token_type {
        TokenType::Identifier => {
            let type_name = &next_next_t.token_str;
            return parse_declaration(lexer, true, type_name)
        }
        TokenType::Equal => {
            return parse_declaration(lexer, true, INFER_TYPE)
        },
        _ => {
            Err(t.error(&format!("Expected a type identifier or '=' after 'mut {} :' in statement, found '{:?}'.",
                                 identifier, next_next_token_type)))
        },
    }
}

fn parse_statement(lexer: &mut Lexer) -> Result<Expr, String> {
    let t = lexer.peek();
    match &t.token_type {
        TokenType::Return => return return_statement(lexer),
        TokenType::Throw => return parse_throw_statement(lexer),
        TokenType::If => return if_statement(lexer),
        TokenType::While => return while_statement(lexer),
        TokenType::For => return parse_for_statement(lexer),
        TokenType::Switch => return parse_switch_statement(lexer),
        TokenType::Mut => return parse_mut_declaration(lexer),
        TokenType::Identifier => return parse_statement_identifier(lexer),
        TokenType::Catch => return parse_catch_statement(lexer),
        TokenType::LeftBrace => {
            lexer.advance(1)?; // Skip LeftBrace
            return parse_body(lexer, TokenType::RightBrace)
        }
        _ => {
            Err(t.error(&format!("Expected statement, found {:?}.", t.token_type)))
        },
    }
}

fn parse_body(lexer: &mut Lexer, end_token: TokenType) -> Result<Expr, String> {

    let initial_current: usize = lexer.current;
    let mut params : Vec<Expr> = Vec::new();
    let mut end_found = false;
    let mut t = lexer.peek(); // track last token for error reporting

    while lexer.current < lexer.len() && !end_found {
        t = lexer.peek(); // update t with the current token
        let token_type = &t.token_type;
        if token_type == &end_token {
            lexer.advance(1)?;
            end_found = true;
            break;
        }
        if token_type == &TokenType::Semicolon { // REM: TokenType::DoubleSemicolon results in a lexical error, no need to parse it
            lexer.expect(TokenType::Semicolon)?; // REM: This is suboptimal but more clear in grep
            continue;
        }

        let stmt = match parse_statement(lexer) {
            Ok(statement) => statement,
            Err(error_string) => return Err(error_string),
        };
        params.push(stmt);
    }
    if end_found {
        return Ok(Expr::new_parse(NodeType::Body, lexer.get_token(initial_current)?.clone(), params))
    }
    return Err(t.error(&format!("Expected '{:?}' to end body.", end_token))); // use last valid token
}

pub fn parse_tokens(lexer: &mut Lexer) -> Result<Expr, String> {

    let e: Expr = match parse_body(lexer, TokenType::Eof) {
        Ok(expr) => expr,
        Err(error_string) => return Err(error_string),
    };

    let mut i = lexer.current;
    let mut unparsed_tokens = 0;
    let lexer_len = lexer.len();
    if i < lexer_len {
        unparsed_tokens = lexer_len - i;
    }
    if unparsed_tokens > 0 {
        println!("Total tokens parsed: {}/{}", lexer.current, lexer_len);
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
