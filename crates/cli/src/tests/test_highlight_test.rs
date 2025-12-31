use tree_sitter::Parser;
use tree_sitter_highlight::{Highlight, Highlighter};

use super::helpers::fixtures::{get_highlight_config, get_language, test_loader};
use crate::{
    query_testing::{parse_position_comments, Assertion, Utf8Point},
    test_highlight::{get_highlight_positions, iterate_assertions, Failure},
};

#[test]
fn test_highlight_test_with_basic_test() {
    let language = get_language("javascript");
    let config = get_highlight_config(
        "javascript",
        Some("injections.scm"),
        &[
            "function".to_string(),
            "variable".to_string(),
            "keyword".to_string(),
        ],
    );
    let source = [
        "// hi",
        "var abc = function(d) {",
        "  // ^ function",
        "  //       ^^^ keyword",
        "  return d + e;",
        "  //     ^ variable",
        "  //       ^ !variable",
        "};",
        "var y̆y̆y̆y̆ = function() {}",
        "  // ^ function",
        "  //       ^ keyword",
    ]
    .join("\n");

    let assertions =
        parse_position_comments(&mut Parser::new(), &language, source.as_bytes()).unwrap();
    assert_eq!(
        assertions,
        &[
            Assertion::new(1, 5, 1, false, String::from("function")),
            Assertion::new(1, 11, 3, false, String::from("keyword")),
            Assertion::new(4, 9, 1, false, String::from("variable")),
            Assertion::new(4, 11, 1, true, String::from("variable")),
            Assertion::new(8, 5, 1, false, String::from("function")),
            Assertion::new(8, 11, 1, false, String::from("keyword")),
        ]
    );

    let mut highlighter = Highlighter::new();
    let highlight_positions =
        get_highlight_positions(test_loader(), &mut highlighter, &config, source.as_bytes())
            .unwrap();
    assert_eq!(
        highlight_positions,
        &[
            (Utf8Point::new(1, 0), Utf8Point::new(1, 3), Highlight(2)), // "var"
            (Utf8Point::new(1, 4), Utf8Point::new(1, 7), Highlight(0)), // "abc"
            (Utf8Point::new(1, 10), Utf8Point::new(1, 18), Highlight(2)), // "function"
            (Utf8Point::new(1, 19), Utf8Point::new(1, 20), Highlight(1)), // "d"
            (Utf8Point::new(4, 2), Utf8Point::new(4, 8), Highlight(2)), // "return"
            (Utf8Point::new(4, 9), Utf8Point::new(4, 10), Highlight(1)), // "d"
            (Utf8Point::new(4, 13), Utf8Point::new(4, 14), Highlight(1)), // "e"
            (Utf8Point::new(8, 0), Utf8Point::new(8, 3), Highlight(2)), // "var"
            (Utf8Point::new(8, 4), Utf8Point::new(8, 8), Highlight(0)), // "y̆y̆y̆y̆"
            (Utf8Point::new(8, 11), Utf8Point::new(8, 19), Highlight(2)), // "function"
        ]
    );
}

#[test]
fn test_assertion_with_non_matching_highlight_at_same_position() {
    // Test that an assertion fails when the highlight at the position does not match

    let highlight_names = vec!["keyword".to_string(), "variable".to_string()];

    let assertions = vec![Assertion::new(1, 0, 1, false, String::from("keyword"))];

    let highlights = vec![
        (Utf8Point::new(1, 0), Utf8Point::new(1, 5), Highlight(1)), // "variable" highlight
    ];

    let result = iterate_assertions(&assertions, &highlights, &highlight_names);

    assert!(result.is_err());
    let err = result.unwrap_err().downcast::<Failure>().unwrap();
    assert_eq!(err.row, 1);
    assert_eq!(err.column, 0);
    assert_eq!(err.expected_highlight, "keyword");
    assert_eq!(err.actual_highlights, vec!["variable".to_string()]);
}

#[test]
fn test_assertion_with_exact_matching_highlight() {
    // Test exact match: assertion and highlight have same start and end

    let highlight_names = vec!["keyword".to_string()];

    let assertions = vec![Assertion::new(0, 5, 3, false, String::from("keyword"))];

    let highlights = vec![(Utf8Point::new(0, 5), Utf8Point::new(0, 8), Highlight(0))];

    let result = iterate_assertions(&assertions, &highlights, &highlight_names);

    assert!(result.is_ok());
    assert_eq!(result.unwrap(), 1);
}

#[test]
fn test_assertion_contained_within_highlight() {
    // Test where assertion is fully contained within a larger highlight

    let highlight_names = vec!["keyword".to_string()];

    let assertions = vec![Assertion::new(0, 3, 2, false, String::from("keyword"))];

    let highlights = vec![(Utf8Point::new(0, 0), Utf8Point::new(0, 10), Highlight(0))];

    let result = iterate_assertions(&assertions, &highlights, &highlight_names);

    assert!(result.is_ok());
    assert_eq!(result.unwrap(), 1);
}

#[test]
fn test_assertion_overlapping_highlight_start() {
    // Test where assertion starts before highlight but overlaps with it

    let highlight_names = vec!["keyword".to_string()];

    let assertions = vec![Assertion::new(0, 3, 4, false, String::from("keyword"))];

    let highlights = vec![(Utf8Point::new(0, 5), Utf8Point::new(0, 10), Highlight(0))];

    let result = iterate_assertions(&assertions, &highlights, &highlight_names);

    assert!(result.is_ok());
    assert_eq!(result.unwrap(), 1);
}

