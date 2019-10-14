use super::error::{Error, Result};
use std::fs;
use std::io::{self, Write};
use std::path::Path;
use tree_sitter::{Language, Node, Parser, Query, QueryCursor};

pub fn query_files_at_paths(
    language: Language,
    paths: Vec<&Path>,
    query_path: &Path,
    ordered_captures: bool,
) -> Result<()> {
    let stdout = io::stdout();
    let mut stdout = stdout.lock();

    let query_source = fs::read_to_string(query_path).map_err(Error::wrap(|| {
        format!("Error reading query file {:?}", query_path)
    }))?;
    let query = Query::new(language, &query_source)
        .map_err(|e| Error::new(format!("Query compilation failed: {:?}", e)))?;

    let mut query_cursor = QueryCursor::new();

    let mut parser = Parser::new();
    parser.set_language(language).map_err(|e| e.to_string())?;

    for path in paths {
        writeln!(&mut stdout, "{}", path.to_str().unwrap())?;

        let source_code = fs::read(path).map_err(Error::wrap(|| {
            format!("Error reading source file {:?}", path)
        }))?;
        let text_callback = |n: Node| &source_code[n.byte_range()];
        let tree = parser.parse(&source_code, None).unwrap();

        if ordered_captures {
            for (mat, capture_index) in
                query_cursor.captures(&query, tree.root_node(), text_callback)
            {
                let capture = mat.captures[capture_index];
                writeln!(
                    &mut stdout,
                    "    pattern: {}, capture: {}, row: {}, text: {:?}",
                    mat.pattern_index,
                    &query.capture_names()[capture.index as usize],
                    capture.node.start_position().row,
                    capture.node.utf8_text(&source_code).unwrap_or("")
                )?;
            }
        } else {
            for m in query_cursor.matches(&query, tree.root_node(), text_callback) {
                writeln!(&mut stdout, "  pattern: {}", m.pattern_index)?;
                for capture in m.captures {
                    writeln!(
                        &mut stdout,
                        "    capture: {}, row: {}, text: {:?}",
                        &query.capture_names()[capture.index as usize],
                        capture.node.start_position().row,
                        capture.node.utf8_text(&source_code).unwrap_or("")
                    )?;
                }
            }
        }
    }

    Ok(())
}
