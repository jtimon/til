use rs::lexer::{LANG_NAME, TokenType, Lexer, Token};

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

pub fn can_be_imported(mode_def: &ModeDef) -> bool {
    return !(
        mode_def.needs_main_proc || // TODO think harder, why not?
        mode_def.allows_base_calls ||
        mode_def.allows_base_anything
    );
}

pub fn mode_from_name(mode_name: &str, path: &str, t: &Token) -> Result<ModeDef, String> {
    return match mode_name {
        "lib" => Ok(
            ModeDef{name                 : mode_name.to_string(),
                    allows_procs         : true,
                    allows_base_calls    : false,
                    allows_base_mut      : true,
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
                    imports              : vec!["src/core/modes/safe_script".to_string()],
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

        _  => return Err(t.error(path, &format!("{} interpreter implementation doesn't support mode '{}'", LANG_NAME, mode_name))),
    };
}

pub fn parse_mode(path: &String, lexer: &mut Lexer) -> Result<ModeDef, String> {
    let _mode_token = lexer.expect(TokenType::Mode)?; // Add one for mode

    if TokenType::Identifier != lexer.peek().token_type {
        let t = lexer.peek();
        return Err(t.error(path, "Expected identifier after 'mode'"));
    }
    let t = lexer.peek();
    let mode_name = &t.token_str;
    let m = match mode_from_name(&mode_name, path, &t) {
        Ok(mode_) => mode_,
        Err(err_) => return Err(err_),
    };

    lexer.expect(TokenType::Identifier)?; // Add one for the identifier of the mode
    return Ok(m);
}
