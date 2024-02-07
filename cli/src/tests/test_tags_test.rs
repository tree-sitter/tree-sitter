use super::helpers::fixtures::{get_language, get_tags_config};
use crate::query_testing::{parse_position_comments, Assertion};
use crate::test_tags::get_tag_positions;
use tree_sitter::{Parser, Point};
use tree_sitter_tags::TagsContext;

#[test]
fn test_tags_test_with_basic_test() {
    let language = get_language("python");
    let config = get_tags_config("python");
    let source = [
        "# hi",
        "def abc(d):",
        "    # <- definition.function",
        "    e = fgh(d)",
        "    #    ^ reference.call",
        "    return d(e)",
        "    #      ^ reference.call",
        "    #        ^ !variable.parameter",
        "",
    ]
    .join("\n");

    let assertions =
        parse_position_comments(&mut Parser::new(), &language, source.as_bytes()).unwrap();

    assert_eq!(
        assertions,
        &[
            Assertion::new(1, 4, false, String::from("definition.function")),
            Assertion::new(3, 9, false, String::from("reference.call")),
            Assertion::new(5, 11, false, String::from("reference.call")),
            Assertion::new(5, 13, true, String::from("variable.parameter")),
        ]
    );

    let mut tags_context = TagsContext::new();
    let tag_positions = get_tag_positions(&mut tags_context, &config, source.as_bytes()).unwrap();
    assert_eq!(
        tag_positions,
        &[
            (
                Point::new(1, 4),
                Point::new(1, 7),
                "definition.function".to_string()
            ),
            (
                Point::new(3, 8),
                Point::new(3, 11),
                "reference.call".to_string()
            ),
            (
                Point::new(5, 11),
                Point::new(5, 12),
                "reference.call".to_string()
            ),
        ]
    );
}
