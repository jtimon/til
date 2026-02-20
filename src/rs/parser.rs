use std::collections::HashMap;
use std::io::Write; // <--- bring flush() into scope
use std::io;
use std::sync::atomic::{AtomicUsize, Ordering};

use rs::lexer::{LANG_NAME, TokenType, Token, Lexer};

// Counter for generating unique loop variable names when _ is used
// Bug #146: Reset per-function for deterministic output (like Issue #127 fix for precomp_forin_counter)
static LOOP_VAR_COUNTER: AtomicUsize = AtomicUsize::new(0);

fn next_loop_var() -> String {
    let n = LOOP_VAR_COUNTER.fetch_add(1, Ordering::SeqCst);
    format!("_loop_{}", n)
}

fn save_loop_var_counter() -> usize {
    LOOP_VAR_COUNTER.load(Ordering::SeqCst)
}

fn reset_loop_var_counter() {
    LOOP_VAR_COUNTER.store(0, Ordering::SeqCst);
}

fn restore_loop_var_counter(saved: usize) {
    LOOP_VAR_COUNTER.store(saved, Ordering::SeqCst);
}

pub const INFER_TYPE : &str = "auto";

// Bug #38 fix: Use a Vec to preserve variant order instead of HashMap
#[derive(Debug, Clone, PartialEq)]
pub struct EnumVariant {
    pub name: String,
    pub payload_type: Option<ValueType>,
}

#[derive(Debug, Clone, PartialEq)]
pub struct SEnumDef {
    pub variants: Vec<EnumVariant>,
    pub methods: crate::rs::ordered_map::OrderedMap<String, Expr>,  // Auto-generated methods (delete, clone)
}

impl SEnumDef {
    // Helper methods for backward compatibility with enum_map interface
    pub fn get(&self, variant_name: &str) -> Option<&Option<ValueType>> {
        for v in &self.variants {
            if v.name == variant_name {
                return Some(&v.payload_type);
            }
        }
        None
    }

    pub fn contains_key(&self, variant_name: &str) -> bool {
        for v in &self.variants {
            if v.name == variant_name {
                return true;
            }
        }
        false
    }
}

#[derive(Debug, Clone, PartialEq)]
pub struct Declaration {
    pub name: String,
    pub value_type: ValueType,
    pub is_mut: bool,
    pub is_copy: bool,
    pub is_own: bool,
    pub default_value: Option<Box<Expr>>,  // For optional function arguments
}

// TODO: PatternInfo is a workaround for homogeneity with TIL's lack of tuple syntax
// Once TIL supports tuple notation like (Str, Str), this can be replaced with:
// Pattern(String, String)  // Pattern(variant_name, binding_var)
#[derive(Debug, Clone, PartialEq)]
pub struct PatternInfo {
    pub variant_name: String,
    pub binding_var: String,
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
    pub return_types: Vec<ValueType>,  // "returns" conflicts with TIL keyword
    pub throw_types: Vec<ValueType>,   // "throws" conflicts with TIL keyword
    pub body: Vec<Expr>,
    pub source_path: String,  // Path to the file where this function was defined
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

    pub fn is_macro(self: &SFuncDef) -> bool {
        match self.function_type {
            FunctionType::FTMacro => true,
            FunctionType::FTFunc | FunctionType::FTProc | FunctionType::FTFuncExt | FunctionType::FTProcExt => false,
        }
    }
}

#[derive(Debug, Clone, PartialEq)]
pub struct SStructDef {
    pub members : Vec<Declaration>,
    pub default_values : HashMap<String, Expr>,
}

impl SStructDef {
    /// Helper to find a member by name
    pub fn get_member(&self, member_name: &str) -> Option<&Declaration> {
        self.members.iter()
            .find(|decl| decl.name == member_name)
    }

    /// Helper to find a member by name or return an error
    pub fn get_member_or_err(
        &self,
        member_name: &str,
        struct_name: &str,
        path: &str,
        e: &Expr
    ) -> Result<&Declaration, String> {
        self.get_member(member_name)
            .ok_or_else(|| e.error(path, "type", &format!(
                "Struct '{}' has no member '{}'", struct_name, member_name
            )))
    }
}

#[derive(Debug, Clone, PartialEq)]
pub struct SNamespaceDef {
    pub type_name: String,
    pub members: Vec<Declaration>,
    pub default_values: HashMap<String, Expr>,
}

#[derive(Debug, Clone, PartialEq)]
pub enum Literal {
    Number(String), // TODO support more kinds of numbers
    Str(String),
    List(String), // TODO You can call it tupple too. who cares? it's not even tested yet, just parsed
}

#[derive(Debug, Clone, PartialEq)]
pub enum NodeType {
    Body,
    LLiteral(Literal),
    FCall(bool),  // Issue #132: bool indicates if call has '?' suffix (calls throwing func)
    Identifier(String),
    Declaration(Declaration),
    Assignment(String),
    NamedArg(String), // Named argument in function call: name=value
    FuncDef(SFuncDef),
    EnumDef(SEnumDef),
    StructDef(SStructDef),
    NamespaceDef(SNamespaceDef),
    Return,
    Throw,
    Catch,
    Break,
    Continue,
    If,
    While,
    Switch,
    DefaultCase,
    Range,
    Pattern(PatternInfo), // Pattern matching for switch case with payload extraction
    ForIn(String), // for VAR: TYPE in COLLECTION - payload is the TYPE name
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
            None => Err(self.lang_error("<internal>", "assert", &format!("Expr index {} out of bounds (len: {}).", i, self.params.len()))),
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

    pub fn lang_error(self: &Expr, path: &str, phase: &str, msg: &str) -> String {
        if phase == "warning" {
            return format!("{}:{}:{}: {} WARNING: {}\nExplanation: This should never happen, this is a bug in the language.", path, self.line, self.col, LANG_NAME, msg);
        }
        return format!("{}:{}:{}: {} {} ERROR: {}\nExplanation: This should never happen, this is a bug in the language.",
                       path, self.line, self.col, LANG_NAME, phase, msg)
    }

    pub fn todo_error(self: &Expr, path: &str, phase: &str, msg: &str) -> String {
        if phase == "warning" {
            return format!("{}:{}:{}: {} WARNING: {}\nExplanation: Not implemented yet, this is a missing feature in the language.", path, self.line, self.col, LANG_NAME, msg);
        }
        return format!("{}:{}:{}: {} {} ERROR: {}\nExplanation: Not implemented yet, this is a missing feature in the language.",
                       path, self.line, self.col, LANG_NAME, phase, msg)
    }

    pub fn error(self: &Expr, path: &str, phase: &str, msg: &str) -> String {
        if phase == "warning" {
            return format!("{}:{}:{}: WARNING: {}", path, self.line, self.col, msg);
        }
        return format!("{}:{}:{}: {} ERROR: {}", path, self.line, self.col, phase, msg)
    }
}

