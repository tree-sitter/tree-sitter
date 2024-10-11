use std::{
    fmt, fs,
    io::{self, StdoutLock, Write},
    path::Path,
    sync::atomic::AtomicUsize,
    time::{Duration, Instant},
};

use anstyle::{AnsiColor, Color, RgbColor};
use anyhow::{anyhow, Context, Result};
use bstr::ByteSlice;
use serde::{Deserialize, Serialize};
use tree_sitter::{ffi, InputEdit, Language, LogType, Parser, Point, Range, Tree, TreeCursor};

use super::util;
use crate::{fuzz::edits::Edit, test::paint};

#[derive(Debug, Default)]
pub struct Stats {
    pub successful_parses: usize,
    pub total_parses: usize,
    pub total_bytes: usize,
    pub total_duration: Duration,
}

impl fmt::Display for Stats {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        let duration_us = self.total_duration.as_micros();
        writeln!(
            f,
            "Total parses: {}; successful parses: {}; failed parses: {}; success percentage: {:.2}%; average speed: {} bytes/ms",
            self.total_parses,
            self.successful_parses,
            self.total_parses - self.successful_parses,
            ((self.successful_parses as f64) / (self.total_parses as f64)) * 100.0,
            if duration_us != 0 {
                ((self.total_bytes as u128) * 1_000) / duration_us
            } else {
                0
            }
        )
    }
}

#[derive(Debug, Copy, Clone)]
pub struct ParseTheme {
    pub node_kind: Option<Color>,
    pub node_text: Option<Color>,
    pub field: Option<Color>,
    pub token: Option<Color>,
    pub row_color: Option<Color>,
    pub row_color_named: Option<Color>,
    pub extra: Option<Color>,
    pub error: Option<Color>,
}

impl ParseTheme {
    #[must_use]
    pub const fn blank() -> Self {
        Self {
            node_kind: None,
            node_text: None,
            field: None,
            token: None,
            row_color: None,
            row_color_named: None,
            extra: None,
            error: None,
        }
    }
}

impl Default for ParseTheme {
    fn default() -> Self {
        const GRAY: Color = Color::Rgb(RgbColor(118, 118, 118));
        Self {
            node_kind: Some(AnsiColor::BrightCyan.into()),
            node_text: Some(GRAY),
            field: Some(AnsiColor::Blue.into()),
            token: Some(GRAY),
            row_color: Some(AnsiColor::White.into()),
            row_color_named: Some(AnsiColor::BrightYellow.into()),
            extra: Some(AnsiColor::BrightMagenta.into()),
            error: Some(AnsiColor::Red.into()),
        }
    }
}

#[derive(Debug, Copy, Clone, Deserialize, Serialize)]
pub struct Rgb(pub u8, pub u8, pub u8);

impl From<Rgb> for RgbColor {
    fn from(val: Rgb) -> Self {
        Self(val.0, val.1, val.2)
    }
}

#[derive(Debug, Copy, Clone, Default, Deserialize, Serialize)]
#[serde(rename_all = "kebab-case")]
pub struct Config {
    pub parse_theme: ParseThemeRaw,
}

#[derive(Debug, Copy, Clone, Default, Deserialize, Serialize)]
#[serde(rename_all = "kebab-case")]
pub struct ParseThemeRaw {
    pub node_kind: Option<Rgb>,
    pub node_text: Option<Rgb>,
    pub field: Option<Rgb>,
    pub token: Option<Rgb>,
    pub row_color: Option<Rgb>,
    pub row_color_named: Option<Rgb>,
    pub extra: Option<Rgb>,
    pub error: Option<Rgb>,
}

impl From<ParseThemeRaw> for ParseTheme {
    fn from(value: ParseThemeRaw) -> Self {
        let resolve_val = |val: Option<Rgb>, default: Option<Color>| -> Option<Color> {
            val.map_or_else(|| default, |v| Some(Into::<RgbColor>::into(v).into()))
        };
        let default = Self::default();

        Self {
            node_kind: resolve_val(value.node_kind, default.node_kind),
            node_text: resolve_val(value.node_text, default.node_text),
            field: resolve_val(value.field, default.field),
            token: resolve_val(value.token, default.token),
            row_color: resolve_val(value.row_color, default.row_color),
            row_color_named: resolve_val(value.row_color_named, default.row_color_named),
            extra: resolve_val(value.extra, default.extra),
            error: resolve_val(value.error, default.error),
        }
    }
}

