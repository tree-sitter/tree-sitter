use super::error::{Error, Result};
use crate::query_testing;
use std::fs;
use std::io::{self, Write};
use std::path::Path;
use tree_sitter::{Language, Node, Parser, Query, QueryCursor};

pub fn query_files_at_paths(
    language: Language,
    paths: Vec<String>,
    query_path: &Path,
    ordered_captures: bool,
    range: Option<(usize, usize)>,
    should_test: bool,
) -> Result<()> {
    let stdout = io::stdout();
    let mut stdout = stdout.lock();

    let query_source = fs::read_to_string(query_path).map_err(Error::wrap(|| {
        format!("Error reading query file {:?}", query_path)
    }))?;
    let query = Query::new(language, &query_source)
        .map_err(|e| Error::new(format!("Query compilation failed: {:?}", e)))?;

    let mut query_cursor = QueryCursor::new();
    if let Some((beg, end)) = range {
        query_cursor.set_byte_range(beg, end);
    }

    let mut parser = Parser::new();
    parser.set_language(language).map_err(|e| e.to_string())?;

    for path in paths {
        let mut results = Vec::new();

        writeln!(&mut stdout, "{}", path)?;

        let source_code = fs::read(&path).map_err(Error::wrap(|| {
            format!("Error reading source file {:?}", path)
        }))?;
        let text_callback = |n: Node| &source_code[n.byte_range()];
        let tree = parser.parse(&source_code, None).unwrap();

        if ordered_captures {
            for (mat, capture_index) in
                query_cursor.captures(&query, tree.root_node(), text_callback)
            {
                let capture = mat.captures[capture_index];
                let capture_name = &query.capture_names()[capture.index as usize];
                writeln!(
                    &mut stdout,
                    "    pattern: {}, capture: {}, row: {}, text: {:?}",
                    mat.pattern_index,
                    capture_name,
                    capture.node.start_position().row,
                    capture.node.utf8_text(&source_code).unwrap_or("")
                )?;
                results.push(query_testing::CaptureInfo {
                    name: capture_name.to_string(),
                    start: capture.node.start_position(),
                    end: capture.node.end_position(),
                });
            }
        } else {
            for m in query_cursor.matches(&query, tree.root_node(), text_callback) {
                writeln!(&mut stdout, "  pattern: {}", m.pattern_index)?;
                for capture in m.captures {
                    let start = capture.node.start_position();
                    let end = capture.node.end_position();
                    let capture_name = &query.capture_names()[capture.index as usize];
                    if end.row == start.row {
                        writeln!(
                            &mut stdout,
                            "    capture: {}, start: {}, text: {:?}",
                            capture_name,
                            start,
                            capture.node.utf8_text(&source_code).unwrap_or("")
                        )?;
                    } else {
                        writeln!(
                            &mut stdout,
                            "    capture: {}, start: {}, end: {}",
                            capture_name, start, end,
                        )?;
                    }
                    results.push(query_testing::CaptureInfo {
                        name: capture_name.to_string(),
                        start: capture.node.start_position(),
                        end: capture.node.end_position(),
                    });
                }
            }
        }
        if should_test {
            query_testing::assert_expected_captures(results, path, &mut parser, language)?
        }
    }

    Ok(())
}
