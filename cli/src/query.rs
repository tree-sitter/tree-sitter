use crate::query_testing;
use anyhow::{Context, Result};
use std::{
    fs,
    io::{self, Write},
    ops::Range,
    path::Path,
    time::Instant,
};
use tree_sitter::{Language, Parser, Point, Query, QueryCursor};

pub fn query_files_at_paths(
    language: Language,
    paths: Vec<String>,
    query_path: &Path,
    ordered_captures: bool,
    byte_range: Option<Range<usize>>,
    point_range: Option<Range<Point>>,
    should_test: bool,
    quiet: bool,
    print_time: bool,
) -> Result<()> {
    let stdout = io::stdout();
    let mut stdout = stdout.lock();

    let query_source = fs::read_to_string(query_path)
        .with_context(|| format!("Error reading query file {:?}", query_path))?;
    let query = Query::new(language, &query_source).with_context(|| "Query compilation failed")?;

    let mut query_cursor = QueryCursor::new();
    if let Some(range) = byte_range {
        query_cursor.set_byte_range(range);
    }
    if let Some(range) = point_range {
        query_cursor.set_point_range(range);
    }

    let mut parser = Parser::new();
    parser.set_language(language)?;

    for path in paths {
        let mut results = Vec::new();

        writeln!(&mut stdout, "{}", path)?;

        let source_code =
            fs::read(&path).with_context(|| format!("Error reading source file {:?}", path))?;
        let tree = parser.parse(&source_code, None).unwrap();

        let start = Instant::now();
        if ordered_captures {
            for (mat, capture_index) in
                query_cursor.captures(&query, tree.root_node(), source_code.as_slice())
            {
                let capture = mat.captures[capture_index];
                let capture_name = &query.capture_names()[capture.index as usize];
                if !quiet {
                    writeln!(
                        &mut stdout,
                        "    pattern: {:>2}, capture: {} - {}, start: {}, end: {}, text: `{}`",
                        mat.pattern_index,
                        capture.index,
                        capture_name,
                        capture.node.start_position(),
                        capture.node.end_position(),
                        capture.node.utf8_text(&source_code).unwrap_or("")
                    )?;
                }
                results.push(query_testing::CaptureInfo {
                    name: capture_name.to_string(),
                    start: capture.node.start_position(),
                    end: capture.node.end_position(),
                });
            }
        } else {
            for m in query_cursor.matches(&query, tree.root_node(), source_code.as_slice()) {
                if !quiet {
                    writeln!(&mut stdout, "  pattern: {}", m.pattern_index)?;
                }
                for capture in m.captures {
                    let start = capture.node.start_position();
                    let end = capture.node.end_position();
                    let capture_name = &query.capture_names()[capture.index as usize];
                    if !quiet {
                        if end.row == start.row {
                            writeln!(
                                &mut stdout,
                                "    capture: {} - {}, start: {}, end: {}, text: `{}`",
                                capture.index,
                                capture_name,
                                start,
                                end,
                                capture.node.utf8_text(&source_code).unwrap_or("")
                            )?;
                        } else {
                            writeln!(
                                &mut stdout,
                                "    capture: {}, start: {}, end: {}",
                                capture_name, start, end,
                            )?;
                        }
                    }
                    results.push(query_testing::CaptureInfo {
                        name: capture_name.to_string(),
                        start: capture.node.start_position(),
                        end: capture.node.end_position(),
                    });
                }
            }
        }
        if query_cursor.did_exceed_match_limit() {
            writeln!(
                &mut stdout,
                "  WARNING: Query exceeded maximum number of in-progress captures!"
            )?;
        }
        if should_test {
            query_testing::assert_expected_captures(results, path, &mut parser, language)?
        }
        if print_time {
            writeln!(&mut stdout, "{:?}", start.elapsed())?;
        }
    }

    Ok(())
}
