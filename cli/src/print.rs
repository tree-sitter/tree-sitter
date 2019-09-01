use super::error::{Result};
use std::io::{Write};
use tree_sitter::{TreeCursor};

pub fn print_tree(output: &mut Write, cursor: &mut TreeCursor, prints_position: bool) -> Result<()> {
    let mut needs_newline = false;
    let mut indent_level = 0;
    let mut did_visit_children = false;
    loop {
        let node = cursor.node();
        let is_named = node.is_named();
        if did_visit_children {
            if is_named {
                output.write(b")")?;
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
                    output.write(b"\n")?;
                }
                for _ in 0..indent_level {
                    output.write(b"  ")?;
                }
                if let Some(field_name) = cursor.field_name() {
                    write!(output, "{}: ", field_name)?;
                }
                write!(output, "({}", node.kind())?;
                if prints_position {
                    let start = node.start_position();
                    let end = node.end_position();
                    write!(
                        output,
                        " [{}, {}] - [{}, {}]",
                        start.row,
                        start.column,
                        end.row,
                        end.column
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
    return Ok(());
}
