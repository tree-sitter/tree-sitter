//! Parse-stage error taxonomy.

use serde::{Deserialize, Serialize};
use thiserror::Error;

use super::{MAX_PARSE_DEPTH, escape::EscapeErrorKind};
use crate::nativedsl::{
    ParseError,
    lexer::TokenKind,
    typecheck::{
        Ty,
        types::{TUPLE_MAX_ARITY, TUPLE_MIN_ARITY},
    },
};

pub type ParseResult<T> = Result<T, ParseError>;

#[derive(Debug, PartialEq, Eq, Serialize, Deserialize, Error)]
pub enum ParseErrorKind {
    #[error("expected {expected}, got {got}")]
    ExpectedToken { expected: TokenKind, got: TokenKind },
    #[error("expected identifier")]
    ExpectedIdent,
    #[error("expected string literal")]
    ExpectedString,
    #[error(transparent)]
    InvalidEscape(EscapeErrorKind),
    #[error(
        "grammar language must start with an ASCII letter or '_' and contain only ASCII letters, digits, or '_'"
    )]
    InvalidLanguageName,
    #[error("reserved context name must be an identifier")]
    InvalidReservedContextName,
    #[error("backslashes are not allowed in module paths. Use '/' as the directory separator")]
    BackslashInModulePath,
    #[error("expected name")]
    ExpectedName,
    #[error("expected an identifier, not a quoted string")]
    QuotedName,
    #[error("expected expression")]
    ExpectedExpression,
    #[error("integer literal out of range (maximum {})", i64::MAX)]
    IntegerOverflow,
    #[error("expected type")]
    ExpectedType,
    #[error("expected a `grammar` block, declaration, or rule-set macro call (`@name(...)`)")]
    ExpectedItem,
    #[error("unknown type '{0}'")]
    UnknownType(String),
    #[error("{0} cannot be stored inside a list")]
    ListInnerType(Ty),
    #[error("{0} cannot be stored inside an object")]
    ObjectInnerType(Ty),
    #[error("tuple elements must be rule_t, str_t, or int_t, got {0}")]
    TupleElementType(Ty),
    #[error(
        "a tuple type needs {min} to {max} element types (there is no grouping operator), got {0}",
        min = TUPLE_MIN_ARITY,
        max = TUPLE_MAX_ARITY
    )]
    TupleArity(usize),
    #[error("unknown grammar field '{0}'")]
    UnknownGrammarField(String),
    #[error("grammar field '{0}' cannot be read via grammar_config()")]
    GrammarFieldNotReadable(String),
    #[error("duplicate grammar field '{0}'")]
    DuplicateGrammarField(String),
    #[error("only identifiers can be used as macro names")]
    ExpectedMacroName,
    #[error("only one grammar block is allowed")]
    DuplicateGrammarBlock,
    #[error("expression nesting too deep (maximum {MAX_PARSE_DEPTH})")]
    NestingTooDeep,
    #[error("too many elements ({0}, maximum {max})", max = u16::MAX)]
    TooManyChildren(usize),
    #[error("too many bindings (maximum 255)")]
    TooManyBindings,
    #[error("{}", format_arg_count(*.expected, *.name, *.got))]
    WrongArgumentCount {
        name: TokenKind,
        expected: u8,
        got: usize,
    },
    #[error("expected 'cfg' inside attribute, got '{0}'")]
    ExpectedCfgKeyword(String),
    #[error("`#[cfg(...)]` is not allowed on a grammar block")]
    CfgOnGrammarBlock,
    #[error("rule-set macro body may only contain rule declarations")]
    RuleSetBodyRequiresRuleDecl,
    #[error("`@` computed-rule syntax is only valid inside a `rules` macro body")]
    ComputedRuleTopLevel,
}

fn format_arg_count(expected: u8, name: TokenKind, got: usize) -> String {
    match expected {
        0 => format!("{name} takes no arguments, got {got}"),
        1 => format!("{name} takes 1 argument, got {got}"),
        _ => format!("{name} takes {expected} arguments, got {got}"),
    }
}