fn is_literal(t: &Token) -> bool {
    return match t.token_type {
        TokenType::String => true,
        TokenType::Number => true,
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

fn parse_literal(lexer: &mut Lexer, t: &Token) -> Result<Expr, String> {
    let params : Vec<Expr> = Vec::new();
    let node_type = match t.token_type {
        TokenType::String => NodeType::LLiteral(Literal::Str(t.token_str.clone())),
        TokenType::Number => {
            let number = t.token_str.parse::<i64>()
                .map_err(|e| t.lang_error(&lexer.path, &format!("Invalid number literal '{}': {}", t.token_str, e)))?;
            NodeType::LLiteral(Literal::Number(number.to_string()))
        },
        _ => {
            return Err(t.lang_error(&lexer.path, &format!("Trying to parse a token that's not a literal as a literal, found '{:?}'.", t.token_type)));
        },
    };
    let e = Expr::new_parse(node_type, t.clone(), params);
    lexer.advance(1)?;
    Ok(e)
}

fn parse_args(lexer: &mut Lexer) -> Result<Expr, String> {
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
                    return Err(list_t.error(&lexer.path, "Unexpected ','."));
                }
            },
            _ => {
                if expect_comma {
                    return Err(list_t.error(&lexer.path, &format!("Expected ')' or ',', found '{:?}'.", list_t.token_type)));
                }
                expect_comma = true;
                let prim = match parse_primary(lexer) {
                    Ok(to_ret) => to_ret,
                    Err(err_str) => return Err(err_str),
                };
                // Check for named argument: identifier = value
                let next_t = lexer.peek();
                if next_t.token_type == TokenType::Equal {
                    // This is a named argument
                    if let NodeType::Identifier(arg_name) = &prim.node_type {
                        if !prim.params.is_empty() {
                            return Err(next_t.error(&lexer.path, "Named argument name cannot be a dotted identifier"));
                        }
                        let arg_name = arg_name.clone();
                        lexer.advance(1)?; // consume '='
                        let value = parse_primary(lexer)?;
                        let named_arg = Expr::new_explicit(
                            NodeType::NamedArg(arg_name),
                            vec![value],
                            prim.line,
                            prim.col,
                        );
                        params.push(named_arg);
                    } else {
                        return Err(next_t.error(&lexer.path, "Named argument requires a simple identifier before '='"));
                    }
                } else {
                    params.push(prim);
                }
                list_t = lexer.peek();
            },
        }
    }
    match list_t.token_type {
        // TODO properly parse lists besides function definition arguments
        TokenType::RightParen => Ok(Expr::new_parse(NodeType::LLiteral(Literal::List("".to_string())), lexer.get_token(initial_current)?.clone(), params)),
        _ => Err(list_t.error(&lexer.path, "Expected closing parentheses.")),
    }
}

fn parse_assignment(lexer: &mut Lexer, t: &Token, name: &String) -> Result<Expr, String> {
    lexer.expect(TokenType::Equal)?;
    let mut params = Vec::new();
    params.push(parse_primary(lexer)?);
    return Ok(Expr::new_parse(NodeType::Assignment(name.to_string()), t.clone(), params))
}

fn validate_mut_copy_own_modifiers(t: &Token, path: &str, modifier: &str, is_mut: bool, is_copy: bool, is_own: bool) -> Result<(), String> {
    if modifier == "mut" {
        if is_copy {
            return Err(t.error(path, "Cannot use both 'mut' and 'copy' on the same parameter. Use 'mut' for mutable reference or 'copy' for explicit copy."));
        }
        if is_own {
            return Err(t.error(path, "Cannot use both 'mut' and 'own' on the same parameter. Use 'mut' for mutable reference or 'own' for ownership transfer."));
        }
    }
    if modifier == "copy" {
        if is_mut {
            return Err(t.error(path, "Cannot use both 'mut' and 'copy' on the same parameter. Use 'mut' for mutable reference or 'copy' for explicit copy."));
        }
        if is_own {
            return Err(t.error(path, "Cannot use both 'own' and 'copy' on the same parameter. Use 'own' for ownership transfer or 'copy' for explicit copy."));
        }
    }
    if modifier == "own" {
        if is_mut {
            return Err(t.error(path, "Cannot use both 'mut' and 'own' on the same parameter. Use 'mut' for mutable reference or 'own' for ownership transfer."));
        }
        if is_copy {
            return Err(t.error(path, "Cannot use both 'own' and 'copy' on the same parameter. Use 'own' for ownership transfer or 'copy' for explicit copy."));
        }
    }
    Ok(())
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
    let mut is_copy = false;
    let mut is_own = false;
    while !(lexer.is_eof(0) || rightparent_found) {
        match t.token_type {
            TokenType::RightParen => {
                rightparent_found = true;
                if expect_colon {
                    return Err(t.error(&lexer.path, &format!("Expected ': Type' after arg name '{}' before ')'.", arg_name)));
                }
                lexer.advance(1)?;
            },
            TokenType::Comma => {
                if expect_colon {
                    return Err(t.error(&lexer.path, &format!("Expected ': Type' after arg name '{}', but found ','.", arg_name)));
                }
                if expect_name {
                    return Err(t.error(&lexer.path, "Expected arg name before ','."));
                }
                if expect_comma {
                    expect_comma = false;
                    expect_colon = false;
                    expect_name = true;
                    is_mut = false;
                    is_copy = false;
                    is_own = false;
                    lexer.expect(TokenType::Comma)?;
                    t = lexer.peek();
                } else {
                    return Err(t.error(&lexer.path, "Unexpected ','."));
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
                        _ => return Err(t.error(&lexer.path, &format!("Expected type after '{}:', but found '{}'.", arg_name, t.token_str))),
                    }
                } else {
                    return Err(t.error(&lexer.path, "Unexpected ':'."));
                }
            },
            TokenType::DoubleDot => {
                if expect_colon {
                    return Err(t.error(&lexer.path, &format!("Expected ': Type' after arg name '{}', but found '..'.", arg_name)));
                }
                if expect_comma {
                    return Err(t.error(&lexer.path, &format!("Expected ',', found '{:?}'.", t.token_type)));
                }
                if expect_name {
                    return Err(t.error(&lexer.path, &format!("Expected arg name, found '{:?}'.", t.token_type)));
                }
                is_variadic = true;
                lexer.advance(1)?;
                t = lexer.peek();
            },
            TokenType::Identifier => {
                if expect_colon {
                    return Err(t.error(&lexer.path, &format!("Expected ': Type' after arg name '{}', but found '{}'.", arg_name, t.token_str)));
                }
                if expect_comma {
                    return Err(t.error(&lexer.path, &format!("Expected ',', found identifier '{}'.", t.token_str)));
                }
                if expect_name {
                    arg_name = t.token_str.to_string();
                    expect_colon = true;
                    expect_name = false;
                } else {
                    let arg_type = if is_variadic {
                        is_variadic = false;
                        ValueType::TMulti(t.token_str.clone())
                    } else {
                        str_to_value_type(&t.token_str)
                    };
                    lexer.advance(1)?;
                    t = lexer.peek();

                    // Check for optional default value: `= expr`
                    let default_value = if t.token_type == TokenType::Equal {
                        lexer.advance(1)?;  // consume '='
                        let default_expr = parse_primary(lexer)?;
                        Some(Box::new(default_expr))
                    } else {
                        None
                    };

                    args.push(Declaration {
                        name: arg_name.to_string(),
                        value_type: arg_type,
                        is_mut: is_mut,
                        is_copy: is_copy,
                        is_own: is_own,
                        default_value: default_value,
                    });
                    expect_comma = true;
                    is_mut = false;
                    is_copy = false;
                    is_own = false;
                    // Don't advance again - we already did above or parse_expression did
                    t = lexer.peek();
                    continue;
                }
                lexer.advance(1)?;
                t = lexer.peek();
            },
            TokenType::Mut => {
                if !expect_name {
                    return Err(t.error(&lexer.path, "Unexpected 'mut' in argument list."));
                }
                validate_mut_copy_own_modifiers(&t, &lexer.path, "mut", is_mut, is_copy, is_own)?;
                is_mut = true;
                lexer.advance(1)?;
                t = lexer.peek();
            },
            TokenType::Copy => {
                if !expect_name {
                    return Err(t.error(&lexer.path, "Unexpected 'copy' in argument list."));
                }
                validate_mut_copy_own_modifiers(&t, &lexer.path, "copy", is_mut, is_copy, is_own)?;
                is_copy = true;
                lexer.advance(1)?;
                t = lexer.peek();
            },
            TokenType::Own => {
                if !expect_name {
                    return Err(t.error(&lexer.path, "Unexpected 'own' in argument list."));
                }
                validate_mut_copy_own_modifiers(&t, &lexer.path, "own", is_mut, is_copy, is_own)?;
                is_own = true;
                lexer.advance(1)?;
                t = lexer.peek();
            },
            _ => {
                return Err(t.error(&lexer.path, &format!("Unexpected '{:?}' in func/proc args.", t.token_type)));
            },
        }
    }
    match t.token_type {
        TokenType::RightParen => return Ok(args),
        _ => return Err(t.error(&lexer.path, "Expected closing parentheses.")),
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
            TokenType::Throws | TokenType::LeftBrace => {
                end_found = true;
                lexer.advance(1)?;
            },
            TokenType::Comma => {
                if expect_comma {
                    lexer.expect(TokenType::Comma)?;
                    expect_comma = false;
                    t = lexer.peek();
                } else {
                    return Err(t.error(&lexer.path, "Unexpected ','."));
                }
            },
            TokenType::Identifier => {
                if expect_comma {
                    return Err(t.error(&lexer.path, &format!("Expected ',', found '{:?}'.", t.token_type)));
                }
                return_types.push(str_to_value_type(&t.token_str));
                expect_comma = true;
                lexer.advance(1)?;
                t = lexer.peek();
            },
            // Issue #105: Allow 'struct' as a return type for first-class structs
            TokenType::Struct => {
                if expect_comma {
                    return Err(t.error(&lexer.path, &format!("Expected ',', found '{:?}'.", t.token_type)));
                }
                return_types.push(str_to_value_type("struct"));
                expect_comma = true;
                lexer.advance(1)?;
                t = lexer.peek();
            },
            // Issue #106: Allow 'enum' as a return type for first-class enums
            TokenType::Enum => {
                if expect_comma {
                    return Err(t.error(&lexer.path, &format!("Expected ',', found '{:?}'.", t.token_type)));
                }
                return_types.push(str_to_value_type("enum"));
                expect_comma = true;
                lexer.advance(1)?;
                t = lexer.peek();
            },
            _ => {
                return Err(t.error(&lexer.path, &format!("Unexpected '{:?}' in func/proc returns.", t.token_type)));
            },
        }
    }
    if end_found {
        return Ok(return_types);
    } else {
        return Err(t.error(&lexer.path, "Expected '{{' or 'throws' after return values."));
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
            TokenType::LeftBrace => {
                end_found = true;
                lexer.advance(1)?;
            },
            TokenType::Comma => {
                if expect_comma {
                    expect_comma = false;
                    lexer.advance(1)?;
                    t = lexer.peek();
                } else {
                    return Err(t.error(&lexer.path, "Unexpected ','."));
                }
            },
            TokenType::Identifier => {
                if expect_comma {
                    return Err(t.error(&lexer.path, &format!("Expected ',', found '{:?}'.", t.token_type)));
                }
                return_types.push(str_to_value_type(&t.token_str));
                expect_comma = true;
                lexer.advance(1)?;
                t = lexer.peek();
            },
            _ => {
                return Err(t.error(&lexer.path, &format!("Unexpected '{:?}' in func/proc throws.", t.token_type)));
            },
        }
    }
    if end_found {
        return Ok(return_types);
    } else {
        return Err(t.error(&lexer.path, "Expected '{{' after throw values."));
    }
}

