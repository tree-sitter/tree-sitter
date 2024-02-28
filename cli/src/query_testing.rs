use anyhow::{anyhow, Result};
use lazy_static::lazy_static;
use regex::Regex;
use std::fs;
use tree_sitter::{Language, Parser, Point};

lazy_static! {
    static ref CAPTURE_NAME_REGEX: Regex = Regex::new("[\\w_\\-.]+").unwrap();
}

#[derive(Debug, Eq, PartialEq)]
pub struct CaptureInfo {
    pub name: String,
    pub start: Point,
    pub end: Point,
}

#[derive(Debug, PartialEq, Eq)]
pub struct Assertion {
    pub position: Point,
    pub negative: bool,
    pub expected_capture_name: String,
}

impl Assertion {
    #[must_use]
    pub fn new(row: usize, col: usize, negative: bool, expected_capture_name: String) -> Self {
        Self {
            position: Point::new(row, col),
            negative,
            expected_capture_name,
        }
    }
}

/// Parse the given source code, finding all of the comments that contain
/// highlighting assertions. Return a vector of (position, expected highlight name)
/// pairs.
pub fn parse_position_comments(
    parser: &mut Parser,
    language: &Language,
    source: &[u8],
) -> Result<Vec<Assertion>> {
    let mut result = Vec::new();
    let mut assertion_ranges = Vec::new();

    // Parse the code.
    parser.set_included_ranges(&[]).unwrap();
    parser.set_language(language).unwrap();
    let tree = parser.parse(source, None).unwrap();

    // Walk the tree, finding comment nodes that contain assertions.
    let mut ascending = false;
    let mut cursor = tree.root_node().walk();
    loop {
        if ascending {
            let node = cursor.node();

            // Find every comment node.
            if node.kind().to_lowercase().contains("comment") {
                if let Ok(text) = node.utf8_text(source) {
                    let mut position = node.start_position();
                    if position.row > 0 {
                        // Find the arrow character ("^" or '<-") in the comment. A left arrow
                        // refers to the column where the comment node starts. An up arrow refers
                        // to its own column.
                        let mut has_left_caret = false;
                        let mut has_arrow = false;
                        let mut negative = false;
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

                        // find any ! after arrows but before capture name
                        if has_arrow {
                            for (i, c) in text[arrow_end..].char_indices() {
                                if c == '!' {
                                    negative = true;
                                    arrow_end += i + 1;
                                    break;
                                } else if !c.is_whitespace() {
                                    break;
                                }
                            }
                        }

                        // If the comment node contains an arrow and a highlight name, record the
                        // highlight name and the position.
                        if let (true, Some(mat)) =
                            (has_arrow, CAPTURE_NAME_REGEX.find(&text[arrow_end..]))
                        {
                            assertion_ranges.push((node.start_position(), node.end_position()));
                            result.push(Assertion {
                                position,
                                negative,
                                expected_capture_name: mat.as_str().to_string(),
                            });
                        }
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
    for assertion in &mut result {
        loop {
            let on_assertion_line = assertion_ranges[i..]
                .iter()
                .any(|(start, _)| start.row == assertion.position.row);
            if on_assertion_line {
                assertion.position.row -= 1;
            } else {
                while i < assertion_ranges.len()
                    && assertion_ranges[i].0.row < assertion.position.row
                {
                    i += 1;
                }
                break;
            }
        }
    }

    // The assertions can end up out of order due to the line adjustments.
    result.sort_unstable_by_key(|a| a.position);

    Ok(result)
}

pub fn assert_expected_captures(
    infos: &[CaptureInfo],
    path: String,
    parser: &mut Parser,
    language: &Language,
) -> Result<()> {
    let contents = fs::read_to_string(path)?;
    let pairs = parse_position_comments(parser, language, contents.as_bytes())?;
    for info in infos {
        if let Some(found) = pairs.iter().find(|p| {
            p.position.row == info.start.row && p.position >= info.start && p.position < info.end
        }) {
            if found.expected_capture_name != info.name && info.name != "name" {
                Err(anyhow!(
                    "Assertion failed: at {}, found {}, expected {}",
                    info.start,
                    found.expected_capture_name,
                    info.name
                ))?;
            }
        }
    }
    Ok(())
}
