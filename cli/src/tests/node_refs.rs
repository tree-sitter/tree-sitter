use super::helpers::fixtures::get_test_language;
use crate::generate::generate_parser_for_grammar;
use tree_sitter::Parser;

#[test]
fn test_basic_node_refs() {
    let (parser_name, parser_code) = generate_parser_for_grammar(
        r#"
        {
            "name": "test_grammar_with_refs",
            "extras": [
                {"type": "PATTERN", "value": "\\s+"}
            ],
            "rules": {
                "rule_a": {
                    "type": "SEQ",
                    "members": [
                        {
                            "type": "REF",
                            "value": "ref_1",
                            "content": {
                                "type": "STRING",
                                "value": "child-1"
                            }
                        },
                        {
                            "type": "CHOICE",
                            "members": [
                                {
                                    "type": "STRING",
                                    "value": "child-2"
                                },
                                {
                                    "type": "BLANK"
                                }
                            ]
                        },
                        {
                            "type": "REF",
                            "value": "ref_2",
                            "content": {
                                "type": "STRING",
                                "value": "child-3"
                            }
                        }
                    ]
                }
            }
        }
    "#,
    )
    .unwrap();

    let mut parser = Parser::new();
    let language = get_test_language(&parser_name, &parser_code, None);
    parser.set_language(language).unwrap();

    let tree = parser.parse("child-1 child-2 child-3", None).unwrap();
    let root_node = tree.root_node();
    assert_eq!(root_node.child_by_ref("ref_1"), root_node.child(0));
    assert_eq!(root_node.child_by_ref("ref_2"), root_node.child(2));
}
