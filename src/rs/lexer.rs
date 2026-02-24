// Bug #141: Separate output directories for rstil vs til to prevent race conditions
pub const LANG_NAME: &str = "rs";

#[derive(Debug, Clone, PartialEq)]
pub enum TokenType {
    // basic
    Eof,

    // Single-character tokens.
    Minus, Plus, Slash, Star,
    LeftParen, RightParen, LeftBrace, RightBrace, LeftBracket, RightBracket,
    Comma, Colon,

    // One or two character tokens.
    Dot, DoubleDot,
    QuestionMark, ExclamationMark,
    Equal, EqualEqual, NotEqual,
    Greater, GreaterEqual,
    Lesser, LesserEqual,
    // Semicolons are skipped by lexer (treated as whitespace)

    // Literals.
    Identifier, String, Number,

    // Reserved words:
    Mut, Copy, Own,

    // type definition
    Struct, Enum, Namespace,
    // function definition
    Returns, Throws,
    // flow control
    If, Else,
    While, For, In,
    Match, Switch, Default, Case,
    Return, Throw,
    Catch,
    Break, Continue,
    Defer,

    // Special in this language:
    Mode,
    Func, Proc, Macro,
    FuncExt, ProcExt,

    // Errors
    Const, Var,
    Fn, Function,
    Try,
    Let, Class,
    Invalid,
    UnterminatedString,
    UnterminatedComment,
}

#[derive(Debug, Clone, PartialEq)]
pub struct Token {
    pub token_type: TokenType,
    pub token_str: String,
    pub line: usize,
    pub col: usize,
}

impl Token {
    pub fn lang_error(self: &Token, path: &str, msg: &str) -> String {
        return format!("{}:{}:{}: parse ERROR: {}\nExplanation: This is not your fault as a user, this is a bug in the language.",
                 path, self.line, self.col, msg);
    }

    #[allow(dead_code)] // Kept for consistency with Expr.todo_error
    pub fn todo_error(self: &Token, path: &str, msg: &str) -> String {
        return format!("{}:{}:{}: parse ERROR: {}\nExplanation: Not implemented yet, this is a missing feature in the language.",
                 path, self.line, self.col, msg);
    }

    pub fn error(self: &Token, path: &str, msg: &str) -> String {
        return format!("{}:{}:{}: parse ERROR: {}", path, self.line, self.col, msg);
    }
}

pub struct Lexer {
    pub path: String,
    tokens: Vec<Token>,
    pub current: usize,
}

impl Lexer {
    pub fn new(source: String) -> Self {
        return Self{path: "<test>".to_string(), tokens: scan_tokens(source), current: 0};
    }

    pub fn len(self: &Lexer) -> usize {
        return self.tokens.len();
    }

    pub fn is_eof(&self, offset: usize) -> bool {
        let index = self.current + offset;
        if index >= self.tokens.len() {
            return true;
        }
        return self.tokens[index].token_type == TokenType::Eof
    }

    pub fn get_token(&self, i: usize) -> Result<&Token, String> {
        match self.tokens.get(i) {
            Some(t) => Ok(t),
            None => {
                let err_token = self.peek();
                return Err(err_token.lang_error(&self.path, &format!("Token in pos {} is out of bounds", i)))
            },
        }
    }

    pub fn peek(&self) -> Token {
        return self.tokens[self.current].clone()
    }

    pub fn previous(&self) -> Result<Token, String> {
        if self.current == 0 {
            let err_token1 = self.peek();
            return Err(err_token1.lang_error(&self.path, "No previous token (at position 0)"));
        }
        if self.current - 1 >= self.tokens.len() {
            let err_token2 = self.peek();
            return Err(err_token2.lang_error(&self.path, "Previous token is out of bounds"));
        }
        return Ok(self.tokens[self.current - 1].clone());
    }