fn parse_func_proc_definition(lexer: &mut Lexer, function_type: FunctionType) -> Result<Expr, String> {

    lexer.advance(1)?;
    let t = lexer.peek();
    if lexer.is_eof(1) {
        return Err(t.error(&lexer.path, "expected '(' after 'func' or 'proc', found EOF."));
    }
    if t.token_type != TokenType::LeftParen {
        return Err(t.error(&lexer.path, &format!("expected '(' after 'func', found '{:?}'.", t.token_type)));
    }
    let args = parse_func_proc_args(lexer)?;
    let return_types = func_proc_returns(lexer)?;
    let throw_types = func_proc_throws(lexer)?;

    // Bug #146: Reset loop var counter per-function for deterministic output
    let saved_loop_counter = save_loop_var_counter();
    reset_loop_var_counter();

    let body = match parse_body(lexer, TokenType::RightBrace) {
        Ok(body) => {
            // ext_func/ext_proc cannot have a body
            if (function_type == FunctionType::FTFuncExt || function_type == FunctionType::FTProcExt) && !body.params.is_empty() {
                restore_loop_var_counter(saved_loop_counter);
                return Err(t.error(&lexer.path, "ext_func/ext_proc cannot have a body"));
            }
            body.params
        },
        Err(err_str) => {
            restore_loop_var_counter(saved_loop_counter);
            return Err(err_str);
        },
    };

    restore_loop_var_counter(saved_loop_counter);

    let func_def = SFuncDef{
        function_type: function_type,
        args: args,
        return_types: return_types,
        throw_types: throw_types,
        body: body,
        source_path: lexer.path.clone(),
    };
    let params : Vec<Expr> = Vec::new();
    let e = Expr::new_parse(NodeType::FuncDef(func_def), t.clone(), params);
    Ok(e)
}