#[derive(Copy, Clone, PartialEq, Eq)]
pub enum ParseOutput {
    Normal,
    Quiet,
    Xml,
    Cst,
    Dot,
}

pub struct ParseFileOptions<'a> {
    pub language: Language,
    pub path: &'a Path,
    pub edits: &'a [&'a str],
    pub max_path_length: usize,
    pub output: ParseOutput,
    pub print_time: bool,
    pub timeout: u64,
    pub debug: bool,
    pub debug_graph: bool,
    pub cancellation_flag: Option<&'a AtomicUsize>,
    pub encoding: Option<u32>,
    pub open_log: bool,
    pub no_ranges: bool,
    pub parse_theme: &'a ParseTheme,
}

#[derive(Copy, Clone)]
pub struct ParseResult {
    pub successful: bool,
    pub bytes: usize,
    pub duration: Option<Duration>,
}

pub fn parse_file_at_path(parser: &mut Parser, opts: &ParseFileOptions) -> Result<ParseResult> {
    let mut _log_session = None;
    parser.set_language(&opts.language)?;
    let mut source_code = fs::read(opts.path)
        .with_context(|| format!("Error reading source file {:?}", opts.path))?;

    // If the `--cancel` flag was passed, then cancel the parse
    // when the user types a newline.
    unsafe { parser.set_cancellation_flag(opts.cancellation_flag) };

    // Set a timeout based on the `--time` flag.
    parser.set_timeout_micros(opts.timeout);

    // Render an HTML graph if `--debug-graph` was passed
    if opts.debug_graph {
        _log_session = Some(util::log_graphs(parser, "log.html", opts.open_log)?);
    }
    // Log to stderr if `--debug` was passed
    else if opts.debug {
        parser.set_logger(Some(Box::new(|log_type, message| {
            if log_type == LogType::Lex {
                io::stderr().write_all(b"  ").unwrap();
            }
            writeln!(&mut io::stderr(), "{message}").unwrap();
        })));
    }

    let time = Instant::now();

    #[inline(always)]
    fn is_utf16_le_bom(bom_bytes: &[u8]) -> bool {
        bom_bytes == [0xFF, 0xFE]
    }

    #[inline(always)]
    fn is_utf16_be_bom(bom_bytes: &[u8]) -> bool {
        bom_bytes == [0xFE, 0xFF]
    }

    let encoding = match opts.encoding {
        None if source_code.len() >= 2 => {
            if is_utf16_le_bom(&source_code[0..2]) {
                Some(ffi::TSInputEncodingUTF16LE)
            } else if is_utf16_be_bom(&source_code[0..2]) {
                Some(ffi::TSInputEncodingUTF16BE)
            } else {
                None
            }
        }
        _ => opts.encoding,
    };

    let tree = match encoding {
        Some(encoding) if encoding == ffi::TSInputEncodingUTF16LE => {
            let source_code_utf16 = source_code
                .chunks_exact(2)
                .map(|chunk| u16::from_le_bytes([chunk[0], chunk[1]]))
                .collect::<Vec<_>>();
            parser.parse_utf16_le(&source_code_utf16, None)
        }
        Some(encoding) if encoding == ffi::TSInputEncodingUTF16BE => {
            let source_code_utf16 = source_code
                .chunks_exact(2)
                .map(|chunk| u16::from_be_bytes([chunk[0], chunk[1]]))
                .collect::<Vec<_>>();
            parser.parse_utf16_be(&source_code_utf16, None)
        }
        _ => parser.parse(&source_code, None),
    };

    let stdout = io::stdout();
    let mut stdout = stdout.lock();

    if let Some(mut tree) = tree {
        if opts.debug_graph && !opts.edits.is_empty() {
            println!("BEFORE:\n{}", String::from_utf8_lossy(&source_code));
        }

        for (i, edit) in opts.edits.iter().enumerate() {
            let edit = parse_edit_flag(&source_code, edit)?;
            perform_edit(&mut tree, &mut source_code, &edit)?;
            tree = parser.parse(&source_code, Some(&tree)).unwrap();

            if opts.debug_graph {
                println!("AFTER {i}:\n{}", String::from_utf8_lossy(&source_code));
            }
        }

        parser.stop_printing_dot_graphs();

        let duration = time.elapsed();
        let duration_ms = duration.as_micros() as f64 / 1e3;
        let mut cursor = tree.walk();

        if opts.output == ParseOutput::Normal {
            let mut needs_newline = false;
            let mut indent_level = 0;
            let mut did_visit_children = false;
            loop {
                let node = cursor.node();
                let is_named = node.is_named();
                if did_visit_children {
                    if is_named {
                        stdout.write_all(b")")?;
                        needs_newline = true;
                    }
                    if cursor.goto_next_sibling() {
                        did_visit_children = false;
                    } else if cursor.goto_parent() {
                        did_visit_children = true;
                        indent_level -= 1;
                    } else {
                        break;
                    }
                } else {
                    if is_named {
                        if needs_newline {
                            stdout.write_all(b"\n")?;
                        }
                        for _ in 0..indent_level {
                            stdout.write_all(b"  ")?;
                        }
                        let start = node.start_position();
                        let end = node.end_position();
                        if let Some(field_name) = cursor.field_name() {
                            write!(&mut stdout, "{field_name}: ")?;
                        }
                        write!(&mut stdout, "({}", node.kind())?;
                        if !opts.no_ranges {
                            write!(
                                &mut stdout,
                                " [{}, {}] - [{}, {}]",
                                start.row, start.column, end.row, end.column
                            )?;
                        }
                        needs_newline = true;
                    }
                    if cursor.goto_first_child() {
                        did_visit_children = false;
                        indent_level += 1;
                    } else {
                        did_visit_children = true;
                    }
                }
            }
            cursor.reset(tree.root_node());
            println!();
        }

        if opts.output == ParseOutput::Cst {
            let Range { end_point, .. } = tree.root_node().range();
            let row_width = (usize::max(1, end_point.row) as f64).log10() as usize + 1;
            let mut indent_level = 0;
            let mut did_visit_children = false;
            loop {
                if did_visit_children {
                    if cursor.goto_next_sibling() {
                        did_visit_children = false;
                    } else if cursor.goto_parent() {
                        did_visit_children = true;
                        indent_level -= 1;
                    } else {
                        break;
                    }
                } else {
                    cst_render_node(
                        opts,
                        &mut cursor,
                        &source_code,
                        &mut stdout,
                        row_width,
                        indent_level,
                    )?;
                    if cursor.goto_first_child() {
                        did_visit_children = false;
                        indent_level += 1;
                    } else {
                        did_visit_children = true;
                    }
                }
            }
            cursor.reset(tree.root_node());
            println!();
        }

        if opts.output == ParseOutput::Xml {
            let mut needs_newline = false;
            let mut indent_level = 0;
            let mut did_visit_children = false;
            let mut had_named_children = false;
            let mut tags = Vec::<&str>::new();
            writeln!(&mut stdout, "<?xml version=\"1.0\"?>")?;
            loop {
                let node = cursor.node();
                let is_named = node.is_named();
                if did_visit_children {
                    if is_named {
                        let tag = tags.pop();
                        if had_named_children {
                            for _ in 0..indent_level {
                                stdout.write_all(b"  ")?;
                            }
                        }
                        write!(&mut stdout, "</{}>", tag.expect("there is a tag"))?;
                        // we only write a line in the case where it's the last sibling
                        if let Some(parent) = node.parent() {
                            if parent.child(parent.child_count() - 1).unwrap() == node {
                                stdout.write_all(b"\n")?;
                            }
                        }
                        needs_newline = true;
                    }
                    if cursor.goto_next_sibling() {
                        did_visit_children = false;
                        had_named_children = false;
                    } else if cursor.goto_parent() {
                        did_visit_children = true;
                        had_named_children = is_named;
                        indent_level -= 1;
                        if !is_named && needs_newline {
                            stdout.write_all(b"\n")?;
                            for _ in 0..indent_level {
                                stdout.write_all(b"  ")?;
                            }
                        }
                    } else {
                        break;
                    }
                } else {
                    if is_named {
                        if needs_newline {
                            stdout.write_all(b"\n")?;
                        }
                        for _ in 0..indent_level {
                            stdout.write_all(b"  ")?;
                        }
                        write!(&mut stdout, "<{}", node.kind())?;
                        if let Some(field_name) = cursor.field_name() {
                            write!(&mut stdout, " field=\"{field_name}\"")?;
                        }
                        let start = node.start_position();
                        let end = node.end_position();
                        write!(&mut stdout, " srow=\"{}\"", start.row)?;
                        write!(&mut stdout, " scol=\"{}\"", start.column)?;
                        write!(&mut stdout, " erow=\"{}\"", end.row)?;
                        write!(&mut stdout, " ecol=\"{}\"", end.column)?;
                        write!(&mut stdout, ">")?;
                        tags.push(node.kind());
                        needs_newline = true;
                    }
                    if cursor.goto_first_child() {
                        did_visit_children = false;
                        had_named_children = false;
                        indent_level += 1;
                    } else {
                        did_visit_children = true;
                        let start = node.start_byte();
                        let end = node.end_byte();
                        let value =
                            std::str::from_utf8(&source_code[start..end]).expect("has a string");
                        // if !is_named {
                        //     for _ in 0..indent_level {
                        //         stdout.write_all(b"  ")?;
                        //     }
                        // }
                        if !is_named && needs_newline {
                            stdout.write_all(b"\n")?;
                            for _ in 0..indent_level {
                                stdout.write_all(b"  ")?;
                            }
                        }
                        write!(&mut stdout, "{}", html_escape::encode_text(value))?;
                    }
                }
            }
            cursor.reset(tree.root_node());
            println!();
        }

        if opts.output == ParseOutput::Dot {
            util::print_tree_graph(&tree, "log.html", opts.open_log).unwrap();
        }

        let mut first_error = None;
        loop {
            let node = cursor.node();
            if node.has_error() {
                if node.is_error() || node.is_missing() {
                    first_error = Some(node);
                    break;
                }
                if !cursor.goto_first_child() {
                    break;
                }
            } else if !cursor.goto_next_sibling() {
                break;
            }
        }

        if first_error.is_some() || opts.print_time {
            write!(
                &mut stdout,
                "{:width$}\t{duration_ms:>7.2} ms\t{:>6} bytes/ms",
                opts.path.to_str().unwrap(),
                (source_code.len() as u128 * 1_000_000) / duration.as_nanos(),
                width = opts.max_path_length
            )?;
            if let Some(node) = first_error {
                let start = node.start_position();
                let end = node.end_position();
                write!(&mut stdout, "\t(")?;
                if node.is_missing() {
                    if node.is_named() {
                        write!(&mut stdout, "MISSING {}", node.kind())?;
                    } else {
                        write!(
                            &mut stdout,
                            "MISSING \"{}\"",
                            node.kind().replace('\n', "\\n")
                        )?;
                    }
                } else {
                    write!(&mut stdout, "{}", node.kind())?;
                }
                write!(
                    &mut stdout,
                    " [{}, {}] - [{}, {}])",
                    start.row, start.column, end.row, end.column
                )?;
            }
            writeln!(&mut stdout)?;
        }

        return Ok(ParseResult {
            successful: first_error.is_none(),
            bytes: source_code.len(),
            duration: Some(duration),
        });
    }
    parser.stop_printing_dot_graphs();

    if opts.print_time {
        let duration = time.elapsed();
        let duration_ms = duration.as_micros() as f64 / 1e3;
        writeln!(
            &mut stdout,
            "{:width$}\t{duration_ms:>7.2} ms\t(timed out)",
            opts.path.to_str().unwrap(),
            width = opts.max_path_length
        )?;
    }

    Ok(ParseResult {
        successful: false,
        bytes: source_code.len(),
        duration: None,
    })
}

