use super::error::{Error, Result};
use super::util;
use std::io::{self, Write};
use std::path::Path;
use std::sync::{atomic::AtomicUsize, Arc};
use std::time::Instant;
use std::{fmt, fs, usize};
use tree_sitter::{InputEdit, Language, LogType, Parser, Point, Tree};

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
        return writeln!(f, "Total parses: {}; successful parses: {}; failed parses: {}; success percentage: {:.2}%",
                 self.total_parses,
                 self.successful_parses,
                 self.total_parses - self.successful_parses,
                 (self.successful_parses as f64) / (self.total_parses as f64) * 100.0);
    }
}

pub fn parse_file_at_path(
    language: Language,
    path: &Path,
    edits: &Vec<&str>,
    max_path_length: usize,
    quiet: bool,
    print_time: bool,
    timeout: u64,
    debug: bool,
    debug_graph: bool,
    debug_xml: bool,
    cancellation_flag: Option<Arc<AtomicUsize>>,
) -> Result<bool> {
    let mut _log_session = None;
    let mut parser = Parser::new();
    parser.set_language(language).map_err(|e| e.to_string())?;
    let mut source_code = fs::read(path).map_err(Error::wrap(|| {
        format!("Error reading source file {:?}", path)
    }))?;

    // If the `--cancel` flag was passed, then cancel the parse
    // when the user types a newline.
    parser.set_cancellation_flag(cancellation_flag);

    // Set a timeout based on the `--time` flag.
    parser.set_timeout_micros(timeout);

    // Render an HTML graph if `--debug-graph` was passed
    if debug_graph {
        _log_session = Some(util::log_graphs(&mut parser, "log.html")?);
    }
    // Log to stderr if `--debug` was passed
    else if debug {
        parser.set_logger(Some(Box::new(|log_type, message| {
            if log_type == LogType::Lex {
                io::stderr().write(b"  ").unwrap();
            }
            write!(&mut io::stderr(), "{}\n", message).unwrap();
        })));
    }

    let time = Instant::now();
    let tree = parser.parse(&source_code, None);

    let stdout = io::stdout();
    let mut stdout = stdout.lock();

    if let Some(mut tree) = tree {
        if debug_graph && !edits.is_empty() {
            println!("BEFORE:\n{}", String::from_utf8_lossy(&source_code));
        }

        for (i, edit) in edits.iter().enumerate() {
            let edit = parse_edit_flag(&source_code, edit)?;
            perform_edit(&mut tree, &mut source_code, &edit);
            tree = parser.parse(&source_code, Some(&tree)).unwrap();

            if debug_graph {
                println!("AFTER {}:\n{}", i, String::from_utf8_lossy(&source_code));
            }
        }

        let duration = time.elapsed();
        let duration_ms = duration.as_secs() * 1000 + duration.subsec_nanos() as u64 / 1000000;
        let mut cursor = tree.walk();

        if !quiet {
            let mut needs_newline = false;
            let mut indent_level = 0;
            let mut did_visit_children = false;
            loop {
                let node = cursor.node();
                let is_named = node.is_named();
                if did_visit_children {
                    if is_named {
                        stdout.write(b")")?;
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
                            stdout.write(b"\n")?;
                        }
                        for _ in 0..indent_level {
                            stdout.write(b"  ")?;
                        }
                        let start = node.start_position();
                        let end = node.end_position();
                        if let Some(field_name) = cursor.field_name() {
                            write!(&mut stdout, "{}: ", field_name)?;
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
            println!("");
        }

        if debug_xml {
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
                        write!(&mut stdout, "</{}>\n", tag.expect("there is a tag"))?;
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
                            stdout.write(b"\n")?;
                        }
                        for _ in 0..indent_level {
                            stdout.write(b"  ")?;
                        }
                        write!(&mut stdout, "<{}", node.kind())?;
                        if let Some(field_name) = cursor.field_name() {
                            write!(&mut stdout, " type=\"{}\"", field_name)?;
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
                        let value = std::str::from_utf8(&source_code[start..end]).expect("has a string");
                        write!(&mut stdout, "{}", html_escape::encode_text(value))?;
                    }
                }
            }
            cursor.reset(tree.root_node());
            println!("");
        }

        let mut first_error = None;
        loop {
            let node = cursor.node();
            if node.has_error() {
                if node.is_error() || node.is_missing() {
                    first_error = Some(node);
                    break;
                } else {
                    if !cursor.goto_first_child() {
                        break;
                    }
                }
            } else if !cursor.goto_next_sibling() {
                break;
            }
        }

        if first_error.is_some() || print_time {
            write!(
                &mut stdout,
                "{:width$}\t{} ms",
                path.to_str().unwrap(),
                duration_ms,
                width = max_path_length
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
                            node.kind().replace("\n", "\\n")
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
            write!(&mut stdout, "\n")?;
        }

        return Ok(first_error.is_some());
    } else if print_time {
        let duration = time.elapsed();
        let duration_ms = duration.as_secs() * 1000 + duration.subsec_nanos() as u64 / 1000000;
        writeln!(
            &mut stdout,
            "{:width$}\t{} ms (timed out)",
            path.to_str().unwrap(),
            duration_ms,
            width = max_path_length
        )?;
    }

    Ok(false)
}

pub fn perform_edit(tree: &mut Tree, input: &mut Vec<u8>, edit: &Edit) -> InputEdit {
    let start_byte = edit.position;
    let old_end_byte = edit.position + edit.deleted_length;
    let new_end_byte = edit.position + edit.inserted_text.len();
    let start_position = position_for_offset(input, start_byte);
    let old_end_position = position_for_offset(input, old_end_byte);
    input.splice(start_byte..old_end_byte, edit.inserted_text.iter().cloned());
    let new_end_position = position_for_offset(input, new_end_byte);
    let edit = InputEdit {
        start_byte,
        old_end_byte,
        new_end_byte,
        start_position,
        old_end_position,
        new_end_position,
    };
    tree.edit(&edit);
    edit
}

fn parse_edit_flag(source_code: &Vec<u8>, flag: &str) -> Result<Edit> {
    let error = || {
        Error::from(format!(concat!(
            "Invalid edit string '{}'. ",
            "Edit strings must match the pattern '<START_BYTE_OR_POSITION> <REMOVED_LENGTH> <NEW_TEXT>'"
        ), flag))
    };

    // Three whitespace-separated parts:
    // * edit position
    // * deleted length
    // * inserted text
    let mut parts = flag.split(" ");
    let position = parts.next().ok_or_else(error)?;
    let deleted_length = parts.next().ok_or_else(error)?;
    let inserted_text = parts.collect::<Vec<_>>().join(" ").into_bytes();

    // Position can either be a byte_offset or row,column pair, separated by a comma
    let position = if position.contains(",") {
        let mut parts = position.split(",");
        let row = parts.next().ok_or_else(error)?;
        let row = usize::from_str_radix(row, 10).map_err(|_| error())?;
        let column = parts.next().ok_or_else(error)?;
        let column = usize::from_str_radix(column, 10).map_err(|_| error())?;
        offset_for_position(source_code, Point { row, column })
    } else {
        usize::from_str_radix(position, 10).map_err(|_| error())?
    };

    // Deleted length must be a byte count.
    let deleted_length = usize::from_str_radix(deleted_length, 10).map_err(|_| error())?;

    Ok(Edit {
        position,
        deleted_length,
        inserted_text,
    })
}

fn offset_for_position(input: &Vec<u8>, position: Point) -> usize {
    let mut current_position = Point { row: 0, column: 0 };
    for (i, c) in input.iter().enumerate() {
        if *c as char == '\n' {
            current_position.row += 1;
            current_position.column = 0;
        } else {
            current_position.column += 1;
        }
        if current_position > position {
            return i;
        }
    }
    return input.len();
}

fn position_for_offset(input: &Vec<u8>, offset: usize) -> Point {
    let mut result = Point { row: 0, column: 0 };
    for c in &input[0..offset] {
        if *c as char == '\n' {
            result.row += 1;
            result.column = 0;
        } else {
            result.column += 1;
        }
    }
    result
}
