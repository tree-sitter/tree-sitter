use std::{
    fs,
    io::{self, Write},
    ops::Range,
    path::Path,
    time::Instant,
};

use anyhow::{Context, Result};
use log::warn;
use streaming_iterator::StreamingIterator;
use tree_sitter::{Language, Parser, Point, Query, QueryCursor};

use crate::{
    query_testing::{self, to_utf8_point},
    test::{TestInfo, TestOutcome, TestResult, TestSummary},
};

#[derive(Default)]
pub struct QueryFileOptions {
    pub ordered_captures: bool,
    pub byte_range: Option<Range<usize>>,
    pub point_range: Option<Range<Point>>,
    pub quiet: bool,
    pub print_time: bool,
    pub stdin: bool,
}

pub fn query_file_at_path(
    language: &Language,
    path: &Path,
    name: &str,
    query_path: &Path,
    opts: &QueryFileOptions,
    test_summary: Option<&mut TestSummary>,
) -> Result<()> {
    let stdout = io::stdout();
    let mut stdout = stdout.lock();

    let query_source = fs::read_to_string(query_path)
        .with_context(|| format!("Error reading query file {}", query_path.display()))?;
    let query = Query::new(language, &query_source).with_context(|| "Query compilation failed")?;

    let mut query_cursor = QueryCursor::new();
    if let Some(ref range) = opts.byte_range {
        query_cursor.set_byte_range(range.clone());
    }
    if let Some(ref range) = opts.point_range {
        query_cursor.set_point_range(range.clone());
    }

    let mut parser = Parser::new();
    parser.set_language(language)?;

    let mut results = Vec::new();
    let should_test = test_summary.is_some();

    if !should_test && !opts.stdin {
        writeln!(&mut stdout, "{name}")?;
    }

    let source_code =
        fs::read(path).with_context(|| format!("Error reading source file {}", path.display()))?;
    let tree = parser.parse(&source_code, None).unwrap();

    let start = Instant::now();
    if opts.ordered_captures {
        let mut captures = query_cursor.captures(&query, tree.root_node(), source_code.as_slice());
        while let Some((mat, capture_index)) = captures.next() {
            let capture = mat.captures[*capture_index];
            let capture_name = &query.capture_names()[capture.index as usize];
            if !opts.quiet && !should_test {
                writeln!(
                        &mut stdout,
                        "    pattern: {:>2}, capture: {} - {capture_name}, start: {}, end: {}, text: `{}`",
                        mat.pattern_index,
                        capture.index,
                        capture.node.start_position(),
                        capture.node.end_position(),
                        capture.node.utf8_text(&source_code).unwrap_or("")
                    )?;
            }
            results.push(query_testing::CaptureInfo {
                name: (*capture_name).to_string(),
                start: to_utf8_point(capture.node.start_position(), source_code.as_slice()),
                end: to_utf8_point(capture.node.end_position(), source_code.as_slice()),
            });
        }
    } else {
        let mut matches = query_cursor.matches(&query, tree.root_node(), source_code.as_slice());
        while let Some(m) = matches.next() {
            if !opts.quiet && !should_test {
                writeln!(&mut stdout, "  pattern: {}", m.pattern_index)?;
            }
            for capture in m.captures {
                let start = capture.node.start_position();
                let end = capture.node.end_position();
                let capture_name = &query.capture_names()[capture.index as usize];
                if !opts.quiet && !should_test {
                    if end.row == start.row {
                        writeln!(
                                &mut stdout,
                                "    capture: {} - {capture_name}, start: {start}, end: {end}, text: `{}`",
                                capture.index,
                                capture.node.utf8_text(&source_code).unwrap_or("")
                            )?;
                    } else {
                        writeln!(
                            &mut stdout,
                            "    capture: {capture_name}, start: {start}, end: {end}",
                        )?;
                    }
                }
                results.push(query_testing::CaptureInfo {
                    name: (*capture_name).to_string(),
                    start: to_utf8_point(capture.node.start_position(), source_code.as_slice()),
                    end: to_utf8_point(capture.node.end_position(), source_code.as_slice()),
                });
            }
        }
    }
    if query_cursor.did_exceed_match_limit() {
        warn!("Query exceeded maximum number of in-progress captures!");
    }
    if should_test {
        let path_name = if opts.stdin {
            "stdin"
        } else {
            Path::new(&path).file_name().unwrap().to_str().unwrap()
        };
        // Invariant: `test_summary` will always be `Some` when `should_test` is true
        let test_summary = test_summary.unwrap();
        match query_testing::assert_expected_captures(&results, path, &mut parser, language) {
            Ok(assertion_count) => {
                test_summary.query_results.add_case(TestResult {
                    name: path_name.to_string(),
                    info: TestInfo::AssertionTest {
                        outcome: TestOutcome::AssertionPassed { assertion_count },
                        test_num: test_summary.test_num,
                    },
                });
            }
            Err(e) => {
                test_summary.query_results.add_case(TestResult {
                    name: path_name.to_string(),
                    info: TestInfo::AssertionTest {
                        outcome: TestOutcome::AssertionFailed {
                            error: e.to_string(),
                        },
                        test_num: test_summary.test_num,
                    },
                });
                return Err(e);
            }
        }
    }
    if opts.print_time {
        writeln!(&mut stdout, "{:?}", start.elapsed())?;
    }

    Ok(())
}
