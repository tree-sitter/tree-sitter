//! Error types shared by every native-DSL pipeline stage.

use std::path::PathBuf;

use serde::{Deserialize, Serialize};
use thiserror::Error;

use crate::nativedsl::{
    DocumentId, DocumentSpan, apply_cfg::CfgErrorKind, ast::Span,
    expand_macro_calls::ExpandErrorKind, lexer::LexErrorKind, lower::LowerErrorKind,
    parser::ParseErrorKind, resolve::ResolveErrorKind, typecheck::TypeErrorKind,
};

pub type DslResult<T> = Result<T, DslError>;

pub type LexError = Diagnostic<LexErrorKind>;
pub type ParseError = Diagnostic<ParseErrorKind>;
pub type CfgError = Diagnostic<CfgErrorKind>;
pub type ExpandError = Diagnostic<ExpandErrorKind>;
pub type ResolveError = Diagnostic<ResolveErrorKind>;
pub type TypeError = Diagnostic<TypeErrorKind>;
pub type LowerError = Diagnostic<LowerErrorKind>;

/// Diagnostic error shared by all pipeline stages.
#[derive(Debug, Serialize, Deserialize, Error, PartialEq, Eq)]
pub struct Diagnostic<K> {
    pub kind: K,
    pub document: DocumentId,
    pub span: Option<Span>,
    #[serde(skip_serializing_if = "Vec::is_empty")]
    pub notes: Vec<Note>,
}

impl<K> Diagnostic<K> {
    pub const fn new(kind: K, document: DocumentId, span: Span) -> Self {
        Self {
            kind,
            document,
            span: Some(span),
            notes: Vec::new(),
        }
    }

    pub const fn without_span(kind: K, document: DocumentId) -> Self {
        Self {
            kind,
            document,
            span: None,
            notes: Vec::new(),
        }
    }

    pub fn with_note(kind: K, document: DocumentId, span: Span, note: Note) -> Self {
        Self {
            kind,
            document,
            span: Some(span),
            notes: vec![note],
        }
    }

    pub fn add_note(&mut self, note: Note) {
        self.notes.push(note);
    }
}

impl<K: std::fmt::Display> std::fmt::Display for Diagnostic<K> {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        self.kind.fmt(f)
    }
}