const fn escape_invisible(c: char) -> Option<&'static str> {
    Some(match c {
        '\n' => "\\n",
        '\r' => "\\r",
        '\t' => "\\t",
        '\0' => "\\0",
        '\\' => "\\\\",
        '\x0b' => "\\v",
        '\x0c' => "\\f",
        _ => return None,
    })
}

fn render_node_text(source: &str) -> String {
    let mut escaped = String::new();
    escaped.reserve(source.len());

    for c in source.chars() {
        if let Some(esc) = escape_invisible(c) {
            escaped.push_str(esc);
        } else {
            escaped.push(c);
        }
    }

    escaped
}

#[allow(clippy::too_many_arguments)]
fn write_node_text(
    opts: &ParseFileOptions,
    stdout: &mut StdoutLock<'static>,
    cursor: &TreeCursor,
    source: &str,
    color: Option<impl Into<Color> + Copy>,
    quote: char,
    row_width: usize,
    indent_level: usize,
) -> Result<()> {
    if source.find('\n') == Some(source.len() - 1)
        || source.find('\n').is_none()
        || !cursor.node().is_named()
    {
        write!(
            stdout,
            "{quote}{}{quote}",
            paint(color, &render_node_text(source))
        )?;
    } else {
        for line in source.split_inclusive('\n') {
            if line.is_empty() {
                break;
            }
            if !opts.no_ranges {
                write!(
                    stdout,
                    "\n{}{}{quote}{}{quote}",
                    render_node_range(opts, cursor, row_width),
                    "  ".repeat(indent_level + 1),
                    &paint(color, &render_node_text(line)),
                )?;
            } else {
                write!(
                    stdout,
                    "\n{}{quote}{}{quote}",
                    "  ".repeat(indent_level + 1),
                    &paint(color, &render_node_text(line)),
                )?;
            }
        }
    }

    Ok(())
}

