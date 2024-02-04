use super::util;
use anyhow::{anyhow, Context, Result};
use std::io::{self, Write};
use std::path::Path;
use std::sync::atomic::AtomicUsize;
use std::time::Instant;
use std::{fmt, fs, usize};
use tree_sitter::{ffi, InputEdit, Language, LogType, Parser, Point, Tree};

#[derive(Debug)]
pub struct Edit {
    pub position: usize,
    pub deleted_length: usize,
    pub inserted_text: Vec<u8>,
}

#[derive(Debug, Default)]
pub struct Stats {
    pub successful_parses: usize,
    pub total_parses: usize,
}

impl fmt::Display for Stats {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        writeln!(f, "Total parses: {}; successful parses: {}; failed parses: {}; success percentage: {:.2}%",
                 self.total_parses,
                 self.successful_parses,
                 self.total_parses - self.successful_parses,
                 (self.successful_parses as f64) / (self.total_parses as f64) * 100.0)
    }
}

#[derive(Copy, Clone)]
pub enum ParseOutput {
    Normal,
    Quiet,
    Xml,
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
}

pub fn parse_file_at_path(parser: &mut Parser, opts: &ParseFileOptions) -> Result<bool> {
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
        _log_session = Some(util::log_graphs(parser, "log.html")?);
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
    fn is_utf16_bom(bom_bytes: &[u8]) -> bool {
        bom_bytes == [0xFF, 0xFE] || bom_bytes == [0xFE, 0xFF]
    }

    let tree = match opts.encoding {
        Some(encoding) if encoding == ffi::TSInputEncodingUTF16 => {
            let source_code_utf16 = source_code
                .chunks_exact(2)
                .map(|chunk| u16::from_le_bytes([chunk[0], chunk[1]]))
                .collect::<Vec<_>>();
            parser.parse_utf16(&source_code_utf16, None)
        }
        None if source_code.len() >= 2 && is_utf16_bom(&source_code[0..2]) => {
            let source_code_utf16 = source_code
                .chunks_exact(2)
                .map(|chunk| u16::from_le_bytes([chunk[0], chunk[1]]))
                .collect::<Vec<_>>();
            parser.parse_utf16(&source_code_utf16, None)
        }
        _ => parser.parse(&source_code, None),
    };

    parser.stop_printing_dot_graphs();

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

        let duration = time.elapsed();
        let duration_ms =
            duration.as_secs() * 1000 + u64::from(duration.subsec_nanos()) / 1_000_000;
        let mut cursor = tree.walk();

        if matches!(opts.output, ParseOutput::Normal) {
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
                        write!(
                            &mut stdout,
                            "({} [{}, {}] - [{}, {}]",
                            node.kind(),
                            start.row,
                            start.column,
                            end.row,
                            end.column
                        )?;
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

        if matches!(opts.output, ParseOutput::Xml) {
            let mut needs_newline = false;
            let mut indent_level = 0;
            let mut did_visit_children = false;
            let mut tags: Vec<&str> = Vec::new();
            loop {
                let node = cursor.node();
                let is_named = node.is_named();
                if did_visit_children {
                    if is_named {
                        let tag = tags.pop();
                        writeln!(&mut stdout, "</{}>", tag.expect("there is a tag"))?;
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
                        write!(&mut stdout, "<{}", node.kind())?;
                        if let Some(field_name) = cursor.field_name() {
                            write!(&mut stdout, " type=\"{field_name}\"")?;
                        }
                        write!(&mut stdout, ">")?;
                        tags.push(node.kind());
                        needs_newline = true;
                    }
                    if cursor.goto_first_child() {
                        did_visit_children = false;
                        indent_level += 1;
                    } else {
                        did_visit_children = true;
                        let start = node.start_byte();
                        let end = node.end_byte();
                        let value =
                            std::str::from_utf8(&source_code[start..end]).expect("has a string");
                        write!(&mut stdout, "{}", html_escape::encode_text(value))?;
                    }
                }
            }
            cursor.reset(tree.root_node());
            println!();
        }

        if matches!(opts.output, ParseOutput::Dot) {
            util::print_tree_graph(&tree, "log.html").unwrap();
        }

        let mut first_error = None;
        loop {
            let node = cursor.node();
            if node.has_error() {
                if node.is_error() || node.is_missing() {
                    first_error = Some(node);
                    break;
                } else if !cursor.goto_first_child() {
                    break;
                }
            } else if !cursor.goto_next_sibling() {
                break;
            }
        }

        if first_error.is_some() || opts.print_time {
            write!(
                &mut stdout,
                "{:width$}\t{duration_ms} ms",
                opts.path.to_str().unwrap(),
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

        return Ok(first_error.is_some());
    } else if opts.print_time {
        let duration = time.elapsed();
        let duration_ms =
            duration.as_secs() * 1000 + u64::from(duration.subsec_nanos()) / 1_000_000;
        writeln!(
            &mut stdout,
            "{:width$}\t{duration_ms} ms (timed out)",
            opts.path.to_str().unwrap(),
            width = opts.max_path_length
        )?;
    }

    Ok(false)
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
