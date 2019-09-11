use super::helpers::allocations;
use super::helpers::fixtures::get_language;
use tree_sitter::{Parser, Query, QueryError, QueryMatch};

#[test]
fn test_query_errors_on_invalid_syntax() {
    allocations::start_recording();

    let language = get_language("javascript");

    assert!(Query::new(language, "(if_statement)").is_ok());
    assert!(Query::new(language, "(if_statement condition:(identifier))").is_ok());

    // Mismatched parens
    assert_eq!(
        Query::new(language, "(if_statement"),
        Err(QueryError::Syntax(13))
    );
    assert_eq!(
        Query::new(language, "(if_statement))"),
        Err(QueryError::Syntax(14))
    );

    // Return an error at the *beginning* of a bare identifier not followed a colon.
    // If there's a colon but no pattern, return an error at the end of the colon.
    assert_eq!(
        Query::new(language, "(if_statement identifier)"),
        Err(QueryError::Syntax(14))
    );
    assert_eq!(
        Query::new(language, "(if_statement condition:)"),
        Err(QueryError::Syntax(24))
    );

    assert_eq!(
        Query::new(language, "(if_statement condition:)"),
        Err(QueryError::Syntax(24))
    );

    allocations::stop_recording();
}

#[test]
fn test_query_errors_on_invalid_symbols() {
    allocations::start_recording();

    let language = get_language("javascript");

    assert_eq!(
        Query::new(language, "(non_existent1)"),
        Err(QueryError::NodeType("non_existent1"))
    );
    assert_eq!(
        Query::new(language, "(if_statement (non_existent2))"),
        Err(QueryError::NodeType("non_existent2"))
    );
    assert_eq!(
        Query::new(language, "(if_statement condition: (non_existent3))"),
        Err(QueryError::NodeType("non_existent3"))
    );
    assert_eq!(
        Query::new(language, "(if_statement not_a_field: (identifier))"),
        Err(QueryError::Field("not_a_field"))
    );

    allocations::stop_recording();
}

#[test]
fn test_query_capture_names() {
    allocations::start_recording();

    let language = get_language("javascript");
    let query = Query::new(
        language,
        r#"
        (if_statement
          condition: (binary_expression
            left: * @left-operand
            operator: "||"
            right: * @right-operand)
          consequence: (statement_block) @body)

        (while_statement
          condition:* @loop-condition)
        "#,
    )
    .unwrap();

    assert_eq!(
        query.capture_names(),
        &[
            "left-operand".to_string(),
            "right-operand".to_string(),
            "body".to_string(),
            "loop-condition".to_string(),
        ]
    );

    drop(query);
    allocations::stop_recording();
}

#[test]
fn test_query_exec_with_simple_pattern() {
    allocations::start_recording();

    let language = get_language("javascript");
    let query = Query::new(
        language,
        "(function_declaration name: (identifier) @fn-name)",
    )
    .unwrap();

    let source = "function one() { two(); function three() {} }";
    let mut parser = Parser::new();
    parser.set_language(language).unwrap();
    let tree = parser.parse(source, None).unwrap();

    let context = query.context();
    let matches = context.exec(tree.root_node());

    assert_eq!(
        collect_matches(matches, &query, source),
        &[
            (0, vec![("fn-name", "one")]),
            (0, vec![("fn-name", "three")])
        ],
    );

    drop(context);
    drop(parser);
    drop(query);
    drop(tree);
    allocations::stop_recording();
}

#[test]
fn test_query_exec_with_multiple_matches_same_root() {
    allocations::start_recording();

    let language = get_language("javascript");
    let query = Query::new(
        language,
        "(class_declaration
            name: (identifier) @the-class-name
            (class_body
                (method_definition
                    name: (property_identifier) @the-method-name)))",
    )
    .unwrap();

    let source = "
        class Person {
            // the constructor
            constructor(name) { this.name = name; }

            // the getter
            getFullName() { return this.name; }
        }
    ";

    let mut parser = Parser::new();
    parser.set_language(language).unwrap();
    let tree = parser.parse(source, None).unwrap();
    let context = query.context();
    let matches = context.exec(tree.root_node());

    assert_eq!(
        collect_matches(matches, &query, source),
        &[
            (
                0,
                vec![
                    ("the-class-name", "Person"),
                    ("the-method-name", "constructor")
                ]
            ),
            (
                0,
                vec![
                    ("the-class-name", "Person"),
                    ("the-method-name", "getFullName")
                ]
            ),
        ],
    );

    drop(context);
    drop(parser);
    drop(query);
    drop(tree);
    allocations::stop_recording();
}

#[test]
fn test_query_exec_multiple_patterns() {
    allocations::start_recording();

    let language = get_language("javascript");
    let query = Query::new(
        language,
        "
            (function_declaration name:(identifier) @fn-def)
            (call_expression function:(identifier) @fn-ref)
        ",
    )
    .unwrap();

    let source = "
        function f1() {
            f2(f3());
        }
    ";

    let mut parser = Parser::new();
    parser.set_language(language).unwrap();
    let tree = parser.parse(source, None).unwrap();
    let context = query.context();
    let matches = context.exec(tree.root_node());

    assert_eq!(
        collect_matches(matches, &query, source),
        &[
            (0, vec![("fn-def", "f1")]),
            (1, vec![("fn-ref", "f2")]),
            (1, vec![("fn-ref", "f3")]),
        ],
    );

    drop(context);
    drop(parser);
    drop(query);
    drop(tree);
    allocations::stop_recording();
}

fn collect_matches<'a>(
    matches: impl Iterator<Item = QueryMatch<'a>>,
    query: &'a Query,
    source: &'a str,
) -> Vec<(usize, Vec<(&'a str, &'a str)>)> {
    matches
        .map(|m| {
            (
                m.pattern_index(),
                m.captures()
                    .map(|(capture_id, node)| {
                        (
                            query.capture_names()[capture_id].as_str(),
                            node.utf8_text(source.as_bytes()).unwrap(),
                        )
                    })
                    .collect(),
            )
        })
        .collect()
}
