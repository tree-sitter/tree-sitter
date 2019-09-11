use super::helpers::allocations;
use super::helpers::fixtures::get_language;
use tree_sitter::{Node, Parser, Query, QueryCursor, QueryError, QueryMatch};

#[test]
fn test_query_errors_on_invalid_syntax() {
    allocations::record(|| {
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
    });
}

#[test]
fn test_query_errors_on_invalid_symbols() {
    allocations::record(|| {
        let language = get_language("javascript");

        assert_eq!(
            Query::new(language, "(clas)"),
            Err(QueryError::NodeType("clas"))
        );
        assert_eq!(
            Query::new(language, "(if_statement (arrayyyyy))"),
            Err(QueryError::NodeType("arrayyyyy"))
        );
        assert_eq!(
            Query::new(language, "(if_statement condition: (non_existent3))"),
            Err(QueryError::NodeType("non_existent3"))
        );
        assert_eq!(
            Query::new(language, "(if_statement condit: (identifier))"),
            Err(QueryError::Field("condit"))
        );
        assert_eq!(
            Query::new(language, "(if_statement conditioning: (identifier))"),
            Err(QueryError::Field("conditioning"))
        );
    });
}

#[test]
fn test_query_matches_with_simple_pattern() {
    allocations::record(|| {
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

        let mut cursor = QueryCursor::new();
        let matches = cursor.matches(&query, tree.root_node());

        assert_eq!(
            collect_matches(matches, &query, source),
            &[
                (0, vec![("fn-name", "one")]),
                (0, vec![("fn-name", "three")])
            ],
        );
    });
}

#[test]
fn test_query_matches_with_multiple_on_same_root() {
    allocations::record(|| {
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
        let mut cursor = QueryCursor::new();
        let matches = cursor.matches(&query, tree.root_node());

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
    });
}

#[test]
fn test_query_matches_with_multiple_patterns_different_roots() {
    allocations::record(|| {
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
        let mut cursor = QueryCursor::new();
        let matches = cursor.matches(&query, tree.root_node());

        assert_eq!(
            collect_matches(matches, &query, source),
            &[
                (0, vec![("fn-def", "f1")]),
                (1, vec![("fn-ref", "f2")]),
                (1, vec![("fn-ref", "f3")]),
            ],
        );
    });
}

#[test]
fn test_query_matches_with_multiple_patterns_same_root() {
    allocations::record(|| {
        let language = get_language("javascript");
        let query = Query::new(
            language,
            "
              (pair
                key: (property_identifier) @method-def
                value: (function))

              (pair
                key: (property_identifier) @method-def
                value: (arrow_function))
            ",
        )
        .unwrap();

        let source = "
            a = {
                b: () => { return c; },
                d: function() { return d; }
            };
        ";

        let mut parser = Parser::new();
        parser.set_language(language).unwrap();
        let tree = parser.parse(source, None).unwrap();
        let mut cursor = QueryCursor::new();
        let matches = cursor.matches(&query, tree.root_node());

        assert_eq!(
            collect_matches(matches, &query, source),
            &[
                (1, vec![("method-def", "b")]),
                (0, vec![("method-def", "d")]),
            ],
        );
    });
}

#[test]
fn test_query_matches_with_nesting_and_no_fields() {
    allocations::record(|| {
        let language = get_language("javascript");
        let query = Query::new(
            language,
            "
                (array
                    (array
                        (identifier) @element-1
                        (identifier) @element-2))
            ",
        )
        .unwrap();

        let source = "
            [[a]];
            [[c, d], [e, f, g]];
            [[h], [i]];
        ";

        let mut parser = Parser::new();
        parser.set_language(language).unwrap();
        let tree = parser.parse(source, None).unwrap();
        let mut cursor = QueryCursor::new();
        let matches = cursor.matches(&query, tree.root_node());

        assert_eq!(
            collect_matches(matches, &query, source),
            &[
                (0, vec![("element-1", "c"), ("element-2", "d")]),
                (0, vec![("element-1", "e"), ("element-2", "f")]),
                (0, vec![("element-1", "f"), ("element-2", "g")]),
                (0, vec![("element-1", "e"), ("element-2", "g")]),
            ],
        );
    });
}

