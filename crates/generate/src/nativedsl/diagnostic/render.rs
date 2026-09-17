//! Diagnostic rendering for DSL errors.

use std::path::Path;
use std::sync::OnceLock;

use anstyle::{AnsiColor, Color, Style};
use serde::{Deserialize, Serialize};
use thiserror::Error;

use super::{DslError, NoteMessage};
use crate::nativedsl::{DocumentId, DocumentMap, DocumentRef, DocumentSpan, ast::Span};

struct Paint<T>(Style, T);

impl<T: std::fmt::Display> std::fmt::Display for Paint<T> {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        if !color_enabled() {
            return self.1.fmt(f);
        }
        // Forward an outer width spec to the value: `write!` args don't
        // inherit it, so `{:>gutter$}` would otherwise be dropped here (all
        // width'd call sites are right-aligned line numbers).
        if let Some(width) = f.width() {
            write!(f, "{}{:>width$}{:#}", self.0, self.1, self.0)
        } else {
            write!(f, "{}{}{:#}", self.0, self.1, self.0)
        }
    }
}

/// Renders a span's leading-text as caret-line indent: tabs stay tabs (same tab
/// stop as the source line), every other char becomes one space.
struct CaretPad<'a>(&'a str);

impl std::fmt::Display for CaretPad<'_> {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        for c in self.0.chars() {
            write!(f, "{}", if c == '\t' { '\t' } else { ' ' })?;
        }
        Ok(())
    }
}

fn color_enabled() -> bool {
    static ENABLED: OnceLock<bool> = OnceLock::new();
    *ENABLED.get_or_init(|| std::env::var_os("NO_COLOR").is_none_or(|v| v.is_empty()))
}

const PIPE: Paint<&str> = Paint(CYAN_STYLE, "|");
const ARROW: Paint<&str> = Paint(CYAN_STYLE, "-->");
const ELLIP: Paint<&str> = Paint(CYAN_STYLE, "...");
const EQUALS: Paint<&str> = Paint(CYAN_STYLE, "===");
const ERROR: Paint<&str> = Paint(RED_STYLE, "error");
const NOTE: Paint<&str> = Paint(CYAN_STYLE, "note");

const RED_STYLE: Style = Style::new()
    .fg_color(Some(Color::Ansi(AnsiColor::Red)))
    .bold();
const CYAN_STYLE: Style = Style::new()
    .fg_color(Some(Color::Ansi(AnsiColor::Cyan)))
    .bold();

struct SnippetMarker {
    style: Style,
    glyph: char,
}

const ERROR_MARKER: SnippetMarker = SnippetMarker {
    style: RED_STYLE,
    glyph: '^',
};
const NOTE_MARKER: SnippetMarker = SnippetMarker {
    style: CYAN_STYLE,
    glyph: '-',
};

/// A located region of source text.
#[derive(Clone, Copy)]
struct Source<'a> {
    span: Span,
    text: &'a str,
    path: &'a Path,
}

#[derive(Clone, Copy)]
enum SnippetKind<'a> {
    Error,
    Note(&'a NoteMessage),
}

impl SnippetKind<'_> {
    const fn marker(self) -> SnippetMarker {
        match self {
            Self::Error => ERROR_MARKER,
            Self::Note(_) => NOTE_MARKER,
        }
    }
}

/// the self contained error returned by [`parse_native_dsl`](crate::nativedsl::parse_native_dsl).
///
/// Owns both the pipeline's [`DslError`] and every source document referenced by
/// its diagnostics. Retain this wrapper to render locations or resolve a [`DocumentId`].
#[derive(Debug, Error, Serialize, Deserialize, PartialEq, Eq)]
pub struct NativeDslError {
    #[source]
    pub error: DslError,
    documents: Box<DocumentMap>,
}

impl NativeDslError {
    pub(crate) fn new(error: DslError, documents: DocumentMap) -> Self {
        Self {
            error,
            documents: Box::new(documents),
        }
    }

    #[must_use]
    pub const fn document(&self, id: DocumentId) -> DocumentRef<'_> {
        self.documents.document(id)
    }

    #[must_use]
    pub fn into_err(self) -> DslError {
        self.error
    }
}

impl std::fmt::Display for NativeDslError {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        if matches!(self.error, DslError::Module(_)) {
            // Walk the Module chain to find the leaf error and collect
            // intermediate ModuleErrors for the reference note chain.
            let mut modules = Vec::new();
            let mut current = &self.error;
            while let DslError::Module(m) = current {
                modules.push(m);
                current = &m.inner;
            }

            render_error(f, current, &self.documents)?;

            // Each wrapper carries its reference location in the parent document.
            // Render the chain from the innermost reference outward.
            for module in modules.iter().rev() {
                writeln!(f)?;
                render_document_span(
                    f,
                    &self.documents,
                    module.reference,
                    SnippetKind::Note(&NoteMessage::ReferencedFromHere),
                )?;
            }

            return Ok(());
        }

        render_error(f, &self.error, &self.documents)
    }
}