fn enum_definition(lexer: &mut Lexer) -> Result<Expr, String> {
    let initial_current: usize = lexer.current;
    lexer.advance(1)?;

    let t = lexer.peek();
    if t.token_type != TokenType::LeftBrace {
        return Err(t.error(&lexer.path, "Expected '{{' after 'enum'."));
    }
    if lexer.is_eof(1) {
        let t = lexer.peek();
        return Err(t.error(&lexer.path, "expected identifier after 'enum {{', found EOF."));
    }
    lexer.advance(1)?;
    let mut variants: Vec<EnumVariant> = Vec::new();
    // Issue #174: namespace members packed into params for post-parse splitting
    let mut namespace_stmts: Vec<Expr> = Vec::new();
    let mut in_namespace = false;

    let mut end_found = false;
    while lexer.current < lexer.len() && !end_found {
        let it_t = lexer.peek();
        match it_t.token_type {
            TokenType::RightBrace => {
                lexer.advance(1)?;
                end_found = true;
            },
            // Issue #174: namespace: separator inside enum body
            TokenType::Namespace => {
                let next = lexer.next()?;
                if next.token_type == TokenType::Colon {
                    if in_namespace {
                        return Err(it_t.error(&lexer.path, "duplicate 'namespace:' inside enum definition"));
                    }
                    in_namespace = true;
                    lexer.advance(2)?; // past namespace and :
                } else {
                    return Err(it_t.error(&lexer.path, "Expected ':' after 'namespace' inside enum body."));
                }
            },
            _ => {
                if in_namespace {
                    // Collect raw statement Exprs for post-parse splitting into NamespaceDef
                    let stmt = parse_statement(lexer)?;
                    namespace_stmts.push(stmt);
                } else {
                    match it_t.token_type {
                        TokenType::Identifier => {
                            let enum_val_name = &it_t.token_str;
                            let next_t = lexer.next()?;
                            match next_t.token_type {
                                TokenType::Colon => {
                                    let next2_t = lexer.peek_ahead(2)?;
                                    if next2_t.token_type != TokenType::Identifier {
                                        return Err(next2_t.error(&lexer.path, &format!("Expected type identifier after '{} :', found '{:?}'.",
                                                                          enum_val_name, next2_t.token_type)));
                                    }
                                    let enum_val_type = &next2_t.token_str;
                                    variants.push(EnumVariant { name: enum_val_name.to_string(), payload_type: Some(str_to_value_type(enum_val_type)) });
                                    lexer.advance(3)?; // past name, :, type
                                },
                                TokenType::Comma => {
                                    variants.push(EnumVariant { name: enum_val_name.to_string(), payload_type: None });
                                    lexer.advance(2)?; // past name and comma
                                },
                                TokenType::RightBrace => {
                                    variants.push(EnumVariant { name: enum_val_name.to_string(), payload_type: None });
                                    lexer.advance(2)?; // past name and }
                                    end_found = true;
                                },
                                _ => {
                                    return Err(next_t.error(&lexer.path, &format!("Expected ',' or ':' after '{}', found '{:?}'.",
                                                                     enum_val_name, next_t.token_type)));
                                }
                            }
                        },
                        TokenType::Comma => {
                            lexer.advance(1)?; // skip comma
                        },
                        _ => {
                            return Err(it_t.error(&lexer.path, &format!("Expected '}}' to end enum or a new identifier, found '{:?}'.",
                                                           it_t.token_type)));
                        }
                    }
                }
            }
        }
    }
    if !end_found {
        return Err(t.error(&lexer.path, "Expected '}}' to end enum."));
    }
    return Ok(Expr::new_parse(NodeType::EnumDef(SEnumDef{variants, methods: crate::rs::ordered_map::OrderedMap::new()}), lexer.get_token(initial_current)?.clone(), namespace_stmts));
}

fn parse_struct_definition(lexer: &mut Lexer) -> Result<Expr, String> {
    lexer.expect(TokenType::Struct)?;
    let t = lexer.peek();
    if t.token_type != TokenType::LeftBrace {
        return Err(t.error(&lexer.path, "Expected '{{' after 'struct'."));
    }
    if lexer.is_eof(1) {
        let t = lexer.peek();
        return Err(t.error(&lexer.path, "expected 'identifier' after 'struct {{', found EOF."));
    }
    lexer.advance(1)?;

    let mut members = Vec::new();
    let mut default_values = HashMap::new();
    // Issue #174: namespace members packed into params for post-parse splitting
    let mut namespace_stmts: Vec<Expr> = Vec::new();
    let mut in_namespace = false;

    let mut end_found = false;
    while lexer.current < lexer.len() && !end_found {
        let peek_t = lexer.peek();
        match peek_t.token_type {
            TokenType::RightBrace => {
                lexer.advance(1)?;
                end_found = true;
            },
            // Issue #174: namespace: separator inside struct body
            TokenType::Namespace => {
                let next = lexer.next()?;
                if next.token_type == TokenType::Colon {
                    if in_namespace {
                        return Err(peek_t.error(&lexer.path, "duplicate 'namespace:' inside struct definition"));
                    }
                    in_namespace = true;
                    lexer.advance(2)?; // past namespace and :
                } else {
                    return Err(peek_t.error(&lexer.path, "Expected ':' after 'namespace' inside struct body."));
                }
            },
            _ => {
                let stmt = parse_statement(lexer)?;
                if in_namespace {
                    // Collect raw statement Exprs for post-parse splitting into NamespaceDef
                    namespace_stmts.push(stmt);
                } else {
                    match &stmt.node_type {
                        NodeType::Declaration(decl) => {
                            members.push(decl.clone());
                            if stmt.params.len() == 1 {
                                match stmt.params.get(0) {
                                    Some(val) => {
                                        default_values.insert(decl.name.clone(), val.clone());
                                    },
                                    None => return Err(t.error(&lexer.path, "expected value in struct member declaration")),
                                }
                            } else {
                                // TODO allow not setting default values in struct members
                                return Err(t.error(&lexer.path, "all declarations inside struct definitions must have a value for now"));
                            }
                        },
                        NodeType::Assignment(name) => {
                            // Handle const := value inside structs (methods like eq := func(...))
                            if stmt.params.len() == 1 {
                                let val = stmt.params.get(0).unwrap();
                                let decl = Declaration {
                                    name: name.clone(),
                                    value_type: ValueType::TCustom(INFER_TYPE.to_string()),
                                    is_mut: false,
                                    is_copy: false,
                                    is_own: false,
                                    default_value: None,
                                };
                                members.push(decl.clone());
                                default_values.insert(name.clone(), val.clone());
                            } else {
                                return Err(t.error(&lexer.path, &format!("struct assignment '{}' must have exactly one value", name)));
                            }
                        },
                        _ => return Err(t.error(&lexer.path, &format!("expected only declarations inside struct definition, found {:?}", stmt.node_type))),
                    }
                }
            }
        }
    }
    if !end_found {
        return Err(t.error(&lexer.path, "Expected '}}' to end struct definition."));
    }

    return Ok(Expr::new_parse(NodeType::StructDef(SStructDef{members: members, default_values: default_values}),
                              t.clone(), namespace_stmts));
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
            return Err(next2_t.error(&lexer.path, &format!("expected identifier after '{}.', found '{:?}'.", current_identifier, next2_t.token_type)));
        }

        current_identifier = next2_t.token_str.to_string();
        lexer.advance(2)?;
        params.push(Expr::new_parse(NodeType::Identifier(current_identifier.clone()), t.clone(), Vec::new()));
        next_t = lexer.next()?;
    }

    let e = Expr::new_parse(NodeType::Identifier(t.token_str.clone()), lexer.get_token(initial_current)?.clone(), params);
    lexer.advance(1)?;

    if TokenType::LeftParen == next_t.token_type {
        let arg_list = match parse_args(lexer) {
            Ok(a_list) => a_list,
            Err(err_str) => return Err(err_str),
        };
        let mut params : Vec<Expr> = Vec::new();
        params.push(e);
        params.extend(arg_list.params);
        // Issue #132: Check for ? after function call (indicates call to throwing function)
        let does_throw = if lexer.peek().token_type == TokenType::QuestionMark {
            lexer.advance(1)?;
            true
        } else {
            false
        };
        let mut result = Expr::new_parse(NodeType::FCall(does_throw), lexer.get_token(initial_current)?.clone(), params);

        // Handle chained method calls and field access: a.method1().method2().field.method3()
        // Bug #32 fix: Support field access after method calls (not just method calls)
        let mut should_continue_chaining = true;
        while should_continue_chaining {
            let peek_t = lexer.peek();
            if peek_t.token_type != TokenType::Dot {
                should_continue_chaining = false;
            }

            if should_continue_chaining {
                // Consume the dot
                lexer.advance(1)?;

                // Expect an identifier for the next method/field name
                let method_t = lexer.peek();
                if method_t.token_type != TokenType::Identifier {
                    return Err(method_t.error(&lexer.path, &format!("Expected identifier after '.', found '{:?}'", method_t.token_type)));
                }
                let method_name = method_t.token_str.clone();
                lexer.advance(1)?;

                // Check if it's a method call (has parentheses) or field access (no parentheses)
                let next_peek = lexer.peek();
                if next_peek.token_type == TokenType::LeftParen {
                    // Method call: parse arguments
                    let method_args = match parse_args(lexer) {
                        Ok(a_list) => a_list,
                        Err(err_str) => return Err(err_str),
                    };

                    // Create a new FCall with the method name as identifier and previous result as first arg
                    // This represents: method_name(result, args...)
                    let method_id = Expr::new_parse(NodeType::Identifier(method_name), method_t.clone(), Vec::new());
                    let mut new_params = Vec::new();
                    new_params.push(method_id);
                    new_params.push(result); // Previous call result becomes first argument
                    new_params.extend(method_args.params);

                    // Issue #132: Check for ? after chained method call
                    let method_does_throw = if lexer.peek().token_type == TokenType::QuestionMark {
                        lexer.advance(1)?;
                        true
                    } else {
                        false
                    };
                    result = Expr::new_parse(NodeType::FCall(method_does_throw), method_t, new_params);
                } else {
                    // Bug #32 fix: Field access on expression result (no parentheses)
                    // Collect all field names in the chain until we hit something else
                    let mut field_params: Vec<Expr> = Vec::new();
                    field_params.push(result); // First param is the FCall/expression result
                    field_params.push(Expr::new_parse(NodeType::Identifier(method_name.clone()), method_t.clone(), Vec::new()));

                    // Continue collecting fields until we hit '(' (method call) or something else
                    loop {
                        let peek_after = lexer.peek();
                        if peek_after.token_type == TokenType::Dot {
                            lexer.advance(1)?;
                            let next_field_t = lexer.peek();
                            if next_field_t.token_type != TokenType::Identifier {
                                return Err(next_field_t.error(&lexer.path, &format!("Expected identifier after '.', found '{:?}'", next_field_t.token_type)));
                            }
                            let next_field_name = next_field_t.token_str.clone();
                            lexer.advance(1)?;

                            // Check if this is a method call
                            let check_paren = lexer.peek();
                            if check_paren.token_type == TokenType::LeftParen {
                                // This is a method call on the field chain
                                // Build the Identifier chain for the field access, then wrap in FCall
                                // Bug #32 fix: Use "_" to signal expression-based field access
                                let field_access = Expr::new_parse(
                                    NodeType::Identifier("_".to_string()),
                                    method_t.clone(),
                                    field_params
                                );

                                let method_args = match parse_args(lexer) {
                                    Ok(a_list) => a_list,
                                    Err(err_str) => return Err(err_str),
                                };

                                let method_id = Expr::new_parse(NodeType::Identifier(next_field_name), next_field_t.clone(), Vec::new());
                                let mut new_params = Vec::new();
                                new_params.push(method_id);
                                new_params.push(field_access);
                                new_params.extend(method_args.params);

                                // Issue #132: Check for ? after field chain method call
                                let field_method_does_throw = if lexer.peek().token_type == TokenType::QuestionMark {
                                    lexer.advance(1)?;
                                    true
                                } else {
                                    false
                                };
                                result = Expr::new_parse(NodeType::FCall(field_method_does_throw), next_field_t, new_params);
                                break;
                            } else {
                                // Another field access
                                field_params.push(Expr::new_parse(NodeType::Identifier(next_field_name), next_field_t.clone(), Vec::new()));
                            }
                        } else {
                            // End of chain - create the field access expression
                            // Bug #32 fix: Use "_" as identifier name to signal that
                            // params[0] is an expression (FCall) to evaluate first, then access
                            // the remaining params as fields on its result
                            result = Expr::new_parse(
                                NodeType::Identifier("_".to_string()),
                                method_t.clone(),
                                field_params
                            );
                            break;
                        }
                    }
                }
            }
        }

        return Ok(result);
    }
    return Ok(e);
}

