// Compile-time external function replacements
// These functions return compile-time information and are replaced with literals during precomp.

use crate::rs::parser::{Expr, NodeType, Literal};
use crate::rs::init::Context;

/// Try to replace compile-time intrinsic calls with literals.
/// Returns Some(Expr) if replaced, None if not a compile-time intrinsic.
pub fn try_replace_comptime_intrinsic(context: &Context, e: &Expr) -> Option<Expr> {
    let func_expr = e.params.first()?;

    if let NodeType::Identifier(name) = &func_expr.node_type {
        if e.params.len() == 1 {
            match name.as_str() {
                "loc" => {
                    let loc_str = format!("{}:{}:{}:", context.path, e.line, e.col);
                    return Some(Expr::new_clone(
                        NodeType::LLiteral(Literal::Str(loc_str)),
                        e,
                        vec![],
                    ));
                },
                "_file" => {
                    return Some(Expr::new_clone(
                        NodeType::LLiteral(Literal::Str(context.path.clone())),
                        e,
                        vec![],
                    ));
                },
                "_line" => {
                    return Some(Expr::new_clone(
                        NodeType::LLiteral(Literal::Number(e.line.to_string())),
                        e,
                        vec![],
                    ));
                },
                "_col" => {
                    return Some(Expr::new_clone(
                        NodeType::LLiteral(Literal::Number(e.col.to_string())),
                        e,
                        vec![],
                    ));
                },
                _ => {},
            }
        }
    }

    None
}
