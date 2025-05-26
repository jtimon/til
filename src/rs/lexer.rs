pub const LANG_NAME  : &str = "rscil";

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
    True,
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
    pub fn lang_error(self: &Token, msg: &str) -> String {
        return format!("{}:{}: {} parse ERROR: {}\nExplanation: This is not your fault as a user, this is a bug in the language.",
                 self.line, self.col, LANG_NAME, msg);
    }

    pub fn todo_error(self: &Token, msg: &str) -> String {
        return format!("{}:{}: {} parse ERROR: {}\nExplanation: Not implemented yet, this is a missing feature in the language.",
                 self.line, self.col, LANG_NAME, msg);
    }

    pub fn error(self: &Token, msg: &str) -> String {
        return format!("{}:{}: parse ERROR: {}", self.line, self.col, msg);
    }
}

pub struct Lexer {
    tokens: Vec<Token>,
    pub current: usize,
}

impl Lexer {
    pub fn new(source: String) -> Self {
        return Self{tokens: scan_tokens(source), current: 0};
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
                let t = self.peek();
                return Err(t.lang_error(&format!("Token in pos {} is out of bounds", i)))
            },
        }
    }

    pub fn peek(&self) -> Token {
        return self.tokens[self.current].clone()
    }

    pub fn previous(&self) -> Result<Token, String> {
        if self.current == 0 {
            let t = self.peek();
            return Err(t.lang_error("No previous token (at position 0)"));
        }
        if self.current - 1 >= self.tokens.len() {
            let t = self.peek();
            return Err(t.lang_error("Previous token is out of bounds"));
        }
        return Ok(self.tokens[self.current - 1].clone());
    }

    pub fn advance(&mut self, count: usize) -> Result<(), String> {
        if self.current + count > self.tokens.len() {
            let t = self.peek();
            return Err(t.lang_error(&format!("Attempt to advance by {} from {} would exceed bounds ({} tokens total)",
                                             count, self.current, self.tokens.len())));
        }
        self.current += count;
        return Ok(());
    }

    pub fn go_back(&mut self, count: usize) -> Result<(), String> {
        if count > self.current {
            let t = self.peek();
            return Err(t.lang_error(&format!("Attempt to go back by {} from {} would underflow", count, self.current)));
        }
        self.current -= count;
        Ok(())
    }

    pub fn peek_ahead(&self, offset: usize) -> Result<Token, String> {
        let i = self.current + offset;
        if i >= self.tokens.len() {
            let t = self.peek();
            return Err(t.lang_error(&format!("Peek ahead by {} from {} is out of bounds", offset, self.current)));
        }
        return Ok(self.tokens[i].clone());
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
            // TODO use token.token_str and implement a token_type_to_str function
            Err(token.lang_error(&format!("Expected token '{:?}', but found '{:?}'", expected, token.token_type)))
        }
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

        // bool literals
        "true" => TokenType::True,

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
                    "*" => {
                        pos += 2;
                        let mut depth = 1;
                        while pos < eof_pos - 1 {
                            if &source[pos..pos+2] == "/*" {
                                depth += 1;
                                pos += 2;
                            } else if &source[pos..pos+2] == "*/" {
                                depth -= 1;
                                pos += 2;
                                if depth == 0 {
                                    break;
                                }
                            } else {
                                if &source[pos..pos+1] == "\n" {
                                    line += 1;
                                    start_line_pos = pos + 1;
                                }
                                pos += 1;
                            }
                        }
                        if depth > 0 {
                            scan_push_token(&mut tokens, TokenType::UnterminatedComment, "/*", line, pos - start_line_pos + 1);
                        }
                        continue;
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
                                if let Some(ch) = source.as_bytes().get(pos).copied() {
                                    lit_string.push(ch as char);
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
                                if let Some(ch) = source.as_bytes().get(pos).copied() {
                                    lit_string.push(ch as char);
                                }
                            }
                        } else {
                            if let Some(ch) = source.as_bytes().get(pos).copied() {
                                lit_string.push(ch as char);
                            }
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

fn print_lex_error(path: &String, t: &Token, errors_found: &mut usize, msg: &str) {
    println!("{}:{}:{}: Lexical error {}: {}. Offending symbol: '{}'",
             path, t.line, t.col, *errors_found, msg, t.token_str);
    *errors_found += 1;
}

fn print_if_lex_error(path: &String, t: &Token, errors_found: &mut usize) {
    match t.token_type {
        TokenType::Invalid => {
            print_lex_error(path, t, errors_found, "Invalid character");
        },
        TokenType::UnterminatedString => {
            print_lex_error(path, t, errors_found, "Unterminated String\nSuggestion: add missing '\"'");
        },
        TokenType::UnterminatedComment => {
            print_lex_error(path, t, errors_found, "Unterminated comment\nSuggestion: add missing '*/'");
        }
        TokenType::Const => {
            print_lex_error(path, t, errors_found, "No need to use 'const', everything is const by default unless 'mut' is used");
        },
        TokenType::Var => {
            print_lex_error(path, t, errors_found, "Keyword 'var' is not supported\nSuggestion: use 'mut' instead");
        },
        TokenType::Fn => {
            print_lex_error(path, t, errors_found, "Keyword 'fn' is not supported\nSuggestion: use 'func' or 'proc' instead");
        },
        TokenType::DoubleSemicolon => {
            print_lex_error(path, t, errors_found, "No need for ';;' (aka empty statements)\nSuggestion: try 'if true {}' instead, whatever you want that for");
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
            print_lex_error(path, t, errors_found, "Operator '==' is not supported yet\nSuggestion: use 'I64.eq' or 'String.eq' instead");
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
        TokenType::Not => {
            print_lex_error(path, t, errors_found, "Operator '!' is not supported yet\nSuggestion: use core func 'not' instead");
        },
        TokenType::NotEqual => {
            print_lex_error(path, t, errors_found, "Operator '!=' is not supported yet\nSuggestion: use core funcs 'not' and 'I64.eq'/'String.eq' instead");
        },
        _ => {
            // No error, do nothing
        }
    }
}

pub fn lexer_from_source(path: &String, source: String) -> Result<Lexer, String> {

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
