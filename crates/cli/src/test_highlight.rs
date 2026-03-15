use std::{fs, path::Path};

use anyhow::{Result, anyhow};
use tree_sitter::Point;
use tree_sitter_highlight::{Highlight, HighlightConfiguration, HighlightEvent, Highlighter};
use tree_sitter_loader::{Config, Loader};

use crate::{
    query_testing::{Assertion, Utf8Point, parse_position_comments, to_utf8_point},
    test::{TestInfo, TestOutcome, TestResult, TestSummary},
    util,
};

#[derive(Debug)]
pub struct Failure {
    pub row: usize,
    pub column: usize,
    pub expected_highlight: String,
    pub actual_highlights: Vec<String>,
}

impl std::error::Error for Failure {}

impl std::fmt::Display for Failure {
    fn fmt(&self, f: &mut std::fmt::Formatter) -> std::fmt::Result {
        write!(
            f,
            "Failure - row: {}, column: {}, expected highlight '{}', actual highlights: ",
            self.row, self.column, self.expected_highlight
        )?;
        if self.actual_highlights.is_empty() {
            write!(f, "none.")?;
        } else {
            for (i, actual_highlight) in self.actual_highlights.iter().enumerate() {
                if i > 0 {
                    write!(f, ", ")?;
                }
                write!(f, "'{actual_highlight}'")?;
            }
        }
        Ok(())
    }
}

pub fn test_highlights(
    loader: &Loader,
    loader_config: &Config,
    highlighter: &mut Highlighter,
    directory: &Path,
    test_summary: &mut TestSummary,
) -> Result<()> {
    let mut failed = false;

    for highlight_test_file in fs::read_dir(directory)? {
        let highlight_test_file = highlight_test_file?;
        let test_file_path = highlight_test_file.path();
        let test_file_name = highlight_test_file.file_name();
        if test_file_path.is_dir() && test_file_path.read_dir()?.next().is_some() {
            test_summary
                .highlight_results
                .add_group(test_file_name.to_string_lossy().as_ref());
            if test_highlights(
                loader,
                loader_config,
                highlighter,
                &test_file_path,
                test_summary,
            )
            .is_err()
            {
                failed = true;
            }
            test_summary.highlight_results.pop_traversal();
        } else {
            let (language, language_config) = loader
                .language_configuration_for_file_name(&test_file_path)?
                .ok_or_else(|| {
                    anyhow!(
                        "{}",
                        util::lang_not_found_for_path(test_file_path.as_path(), loader_config)
                    )
                })?;
            let highlight_config = language_config
                .highlight_config(language, None)?
                .ok_or_else(|| {
                    anyhow!(
                        "No highlighting config found for {}",
                        test_file_path.display()
                    )
                })?;
            match test_highlight(
                loader,
                highlighter,
                highlight_config,
                fs::read(&test_file_path)?.as_slice(),
            ) {
                Ok(assertion_count) => {
                    test_summary.highlight_results.add_case(TestResult {
                        name: test_file_name.to_string_lossy().to_string(),
                        info: TestInfo::AssertionTest {
                            outcome: TestOutcome::AssertionPassed { assertion_count },
                            test_num: test_summary.test_num,
                        },
                    });
                }
                Err(e) => {
                    test_summary.highlight_results.add_case(TestResult {
                        name: test_file_name.to_string_lossy().to_string(),
                        info: TestInfo::AssertionTest {
                            outcome: TestOutcome::AssertionFailed {
                                error: e.to_string(),
                            },
                            test_num: test_summary.test_num,
                        },
                    });
                    failed = true;
                }
            }
            test_summary.test_num += 1;
        }
    }

    if failed { Err(anyhow!("")) } else { Ok(()) }
}