    pub fn advance(&mut self, count: usize) -> Result<(), String> {
        if self.current + count > self.tokens.len() {
            let err_token = self.peek();
            return Err(err_token.lang_error(&self.path, &format!("Attempt to advance by {} from {} would exceed bounds ({} tokens total)",
                                             count, self.current, self.tokens.len())));
        }
        self.current += count;
        return Ok(());
    }

    pub fn peek_ahead(&self, offset: usize) -> Result<Token, String> {
        let peek_idx = self.current + offset;
        if peek_idx >= self.tokens.len() {
            let err_token = self.peek();
            return Err(err_token.lang_error(&self.path, &format!("Peek ahead by {} from {} is out of bounds", offset, self.current)));
        }
        return Ok(self.tokens[peek_idx].clone());
    }

    pub fn next(&self) -> Result<Token, String> {
        return self.peek_ahead(1)
    }

    pub fn expect(&mut self, expected: TokenType) -> Result<Token, String> {
        let token = self.peek();
        if token.token_type == expected {
            self.advance(1)?; // consume the token
            Ok(token)
        } else {
            Err(token.lang_error(&self.path, &format!("Expected token '{}', but found '{}'",
                token_type_to_str(&expected), token.token_str)))
        }
    }

}

fn token_type_to_str(tt: &TokenType) -> &'static str {
    match tt {
        TokenType::If => "if",
        TokenType::Else => "else",
        TokenType::While => "while",
        TokenType::For => "for",
        TokenType::In => "in",
        TokenType::Return => "return",
        TokenType::Throw => "throw",
        TokenType::Catch => "catch",
        TokenType::Break => "break",
        TokenType::Continue => "continue",
        TokenType::Struct => "struct",
        TokenType::Enum => "enum",
        TokenType::Namespace => "namespace",
        TokenType::Mode => "mode",
        TokenType::Func => "func",
        TokenType::Proc => "proc",
        TokenType::Macro => "macro",
        TokenType::FuncExt => "ext_func",
        TokenType::ProcExt => "ext_proc",
        TokenType::Returns => "returns",
        TokenType::Throws => "throws",
        TokenType::Match => "match",
        TokenType::Switch => "switch",
        TokenType::Default => "default",
        TokenType::Case => "case",
        TokenType::Mut => "mut",
        TokenType::Copy => "copy",
        TokenType::Own => "own",
        TokenType::LeftParen => "(",
        TokenType::RightParen => ")",
        TokenType::LeftBrace => "{",
        TokenType::RightBrace => "}",
        TokenType::LeftBracket => "[",
        TokenType::RightBracket => "]",
        TokenType::Comma => ",",
        TokenType::Dot => ".",
        TokenType::DoubleDot => "..",
        TokenType::QuestionMark => "?",
        TokenType::Colon => ":",
        TokenType::Equal => "=",
        TokenType::EqualEqual => "==",
        TokenType::ExclamationMark => "!",
        TokenType::NotEqual => "!=",
        TokenType::Lesser => "<",
        TokenType::LesserEqual => "<=",
        TokenType::Greater => ">",
        TokenType::GreaterEqual => ">=",
        TokenType::Plus => "+",
        TokenType::Minus => "-",
        TokenType::Star => "*",
        TokenType::Slash => "/",
        TokenType::Identifier => "identifier",
        TokenType::String => "string",
        TokenType::Number => "number",
        TokenType::Eof => "eof",
        _ => "invalid",
    }
}

fn is_digit(source: &str, pos: usize) -> bool {
    match source.as_bytes().get(pos).copied() {
        Some(b'0'..=b'9') => true,
        _ => false,
    }
}

fn is_id_start(source: &str, pos: usize) -> bool {
    match source.as_bytes().get(pos).copied() {
        Some(b'a'..=b'z') | Some(b'A'..=b'Z') | Some(b'_') => true,
        _ => false,
    }
}

