use std::collections::HashMap;
use std::io::Write; // <--- bring flush() into scope
use std::io;

use rs::lexer::{TokenType, Token, Lexer};

pub const LANG_NAME  : &str = "rscil";
pub const INFER_TYPE : &str = "auto";

#[derive(Debug, Clone, PartialEq)]
pub struct SEnumDef {
    pub enum_map: HashMap<String, Option<ValueType>>,
}

impl SEnumDef {
    pub fn get_variant_pos(self: &SEnumDef, variant_name: &str) -> i64 {
        return match self.enum_map.keys().position(|k| k == variant_name) {
            Some(position) => {
                position as i64
            }
            None => {
                println!("Error: Enum variant '{}' not found in enum map.", variant_name);
                0
            }
        }
    }

    pub fn variant_pos_to_str(self: &SEnumDef, position: i64) -> Result<String, String> {
        let keys: Vec<String> = self.enum_map.keys().cloned().collect();
        if position < 0 || position >= keys.len() as i64 {
            // Return an error if the position is out of bounds
            return Err(format!("Error: Invalid position '{}' for enum variant in '{}'.",
                               position, self.enum_map.keys().cloned().collect::<Vec<_>>().join(", ")))
        }

        // If position is valid, return the corresponding variant name
        return Ok(keys[position as usize].clone())
    }
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
pub enum NodeType {
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

    pub fn get(self: &Expr, i: usize) -> &Expr {
        return &self.params.get(i).unwrap();
    }

    pub fn lang_error(self: &Expr, phase: &str, msg: &str) -> String {
        if phase == "assert" || phase == "panic_type" || phase == "eval" {
            println!("{}:{}: {} {} ERROR: {}\nExplanation: This is not your fault as a user, this is a bug in the language.",
                     self.line, self.col, LANG_NAME, phase, msg);
            io::stdout().flush().unwrap();
            std::process::exit(1);
        }
        return format!("{}:{}: {} {} ERROR: {}", self.line, self.col, LANG_NAME, phase, msg)
    }

    pub fn todo_error(self: &Expr, phase: &str, msg: &str) -> String {
        if phase == "assert" {
            panic!("Expr.todo_error() cannot be called for phase 'assert', use Expr.lang_error() instead")
        }
        if phase == "panic_type" || phase == "eval" {
            println!("{}:{}: {} {} ERROR: {}\nExplanation: Not implemented yet, this is a missing feature in the language.",
                     self.line, self.col, LANG_NAME, phase, msg);
            io::stdout().flush().unwrap();
            std::process::exit(1);
        }
        return format!("{}:{}: {} {} ERROR: {}", self.line, self.col, LANG_NAME, phase, msg)
    }

    pub fn error(self: &Expr, phase: &str, msg: &str) -> String {
        if phase == "assert" {
            panic!("Expr.error() cannot be called for phase 'assert', use Expr.lang_error() instead")
        }
        if phase == "panic_type" || phase == "eval" {
            println!("{}:{}: {} ERROR: {}", self.line, self.col, phase, msg);
            io::stdout().flush().unwrap();
            std::process::exit(1);
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
pub enum ValueType {
    TList,
    TFunc,
    TProc,
    TMacro,
    TEnumDef,
    TStructDef,
    TCustom(String),
    TMulti(String),
    ToInferType,
}

pub fn value_type_to_str(arg_type: &ValueType) -> String {
    match arg_type {
        ValueType::ToInferType => INFER_TYPE.to_string(),
        ValueType::TList => "list".to_string(),
        ValueType::TFunc => "func".to_string(),
        ValueType::TProc => "proc".to_string(),
        ValueType::TMacro => "macro".to_string(),
        ValueType::TEnumDef => "enum".to_string(),
        ValueType::TStructDef => "struct".to_string(),
        ValueType::TMulti(type_name) => format!("{}", type_name),
        ValueType::TCustom(type_name) => format!("{}", type_name),
    }
}

pub fn str_to_value_type(arg_type: &str) -> ValueType {
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
pub struct ModeDef {
    pub name: String,
    pub allows_base_mut: bool,
    pub allows_base_calls: bool,
    pub allows_base_anything: bool,
    pub needs_main_proc: bool,
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
                    allows_base_mut: true,
                    allows_base_anything: false,
                    needs_main_proc: false,
        }),

        _  => return Err(format!("0:0: {} interpreter implementation doesn't support mode '{}'", LANG_NAME, mode_name)),
    };
}

pub fn parse_mode(path: &String, lexer: &Lexer, mut current: &mut usize) -> Result<ModeDef, String> {
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

pub fn parse_tokens(lexer: Lexer, current: &mut usize) -> Result<Expr, String> {

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
