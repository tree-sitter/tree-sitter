//! Source spans and span-tagged values.

use serde::{Deserialize, Serialize};

/// Byte offset range `[start, end)` in the source text.
#[expect(clippy::unsafe_derive_deserialize)]
#[derive(Clone, Copy, Debug, PartialEq, Eq, Serialize, Deserialize)]
pub struct Span {
    pub start: u32,
    pub end: u32,
}

impl Span {
    #[must_use]
    pub const fn new(start: u32, end: u32) -> Self {
        Self { start, end }
    }

    #[must_use]
    pub const fn from_usize(start: usize, end: usize) -> Self {
        Self {
            start: start as u32,
            end: end as u32,
        }
    }

    /// Strip the first and last byte (e.g. surrounding quotes).
    #[must_use]
    pub const fn strip_quotes(self) -> Self {
        Self {
            start: self.start + 1,
            end: self.end - 1,
        }
    }

    /// Strip the `r#...#"` prefix and `"#...#` suffix from a raw string span.
    #[must_use]
    pub const fn strip_raw(self, hash_count: u8) -> Self {
        Self {
            start: self.start + 2 + hash_count as u32,
            end: self.end - 1 - hash_count as u32,
        }
    }

    #[must_use]
    pub fn merge(self, other: Self) -> Self {
        Self {
            start: self.start.min(other.start),
            end: self.end.max(other.end),
        }
    }

    /// Caller must pair the span with the source it was lexed from.
    #[must_use]
    pub(crate) fn resolve(self, source: &str) -> &str {
        // SAFETY: lexer emits spans at UTF-8 char boundaries within `source`.
        unsafe { source.get_unchecked(self.start as usize..self.end as usize) }
    }
}

/// A value paired with the source span to blame for it in diagnostics.
#[derive(Clone, Copy, Debug, PartialEq, Eq, Serialize, Deserialize)]
pub struct Spanned<T> {
    pub value: T,
    pub span: Span,
}

impl<T> Spanned<T> {
    pub const fn new(value: T, span: Span) -> Self {
        Self { value, span }
    }
}