fn scan_reserved_words(identifier: &str) -> TokenType {
    match identifier {
        "mode" => TokenType::Mode,

        // declaration/arg modifiers
        "mut" => TokenType::Mut,
        "copy" => TokenType::Copy,
        "own" => TokenType::Own,

        // core data types
        "enum" => TokenType::Enum,
        "struct" => TokenType::Struct,
        "namespace" => TokenType::Namespace,

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
        "for" => TokenType::For,
        "in" => TokenType::In,
        "switch" => TokenType::Switch,
        "match" => TokenType::Match, // TODO like switch but special for declarations/assignments
        "case" => TokenType::Case,
        "default" => TokenType::Default, // TODO currently using "case:", but "default:" is more traditional, grepable and overt
        "return" => TokenType::Return,
        "throw" => TokenType::Throw, // TODO
        // TODO throw should just act as a return that gets post-processed by the next catch or rethrown
        "catch" => TokenType::Catch,
        "break" => TokenType::Break,
        "continue" => TokenType::Continue,
        "defer" => TokenType::Defer,

        // Reserved forbidden/illegal words (intentionally unsupported reserved words)
        // TODO intentionally unsupport more reserved words
        // TODO nicer messages for forbidden words
        "fn" => TokenType::Fn,
        "function" => TokenType::Function,
        "try" => TokenType::Try, // TIL uses catch without try (try is forbidden for users from other languages)
        "let" => TokenType::Let,
        "class" => TokenType::Class,
        "global" => TokenType::Invalid, // just use mut declaration in the root of the file, but they're not allowed in all modes
        // const/vars are the most abstract types, you can't even explicitly declare them
        "const" => TokenType::Const,
        "var" => TokenType::Var,

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
    let mut start_line_pos: isize = -1;

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
            scan_push_token(&mut tokens, TokenType::Number, &source[start..pos], line, (start as isize - start_line_pos) as usize);
        } else {
            let mut should_process_token = true;

            let token_type = match &source[pos..pos+1] {
                // chars to ignore in this language (increment pos, no token, continue loop):
                " " => { pos += 1; should_process_token = false; TokenType::Invalid },
                "\r" => { pos += 1; should_process_token = false; TokenType::Invalid },
                "\t" => { pos += 1; should_process_token = false; TokenType::Invalid },
                "\n" => {
                    pos += 1;
                    line = line + 1;
                    start_line_pos = (pos - 1) as isize;
                    should_process_token = false;
                    TokenType::Invalid
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

                // Issue #132: Question mark for throwing function calls
                "?" => TokenType::QuestionMark,

                // reserved for two chars in a row
                "." => if &source[pos+1..pos+2] == "." { pos += 1; TokenType::DoubleDot } else { TokenType::Dot },
                "=" => if &source[pos+1..pos+2] == "=" { pos += 1; TokenType::EqualEqual } else { TokenType::Equal },
                "<" => if &source[pos+1..pos+2] == "=" { pos += 1; TokenType::LesserEqual } else { TokenType::Lesser },
                ">" => if &source[pos+1..pos+2] == "=" { pos += 1; TokenType::GreaterEqual } else { TokenType::Greater },
                "!" => if &source[pos+1..pos+2] == "=" { pos += 1; TokenType::NotEqual } else { TokenType::ExclamationMark },

                // Semicolons are completely optional - skip any number of them
                ";" => {
                    pos += 1; // Skip the first semicolon
                    while pos < eof_pos && &source[pos..pos+1] == ";" {
                        pos += 1;
                    }
                    should_process_token = false;
                    TokenType::Invalid
                },

                // comments:
                "#" => {
                    pos += 1;
                    while pos + 1 < eof_pos && &source[pos..pos+1] != "\n" {
                        pos += 1;
                    }
                    should_process_token = false;
                    TokenType::Invalid
                },
                "/" => match &source[pos+1..pos+2] {
                    "/" => {
                        pos += 1;
                        while pos + 1 < eof_pos && &source[pos..pos+1] != "\n" {
                            pos += 1;
                        }
                        should_process_token = false;
                        TokenType::Invalid
                    },
                    "*" => {
                        pos += 2;
                        let mut depth = 1;
                        let mut should_continue_parsing = true;
                        while pos < eof_pos - 1 && should_continue_parsing {
                            if &source[pos..pos+2] == "/*" {
                                depth += 1;
                                pos += 2;
                            } else if &source[pos..pos+2] == "*/" {
                                depth -= 1;
                                pos += 2;
                                if depth == 0 {
                                    should_continue_parsing = false;
                                }
                            } else {
                                if &source[pos..pos+1] == "\n" {
                                    line += 1;
                                    start_line_pos = pos as isize;
                                }
                                pos += 1;
                            }
                        }
                        if depth > 0 {
                            scan_push_token(&mut tokens, TokenType::UnterminatedComment, "/*", line, (pos as isize - start_line_pos) as usize);
                        }
                        should_process_token = false;
                        TokenType::Invalid
                    },
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
                                match source.as_bytes().get(pos).copied() {
                                    Some(ch) => {
                                        lit_string.push(ch as char);
                                    },
                                    None => {}
                                }
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
                                // TODO print some warning with unkown escaped characters?
                                lit_string.push('\\');
                                match source.as_bytes().get(pos).copied() {
                                    Some(ch) => {
                                        lit_string.push(ch as char);
                                    },
                                    None => {}
                                }
                            }
                        } else {
                            match source.as_bytes().get(pos).copied() {
                                Some(ch) => {
                                    lit_string.push(ch as char);
                                },
                                None => {}
                            }
                        }
                        pos += 1;
                    }

                    if pos >= eof_pos {
                        TokenType::UnterminatedString
                    } else {
                        scan_push_token(&mut tokens, TokenType::String, &lit_string, line, (start as isize - start_line_pos) as usize);
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
            if should_process_token && token_type != TokenType::String {
                scan_push_token(&mut tokens, token_type, &source[start..pos + 1], line, (start as isize - start_line_pos) as usize);
            }
            if should_process_token {
                pos += 1;
            }
        } // else
    } // while

    scan_push_token(&mut tokens, TokenType::Eof, "End of file", line, 0);
    return tokens
}