pub fn get_combined_name(path: &str, e: &Expr) -> Result<String, String> {
    let mut to_return = String::new();
    match &e.node_type {
        NodeType::Identifier(id_str_) => {
            to_return.push_str(&id_str_);
            to_return.push_str(".");
        },
        _ => {
            return Err(e.lang_error(path, "parse", "get_combined_name() is to be called with Identifier expressions only"))
        },
    }
    for p in &e.params {
        match &p.node_type {
            NodeType::Identifier(id_str_) => {
                to_return.push_str(&id_str_);
                to_return.push_str(".");
            },
            _ => {
                return Err(e.lang_error(path, "parse", "the params of an identifier expression must be Identifier expressions only"))
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
                NodeType::FCall(_) => return Ok(e),
                NodeType::Identifier(_) => {},
                _ => {
                    return Err(t.lang_error(&lexer.path, "a series of identifiers and dots should have been parsed as identifier or function call"));
                },
            }
            next_t = lexer.peek();
            next_token_type = &next_t.token_type;
            match next_token_type {
                TokenType::Equal => {
                    let name = get_combined_name(&lexer.path, &e)?;
                    return parse_assignment(lexer, &t, &name)
                },
                _ => {
                    return Err(t.lang_error(&lexer.path, "While parsing a '.', this should never happen"));
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
                    return parse_declaration(lexer, false, false, type_name, true)
                }
                TokenType::Equal => {
                    return parse_declaration(lexer, false, false, INFER_TYPE, false)
                },
                _ => {
                    Err(t.error(&lexer.path, &format!("Expected Type or '=' after '{} :' in statement, found '{:?}'.", identifier, next_next_token_type)))
                },
            }

        },
        _ => {
            Err(t.error(&lexer.path, &format!("Expected '(', ':' or '=' after identifier in statement, found '{:?}'.", next_token_type)))
        },
    }
}

fn parse_primary(lexer: &mut Lexer) -> Result<Expr, String> {

    let t = lexer.peek();
    if is_literal(&t) {
        return parse_literal(lexer, &t)
    }
    match &t.token_type {
        TokenType::Func => return parse_func_proc_definition(lexer, FunctionType::FTFunc),
        TokenType::FuncExt => return parse_func_proc_definition(lexer, FunctionType::FTFuncExt),
        TokenType::Macro => return parse_func_proc_definition(lexer, FunctionType::FTMacro),
        TokenType::Proc => return parse_func_proc_definition(lexer, FunctionType::FTProc),
        TokenType::ProcExt => return parse_func_proc_definition(lexer, FunctionType::FTProcExt),
        TokenType::Enum => return enum_definition(lexer),
        TokenType::Struct => return parse_struct_definition(lexer),
        TokenType::Namespace => return Err(t.error(&lexer.path, "Separate 'namespace TypeName {{ }}' blocks are no longer supported. Use 'namespace:' inside the struct/enum body instead.")),
        TokenType::LeftParen => return parse_args(lexer),
        TokenType::Identifier => return parse_primary_identifier(lexer),
        _ => return Err(t.error(&lexer.path, &format!("Expected primary expression, found '{:?}'.", t.token_type))),
    }
}

