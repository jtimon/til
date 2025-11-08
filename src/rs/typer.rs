// Type checking module for TIL language
// This module contains all type checking logic, separated from evaluation/interpretation
// to enforce phase boundaries and prevent eval code from being called during type checking.

use std::collections::HashMap;
use std::collections::HashSet;

use crate::rs::parser::{
    INFER_TYPE,
    Expr, NodeType, FunctionType, Declaration, SStructDef, ValueType, ModeDef,
    SFuncDef, SEnumDef, TTypeDef, Literal,
    value_type_to_str, str_to_value_type,
};
use crate::rs::lexer::LANG_NAME;

// Import Context and related types from parent crate
use crate::{Context, SymbolInfo, EvalResult, RETURN_INSTANCE_NAME};

// Type checking functions will be moved here from rstil.rs
// This creates a clean phase boundary where typer.rs cannot call eval code
// since rstil.rs (which contains eval) depends on typer.rs, not vice versa.

