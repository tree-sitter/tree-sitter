use crate::error;
use crate::error::Result;
use crate::test_highlight::parse_highlight_test;
use lazy_static::lazy_static;
use regex::Regex;
use std::collections::hash_map::HashMap;
use std::fs;
use tree_sitter::{Language, Parser, Point};

// TODO: It would be cooler to do this with a comments query rather than with a regex
// directly.
lazy_static! {
    static ref METADATA_REGEX: Regex = Regex::new(r#"(\w+): ([^\s,]+), (\d+), (\d+)"#).unwrap();
}

#[derive(Debug, Eq, PartialEq)]
pub struct CaptureInfo {
    pub name: String,
    pub position: Point,
}

#[derive(Debug, Eq, PartialEq)]
struct Assertion {
    position: Point,
    expected: String,
}

impl From<&(Point, String)> for Assertion {
    fn from(item: &(Point, String)) -> Assertion {
        let (pos, info) = item;
        Assertion {
            position: *pos,
            expected: info.to_string(),
        }
    }
}

pub fn assert_expected_captures(
    infos: Vec<CaptureInfo>,
    path: String,
    parser: &mut Parser,
    language: Language,
) -> Result<()> {
    let contents = fs::read_to_string(path)?;
    let pairs = parse_highlight_test(parser, language, contents.as_bytes())?;
    println!("{:?}", pairs);

    let assertions: Vec<Assertion> = pairs.iter().map(Assertion::from).collect();

    let per_position_index: HashMap<Point, &Assertion> =
        assertions.iter().map(|a| (a.position, a)).collect();

    for info in &infos {
        if !per_position_index.contains_key(&info.position) {
            continue;
        }
        let found = per_position_index.get(&info.position).unwrap();
        if found.expected != info.name && info.name != "name" {
            Err(error::Error::new(format!(
                "Assertion failed: at {}, found {}, expected {}",
                info.position, info.name, found.expected
            )))?
        }
    }
    Ok(())
}