fn return_statement(lexer: &mut Lexer) -> Result<Expr, String> {
    let initial_current = lexer.current;
    lexer.advance(1)?;
    let mut params : Vec<Expr> = Vec::new();
    // Try to parse first primary expression
    match parse_primary(lexer) {
        Ok(prim) => {
            params.push(prim);
        },
        // No primary expression found, that's okay for return statements
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

fn parse_break_statement(lexer: &mut Lexer) -> Result<Expr, String> {
    let initial_current = lexer.current;
    lexer.advance(1)?; // consume 'break'
    Ok(Expr::new_parse(NodeType::Break, lexer.get_token(initial_current)?.clone(), vec![]))
}

fn parse_continue_statement(lexer: &mut Lexer) -> Result<Expr, String> {
    let initial_current = lexer.current;
    lexer.advance(1)?; // consume 'continue'
    Ok(Expr::new_parse(NodeType::Continue, lexer.get_token(initial_current)?.clone(), vec![]))
}

fn parse_throw_statement(lexer: &mut Lexer) -> Result<Expr, String> {
    let initial_current = lexer.current;
    lexer.advance(1)?;
    let mut params : Vec<Expr> = Vec::new();
    // Parse first primary expression (required for throw)
    let prim = parse_primary(lexer)?;
    params.push(prim);
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
        return Err(t.error(&lexer.path, &format!("Expected '{{' after condition in 'if' statement, found '{:?}'.", t.token_type)));
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
            return Err(t.error(&lexer.path, &format!("Expected '{{' or 'if' after 'else', found '{:?}'.", next.token_type)));
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
        return Err(t.error(&lexer.path, "Expected '{{' after condition in 'while' statement."));
    }
    lexer.advance(1)?;
    let body = match parse_body(lexer, TokenType::RightBrace) {
        Ok(body) => body,
        Err(err_str) => return Err(err_str),
    };
    params.push(body);
    Ok(Expr::new_parse(NodeType::While, lexer.get_token(initial_current)?.clone(), params))
}

// Bug #57 fix: Transform continue statements to include the step expression before continue.
// This ensures the loop variable is incremented/decremented even when continue is used.
// Transforms: continue -> { step_expr; continue }
pub fn transform_continue_with_step(expr: &Expr, step_expr: &Expr) -> Expr {
    match &expr.node_type {
        NodeType::Continue => {
            // Replace continue with { step_expr; continue }
            Expr::new_explicit(
                NodeType::Body,
                vec![step_expr.clone(), expr.clone()],
                expr.line,
                expr.col,
            )
        }
        // Don't recurse into nested loops - their continues are for their own loop
        NodeType::While | NodeType::ForIn(_) => expr.clone(),
        // Recurse into other nodes
        _ => {
            let new_params: Vec<Expr> = expr.params.iter()
                .map(|p| transform_continue_with_step(p, step_expr))
                .collect();
            Expr {
                node_type: expr.node_type.clone(),
                params: new_params,
                line: expr.line,
                col: expr.col,
            }
        }
    }
}

// Helper to desugar range-based for loop to while loop
// Shared by typed (for i: I64 in 0..10) and untyped (for i in 0..10) range loops
fn desugar_range_for(
    loop_var_name: &str,
    var_type: &str,
    start_expr: &Expr,
    end_expr: &Expr,
    body_expr: &Expr,
    initial_token: &Token,
) -> Expr {
    // Check if both bounds are numeric literals for compile-time direction detection
    let start_literal = match &start_expr.node_type {
        NodeType::LLiteral(Literal::Number(s)) => s.parse::<i64>().ok(),
        _ => None,
    };
    let end_literal = match &end_expr.node_type {
        NodeType::LLiteral(Literal::Number(s)) => s.parse::<i64>().ok(),
        _ => None,
    };

    // Determine direction: Some(true) = forward, Some(false) = reverse, None = runtime check
    let is_forward = match (start_literal, end_literal) {
        (Some(start), Some(end)) => Some(start < end),
        _ => None,
    };

    // Declaration with specified type (could be explicit or INFER_TYPE)
    let decl = Declaration {
        name: loop_var_name.to_string(),
        value_type: str_to_value_type(var_type),
        is_mut: true,
        is_copy: false,
        is_own: false,
        default_value: None,
    };
    let decl_expr = Expr::new_parse(NodeType::Declaration(decl), initial_token.clone(), vec![start_expr.clone()]);

    // Helper to create forward while loop
    let make_fwd_while = |body: &Expr| {
        let cond = Expr::new_explicit(
            NodeType::FCall(false),  // Issue #132: lt doesn't throw
            vec![
                Expr::new_parse(
                    NodeType::Identifier(loop_var_name.to_string()),
                    initial_token.clone(),
                    vec![Expr::new_parse(NodeType::Identifier("lt".to_string()), initial_token.clone(), vec![])],
                ),
                end_expr.clone(),
            ],
            initial_token.line, initial_token.col,
        );
        let inc = Expr::new_explicit(
            NodeType::FCall(false),  // Issue #132: inc doesn't throw
            vec![Expr::new_parse(NodeType::Identifier(loop_var_name.to_string()), initial_token.clone(), vec![
                Expr::new_parse(NodeType::Identifier("inc".to_string()), initial_token.clone(), vec![]),
            ])],
            initial_token.line, initial_token.col,
        );
        // Bug #57 fix: Transform continue statements to include increment before continue
        let transformed_body = transform_continue_with_step(body, &inc);
        let mut body_params = transformed_body.params.clone();
        body_params.push(inc.clone());
        let while_body = Expr::new_explicit(NodeType::Body, body_params, body.line, body.col);
        Expr::new_explicit(NodeType::While, vec![cond, while_body], initial_token.line, initial_token.col)
    };

    // Helper to create reverse while loop
    let make_rev_while = |body: &Expr| {
        let cond = Expr::new_explicit(
            NodeType::FCall(false),  // Issue #132: gt doesn't throw
            vec![
                Expr::new_parse(
                    NodeType::Identifier(loop_var_name.to_string()),
                    initial_token.clone(),
                    vec![Expr::new_parse(NodeType::Identifier("gt".to_string()), initial_token.clone(), vec![])],
                ),
                end_expr.clone(),
            ],
            initial_token.line, initial_token.col,
        );
        let dec = Expr::new_explicit(
            NodeType::FCall(false),  // Issue #132: dec doesn't throw
            vec![Expr::new_parse(NodeType::Identifier(loop_var_name.to_string()), initial_token.clone(), vec![
                Expr::new_parse(NodeType::Identifier("dec".to_string()), initial_token.clone(), vec![]),
            ])],
            initial_token.line, initial_token.col,
        );
        // Bug #57 fix: Transform continue statements to include decrement before continue
        let transformed_body = transform_continue_with_step(body, &dec);
        let mut body_params = transformed_body.params.clone();
        body_params.push(dec.clone());
        let while_body = Expr::new_explicit(NodeType::Body, body_params, body.line, body.col);
        Expr::new_explicit(NodeType::While, vec![cond, while_body], initial_token.line, initial_token.col)
    };

    let loop_expr = match is_forward {
        Some(true) => {
            // Compile-time: forward loop only
            make_fwd_while(body_expr)
        }
        Some(false) => {
            // Compile-time: reverse loop only
            make_rev_while(body_expr)
        }
        None => {
            // Runtime: if start < end { forward } else { reverse }
            let fwd_while = make_fwd_while(body_expr);
            let rev_while = make_rev_while(body_expr);
            let direction_cond = Expr::new_explicit(
                NodeType::FCall(false),  // Issue #132: lt doesn't throw
                vec![
                    Expr::new_parse(NodeType::Identifier("lt".to_string()), initial_token.clone(), vec![]),
                    start_expr.clone(),
                    end_expr.clone(),
                ],
                initial_token.line, initial_token.col,
            );
            let fwd_body = Expr::new_explicit(NodeType::Body, vec![fwd_while], initial_token.line, initial_token.col);
            let rev_body = Expr::new_explicit(NodeType::Body, vec![rev_while], initial_token.line, initial_token.col);
            Expr::new_explicit(NodeType::If, vec![direction_cond, fwd_body, rev_body], initial_token.line, initial_token.col)
        }
    };

    Expr::new_explicit(NodeType::Body, vec![decl_expr, loop_expr], initial_token.line, initial_token.col)
}

fn parse_for_statement(lexer: &mut Lexer) -> Result<Expr, String> {
    let initial_token = lexer.peek();
    lexer.advance(1)?; // consume 'for'

    // Expect loop variable name
    let ident_token = lexer.expect(TokenType::Identifier)?;
    // Replace _ with a unique generated name to avoid C redeclaration issues
    let loop_var_name = if ident_token.token_str == "_" {
        next_loop_var()
    } else {
        ident_token.token_str.clone()
    };

    // Check if next token is ':' (type annotation)
    let next_token = lexer.peek();
    if next_token.token_type == TokenType::Colon {
        // Type annotation present: for VAR: TYPE in ...
        lexer.advance(1)?; // consume ':'

        let type_token = lexer.expect(TokenType::Identifier)?;
        let var_type_name = type_token.token_str.clone();

        lexer.expect(TokenType::In)?;

        // Parse expression after 'in' - could be Range or collection
        // Bug #92: Don't use parse_case_expr here because its pattern matching logic
        // interferes with function calls like list_dir(dir)?
        let first_expr = parse_primary(lexer)?;

        // Check if it's a Range expression (primary followed by ..)
        if lexer.peek().token_type == TokenType::DoubleDot {
            // Range-based for with type annotation: for VAR: TYPE in start..end { ... }
            lexer.advance(1)?; // consume ..
            let start_expr = first_expr;
            let end_expr = parse_primary(lexer)?;

            lexer.expect(TokenType::LeftBrace)?;
            let body_expr = parse_body(lexer, TokenType::RightBrace)?;

            // Use shared helper for range desugaring with explicit type
            return Ok(desugar_range_for(&loop_var_name, &var_type_name, &start_expr, &end_expr, &body_expr, &initial_token));
        }

        // Collection-based for: for VAR: TYPE in COLLECTION { ... }
        lexer.expect(TokenType::LeftBrace)?;
        let forin_body_expr = parse_body(lexer, TokenType::RightBrace)?;

        // ForIn node: params[0] = Identifier(var_name), params[1] = collection, params[2] = body
        let var_ident = Expr::new_parse(NodeType::Identifier(loop_var_name), initial_token.clone(), vec![]);

        return Ok(Expr::new_explicit(
            NodeType::ForIn(var_type_name),
            vec![var_ident, first_expr, forin_body_expr],
            initial_token.line,
            initial_token.col,
        ));
    }

    // Range-based for: for VAR in RANGE { ... }
    lexer.expect(TokenType::In)?;

    // Parse the range expression (e.g., 1..10)
    let range_expr = parse_case_expr(lexer)?;
    if range_expr.node_type != NodeType::Range {
        return Err(ident_token.error(&lexer.path, "Expected range expression (start..end) after 'in'. For collection iteration, use 'for VAR: TYPE in COLLECTION'"));
    }
    let start_expr = range_expr.get(0)?.clone();
    let end_expr = range_expr.get(1)?.clone();

    lexer.expect(TokenType::LeftBrace)?;
    let body_expr = parse_body(lexer, TokenType::RightBrace)?;

    // Use shared helper for range desugaring with inferred type
    Ok(desugar_range_for(&loop_var_name, INFER_TYPE, &start_expr, &end_expr, &body_expr, &initial_token))
}

// Helper function to extract full identifier name from an expression
// Handles both simple identifiers and dotted names (represented as FCall)
fn get_full_identifier_name(expr: &Expr) -> Result<String, String> {
    match &expr.node_type {
        NodeType::Identifier(name) => {
            // Check if this is a dotted name: Identifier with params
            // For example, "Color.Green" is Identifier("Color") with params=[Identifier("Green")]
            if expr.params.len() == 1 {
                match &expr.get(0)?.node_type {
                    NodeType::Identifier(param_name) => {
                        return Ok(format!("{}.{}", name, param_name));
                    },
                    _ => {}
                }
            }
            Ok(name.clone())
        }
        NodeType::FCall(_) if expr.params.len() >= 1 => {
            // For FCall, try to extract the function name
            get_full_identifier_name(expr.get(0)?)
        }
        _ => Ok(String::new()),
    }
}

fn parse_case_expr(lexer: &mut Lexer) -> Result<Expr, String> {
    let left = parse_primary(lexer)?;
    let t = lexer.peek();
    if t.token_type == TokenType::DoubleDot {
        lexer.advance(1)?;
        let right = parse_primary(lexer)?;
        return Ok(Expr::new_parse(NodeType::Range, t, vec![left, right]));
    }

    // Check if this is a pattern match: EnumVariant(binding_var)
    // This would have been parsed as FCall with one Identifier parameter
    if matches!(left.node_type, NodeType::FCall(_)) && left.params.len() == 2 {
        // FCall params are: [function_name, arg1, arg2, ...]
        // For pattern matching, we expect: [variant_identifier, binding_identifier]
        // Note: variant_identifier might be a dotted name like "Color.Green" which could be
        // represented as an FCall itself (for the dot access)

        // Get the full variant name (handling dotted names)
        let p0 = left.get(0)?;
        let variant_name = get_full_identifier_name(p0)?;

        let p1 = left.get(1)?;
        match &p1.node_type {
            NodeType::Identifier(binding_var) => {
                // Only treat as a binding variable if it's a simple identifier
                // (no nested params like TTypeDef.TEnumDef)
                if p1.params.is_empty() {
                    // Convert FCall to Pattern
                    let pattern_info = PatternInfo {
                        variant_name: variant_name,
                        binding_var: binding_var.clone(),
                    };
                    return Ok(Expr::new_explicit(
                        NodeType::Pattern(pattern_info),
                        Vec::new(),
                        left.line,
                        left.col
                    ));
                }
                // Otherwise, it's a nested pattern like ValueType.TType(TTypeDef.TEnumDef)
                // Keep it as FCall for now (will be handled by interpreter)
            },
            _ => {}
        }
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
        return Err(t.error(&lexer.path, "Expected '{{' after primary expression in 'switch' statement."));
    }
    lexer.advance(1)?;

    let mut end_found = false;
    let mut seen_default = false;
    while lexer.current < lexer.len() && !end_found {
        let mut next_t = lexer.peek();
        if next_t.token_type != TokenType::Case {
            return Err(next_t.error(&lexer.path, &format!("Expected 'case' in switch, found '{:?}'", next_t.token_type)));
        }
        if seen_default {
            return Err(next_t.error(&lexer.path, "default case must be last in switch"));
        }

        lexer.advance(1)?;
        next_t = lexer.peek();
        if next_t.token_type == TokenType::Colon {
            seen_default = true;
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
            return Err(next_t.error(&lexer.path, &format!("Expected ':' case <primary_expr> in switch, found '{:?}'", next_t.token_type)));
        }

        lexer.advance(1)?;
        next_t = lexer.peek();
        let mut body_params : Vec<Expr> = Vec::new();
        let mut should_continue_parsing = true;
        while lexer.current < lexer.len() && should_continue_parsing {
            if next_t.token_type == TokenType::RightBrace {
                end_found = true;
                lexer.advance(1)?;
                should_continue_parsing = false;
            } else if next_t.token_type == TokenType::Case {
                should_continue_parsing = false;
            } else {
                let stmt = match parse_statement(lexer) {
                    Ok(statement) => statement,
                    Err(error_string) => return Err(error_string),
                };
                body_params.push(stmt);
                next_t = lexer.peek();
            }
        }
        params.push(Expr::new_parse(NodeType::Body, t.clone(), body_params));
    }
    if end_found {
        return Ok(Expr::new_parse(NodeType::Switch, lexer.get_token(initial_current)?.clone(), params))
    }
    return Err(t.error(&lexer.path, "Expected '}}' to end switch."));
}

fn parse_declaration(lexer: &mut Lexer, is_mut: bool, is_copy: bool, explicit_type: &str, has_explicit_type: bool) -> Result<Expr, String> {
    let t = lexer.peek();
    let decl_name = &t.token_str;
    let initial_current = lexer.current;

    lexer.advance(3)?; // skip identifier, colon and equal (or identifier, colon, type)
    if has_explicit_type {
        lexer.advance(1)?; // skip equal after type token (Bug #129: use boolean, not string comparison)
    }

    let mut params : Vec<Expr> = Vec::new();
    params.push(parse_primary(lexer)?);

    let decl = Declaration{name: decl_name.to_string(), value_type: str_to_value_type(explicit_type), is_mut: is_mut, is_copy: is_copy, is_own: false, default_value: None};

    return Ok(Expr::new_parse(NodeType::Declaration(decl), lexer.get_token(initial_current)?.clone(), params))
}

fn parse_mut_declaration(lexer: &mut Lexer) -> Result<Expr, String> {
    let t = lexer.peek();
    let mut next_t = lexer.next()?;
    let mut next_token_type = &next_t.token_type;
    if next_token_type != &TokenType::Identifier {
        return Err(t.error(&lexer.path, &format!("Expected identifier after 'mut', found '{:?}'.", next_token_type)));
    }
    let identifier = &next_t.token_str.to_string();
    lexer.advance(1)?;
    next_t = lexer.next()?;
    next_token_type = &next_t.token_type;
    if next_token_type != &TokenType::Colon {
        return Err(t.error(&lexer.path, &format!("Expected ':' after 'mut {}', found '{:?}'.", identifier, next_token_type)));
    }
    let next_next_t = lexer.peek_ahead(2)?;
    let next_next_token_type = &next_next_t.token_type;
    match next_next_token_type {
        TokenType::Identifier => {
            let type_name = &next_next_t.token_str;
            return parse_declaration(lexer, true, false, type_name, true)
        }
        TokenType::Equal => {
            return parse_declaration(lexer, true, false, INFER_TYPE, false)
        },
        _ => {
            Err(t.error(&lexer.path, &format!("Expected a type identifier or '=' after 'mut {} :' in statement, found '{:?}'.",
                                 identifier, next_next_token_type)))
        },
    }
}

fn parse_statement(lexer: &mut Lexer) -> Result<Expr, String> {
    let t = lexer.peek();
    match &t.token_type {
        TokenType::Return => return return_statement(lexer),
        TokenType::Throw => return parse_throw_statement(lexer),
        TokenType::Break => return parse_break_statement(lexer),
        TokenType::Continue => return parse_continue_statement(lexer),
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
        TokenType::Namespace => return Err(t.error(&lexer.path, "Separate 'namespace TypeName {{ }}' blocks are no longer supported. Use 'namespace:' inside the struct/enum body instead.")),
        _ => {
            Err(t.error(&lexer.path, &format!("Expected statement, found {:?}.", t.token_type)))
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
        } else {
            let stmt = match parse_statement(lexer) {
                Ok(statement) => statement,
                Err(error_string) => return Err(error_string),
            };
            params.push(stmt);
        }
    }
    if end_found {
        return Ok(Expr::new_parse(NodeType::Body, lexer.get_token(initial_current)?.clone(), params))
    }
    return Err(t.error(&lexer.path, &format!("Expected '{:?}' to end body.", end_token))); // use last valid token
}

// Issue #174: Post-parse pass to split inline namespace members from StructDef/EnumDef params
// into synthetic NamespaceDef nodes. This keeps SStructDef/SEnumDef unchanged (no new fields).
fn split_inline_namespaces(ast: &Expr) -> Expr {
    if let NodeType::Body = &ast.node_type {
        let mut new_params: Vec<Expr> = Vec::new();
        for child in &ast.params {
            // Check if this is a Declaration whose value is a StructDef with namespace params
            if let NodeType::Declaration(decl) = &child.node_type {
                if child.params.len() == 1 {
                    // Issue #174: Extract inline namespace from StructDef or EnumDef params
                    let has_ns_params = !child.params[0].params.is_empty();
                    let is_struct_or_enum = matches!(&child.params[0].node_type, NodeType::StructDef(_) | NodeType::EnumDef(_));
                    if has_ns_params && is_struct_or_enum {
                        // Extract namespace members from params
                        let ns_stmts = &child.params[0].params;
                        let mut ns_members = Vec::new();
                        let mut ns_default_values = HashMap::new();
                        for stmt in ns_stmts {
                            match &stmt.node_type {
                                NodeType::Declaration(ns_decl) => {
                                    ns_members.push(ns_decl.clone());
                                    if stmt.params.len() == 1 {
                                        if let Some(val) = stmt.params.get(0) {
                                            ns_default_values.insert(ns_decl.name.clone(), val.clone());
                                        }
                                    }
                                },
                                NodeType::Assignment(name) => {
                                    if stmt.params.len() == 1 {
                                        let val = stmt.params.get(0).unwrap();
                                        let ns_decl = Declaration {
                                            name: name.clone(),
                                            value_type: ValueType::TCustom(INFER_TYPE.to_string()),
                                            is_mut: false,
                                            is_copy: false,
                                            is_own: false,
                                            default_value: None,
                                        };
                                        ns_members.push(ns_decl);
                                        ns_default_values.insert(name.clone(), val.clone());
                                    }
                                },
                                _ => {}
                            }
                        }
                        // Emit StructDef/EnumDef without namespace params
                        let clean_type_def = Expr::new_explicit(
                            child.params[0].node_type.clone(),
                            vec![],
                            child.params[0].line,
                            child.params[0].col,
                        );
                        let clean_decl = Expr::new_explicit(
                            child.node_type.clone(),
                            vec![clean_type_def],
                            child.line,
                            child.col,
                        );
                        new_params.push(clean_decl);
                        // Emit synthetic NamespaceDef
                        if !ns_members.is_empty() {
                            let ns_def = SNamespaceDef {
                                type_name: decl.name.clone(),
                                members: ns_members,
                                default_values: ns_default_values,
                            };
                            let ns_expr = Expr::new_explicit(
                                NodeType::NamespaceDef(ns_def),
                                vec![],
                                child.line,
                                child.col,
                            );
                            new_params.push(ns_expr);
                        }
                        continue;
                    }
                }
            }
            new_params.push(child.clone());
        }
        return Expr::new_explicit(ast.node_type.clone(), new_params, ast.line, ast.col);
    }
    ast.clone()
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
        let t = lexer.get_token(lexer.current)?;
        return Err(t.error(&lexer.path, &format!("Total unparsed tokens: {}/{}", unparsed_tokens, lexer_len)));
    }
    // Issue #174: Split inline namespace members into synthetic NamespaceDef nodes
    let e = split_inline_namespaces(&e);
    return Ok(e)
}
