use super::helpers::fixtures::{get_highlight_config, get_language, test_loader};
use crate::test_highlight::{get_highlight_positions, parse_highlight_test};
use tree_sitter::{Parser, Point};
use tree_sitter_highlight::{Highlight, Highlighter};

#[test]
fn test_highlight_test_with_basic_test() {
    let language = get_language("javascript");
    let config = get_highlight_config(
        "javascript",
        "injections.scm",
        &[
            "function".to_string(),
            "variable.parameter".to_string(),
            "keyword".to_string(),
        ],
    );
    let source = [
        "var abc = function(d) {",
        "  // ^ function",
        "  //       ^ keyword",
        "  return d + e;",
        "  //     ^ variable.parameter",
        "};",
    ]
    .join("\n");

    let assertions = parse_highlight_test(&mut Parser::new(), language, source.as_bytes()).unwrap();
    assert_eq!(
        assertions,
        &[
            (Point::new(0, 5), "function".to_string()),
            (Point::new(0, 11), "keyword".to_string()),
            (Point::new(3, 9), "variable.parameter".to_string()),
        ]
    );

    let mut highlighter = Highlighter::new();
    let highlight_positions =
        get_highlight_positions(test_loader(), &mut highlighter, &config, source.as_bytes())
            .unwrap();
    assert_eq!(
        highlight_positions,
        &[
            (Point::new(0, 0), Point::new(0, 3), Highlight(2)), // "var"
            (Point::new(0, 4), Point::new(0, 7), Highlight(0)), // "abc"
            (Point::new(0, 10), Point::new(0, 18), Highlight(2)), // "function"
            (Point::new(0, 19), Point::new(0, 20), Highlight(1)), // "d"
            (Point::new(3, 2), Point::new(3, 8), Highlight(2)), // "return"
            (Point::new(3, 9), Point::new(3, 10), Highlight(1)), // "d"
        ]
    );
}
