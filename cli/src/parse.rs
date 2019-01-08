use super::error::Result;
use std::fs;
use std::path::Path;
use tree_sitter::{Language, Parser};
use std::io::{self, Write};

pub fn parse_file_at_path(language: Language, path: &Path) -> Result<()> {
    let mut parser = Parser::new();
    parser.set_language(language)?;
    let source_code = fs::read_to_string(path)?;
    let tree = parser
        .parse_str(&source_code, None)
        .expect("Incompatible language version");

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
