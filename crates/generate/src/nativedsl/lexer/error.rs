//! Lexer error taxonomy.

use serde::{Deserialize, Serialize};
use thiserror::Error;

use crate::nativedsl::{LexError, diagnostic::DiagnosticChar};

pub type LexResult<T> = Result<T, LexError>;

/// The specific kind of lexer error.
#[derive(Debug, PartialEq, Eq, Serialize, Deserialize, Error)]
pub enum LexErrorKind {
    #[error("unterminated string literal")]
    UnterminatedString,
    #[error("unterminated raw string literal")]
    UnterminatedRawString,
    #[error("unterminated escape sequence")]
    UnterminatedEscape,
    #[error("unexpected character: {}", DiagnosticChar(*.0))]
    UnexpectedChar(char),
    #[error("unterminated string literal (newline before closing quote)")]
    NewlineInString,
    #[error("expected '\"' after 'r' and '#' delimiters")]
    ExpectedRawStringQuote,
    #[error("raw string has {0} '#' delimiters (maximum {max})", max = u8::MAX)]
    TooManyHashes(u32),
    #[error("input exceeds the maximum size ({} bytes)", u32::MAX)]
    InputTooLarge,
}
