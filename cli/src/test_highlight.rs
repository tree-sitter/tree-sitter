use super::error::Result;
use crate::loader::Loader;
use ansi_term::Colour;
use lazy_static::lazy_static;
use regex::Regex;
use std::fs;
use std::path::Path;
use tree_sitter::{Language, Parser, Point};
use tree_sitter_highlight::{Highlight, HighlightConfiguration, HighlightEvent, Highlighter};

lazy_static! {
    static ref HIGHLIGHT_NAME_REGEX: Regex = Regex::new("[\\w_\\-.]+").unwrap();
}

pub struct Failure {
    row: usize,
    column: usize,
    expected_highlight: String,
    actual_highlights: Vec<String>,
}

impl Failure {
    pub fn message(&self) -> String {
        let mut result = format!(
            "Failure - row: {}, column: {}, expected highlight '{}', actual highlights: ",
            self.row, self.column, self.expected_highlight
        );
        if self.actual_highlights.is_empty() {
            result += "none.";
        } else {
            for (i, actual_highlight) in self.actual_highlights.iter().enumerate() {
                if i > 0 {
                    result += ", ";
                }
                result += "'";
                result += actual_highlight;
                result += "'";
            }
        }
        result
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
            .ok_or_else(|| format!("No language found for path {:?}", test_file_path))?;
        let highlight_config = language_config
            .highlight_config(language)?
            .ok_or_else(|| format!("No highlighting config found for {:?}", test_file_path))?;
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
                println!("    {}", e.message());
                failed = true;
            }
        }
    }

    if failed {
        Err(String::new().into())
    } else {
        Ok(())
    }
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
    let assertions = parse_highlight_test(highlighter.parser(), highlight_config.language, source)?;

    // Iterate through all of the highlighting assertions, checking each one against the
    // actual highlights.
    let mut i = 0;
    let mut actual_highlights = Vec::<&String>::new();
    for (position, expected_highlight) in &assertions {
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

/// Parse the given source code, finding all of the comments that contain
/// highlighting assertions. Return a vector of (position, expected highlight name)
/// pairs.
pub fn parse_highlight_test(
    parser: &mut Parser,
    language: Language,
    source: &[u8],
) -> Result<Vec<(Point, String)>> {
    let mut result = Vec::new();
    let mut assertion_ranges = Vec::new();

    // Parse the code.
    parser.set_language(language).unwrap();
    let tree = parser.parse(source, None).unwrap();

    // Walk the tree, finding comment nodes that contain assertions.
    let mut ascending = false;
    let mut cursor = tree.root_node().walk();
    loop {
        if ascending {
            let node = cursor.node();

            // Find every comment node.
            if node.kind().contains("comment") {
                if let Ok(text) = node.utf8_text(source) {
                    let mut position = node.start_position();
                    if position.row == 0 {
                        continue;
                    }

                    // Find the arrow character ("^" or '<-") in the comment. A left arrow
                    // refers to the column where the comment node starts. An up arrow refers
                    // to its own column.
                    let mut has_left_caret = false;
                    let mut has_arrow = false;
                    let mut arrow_end = 0;
                    for (i, c) in text.char_indices() {
                        arrow_end = i + 1;
                        if c == '-' && has_left_caret {
                            has_arrow = true;
                            break;
                        }
                        if c == '^' {
                            has_arrow = true;
                            position.column += i;
                            break;
                        }
                        has_left_caret = c == '<';
                    }

                    // If the comment node contains an arrow and a highlight name, record the
                    // highlight name and the position.
                    if let (true, Some(mat)) =
                        (has_arrow, HIGHLIGHT_NAME_REGEX.find(&text[arrow_end..]))
                    {
                        assertion_ranges.push((node.start_position(), node.end_position()));
                        result.push((position, mat.as_str().to_string()));
                    }
                }
            }

            // Continue walking the tree.
            if cursor.goto_next_sibling() {
                ascending = false;
            } else if !cursor.goto_parent() {
                break;
            }
        } else if !cursor.goto_first_child() {
            ascending = true;
        }
    }

    // Adjust the row number in each assertion's position to refer to the line of
    // code *above* the assertion. There can be multiple lines of assertion comments,
    // so the positions may have to be decremented by more than one row.
    let mut i = 0;
    for (position, _) in result.iter_mut() {
        loop {
            let on_assertion_line = assertion_ranges[i..]
                .iter()
                .any(|(start, _)| start.row == position.row);
            if on_assertion_line {
                position.row -= 1;
            } else {
                while i < assertion_ranges.len() && assertion_ranges[i].0.row < position.row {
                    i += 1;
                }
                break;
            }
        }
    }

    // The assertions can end up out of order due to the line adjustments.
    result.sort_unstable_by_key(|a| a.0);

    Ok(result)
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