fn print_lex_error(path: &String, t: &Token, errors_found: &mut usize, msg: &str) {
    println!("{}:{}:{}: Lexical error {}: {}. Offending symbol: '{}'",
             path, t.line, t.col, *errors_found, msg, t.token_str);
    *errors_found += 1;
}

fn build_var_suggestion(tokens: &Vec<Token>, var_index: usize) -> String {
    // Check if pattern is: var <identifier> = <value>
    if var_index + 3 < tokens.len() {
        let ident_token = &tokens[var_index + 1];
        let equals_token = &tokens[var_index + 2];
        let value_token = &tokens[var_index + 3];

        if ident_token.token_type == TokenType::Identifier
            && equals_token.token_type == TokenType::Equal {
            return format!("Suggestion: mut {} := {}",
                          ident_token.token_str,
                          value_token.token_str);
        }
    }
    return "Suggestion: use 'mut' instead".to_string();
}

pub fn print_lex_errors(tokens: &Vec<Token>, path: &String) -> usize {
    let mut errors_found = 0;
    for (index, t) in tokens.iter().enumerate() {
        print_if_lex_error(path, tokens, index, t, &mut errors_found);
    }
    return errors_found;
}

fn print_if_lex_error(path: &String, tokens: &Vec<Token>, index: usize, t: &Token, errors_found: &mut usize) {
    match t.token_type {
        TokenType::Invalid => {
            print_lex_error(path, t, errors_found, "Invalid character");
        },
        TokenType::UnterminatedString => {
            print_lex_error(path, t, errors_found, "Unterminated Str\nSuggestion: add missing '\"'");
        },
        TokenType::UnterminatedComment => {
            print_lex_error(path, t, errors_found, "Unterminated comment\nSuggestion: add missing '*/'");
        }
        TokenType::Const => {
            print_lex_error(path, t, errors_found, "No need to use 'const', everything is const by default unless 'mut' is used");
        },
        TokenType::Var => {
            let suggestion = build_var_suggestion(tokens, index);
            print_lex_error(path, t, errors_found, &format!("Keyword 'var' is not supported\n{}", suggestion));
        },
        TokenType::Fn => {
            print_lex_error(path, t, errors_found, "Keyword 'fn' is not supported\nSuggestion: use 'func' or 'proc' instead");
        },
        TokenType::Function => {
            print_lex_error(path, t, errors_found, "Keyword 'function' is not supported\nSuggestion: use 'func' or 'proc' instead");
        },
        TokenType::Try => {
            print_lex_error(path, t, errors_found, "Keyword 'try' is not supported\nSuggestion: TIL uses 'catch' blocks without 'try' (just use throw/catch)");
        },
        TokenType::Let => {
            print_lex_error(path, t, errors_found, "Keyword 'let' is not supported\nSuggestion: use ':=' for declaration");
        },
        TokenType::Class => {
            print_lex_error(path, t, errors_found, "Keyword 'class' is not supported\nSuggestion: use 'struct' instead");
        },
        TokenType::Plus => {
            print_lex_error(path, t, errors_found, "Operator '+' is not supported yet\nSuggestion: use core func 'add' instead");
        },
        TokenType::Minus => {
            print_lex_error(path, t, errors_found, "Operator '-' is not supported yet\nSuggestion: use core func 'sub' instead");
        },
        TokenType::Star => {
            print_lex_error(path, t, errors_found, "Operator '*' is not supported yet\nSuggestion: use core func 'mul' instead");
        },
        TokenType::Slash => {
            print_lex_error(path, t, errors_found, "Operator '/' is not supported yet\nSuggestion: use core func 'div' instead");
        },
        TokenType::EqualEqual => {
            print_lex_error(path, t, errors_found, "Operator '==' is not supported yet\nSuggestion: use 'I64.eq' or 'Str.eq' instead");
        },
        TokenType::NotEqual => {
            print_lex_error(path, t, errors_found, "Operator '!=' is not supported yet\nSuggestion: use core funcs 'not' and 'I64.eq'/'Str.eq' instead");
        },
        TokenType::Lesser => {
            print_lex_error(path, t, errors_found, "Operator '<' is not supported yet\nSuggestion: use core func 'lt' instead");
        },
        TokenType::LesserEqual => {
            print_lex_error(path, t, errors_found, "Operator '<=' is not supported yet\nSuggestion: use core func 'lteq' instead");
        },
        TokenType::Greater => {
            print_lex_error(path, t, errors_found, "Operator '>' is not supported yet\nSuggestion: use core func 'gt' instead");
        },
        TokenType::GreaterEqual => {
            print_lex_error(path, t, errors_found, "Operator '>=' is not supported yet\nSuggestion: use core func 'gteq' instead");
        },
        TokenType::ExclamationMark => {
            // Issue #180: TokenType::ExclamationMark (!) is now used for bang operator (panic on throw)
        },
        _ => {
            // No error, do nothing
        }
    }
}

pub fn lexer_from_source(path: &String, source: String) -> Result<Lexer, String> {

    let mut lexer = Lexer::new(source);
    lexer.path = path.clone();  // Set the correct path for error messages
    if lexer.len() < 1 {
        return Err(format!("{}:1:0: rstil compiler ERROR: End of file not found.\nExplanation: This should never happen, this is a bug in the language.", path));
    } else if lexer.is_eof(0) {
        // Use the first token for the error
        let t = &lexer.tokens[0];
        return Err(t.lang_error(path, "Nothing to be done"));
    }

    let errors_found = print_lex_errors(&lexer.tokens, &path);
    if errors_found > 0 {
        // Use the first token for the summary error
        let t = &lexer.tokens[0];
        return Err(t.error(path, &format!("{} lexical errors found", errors_found)));
    }
    return Ok(lexer);
}