fn render_node_range(opts: &ParseFileOptions, cursor: &TreeCursor, row_width: usize) -> String {
    let node = cursor.node();
    let is_named = node.is_named();
    let start = node.start_position();
    let end = node.end_position();
    let range_color = if is_named && cursor.field_name().is_none() {
        opts.parse_theme.row_color_named
    } else {
        opts.parse_theme.row_color
    };
    paint(
        range_color,
        &format!(
            "{:row_width$}:{:<3} - {:row_width$}:{:<3}",
            start.row, start.column, end.row, end.column,
        ),
    )
}

fn cst_render_node(
    opts: &ParseFileOptions,
    cursor: &mut TreeCursor,
    source_code: &[u8],
    stdout: &mut StdoutLock<'static>,
    row_width: usize,
    indent_level: usize,
) -> Result<()> {
    let node = cursor.node();
    let is_named = node.is_named();
    if !opts.no_ranges {
        write!(stdout, "{}", render_node_range(opts, cursor, row_width))?;
    }
    write!(stdout, "{}", "  ".repeat(indent_level))?;
    if is_named {
        if let Some(field_name) = cursor.field_name() {
            write!(
                stdout,
                "{}",
                paint(opts.parse_theme.field, &format!("{field_name}: "))
            )?;
        }
        let kind_color = if node.is_error() {
            opts.parse_theme.error
        } else if node.is_extra() || node.parent().is_some_and(|p| p.is_extra()) {
            opts.parse_theme.extra
        } else {
            opts.parse_theme.node_kind
        };
        write!(stdout, "{} ", paint(kind_color, node.kind()))?;
        if node.child_count() == 0 {
            let color = if source_code.is_utf8() {
                opts.parse_theme.node_text
            } else {
                opts.parse_theme.error
            };
            write_node_text(
                opts,
                stdout,
                cursor,
                &String::from_utf8_lossy(&source_code[node.start_byte()..node.end_byte()]),
                color,
                '`',
                row_width,
                indent_level,
            )?;
        }
    } else {
        let color = if node.is_missing() || !source_code.is_utf8() {
            opts.parse_theme.error
        } else {
            opts.parse_theme.node_text
        };
        if node.is_missing() {
            write!(
                stdout,
                "{}",
                &format!("{}: \"{}\"", paint(color, "MISSING"), node.kind())
            )?;
        } else {
            write_node_text(
                opts,
                stdout,
                cursor,
                &String::from_utf8_lossy(&source_code[node.start_byte()..node.end_byte()]),
                color,
                '\"',
                row_width,
                indent_level,
            )?;
        }
    }
    writeln!(stdout)?;

    Ok(())
}

