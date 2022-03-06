use super::helpers::fixtures::{get_highlight_config, get_language, test_loader};
use crate::query_testing::{parse_position_comments, Assertion};
use crate::test_highlight::get_highlight_positions;
use tree_sitter::{Parser, Point};
use tree_sitter_highlight::{Highlight, Highlighter};

#[test]
fn test_highlight_test_with_basic_test() {
    let language = get_language("javascript");
    let config = get_highlight_config(
        "javascript",
        Some("injections.scm"),
        &[
            "function".to_string(),
            "variable.parameter".to_string(),
            "keyword".to_string(),
        ],
    );
    let source = [
        "// hi",
        "var abc = function(d) {",
        "  // ^ function",
        "  //       ^ keyword",
        "  return d + e;",
        "  //     ^ variable.parameter",
        "};",
    ]
    .join("\n");

    let assertions =
        parse_position_comments(&mut Parser::new(), language, source.as_bytes()).unwrap();
    assert_eq!(
        assertions,
        &[
            Assertion {
                position: Point::new(1, 5),
                expected_capture_name: "function".to_string()
            },
            Assertion {
                position: Point::new(1, 11),
                expected_capture_name: "keyword".to_string()
            },
            Assertion {
                position: Point::new(4, 9),
                expected_capture_name: "variable.parameter".to_string()
            },
        ]
    );

    let mut highlighter = Highlighter::new();
    let highlight_positions =
        get_highlight_positions(test_loader(), &mut highlighter, &config, source.as_bytes())
            .unwrap();
    assert_eq!(
        highlight_positions,
        &[
            (Point::new(1, 0), Point::new(1, 3), Highlight(2)), // "var"
            (Point::new(1, 4), Point::new(1, 7), Highlight(0)), // "abc"
            (Point::new(1, 10), Point::new(1, 18), Highlight(2)), // "function"
            (Point::new(1, 19), Point::new(1, 20), Highlight(1)), // "d"
            (Point::new(4, 2), Point::new(4, 8), Highlight(2)), // "return"
            (Point::new(4, 9), Point::new(4, 10), Highlight(1)), // "d"
        ]
    );
}
