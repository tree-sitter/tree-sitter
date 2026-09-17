//! Shared native DSL error types, terminal rendering, and Levenshtein-based suggestions
//! for "did you mean" notes.

mod render;
mod suggest;
mod types;

pub use render::NativeDslError;
pub(crate) use suggest::suggest_name;
pub(crate) use types::DiagnosticChar;
pub use types::{
    CfgError, Diagnostic, DslError, DslResult, ExpandError, LexError, LowerError, ModuleError,
    Note, NoteMessage, ParseError, ResolveError, TypeError,
};
