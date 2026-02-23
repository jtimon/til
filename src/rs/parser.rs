use std::collections::HashMap;
use std::sync::atomic::{AtomicUsize, Ordering};

pub use crate::rs::ast::*;
use rs::lexer::{TokenType, Token, Lexer};

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

pub fn value_type_to_str(arg_type: &ValueType) -> String {
    match arg_type {
        ValueType::TType(TTypeDef::TEnumDef) => "enum".to_string(),
        ValueType::TType(TTypeDef::TStructDef) => "struct".to_string(),
        ValueType::TType(TTypeDef::TFuncSig) => "FunctionSig".to_string(),
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
        "FunctionSig" => ValueType::TType(TTypeDef::TFuncSig),
        type_name => ValueType::TCustom(type_name.to_string()),
    }
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
}

fn is_literal(t: &Token) -> bool {
    return match t.token_type {
        TokenType::String => true,
        TokenType::Number => true,
        _ => false,
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
                    // Issue #91: Lookahead to distinguish named param (name: Type)
                    // from type-only param (Type) in normal form like func(I64, I64)
                    let lookahead = lexer.peek_ahead(1)?;
                    if lookahead.token_type == TokenType::Colon {
                        // Named param: this identifier is the parameter name
                        arg_name = t.token_str.to_string();
                        expect_colon = true;
                        expect_name = false;
                    } else {
                        // Type-only param (normal form): no name, just the type
                        let arg_type = str_to_value_type(&t.token_str);
                        lexer.advance(1)?;
                        t = lexer.peek();
                        args.push(Declaration {
                            name: "".to_string(),
                            value_type: arg_type,
                            is_mut: false,
                            is_copy: false,
                            is_own: false,
                            default_value: None,
                        });
                        expect_comma = true;
                        expect_name = false;
                        continue;
                    }
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
    // Issue #91: Don't consume '=' (new syntax: `func() = { body }`)
    if t.token_type == TokenType::Equal {
        return Ok(return_types);
    }
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
            // Issue #91: new syntax `name : func(...) returns T = { body }`
            TokenType::Equal => {
                end_found = true;
                // Don't advance - parse_func_proc_definition handles '='
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
        return Err(t.error(&lexer.path, "Expected '{{', '=' or 'throws' after return values."));
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
            // Issue #91: new syntax `name : func(...) throws E = { body }`
            TokenType::Equal => {
                end_found = true;
                // Don't advance - parse_func_proc_definition handles '='
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
        return Err(t.error(&lexer.path, "Expected '{{' or '=' after throw values."));
    }
}

// Issue #91: Parse binding tuple `(a, b, c)` for normal form function definitions
// e.g. `func(I64, I64) returns I64 = (a, b) { body }`
fn parse_binding_tuple(lexer: &mut Lexer) -> Result<Vec<String>, String> {
    lexer.expect(TokenType::LeftParen)?;
    let mut names: Vec<String> = Vec::new();
    let mut expect_comma = false;
    loop {
        let t = lexer.peek();
        match t.token_type {
            TokenType::RightParen => {
                lexer.advance(1)?;
                return Ok(names);
            },
            TokenType::Comma => {
                if !expect_comma {
                    return Err(t.error(&lexer.path, "Unexpected ',' in binding tuple."));
                }
                lexer.advance(1)?;
                expect_comma = false;
            },
            TokenType::Identifier => {
                if expect_comma {
                    return Err(t.error(&lexer.path, &format!("Expected ',' before '{}' in binding tuple.", t.token_str)));
                }
                names.push(t.token_str.clone());
                lexer.advance(1)?;
                expect_comma = true;
            },
            _ => {
                return Err(t.error(&lexer.path, &format!("Expected identifier or ')' in binding tuple, found '{:?}'.", t.token_type)));
            },
        }
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
    let mut args = parse_func_proc_args(lexer)?;
    let return_types = func_proc_returns(lexer)?;
    let throw_types = func_proc_throws(lexer)?;

    // Bug #146: Reset loop var counter per-function for deterministic output
    let saved_loop_counter = save_loop_var_counter();
    reset_loop_var_counter();

    // Issue #91: Check for new syntax `= (binding) { body }` or `= { body }` vs current `{ body }`
    // After returns/throws, lexer is either past '{' (current) or at '=' (new)
    let next = lexer.peek();
    let body = if next.token_type == TokenType::Equal {
        lexer.advance(1)?; // consume '='
        let after_eq = lexer.peek();
        if after_eq.token_type == TokenType::LeftParen {
            // Normal form binding tuple: = (a, b) { body }
            let binding_names = parse_binding_tuple(lexer)?;
            if binding_names.len() != args.len() {
                restore_loop_var_counter(saved_loop_counter);
                return Err(after_eq.error(&lexer.path, &format!(
                    "Binding tuple has {} names but signature has {} parameters.",
                    binding_names.len(), args.len())));
            }
            for (i, name) in binding_names.iter().enumerate() {
                if !args[i].name.is_empty() {
                    restore_loop_var_counter(saved_loop_counter);
                    return Err(after_eq.error(&lexer.path, &format!(
                        "Parameter '{}' already has a name from signature; cannot also have binding name '{}'.",
                        args[i].name, name)));
                }
                args[i].name = name.clone();
            }
            // Expect '{' after binding tuple
            let brace = lexer.peek();
            if brace.token_type != TokenType::LeftBrace {
                restore_loop_var_counter(saved_loop_counter);
                return Err(brace.error(&lexer.path, "Expected '{{' after binding tuple in function definition"));
            }
            lexer.advance(1)?; // consume '{'
            match parse_body(lexer, TokenType::RightBrace) {
                Ok(body) => {
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
            }
        } else if after_eq.token_type == TokenType::LeftBrace {
            // Sugar form: = { body } — names already in args from signature
            // Validate: all params must have names (no type-only params without binding)
            for arg in &args {
                if arg.name.is_empty() {
                    restore_loop_var_counter(saved_loop_counter);
                    return Err(after_eq.error(&lexer.path,
                        "Type-only parameters require a binding tuple: = (name, ...) {{ body }}"));
                }
            }
            lexer.advance(1)?; // consume '{'
            match parse_body(lexer, TokenType::RightBrace) {
                Ok(body) => {
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
            }
        } else {
            restore_loop_var_counter(saved_loop_counter);
            return Err(after_eq.error(&lexer.path, "Expected '{{' or '(' after '=' in function definition"));
        }
    } else {
        // Current syntax: '{' already consumed by returns/throws
        match parse_body(lexer, TokenType::RightBrace) {
            Ok(body) => {
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
        }
    };

    restore_loop_var_counter(saved_loop_counter);

    // Issue #91: Split args into sig (types+modifiers) and arg_names
    let arg_names: Vec<String> = args.iter().map(|a| a.name.clone()).collect();
    let func_def = FuncDef{
        sig: FuncSig {
            function_type: function_type,
            args: args,
            return_types: return_types,
            throw_types: throw_types,
        },
        arg_names: arg_names,
        body: body,
        source_path: lexer.path.clone(),
    };
    let params : Vec<Expr> = Vec::new();
    let e = Expr::new_parse(NodeType::FuncDef(func_def), t.clone(), params);
    Ok(e)
}

// Issue #105: Build NamespaceDef from collected namespace statements
fn build_namespace_from_stmts(namespace_stmts: Vec<Expr>) -> NamespaceDef {
    let mut ns_members = Vec::new();
    let mut ns_default_values = HashMap::new();
    for stmt in &namespace_stmts {
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
    NamespaceDef {
        members: ns_members,
        default_values: ns_default_values,
    }
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
    let ns = build_namespace_from_stmts(namespace_stmts);
    return Ok(Expr::new_parse(NodeType::EnumDef(EnumDef{variants, methods: crate::rs::ordered_map::OrderedMap::new(), ns}), lexer.get_token(initial_current)?.clone(), vec![]));
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
                // Issue #105: allow comma-separated fields in inline struct definitions
                if lexer.current < lexer.len() && lexer.peek().token_type == TokenType::Comma {
                    lexer.advance(1)?;
                }
            }
        }
    }
    if !end_found {
        return Err(t.error(&lexer.path, "Expected '}}' to end struct definition."));
    }

    let ns = build_namespace_from_stmts(namespace_stmts);
    return Ok(Expr::new_parse(NodeType::StructDef(StructDef{members: members, default_values: default_values, ns}),
                              t.clone(), vec![]));
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
        // Issue #180: ! is a synonym for ? (panic on throw, desugared later)
        let does_throw = if lexer.peek().token_type == TokenType::QuestionMark || lexer.peek().token_type == TokenType::ExclamationMark {
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
                    // Issue #180: ! is a synonym for ?
                    let method_does_throw = if lexer.peek().token_type == TokenType::QuestionMark || lexer.peek().token_type == TokenType::ExclamationMark {
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
                                // Issue #180: ! is a synonym for ?
                                let field_method_does_throw = if lexer.peek().token_type == TokenType::QuestionMark || lexer.peek().token_type == TokenType::ExclamationMark {
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
                    // Issue #91: Allow ':= func(...)' for function signature definitions
                    // (e.g., BinaryOp := func(I64, I64) returns I64 {})
                    // Regular functions use 'name : func(...) = { body }' syntax.
                    return parse_declaration(lexer, false, false, INFER_TYPE, false)
                },
                // Issue #91: name : func(...) = { body }
                TokenType::Func | TokenType::Proc | TokenType::FuncExt
                | TokenType::ProcExt | TokenType::Macro => {
                    let func_type = match next_next_token_type {
                        TokenType::Func => FunctionType::FTFunc,
                        TokenType::Proc => FunctionType::FTProc,
                        TokenType::FuncExt => FunctionType::FTFuncExt,
                        TokenType::ProcExt => FunctionType::FTProcExt,
                        TokenType::Macro => FunctionType::FTMacro,
                        _ => unreachable!(),
                    };
                    lexer.advance(2)?; // past name and colon, now at func/proc
                    let func_expr = parse_func_proc_definition(lexer, func_type)?;
                    let decl = Declaration{name: identifier.to_string(), value_type: str_to_value_type(INFER_TYPE), is_mut: false, is_copy: false, is_own: false, default_value: None};
                    return Ok(Expr::new_parse(NodeType::Declaration(decl), t.clone(), vec![func_expr]))
                },
                _ => {
                    Err(t.error(&lexer.path, &format!("Expected Type, '=' or func/proc after '{} :' in statement, found '{:?}'.", identifier, next_next_token_type)))
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
        TokenType::Struct => {
            let struct_expr = parse_struct_definition(lexer)?;
            // Issue #105: anonymous instantiation - struct { ... }(args)
            if lexer.peek().token_type == TokenType::LeftParen {
                let arg_list = parse_args(lexer)?;
                let mut params = Vec::new();
                params.push(struct_expr);
                params.extend(arg_list.params);
                return Ok(Expr::new_parse(NodeType::FCall(false), t.clone(), params));
            }
            return Ok(struct_expr);
        },
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
    let start_expr = range_expr.params.get(0).unwrap().clone();
    let end_expr = range_expr.params.get(1).unwrap().clone();

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
                match &expr.params.get(0).unwrap().node_type {
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
            get_full_identifier_name(expr.params.get(0).unwrap())
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
        let p0 = left.params.get(0).unwrap();
        let variant_name = get_full_identifier_name(p0)?;

        let p1 = left.params.get(1).unwrap();
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

// Issue #91: Check if the current position starts a binding-tuple-body pattern: (ident, ...) {
fn is_binding_tuple_body(lexer: &Lexer) -> bool {
    let mut offset = 1; // skip past '('
    let mut depth = 1;
    loop {
        let t = match lexer.peek_ahead(offset) {
            Ok(t) => t,
            Err(_) => return false,
        };
        match t.token_type {
            TokenType::LeftParen => { depth += 1; },
            TokenType::RightParen => {
                depth -= 1;
                if depth == 0 {
                    // Check if token after ')' is '{'
                    return match lexer.peek_ahead(offset + 1) {
                        Ok(next) => next.token_type == TokenType::LeftBrace,
                        Err(_) => false,
                    };
                }
            },
            TokenType::Identifier | TokenType::Comma => {},
            _ => return false,
        }
        offset += 1;
    }
}

fn parse_declaration(lexer: &mut Lexer, is_mut: bool, is_copy: bool, explicit_type: &str, has_explicit_type: bool) -> Result<Expr, String> {
    let t = lexer.peek();
    let decl_name = &t.token_str;
    let initial_current = lexer.current;

    lexer.advance(3)?; // skip identifier, colon and equal (or identifier, colon, type)
    if has_explicit_type {
        lexer.advance(1)?; // skip equal after type token (Bug #129: use boolean, not string comparison)
    }

    // Issue #91: Detect binding-tuple-body pattern: name : TypeName = (a, b) { body }
    // This creates a FuncDef with arg names from the binding tuple and inferred types.
    if has_explicit_type {
        let next_t = lexer.peek();
        if next_t.token_type == TokenType::LeftParen && is_binding_tuple_body(lexer) {
            let binding_names = parse_binding_tuple(lexer)?;
            let brace = lexer.peek();
            if brace.token_type != TokenType::LeftBrace {
                return Err(brace.error(&lexer.path, "Expected '{' after binding tuple in function declaration"));
            }
            lexer.advance(1)?; // consume '{'
            let body = parse_body(lexer, TokenType::RightBrace)?;
            // Issue #91: Binding tuple form - arg names come from binding, types inferred later
            let sig_args: Vec<Declaration> = binding_names.iter().map(|n| {
                Declaration { name: n.clone(), value_type: str_to_value_type(INFER_TYPE), is_mut: false, is_copy: false, is_own: false, default_value: None }
            }).collect();
            let func_def = FuncDef {
                sig: FuncSig {
                    function_type: FunctionType::FTFunc,
                    args: sig_args,
                    return_types: Vec::new(),
                    throw_types: Vec::new(),
                },
                arg_names: binding_names,
                body: body.params,
                source_path: lexer.path.clone(),
            };
            let func_expr = Expr::new_parse(NodeType::FuncDef(func_def), t.clone(), Vec::new());
            let decl = Declaration{name: decl_name.to_string(), value_type: str_to_value_type(explicit_type), is_mut: is_mut, is_copy: is_copy, is_own: false, default_value: None};
            return Ok(Expr::new_parse(NodeType::Declaration(decl), lexer.get_token(initial_current)?.clone(), vec![func_expr]));
        }
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
            // Issue #91: Allow ':= func(...)' for function signature definitions
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
// into synthetic NamespaceDef nodes. This keeps StructDef/EnumDef unchanged (no new fields).
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
    return Ok(e)
}