pub fn perform_edit(tree: &mut Tree, input: &mut Vec<u8>, edit: &Edit) -> Result<InputEdit> {
    let start_byte = edit.position;
    let old_end_byte = edit.position + edit.deleted_length;
    let new_end_byte = edit.position + edit.inserted_text.len();
    let start_position = position_for_offset(input, start_byte)?;
    let old_end_position = position_for_offset(input, old_end_byte)?;
    input.splice(start_byte..old_end_byte, edit.inserted_text.iter().copied());
    let new_end_position = position_for_offset(input, new_end_byte)?;
    let edit = InputEdit {
        start_byte,
        old_end_byte,
        new_end_byte,
        start_position,
        old_end_position,
        new_end_position,
    };
    tree.edit(&edit);
    Ok(edit)
}

fn parse_edit_flag(source_code: &[u8], flag: &str) -> Result<Edit> {
    let error = || {
        anyhow!(concat!(
            "Invalid edit string '{}'. ",
            "Edit strings must match the pattern '<START_BYTE_OR_POSITION> <REMOVED_LENGTH> <NEW_TEXT>'"
        ), flag)
    };

    // Three whitespace-separated parts:
    // * edit position
    // * deleted length
    // * inserted text
    let mut parts = flag.split(' ');
    let position = parts.next().ok_or_else(error)?;
    let deleted_length = parts.next().ok_or_else(error)?;
    let inserted_text = parts.collect::<Vec<_>>().join(" ").into_bytes();

    // Position can either be a byte_offset or row,column pair, separated by a comma
    let position = if position == "$" {
        source_code.len()
    } else if position.contains(',') {
        let mut parts = position.split(',');
        let row = parts.next().ok_or_else(error)?;
        let row = row.parse::<usize>().map_err(|_| error())?;
        let column = parts.next().ok_or_else(error)?;
        let column = column.parse::<usize>().map_err(|_| error())?;
        offset_for_position(source_code, Point { row, column })?
    } else {
        position.parse::<usize>().map_err(|_| error())?
    };

    // Deleted length must be a byte count.
    let deleted_length = deleted_length.parse::<usize>().map_err(|_| error())?;

    Ok(Edit {
        position,
        deleted_length,
        inserted_text,
    })
}

