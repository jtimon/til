use std::collections::HashMap;
use std::io::Write; // <--- bring flush() into scope
use std::io;

use crate::rs::ordered_map::OrderedMap;

// Bug #38 fix: Use a Vec to preserve variant order instead of HashMap
#[derive(Debug, Clone, PartialEq)]
pub struct EnumVariant {
    pub name: String,
    pub payload_type: Option<ValueType>,
}

#[derive(Debug, Clone, PartialEq)]
pub struct EnumDef {
    pub variants: Vec<EnumVariant>,
    pub methods: OrderedMap<String, Expr>,  // Auto-generated methods (delete, clone)
    pub ns: NamespaceDef,
}

impl EnumDef {
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

// Issue #91: FuncSig is the type-level signature (types + modifiers, no arg names)
#[derive(Debug, Clone, PartialEq)]
pub struct FuncSig {
    pub function_type: FunctionType,
    pub args: Vec<Declaration>,      // name is always "" -- types + modifiers only
    pub return_types: Vec<ValueType>,
    pub throw_types: Vec<ValueType>,
}

impl FuncSig {
    pub fn is_proc(&self) -> bool {
        match self.function_type {
            FunctionType::FTProc | FunctionType::FTProcExt => true,
            FunctionType::FTFunc | FunctionType::FTFuncExt | FunctionType::FTMacro => false,
        }
    }

    pub fn is_ext(&self) -> bool {
        match self.function_type {
            FunctionType::FTFuncExt | FunctionType::FTProcExt => true,
            FunctionType::FTFunc | FunctionType::FTProc | FunctionType::FTMacro => false,
        }
    }

    pub fn is_macro(&self) -> bool {
        match self.function_type {
            FunctionType::FTMacro => true,
            FunctionType::FTFunc | FunctionType::FTProc | FunctionType::FTFuncExt | FunctionType::FTProcExt => false,
        }
    }
}

// Issue #91: FuncDef = FuncSig (type) + arg names (instance) + body + source_path
#[derive(Debug, Clone, PartialEq)]
pub struct FuncDef {
    pub sig: FuncSig,
    pub arg_names: Vec<String>,      // paired by index with sig.args
    pub body: Vec<Expr>,
    pub source_path: String,  // Path to the file where this function was defined
}

impl FuncDef {
    pub fn is_proc(&self) -> bool { self.sig.is_proc() }
    pub fn is_ext(&self) -> bool { self.sig.is_ext() }
    pub fn is_macro(&self) -> bool { self.sig.is_macro() }
}

#[derive(Debug, Clone, PartialEq)]
pub struct StructDef {
    pub members : Vec<Declaration>,
    pub default_values : HashMap<String, Expr>,
    pub ns: NamespaceDef,
}

impl StructDef {
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
pub struct NamespaceDef {
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
    FuncDef(FuncDef),
    EnumDef(EnumDef),
    StructDef(StructDef),
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

    pub fn exit_error(self: &Expr, phase: &str, msg: &str) -> String {
        if phase == "warning" {
            println!("{}:{}: WARNING: {}\nExplanation: This should never happen, this is a bug in the language.",
                     self.line, self.col, msg);
        } else {
            println!("{}:{}: {} ERROR: {}\nExplanation: This should never happen, this is a bug in the language.",
                     self.line, self.col, phase, msg);
        }
        let _ = io::stdout().flush(); // Disregard flush errors, don't unwrap
        std::process::exit(1);
    }

    pub fn lang_error(self: &Expr, path: &str, phase: &str, msg: &str) -> String {
        if phase == "warning" {
            return format!("{}:{}:{}: WARNING: {}\nExplanation: This should never happen, this is a bug in the language.", path, self.line, self.col, msg);
        }
        return format!("{}:{}:{}: {} ERROR: {}\nExplanation: This should never happen, this is a bug in the language.",
                       path, self.line, self.col, phase, msg)
    }

    pub fn todo_error(self: &Expr, path: &str, phase: &str, msg: &str) -> String {
        if phase == "warning" {
            return format!("{}:{}:{}: WARNING: {}\nExplanation: Not implemented yet, this is a missing feature in the language.", path, self.line, self.col, msg);
        }
        return format!("{}:{}:{}: {} ERROR: {}\nExplanation: Not implemented yet, this is a missing feature in the language.",
                       path, self.line, self.col, phase, msg)
    }

    pub fn error(self: &Expr, path: &str, phase: &str, msg: &str) -> String {
        if phase == "warning" {
            return format!("{}:{}:{}: WARNING: {}", path, self.line, self.col, msg);
        }
        return format!("{}:{}:{}: {} ERROR: {}", path, self.line, self.col, phase, msg)
    }
}

#[derive(Debug, Clone, PartialEq)]
pub enum TTypeDef {
    TEnumDef,
    TStructDef,
    TFuncSig,
}

#[derive(Debug, Clone, PartialEq)]
pub enum ValueType {
    TFunction(FunctionType),
    TType(TTypeDef),
    TCustom(String),
    TMulti(String),
}