fn render_error(
    f: &mut std::fmt::Formatter<'_>,
    error: &DslError,
    documents: &DocumentMap,
) -> std::fmt::Result {
    writeln!(f, "{ERROR}: {error}")?;
    let document = documents.document(error.document());

    // A file-level error (e.g. a missing grammar block) has no location within
    // the source, located errors fall through to the snippet below.
    let Some(span) = error.span() else {
        writeln!(f, " {ARROW} {}", document.path().display())?;
        return Ok(());
    };

    render_snippet(
        f,
        Source {
            span,
            text: document.text(),
            path: document.path(),
        },
        SnippetKind::Error,
    )?;

    for note in error.notes() {
        writeln!(f)?;
        render_document_span(
            f,
            documents,
            note.location,
            SnippetKind::Note(&note.message),
        )?;
    }

    if let Some(trace) = error.call_trace() {
        let show = 3;
        let elided = trace.len().saturating_sub(show * 2);
        writeln!(f)?;
        writeln!(f, " {EQUALS} call trace:")?;
        for (i, (name, path, line, col)) in trace.iter().enumerate() {
            if elided > 0 && i == show {
                writeln!(f, "   {ELLIP} {elided} more frames ...")?;
            }
            if i >= show && i < trace.len().saturating_sub(show) {
                continue;
            }
            writeln!(f, "   {ARROW} {}:{line}:{col} in {name}()", path.display())?;
        }
    }

    Ok(())
}

fn render_document_span(
    f: &mut std::fmt::Formatter<'_>,
    documents: &DocumentMap,
    location: DocumentSpan,
    kind: SnippetKind<'_>,
) -> std::fmt::Result {
    let document = documents.document(location.document);
    render_snippet(
        f,
        Source {
            span: location.span,
            text: document.text(),
            path: document.path(),
        },
        kind,
    )
}

/// Render a source snippet with a location header, source line, and underline.
fn render_snippet(
    f: &mut std::fmt::Formatter<'_>,
    src: Source<'_>,
    kind: SnippetKind<'_>,
) -> std::fmt::Result {
    let show_prev_line = matches!(kind, SnippetKind::Error);
    let marker = kind.marker();
    let ctx = SpanContext::new(src.span, src.text);
    let underline = Paint(
        marker.style,
        marker.glyph.to_string().repeat(ctx.underline_len),
    );
    let gutter = ctx.gutter_width;

    writeln!(
        f,
        " {ARROW} {}:{}:{}",
        src.path.display(),
        ctx.line_num,
        ctx.col
    )?;
    writeln!(f, " {:>gutter$} {PIPE}", "")?;
    if show_prev_line && let Some(prev_text) = ctx.prev_line_text {
        writeln!(
            f,
            " {:>gutter$} {PIPE} {prev_text}",
            Paint(CYAN_STYLE, ctx.prev_line_num)
        )?;
    }
    writeln!(
        f,
        " {:>gutter$} {PIPE} {}",
        Paint(CYAN_STYLE, ctx.line_num),
        ctx.line_text,
    )?;
    write!(
        f,
        " {pad:>gutter$} {PIPE} {indent}{underline}",
        pad = "",
        indent = CaretPad(ctx.caret_prefix)
    )?;
    if let SnippetKind::Note(msg) = kind {
        write!(f, " {NOTE}: {}", Paint(marker.style, msg))?;
    }

    Ok(())
}

/// Largest char boundary `<= i` (clamped to the string length). Spans are byte
/// offsets and an error span can land inside a multibyte char, so clamp before
/// slicing `source_text` to avoid a panic while rendering the diagnostic.
fn floor_char_boundary(s: &str, i: usize) -> usize {
    let mut i = i.min(s.len());
    while !s.is_char_boundary(i) {
        i -= 1;
    }
    i
}

/// Smallest char boundary `>= i` (clamped to the string length).
fn ceil_char_boundary(s: &str, i: usize) -> usize {
    let mut i = i.min(s.len());
    while !s.is_char_boundary(i) {
        i += 1;
    }
    i
}

struct SpanContext<'a> {
    line_num: usize,
    col: usize,
    line_text: &'a str,
    prev_line_text: Option<&'a str>,
    prev_line_num: usize,
    caret_prefix: &'a str,
    underline_len: usize,
    gutter_width: usize,
}

impl SpanContext<'_> {
    fn new(span: Span, source_text: &str) -> SpanContext<'_> {
        let offset = floor_char_boundary(source_text, span.start as usize);
        let bytes = source_text.as_bytes();
        let prefix = &bytes[..offset];
        let line_num = memchr::memchr_iter(b'\n', prefix).count() + 1;
        let line_start = memchr::memrchr(b'\n', prefix).map_or(0, |i| i + 1);
        let prev_line_start = if line_start > 0 {
            Some(memchr::memrchr(b'\n', &prefix[..line_start - 1]).map_or(0, |i| i + 1))
        } else {
            None
        };
        let line_end =
            memchr::memchr(b'\n', &bytes[line_start..]).map_or(bytes.len(), |pos| line_start + pos);
        let line_text = &source_text[line_start..line_end];
        // The line's leading text before the span. The caret line renders it via
        // CaretPad (tabs kept, other chars one space each) so the caret lands
        // on the same tab stops as the source line under any terminal tab width.
        let caret_prefix = &source_text[line_start..offset];
        let col = caret_prefix.chars().count() + 1;
        let underline_end =
            ceil_char_boundary(source_text, (span.end as usize).min(line_end)).max(offset);
        let underline_len = source_text[offset..underline_end].chars().count().max(1);

        let prev_line_text =
            prev_line_start.map(|ps| &source_text[ps..line_start.saturating_sub(1)]);

        SpanContext {
            line_num,
            col,
            line_text,
            prev_line_text,
            prev_line_num: line_num.saturating_sub(1),
            caret_prefix,
            underline_len,
            gutter_width: digit_count(line_num),
        }
    }
}

fn digit_count(n: usize) -> usize {
    n.checked_ilog10().map_or(1, |d| d as usize + 1)
}