pub fn iterate_assertions(
    assertions: &[Assertion],
    highlights: &[HighlightPosition],
    highlight_names: &[String],
) -> Result<usize> {
    // Iterate through all of the highlighting assertions, checking each one against the
    // actual highlights.
    let mut actual_highlights = Vec::new();
    for Assertion {
        position,
        length,
        negative,
        expected_capture_name: expected_highlight,
    } in assertions
    {
        let mut found = false;

        let end_column = position.column + length - 1;
        actual_highlights.clear();

        // Iterate through all of the highlights that start at or before this assertion's
        // position, looking for one that matches the assertion.
        for highlight in highlights {
            // The assertions are ordered by position, so skip past all of the highlights that
            // end at or before this assertion's position.
            if highlight.end <= *position {
                continue;
            }

            // Once we've moved on to the next line or passed the end of the assertion, stop
            // looping.
            if highlight.start.row > position.row ||
                highlight.start.row == position.row && highlight.start.column > end_column {
                break;
            }

            let highlight_name = &highlight_names[(highlight.highlight).0];
            if highlight_name == expected_highlight {
                found = true;
            }

            // If the highlight matches the assertion, or if the highlight doesn't
            // match the assertion but it's negative, this test passes. Otherwise,
            // add this highlight to the list of actual highlights that span the
            // assertion's position, in order to generate an error message in the event
            // of a failure.
            if (*highlight_name == *expected_highlight) == *negative {
                actual_highlights.push(highlight_name);
            }
        }

        if found == *negative {
            let expected_highlight = if *negative {
                format!("!{}", expected_highlight)
            } else {
                expected_highlight.clone()
            };
            return Err(Failure {
                row: position.row,
                column: end_column,
                expected_highlight,
                actual_highlights: actual_highlights.into_iter().cloned().collect(),
            }
            .into());
        }
    }

    Ok(assertions.len())
}

pub fn test_highlight(
    loader: &Loader,
    highlighter: &mut Highlighter,
    highlight_config: &HighlightConfiguration,
    source: &[u8],
) -> Result<usize> {
    // Highlight the file, and parse out all of the highlighting assertions.
    let highlight_names = loader.highlight_names();
    let highlights = get_highlight_positions(loader, highlighter, highlight_config, source)?;
    let assertions =
        parse_position_comments(highlighter.parser(), &highlight_config.language, source)?;

    iterate_assertions(&assertions, &highlights, &highlight_names)
}

#[derive(Debug, PartialEq, Eq)]
pub struct HighlightPosition {
    pub start: Utf8Point,
    pub end: Utf8Point,
    pub highlight: Highlight,
}

pub fn get_highlight_positions(
    loader: &Loader,
    highlighter: &mut Highlighter,
    highlight_config: &HighlightConfiguration,
    source: &[u8],
) -> Result<Vec<HighlightPosition>> {
    let mut row = 0;
    let mut column = 0;
    let mut byte_offset = 0;
    let mut was_newline = false;
    let mut result = Vec::new();
    let mut highlight_stack = Vec::new();
    let source = String::from_utf8_lossy(source);
    let mut char_indices = source.char_indices();
    for event in
        highlighter.highlight(highlight_config, source.as_bytes(), None, None, |string| {
            loader.highlight_config_for_injection_string(string)
        })?
    {
        match event? {
            HighlightEvent::HighlightStart(h) => highlight_stack.push(h),
            HighlightEvent::HighlightEnd => {
                highlight_stack.pop();
            }
            HighlightEvent::Source { start, end } => {
                let mut start_position = Point::new(row, column);
                while byte_offset < end {
                    if byte_offset <= start {
                        start_position = Point::new(row, column);
                    }
                    if let Some((i, c)) = char_indices.next() {
                        if was_newline {
                            row += 1;
                            column = 0;
                        } else {
                            column += i - byte_offset;
                        }
                        was_newline = c == '\n';
                        byte_offset = i;
                    } else {
                        break;
                    }
                }
                if let Some(highlight) = highlight_stack.last().cloned() {
                    let start = to_utf8_point(start_position, source.as_bytes());
                    let end =
                        to_utf8_point(Point::new(row, column), source.as_bytes());
                    result.push(HighlightPosition { start, end, highlight });
                }
            }
        }
    }
    Ok(result)
}
