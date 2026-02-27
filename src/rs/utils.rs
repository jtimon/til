use crate::rs::parser::{FuncDef, FunctionType};

/// Issue #91: Detect function signature definitions.
/// A FuncDef with empty body and type-only args (no names) is a function signature type.
pub fn is_function_signature(func_def: &FuncDef) -> bool {
    func_def.body.is_empty() && func_def.sig.args.iter().all(|a| a.name.is_empty())
        && matches!(func_def.sig.function_type, FunctionType::FTFunc | FunctionType::FTProc)
}