#[test]
fn test_assertion_with_no_highlights() {
    // Test that an assertion fails when there are no highlights at all

    let highlight_names = vec!["keyword".to_string()];

    let assertions = vec![Assertion::new(0, 0, 1, false, String::from("keyword"))];

    let highlights = vec![];

    let result = iterate_assertions(&assertions, &highlights, &highlight_names);

    assert!(result.is_err());
    let err = result.unwrap_err().downcast::<Failure>().unwrap();
    assert_eq!(err.row, 0);
    assert_eq!(err.column, 0);
    assert_eq!(err.expected_highlight, "keyword");
    assert_eq!(err.actual_highlights, Vec::<String>::new());
}

#[test]
fn test_assertion_with_highlight_ending_before() {
    // Test where highlight ends before the assertion starts

    let highlight_names = vec!["keyword".to_string()];

    let assertions = vec![Assertion::new(0, 10, 1, false, String::from("keyword"))];

    let highlights = vec![(Utf8Point::new(0, 0), Utf8Point::new(0, 5), Highlight(0))];

    let result = iterate_assertions(&assertions, &highlights, &highlight_names);

    assert!(result.is_err());
    let err = result.unwrap_err().downcast::<Failure>().unwrap();
    assert_eq!(err.row, 0);
    assert_eq!(err.column, 10);
    assert_eq!(err.expected_highlight, "keyword");
    assert_eq!(err.actual_highlights, Vec::<String>::new());
}

#[test]
fn test_negative_assertion_with_non_matching_highlight() {
    // Test that a negative assertion passes when the specified highlight is NOT present

    let highlight_names = vec!["keyword".to_string(), "variable".to_string()];

    let assertions = vec![Assertion::new(0, 0, 1, true, String::from("keyword"))];

    let highlights = vec![
        (Utf8Point::new(0, 0), Utf8Point::new(0, 5), Highlight(1)), // "variable" highlight
    ];

    let result = iterate_assertions(&assertions, &highlights, &highlight_names);

    assert!(result.is_ok());
    assert_eq!(result.unwrap(), 1);
}

#[test]
fn test_negative_assertion_with_matching_highlight() {
    // Test that a negative assertion fails when the specified highlight IS present

    let highlight_names = vec!["keyword".to_string()];

    let assertions = vec![Assertion::new(0, 0, 1, true, String::from("keyword"))];

    let highlights = vec![
        (Utf8Point::new(0, 0), Utf8Point::new(0, 5), Highlight(0)), // "keyword" highlight
    ];

    let result = iterate_assertions(&assertions, &highlights, &highlight_names);

    assert!(result.is_err());
    let err = result.unwrap_err().downcast::<Failure>().unwrap();
    assert_eq!(err.row, 0);
    assert_eq!(err.column, 0);
    assert_eq!(err.expected_highlight, "!keyword");
    assert_eq!(err.actual_highlights, vec!["keyword".to_string()]);
}

#[test]
fn test_multiple_assertions_sequential() {
    // Test multiple assertions in sequence with non-overlapping highlights

    let highlight_names = vec!["keyword".to_string(), "variable".to_string()];

    let assertions = vec![
        Assertion::new(0, 0, 3, false, String::from("keyword")),
        Assertion::new(0, 10, 1, false, String::from("variable")),
    ];

    let highlights = vec![
        (Utf8Point::new(0, 0), Utf8Point::new(0, 3), Highlight(0)), // "keyword"
        (Utf8Point::new(0, 10), Utf8Point::new(0, 11), Highlight(1)), // "variable"
    ];

    let result = iterate_assertions(&assertions, &highlights, &highlight_names);

    assert!(result.is_ok());
    assert_eq!(result.unwrap(), 2);
}

#[test]
fn test_multiple_highlights_at_same_position() {
    // Test where multiple highlights overlap at the assertion position

    let highlight_names = vec![
        "keyword".to_string(),
        "variable".to_string(),
        "function".to_string(),
    ];

    let assertions = vec![Assertion::new(0, 5, 1, false, String::from("variable"))];

    let highlights = vec![
        (Utf8Point::new(0, 0), Utf8Point::new(0, 10), Highlight(0)), // "keyword" spans entire range
        (Utf8Point::new(0, 5), Utf8Point::new(0, 8), Highlight(1)), // "variable" at assertion position
        (Utf8Point::new(0, 7), Utf8Point::new(0, 12), Highlight(2)), // "function" overlaps
    ];

    let result = iterate_assertions(&assertions, &highlights, &highlight_names);

    assert!(result.is_ok());
    assert_eq!(result.unwrap(), 1);
}

#[test]
fn test_assertions_across_multiple_rows() {
    // Test assertions on different rows

    let highlight_names = vec!["keyword".to_string(), "variable".to_string()];

    let assertions = vec![
        Assertion::new(0, 5, 3, false, String::from("keyword")),
        Assertion::new(2, 10, 1, false, String::from("variable")),
    ];

    let highlights = vec![
        (Utf8Point::new(0, 5), Utf8Point::new(0, 8), Highlight(0)), // "keyword" on row 0
        (Utf8Point::new(2, 10), Utf8Point::new(2, 11), Highlight(1)), // "variable" on row 2
    ];

    let result = iterate_assertions(&assertions, &highlights, &highlight_names);

    assert!(result.is_ok());
    assert_eq!(result.unwrap(), 2);
}
