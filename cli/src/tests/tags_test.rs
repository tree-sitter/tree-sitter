use super::helpers::fixtures::get_language;
use tree_sitter_tags::{TagKind, TagsConfiguration, TagsContext};

#[test]
fn test_tags_python() {
    let language = get_language("python");
    let tags_config = TagsConfiguration::new(
        language,
        r#"
        ((function_definition
            name: (identifier) @name
            body: (block . (expression_statement (string) @doc))) @function
         (set! strip @doc "(^['\"\\s]*)|(['\"\\s]*$)"))
        (function_definition
            name: (identifier) @name) @function
        ((class_definition
            name: (identifier) @name
            body: (block . (expression_statement (string) @doc))) @class
         (set! strip @doc "(^['\"\\s]*)|(['\"\\s]*$)"))
        (class_definition
            name: (identifier) @name) @class
        (call
            function: (identifier) @name) @call
        "#,
        "",
    )
    .unwrap();

    let mut tag_context = TagsContext::new();
    let tags = tag_context
        .generate_tags(
            &tags_config,
            br#"
        class Customer:
            """
            Data about a customer
            """

            def age(self):
                '''
                Get the customer's age
                '''
                compute_age(self.id)
        }
        "#,
        )
        .collect::<Vec<_>>();

    assert_eq!(
        tags.iter().map(|t| (t.name, t.kind)).collect::<Vec<_>>(),
        &[
            ("Customer", TagKind::Class),
            ("age", TagKind::Function),
            ("compute_age", TagKind::Call),
        ]
    );

    assert_eq!(tags[0].docs.as_ref().unwrap(), "Data about a customer");
    assert_eq!(tags[0].line, "class Customer:");
    assert_eq!(tags[1].docs.as_ref().unwrap(), "Get the customer's age");
}