pub fn offset_for_position(input: &[u8], position: Point) -> Result<usize> {
    let mut row = 0;
    let mut offset = 0;
    let mut iter = memchr::memchr_iter(b'\n', input);
    loop {
        if let Some(pos) = iter.next() {
            if row < position.row {
                row += 1;
                offset = pos;
                continue;
            }
        }
        offset += 1;
        break;
    }
    if position.row - row > 0 {
        return Err(anyhow!("Failed to address a row: {}", position.row));
    }
    if let Some(pos) = iter.next() {
        if (pos - offset < position.column) || (input[offset] == b'\n' && position.column > 0) {
            return Err(anyhow!("Failed to address a column: {}", position.column));
        };
    } else if input.len() - offset < position.column {
        return Err(anyhow!("Failed to address a column over the end"));
    }
    Ok(offset + position.column)
}

pub fn position_for_offset(input: &[u8], offset: usize) -> Result<Point> {
    if offset > input.len() {
        return Err(anyhow!("Failed to address an offset: {offset}"));
    }
    let mut result = Point { row: 0, column: 0 };
    let mut last = 0;
    for pos in memchr::memchr_iter(b'\n', &input[..offset]) {
        result.row += 1;
        last = pos;
    }
    result.column = if result.row > 0 {
        offset - last - 1
    } else {
        offset
    };
    Ok(result)
}