#[test]
fn test_query_matches_with_many() {
    allocations::record(|| {
        let language = get_language("javascript");
        let query = Query::new(language, "(array (identifier) @element)").unwrap();

        let source = "[hello];\n".repeat(50);

        let mut parser = Parser::new();
        parser.set_language(language).unwrap();
        let tree = parser.parse(&source, None).unwrap();
        let mut cursor = QueryCursor::new();
        let matches = cursor.matches(&query, tree.root_node());

        assert_eq!(
            collect_matches(matches, &query, source.as_str()),
            vec![(0, vec![("element", "hello")]); 50],
        );
    });
}

#[test]
fn test_query_matches_with_too_many_permutations_to_track() {
    allocations::record(|| {
        let language = get_language("javascript");
        let query = Query::new(
            language,
            "
            (array (identifier) @pre (identifier) @post)
        ",
        )
        .unwrap();

        let mut source = "hello, ".repeat(50);
        source.insert(0, '[');
        source.push_str("];");

        let mut parser = Parser::new();
        parser.set_language(language).unwrap();
        let tree = parser.parse(&source, None).unwrap();
        let mut cursor = QueryCursor::new();
        let matches = cursor.matches(&query, tree.root_node());

        // For this pathological query, some match permutations will be dropped.
        // Just check that a subset of the results are returned, and crash or
        // leak occurs.
        assert_eq!(
            collect_matches(matches, &query, source.as_str())[0],
            (0, vec![("pre", "hello"), ("post", "hello")]),
        );
    });
}

#[test]
fn test_query_matches_with_anonymous_tokens() {
    allocations::record(|| {
        let language = get_language("javascript");
        let query = Query::new(
            language,
            r#"
            ";" @ punctuation
            "&&" @ operator
            "#,
        )
        .unwrap();

        let source = "foo(a && b);";

        let mut parser = Parser::new();
        parser.set_language(language).unwrap();
        let tree = parser.parse(&source, None).unwrap();
        let mut cursor = QueryCursor::new();
        let matches = cursor.matches(&query, tree.root_node());

        assert_eq!(
            collect_matches(matches, &query, source),
            &[
                (1, vec![("operator", "&&")]),
                (0, vec![("punctuation", ";")]),
            ]
        );
    });
}

#[test]
fn test_query_matches_within_byte_range() {
    allocations::record(|| {
        let language = get_language("javascript");
        let query = Query::new(language, "(identifier) @element").unwrap();

        let source = "[a, b, c, d, e, f, g]";

        let mut parser = Parser::new();
        parser.set_language(language).unwrap();
        let tree = parser.parse(&source, None).unwrap();

        let mut cursor = QueryCursor::new();
        let matches = cursor
            .set_byte_range(5, 15)
            .matches(&query, tree.root_node());

        assert_eq!(
            collect_matches(matches, &query, source),
            &[
                (0, vec![("element", "c")]),
                (0, vec![("element", "d")]),
                (0, vec![("element", "e")]),
            ]
        );
    });
}

#[test]
fn test_query_matches_different_queries_same_cursor() {
    allocations::record(|| {
        let language = get_language("javascript");
        let query1 = Query::new(
            language,
            "
            (array (identifier) @id1)
        ",
        )
        .unwrap();
        let query2 = Query::new(
            language,
            "
            (array (identifier) @id1)
            (pair (identifier) @id2)
        ",
        )
        .unwrap();
        let query3 = Query::new(
            language,
            "
            (array (identifier) @id1)
            (pair (identifier) @id2)
            (parenthesized_expression (identifier) @id3)
        ",
        )
        .unwrap();

        let source = "[a, {b: b}, (c)];";

        let mut parser = Parser::new();
        let mut cursor = QueryCursor::new();

        parser.set_language(language).unwrap();
        let tree = parser.parse(&source, None).unwrap();

        let matches = cursor.matches(&query1, tree.root_node());
        assert_eq!(
            collect_matches(matches, &query1, source),
            &[(0, vec![("id1", "a")]),]
        );

        let matches = cursor.matches(&query3, tree.root_node());
        assert_eq!(
            collect_matches(matches, &query3, source),
            &[
                (0, vec![("id1", "a")]),
                (1, vec![("id2", "b")]),
                (2, vec![("id3", "c")]),
            ]
        );

        let matches = cursor.matches(&query2, tree.root_node());
        assert_eq!(
            collect_matches(matches, &query2, source),
            &[(0, vec![("id1", "a")]), (1, vec![("id2", "b")]),]
        );
    });
}

