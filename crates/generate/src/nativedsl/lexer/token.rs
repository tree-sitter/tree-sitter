//! Token kinds and keyword lookup shared by the lexer and parser.

use serde::{Deserialize, Serialize};

use crate::nativedsl::ast::Span;

/// A token and its source span.
#[derive(Clone)]
pub struct Token {
    pub kind: TokenKind,
    pub span: Span,
}

/// The kind of a lexer token.
#[derive(Clone, Copy, Debug, PartialEq, Eq, Serialize, Deserialize)]
pub enum TokenKind {
    /// Identifier. Raw identifier spans exclude the `r#` prefix.
    Ident,
    /// String literal. The token span includes its quotes.
    StringLit,
    /// Raw string literal. The token span includes its quotes and delimiters.
    RawStringLit,
    /// Integer literal.
    IntLit,
    // Keywords
    KwGrammar,
    KwRule,
    KwRules,
    KwLet,
    KwMacro,
    KwFor,
    KwIn,
    KwSeq,
    KwChoice,
    KwRepeat,
    KwRepeat1,
    KwOptional,
    KwBlank,
    KwEof,
    KwField,
    KwAlias,
    KwToken,
    KwPrec,
    KwPrecLeft,
    KwPrecRight,
    KwPrecDynamic,
    KwReserved,
    KwTokenImmediate,
    KwConcat,
    KwRegexp,
    KwInherit,
    KwImport,
    KwOverride,
    KwAppend,
    KwGrammarConfig,
    KwExpect,
    // Punctuation
    LBrace,
    RBrace,
    LParen,
    RParen,
    LBracket,
    RBracket,
    Comma,
    Colon,
    ColonColon,
    Dot,
    Minus,
    Plus,
    Eq,
    Lt,
    Gt,
    Pound,
    At,
    /// Synthetic token marking the end of input.
    Eof,
}

const _: () = assert!(std::mem::size_of::<TokenKind>() == 1);

/// Defines keyword spellings and their lookup helpers.
macro_rules! keywords {
    (
        decls { $($d_variant:ident => $d_str:literal),* $(,)? }
        expressions { $($c_variant:ident => $c_str:literal),* $(,)? }
    ) => {
        impl TokenKind {
            /// Expression keywords considered when suggesting a replacement for an
            /// unknown identifier.
            pub(crate) const EXPRESSION_KEYWORD_NAMES: &'static [&'static str] = &[$($c_str),*];

            #[must_use]
            pub const fn is_keyword(self) -> bool {
                matches!(self, $(Self::$d_variant)|* $(| Self::$c_variant)*)
            }

            /// Returns this token's source spelling, if it is a keyword.
            const fn keyword_str(self) -> Option<&'static str> {
                match self {
                    $(Self::$d_variant => Some($d_str),)*
                    $(Self::$c_variant => Some($c_str),)*
                    _ => None,
                }
            }

            /// Returns the token for a known keyword, or `Ident` otherwise.
            #[inline]
            pub(super) fn from_keyword(text: &str) -> Self {
                match text {
                    $($d_str => Self::$d_variant,)*
                    $($c_str => Self::$c_variant,)*
                    _ => Self::Ident,
                }
            }
        }
    };
}

keywords! {
    decls {
        KwGrammar => "grammar", KwRule => "rule", KwRules => "rules", KwLet => "let",
        KwMacro => "macro", KwOverride => "override", KwExpect => "expect", KwIn => "in",
    }
    expressions {
        KwFor => "for", KwSeq => "seq", KwChoice => "choice", KwRepeat => "repeat",
        KwRepeat1 => "repeat1", KwOptional => "optional", KwBlank => "blank", KwEof => "eof",
        KwField => "field", KwAlias => "alias", KwToken => "token", KwPrec => "prec",
        KwPrecLeft => "prec_left", KwPrecRight => "prec_right", KwPrecDynamic => "prec_dynamic",
        KwReserved => "reserved", KwTokenImmediate => "token_immediate", KwConcat => "concat",
        KwRegexp => "regexp", KwInherit => "inherit", KwImport => "import", KwAppend => "append",
        KwGrammarConfig => "grammar_config",
    }
}

impl std::fmt::Display for TokenKind {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        if let Some(kw) = self.keyword_str() {
            return write!(f, "'{kw}'");
        }
        f.write_str(match self {
            Self::Ident => "identifier",
            Self::StringLit => "string literal",
            Self::RawStringLit => "raw string literal",
            Self::IntLit => "integer literal",
            Self::LBrace => "'{'",
            Self::RBrace => "'}'",
            Self::LParen => "'('",
            Self::RParen => "')'",
            Self::LBracket => "'['",
            Self::RBracket => "']'",
            Self::Comma => "','",
            Self::Colon => "':'",
            Self::ColonColon => "'::'",
            Self::Dot => "'.'",
            Self::Minus => "'-'",
            Self::Plus => "'+'",
            Self::Eq => "'='",
            Self::Lt => "'<'",
            Self::Gt => "'>'",
            Self::Pound => "'#'",
            Self::At => "'@'",
            Self::Eof => "end of file",
            _ => unreachable!(),
        })
    }
}
