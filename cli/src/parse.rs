use super::error::{Error, Result};
use super::util;
use std::fs;
use std::io::{self, Write};
use std::path::Path;
use std::time::Instant;
use tree_sitter::{Language, LogType, Parser};

pub fn parse_file_at_path(
    language: Language,
    path: &Path,
    max_path_length: usize,
    quiet: bool,
    print_time: bool,
    debug: bool,
    debug_graph: bool,
) -> Result<bool> {
    let mut _log_session = None;
    let mut parser = Parser::new();
    parser.set_language(language)?;
    let source_code = fs::read(path)
        .map_err(|e| Error(format!("Error reading source file {:?}: {}", path, e)))?;

    if debug_graph {
        _log_session = Some(util::log_graphs(&mut parser, "log.html")?);
    } else if debug {
        parser.set_logger(Some(Box::new(|log_type, message| {
            if log_type == LogType::Lex {
                io::stderr().write(b"  ").unwrap();
            }
            write!(&mut io::stderr(), "{}\n", message).unwrap();
        })));
    }

    let time = Instant::now();
    let tree = parser
        .parse(&source_code, None)
        .expect("Incompatible language version");
    let duration = time.elapsed();
    let duration_ms = duration.as_secs() * 1000 + duration.subsec_nanos() as u64 / 1000000;

    let mut cursor = tree.walk();

    let stdout = io::stdout();
    let mut stdout = stdout.lock();

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

    let mut first_error = None;
    loop {
        let node = cursor.node();
        if node.has_error() {
            if node.is_error() || node.is_missing() {
                first_error = Some(node);
                break;
            } else {
                cursor.goto_first_child();
            }
        } else if !cursor.goto_next_sibling() {
            if !cursor.goto_parent() {
                break;
            }
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
            write!(
                &mut stdout,
                "\t({} [{}, {}] - [{}, {}])",
                node.kind(),
                start.row,
                start.column,
                end.row,
                end.column
            )?;
        }
        write!(&mut stdout, "\n")?;
    }

    Ok(first_error.is_some())
}
