use crate::query_testing::{parse_position_comments, Assertion};
use ansi_term::Colour;
use anyhow::{anyhow, Result};
use std::fs;
use std::path::Path;
use tree_sitter::Point;
use tree_sitter_highlight::{Highlight, HighlightConfiguration, HighlightEvent, Highlighter};
use tree_sitter_loader::Loader;

#[derive(Debug)]
pub struct Failure {
    row: usize,
    column: usize,
    expected_highlight: String,
    actual_highlights: Vec<String>,
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
                write!(f, "'{}'", actual_highlight)?;
            }
        }
        Ok(())
    }
}

pub fn test_highlights(loader: &Loader, directory: &Path) -> Result<()> {
    let mut failed = false;
    let mut highlighter = Highlighter::new();

    println!("syntax highlighting:");
    for highlight_test_file in fs::read_dir(directory)? {
        let highlight_test_file = highlight_test_file?;
        let test_file_path = highlight_test_file.path();
        let test_file_name = highlight_test_file.file_name();
        let (language, language_config) = loader
            .language_configuration_for_file_name(&test_file_path)?
            .ok_or_else(|| anyhow!("No language found for path {:?}", test_file_path))?;
        let highlight_config = language_config
            .highlight_config(language)?
            .ok_or_else(|| anyhow!("No highlighting config found for {:?}", test_file_path))?;
        match test_highlight(
            &loader,
            &mut highlighter,
            highlight_config,
            fs::read(&test_file_path)?.as_slice(),
        ) {
            Ok(assertion_count) => {
                println!(
                    "  ✓ {} ({} assertions)",
                    Colour::Green.paint(test_file_name.to_string_lossy().as_ref()),
                    assertion_count
                );
            }
            Err(e) => {
                println!(
                    "  ✗ {}",
                    Colour::Red.paint(test_file_name.to_string_lossy().as_ref())
                );
                println!("    {}", e);
                failed = true;
            }
        }
    }

    if failed {
        Err(anyhow!(""))
    } else {
        Ok(())
    }
}
pub fn iterate_assertions(
    assertions: &Vec<Assertion>,
    highlights: &Vec<(Point, Point, Highlight)>,
    highlight_names: &Vec<String>,
) -> Result<usize> {
    // Iterate through all of the highlighting assertions, checking each one against the
    // actual highlights.
    let mut i = 0;
    let mut actual_highlights = Vec::<&String>::new();
    for Assertion {
        position,
        expected_capture_name: expected_highlight,
    } in assertions
    {
        let mut passed = false;
        actual_highlights.clear();

        'highlight_loop: loop {
            // The assertions are ordered by position, so skip past all of the highlights that
            // end at or before this assertion's position.
            if let Some(highlight) = highlights.get(i) {
                if highlight.1 <= *position {
                    i += 1;
                    continue;
                }

                // Iterate through all of the highlights that start at or before this assertion's,
                // position, looking for one that matches the assertion.
                let mut j = i;
                while let (false, Some(highlight)) = (passed, highlights.get(j)) {
                    if highlight.0 > *position {
                        break 'highlight_loop;
                    }

                    // If the highlight matches the assertion, this test passes. Otherwise,
                    // add this highlight to the list of actual highlights that span the
                    // assertion's position, in order to generate an error message in the event
                    // of a failure.
                    let highlight_name = &highlight_names[(highlight.2).0];
                    if *highlight_name == *expected_highlight {
                        passed = true;
                        break 'highlight_loop;
                    } else {
                        actual_highlights.push(highlight_name);
                    }

                    j += 1;
                }
            } else {
                break;
            }
        }

        if !passed {
            return Err(Failure {
                row: position.row,
                column: position.column,
                expected_highlight: expected_highlight.clone(),
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
        parse_position_comments(highlighter.parser(), highlight_config.language, source)?;

    iterate_assertions(&assertions, &highlights, &highlight_names)?;

    // Iterate through all of the highlighting assertions, checking each one against the
    // actual highlights.
    let mut i = 0;
    let mut actual_highlights = Vec::<&String>::new();
    for Assertion {
        position,
        expected_capture_name: expected_highlight,
    } in &assertions
    {
        let mut passed = false;
        actual_highlights.clear();

        'highlight_loop: loop {
            // The assertions are ordered by position, so skip past all of the highlights that
            // end at or before this assertion's position.
            if let Some(highlight) = highlights.get(i) {
                if highlight.1 <= *position {
                    i += 1;
                    continue;
                }

                // Iterate through all of the highlights that start at or before this assertion's,
                // position, looking for one that matches the assertion.
                let mut j = i;
                while let (false, Some(highlight)) = (passed, highlights.get(j)) {
                    if highlight.0 > *position {
                        break 'highlight_loop;
                    }

                    // If the highlight matches the assertion, this test passes. Otherwise,
                    // add this highlight to the list of actual highlights that span the
                    // assertion's position, in order to generate an error message in the event
                    // of a failure.
                    let highlight_name = &highlight_names[(highlight.2).0];
                    if *highlight_name == *expected_highlight {
                        passed = true;
                        break 'highlight_loop;
                    } else {
                        actual_highlights.push(highlight_name);
                    }

                    j += 1;
                }
            } else {
                break;
            }
        }

        if !passed {
            return Err(Failure {
                row: position.row,
                column: position.column,
                expected_highlight: expected_highlight.clone(),
                actual_highlights: actual_highlights.into_iter().cloned().collect(),
            }
            .into());
        }
    }

    Ok(assertions.len())
}

pub fn get_highlight_positions(
    loader: &Loader,
    highlighter: &mut Highlighter,
    highlight_config: &HighlightConfiguration,
    source: &[u8],
) -> Result<Vec<(Point, Point, Highlight)>> {
    let mut row = 0;
    let mut column = 0;
    let mut byte_offset = 0;
    let mut was_newline = false;
    let mut result = Vec::new();
    let mut highlight_stack = Vec::new();
    let source = String::from_utf8_lossy(source);
    let mut char_indices = source.char_indices();
    for event in highlighter.highlight(highlight_config, source.as_bytes(), None, |string| {
        loader.highlight_config_for_injection_string(string)
    })? {
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
                if let Some(highlight) = highlight_stack.last() {
                    result.push((start_position, Point::new(row, column), *highlight))
                }
            }
        }
    }
    Ok(result)
}
