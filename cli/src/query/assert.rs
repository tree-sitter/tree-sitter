use crate::error;
use crate::error::Result;
use crate::test_highlight::parse_highlight_test;
use std::collections::hash_map::HashMap;
use std::fs;
use tree_sitter::{Language, Parser, Point};

#[derive(Debug, Eq, PartialEq)]
pub struct CaptureInfo {
    pub name: String,
    pub position: Point,
}

pub fn assert_expected_captures(
    infos: Vec<CaptureInfo>,
    path: String,
    parser: &mut Parser,
    language: Language,
) -> Result<()> {
    let contents = fs::read_to_string(path)?;
    let pairs = parse_highlight_test(parser, language, contents.as_bytes())?;

    let per_position_index: HashMap<Point, &String> =
        pairs.iter().map(|a| (a.position, &a.expected)).collect();

    for info in &infos {
        if !per_position_index.contains_key(&info.position) {
            continue;
        }
        let found = per_position_index.get(&info.position).unwrap();
        if **found != info.name && info.name != "name" {
            Err(error::Error::new(format!(
                "Assertion failed: at {}, found {}, expected {}",
                info.position, info.name, found
            )))?
        }
    }
    Ok(())
}
