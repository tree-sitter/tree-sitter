use super::super::error::Result;
use lazy_static::lazy_static;
use regex::Regex;
use tree_sitter::Point;

// TODO: It would be cooler to do this with a comments query rather than with a regex
// directly.
lazy_static! {
    static ref METADATA_PAIR_REGEX: Regex = Regex::new(r#"(\w+): ([^\s,]+)"#).unwrap();
    static ref NUMBER_REGEX: Regex = Regex::new(r#"\d+"#).unwrap();
}

pub struct CaptureInfo {
    pub name: String,
}

#[derive(Debug, Eq, PartialEq)]
struct Assertion {
    position: Point,
    line_numbers: Vec<usize>,
    capture_type: String,
}

pub fn assert_expected_captures(_captures: Vec<CaptureInfo>, _path: String) -> Result<()> {
    Ok(())
}