#[test]
fn test_query_captures() {
    allocations::record(|| {
        let language = get_language("javascript");
        let query = Query::new(
            language,
            r#"
            (pair
              key: * @method.def
              (function
                name: (identifier) @method.alias))

            (variable_declarator
              name: * @function.def
              value: (function
                name: (identifier) @function.alias))

            ":" @delimiter
            "=" @operator
            "#,
        )
        .unwrap();

        let source = "
          a({
            bc: function de() {
              const fg = function hi() {}
            },
            jk: function lm() {
              const no = function pq() {}
            },
          });
        ";

        let mut parser = Parser::new();
        parser.set_language(language).unwrap();
        let tree = parser.parse(&source, None).unwrap();
        let mut cursor = QueryCursor::new();
        let matches = cursor.matches(&query, tree.root_node());

        assert_eq!(
            collect_matches(matches, &query, source),
            &[
                (2, vec![("delimiter", ":")]),
                (0, vec![("method.def", "bc"), ("method.alias", "de")]),
                (3, vec![("operator", "=")]),
                (1, vec![("function.def", "fg"), ("function.alias", "hi")]),
                (2, vec![("delimiter", ":")]),
                (0, vec![("method.def", "jk"), ("method.alias", "lm")]),
                (3, vec![("operator", "=")]),
                (1, vec![("function.def", "no"), ("function.alias", "pq")]),
            ],
        );

        let captures = cursor.captures(&query, tree.root_node());
        assert_eq!(
            collect_captures(captures, &query, source),
            &[
                ("method.def", "bc"),
                ("delimiter", ":"),
                ("method.alias", "de"),
                ("function.def", "fg"),
                ("operator", "="),
                ("function.alias", "hi"),
                ("method.def", "jk"),
                ("delimiter", ":"),
                ("method.alias", "lm"),
                ("function.def", "no"),
                ("operator", "="),
                ("function.alias", "pq"),
            ]
        );
    });
}

#[test]
fn test_query_capture_names() {
    allocations::record(|| {
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
    });
}

#[test]
fn test_query_comments() {
    allocations::record(|| {
        let language = get_language("javascript");
        let query = Query::new(
            language,
            "
                ; this is my first comment
                ; i have two comments here
                (function_declaration
                    ; there is also a comment here
                    ; and here
                    name: (identifier) @fn-name)",
        )
        .unwrap();

        let source = "function one() { }";
        let mut parser = Parser::new();
        parser.set_language(language).unwrap();
        let tree = parser.parse(source, None).unwrap();
        let mut cursor = QueryCursor::new();
        let matches = cursor.matches(&query, tree.root_node());
        assert_eq!(
            collect_matches(matches, &query, source),
            &[(0, vec![("fn-name", "one")]),],
        );
    });
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
                collect_captures(m.captures(), query, source),
            )
        })
        .collect()
}

fn collect_captures<'a, 'b>(
    captures: impl Iterator<Item = (usize, Node<'a>)>,
    query: &'b Query,
    source: &'b str,
) -> Vec<(&'b str, &'b str)> {
    captures
        .map(|(capture_id, node)| {
            (
                query.capture_names()[capture_id].as_str(),
                node.utf8_text(source.as_bytes()).unwrap(),
            )
        })
        .collect()
}
