use super::error::Result;
use super::util;
use std::fs;
use std::io::{self, Write};
use std::path::Path;
use tree_sitter::{Language, LogType, Parser};

pub fn parse_file_at_path(
    language: Language,
    path: &Path,
    debug: bool,
    debug_graph: bool,
) -> Result<()> {
    let mut parser = Parser::new();
    parser.set_language(language)?;
    let source_code = fs::read_to_string(path)?;

    let mut log_session = None;

    if debug_graph {
        log_session = Some(util::start_logging_graphs(&mut parser, "log.html")?);
    } else if debug {
        parser.set_logger(Some(Box::new(|log_type, message| {
            if log_type == LogType::Lex {
                io::stderr().write(b"  ").unwrap();
            }
            write!(&mut io::stderr(), "{}\n", message).unwrap();
        })));
    }

    let tree = parser
        .parse_str(&source_code, None)
        .expect("Incompatible language version");

    if let Some(log_session) = log_session {
        util::stop_logging_graphs(&mut parser, log_session)?;
    }

    let stdout = io::stdout();
    let mut stdout = stdout.lock();
    let mut cursor = tree.walk();
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

    println!("");
    Ok(())
}