/// A failure produced by a native DSL compilation stage.
///
/// This is the compact diagnostic payload used inside the compiler. Its [`DocumentId`]
/// values index the document map owned by [`NativeDslError`](crate::nativedsl::NativeDslError).
/// Public callers should retain `NativeDslError` and use this type to inspect the
/// error kind. By itself, this type cannot resolve source text or paths.
#[derive(Debug, Error, Serialize, Deserialize, PartialEq, Eq)]
#[error(transparent)]
pub enum DslError {
    Lex(#[from] LexError),
    Parse(#[from] ParseError),
    Cfg(#[from] CfgError),
    Expand(#[from] ExpandError),
    Resolve(#[from] ResolveError),
    Type(#[from] TypeError),
    Lower(#[from] LowerError),
    Module(#[from] ModuleError),
}

/// Error from loading a child module.
#[derive(Debug, Serialize, Deserialize, Error, PartialEq, Eq)]
#[error("{inner}")]
pub struct ModuleError {
    #[source]
    pub inner: Box<DslError>,
    pub reference: DocumentSpan,
}

impl ModuleError {
    #[must_use]
    pub fn new(inner: DslError, reference: DocumentSpan) -> Self {
        Self {
            inner: Box::new(inner),
            reference,
        }
    }

    /// The child document this module reference loaded.
    #[must_use]
    pub fn child_document(&self) -> DocumentId {
        self.inner.document()
    }
}

/// Secondary annotation on an error, pointing to a related source location.
#[derive(Clone, Debug, Serialize, Deserialize, PartialEq, Eq)]
pub struct Note {
    pub message: NoteMessage,
    pub location: DocumentSpan,
}

/// Message attached to a secondary diagnostic location.
#[derive(Clone, Debug, PartialEq, Eq, Serialize, Deserialize)]
pub enum NoteMessage {
    /// Points to the first location involved in a duplicate or repeated construct.
    FirstDefinedHere,
    /// Points to the declaration associated with the primary error.
    DefinedHere,
    /// Points to the `inherit()` call that selected the grammar's base.
    BaseInheritedHere,
    /// Points to the parent module reference through which a failing child was loaded.
    ReferencedFromHere,
    /// Points to an additional override declaration covered by the primary error.
    OverrideDeclaredHere,
    /// Points to an additional redundant `inherit()` call.
    AlsoInheritedHere,
    /// Points to an `expect` declaration whose promised symbol was never defined.
    ForwardDeclaredHere,
    /// Points to a matching declaration removed by the named cfg flag.
    GatedByDisabledCfg(String),
    /// Carries replacement text suggested for the primary error.
    DidYouMean(String),
    /// Points to a module-qualified rule reference and carries its bare name.
    UseBareName(String),
    /// Points to the reference that closes a circular `let` dependency.
    SelfReferenceHere,
}

impl std::fmt::Display for NoteMessage {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        match self {
            Self::FirstDefinedHere => write!(f, "first defined here"),
            Self::DefinedHere => write!(f, "defined here"),
            Self::BaseInheritedHere => write!(f, "base grammar inherited here"),
            Self::ReferencedFromHere => write!(f, "referenced from here"),
            Self::OverrideDeclaredHere => write!(f, "override declared here"),
            Self::AlsoInheritedHere => write!(f, "also inherited here"),
            Self::ForwardDeclaredHere => write!(f, "forward-declared with `expect` here"),
            Self::GatedByDisabledCfg(flag) => {
                write!(f, "this declaration is disabled by `#[cfg({flag})]`")
            }
            Self::DidYouMean(name) => write!(f, "did you mean `{name}`?"),
            Self::UseBareName(name) => {
                write!(
                    f,
                    "inherited and imported rules are in scope by name, use `{name}`"
                )
            }
            Self::SelfReferenceHere => write!(f, "self-reference here"),
        }
    }
}

impl DslError {
    #[must_use]
    pub const fn document(&self) -> DocumentId {
        match self {
            Self::Lex(e) => e.document,
            Self::Parse(e) => e.document,
            Self::Cfg(e) => e.document,
            Self::Expand(e) => e.document,
            Self::Resolve(e) => e.document,
            Self::Type(e) => e.document,
            Self::Lower(e) => e.document,
            Self::Module(e) => e.reference.document,
        }
    }

    #[must_use]
    pub const fn span(&self) -> Option<Span> {
        match self {
            Self::Lex(e) => e.span,
            Self::Parse(e) => e.span,
            Self::Cfg(e) => e.span,
            Self::Expand(e) => e.span,
            Self::Resolve(e) => e.span,
            Self::Type(e) => e.span,
            Self::Lower(e) => e.span,
            Self::Module(e) => Some(e.reference.span),
        }
    }

    #[must_use]
    pub fn notes(&self) -> &[Note] {
        match self {
            Self::Lex(e) => &e.notes,
            Self::Parse(e) => &e.notes,
            Self::Cfg(e) => &e.notes,
            Self::Expand(e) => &e.notes,
            Self::Resolve(e) => &e.notes,
            Self::Type(e) => &e.notes,
            Self::Lower(e) => &e.notes,
            Self::Module(e) => e.inner.notes(),
        }
    }

    #[must_use]
    pub fn call_trace(&self) -> Option<&[(String, PathBuf, usize, usize)]> {
        if let Self::Lower(e) = self
            && let LowerErrorKind::CallDepthExceeded(trace) = &e.kind
        {
            Some(trace)
        } else {
            None
        }
    }
}

pub struct DiagnosticChar(pub char);

impl std::fmt::Display for DiagnosticChar {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        let displayed = self.0.escape_debug();
        let escaped = self.0.escape_default();

        if displayed.clone().eq(escaped.clone()) {
            write!(f, "{displayed}")
        } else {
            write!(f, "{displayed} ({escaped})")
        }
    }
}
