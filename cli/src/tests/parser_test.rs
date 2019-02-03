use super::helpers::fixtures::get_language;
use std::thread;
use tree_sitter::{InputEdit, Language, LogType, Parser, Point, Range};

#[test]
fn test_basic_parsing() {
    let mut parser = Parser::new();
    parser.set_language(rust()).unwrap();

    let tree = parser
        .parse_str(
            "
        struct Stuff {}
        fn main() {}
    ",
            None,
        )
        .unwrap();

    let root_node = tree.root_node();
    assert_eq!(root_node.kind(), "source_file");

    assert_eq!(
        root_node.to_sexp(),
        "(source_file (struct_item (type_identifier) (field_declaration_list)) (function_item (identifier) (parameters) (block)))"
    );

    let struct_node = root_node.child(0).unwrap();
    assert_eq!(struct_node.kind(), "struct_item");
}

#[test]
fn test_parsing_with_logging() {
    let mut parser = Parser::new();
    parser.set_language(rust()).unwrap();

    let mut messages = Vec::new();
    parser.set_logger(Some(Box::new(|log_type, message| {
        messages.push((log_type, message.to_string()));
    })));

    parser
        .parse_str(
            "
        struct Stuff {}
        fn main() {}
    ",
            None,
        )
        .unwrap();

    assert!(messages.contains(&(
        LogType::Parse,
        "reduce sym:struct_item, child_count:3".to_string()
    )));
    assert!(messages.contains(&(LogType::Lex, "skip character:' '".to_string())));
}

#[test]
fn test_parsing_with_custom_utf8_input() {
    let mut parser = Parser::new();
    parser.set_language(rust()).unwrap();

    let lines = &["pub fn foo() {", "  1", "}"];

    let tree = parser
        .parse_utf8(
            &mut |_, position| {
                let row = position.row;
                let column = position.column;
                if row < lines.len() {
                    if column < lines[row].as_bytes().len() {
                        &lines[row].as_bytes()[column..]
                    } else {
                        "\n".as_bytes()
                    }
                } else {
                    &[]
                }
            },
            None,
        )
        .unwrap();

    let root = tree.root_node();
    assert_eq!(root.to_sexp(), "(source_file (function_item (visibility_modifier) (identifier) (parameters) (block (integer_literal))))");
    assert_eq!(root.kind(), "source_file");
    assert_eq!(root.has_error(), false);
    assert_eq!(root.child(0).unwrap().kind(), "function_item");
}

#[test]
fn test_parsing_with_custom_utf16_input() {
    let mut parser = Parser::new();
    parser.set_language(rust()).unwrap();

    let lines: Vec<Vec<u16>> = ["pub fn foo() {", "  1", "}"]
        .iter()
        .map(|s| s.encode_utf16().collect())
        .collect();

    let tree = parser
        .parse_utf16(
            &mut |_, position| {
                let row = position.row;
                let column = position.column;
                if row < lines.len() {
                    if column < lines[row].len() {
                        &lines[row][column..]
                    } else {
                        &[10]
                    }
                } else {
                    &[]
                }
            },
            None,
        )
        .unwrap();

    let root = tree.root_node();
    assert_eq!(root.to_sexp(), "(source_file (function_item (visibility_modifier) (identifier) (parameters) (block (integer_literal))))");
    assert_eq!(root.kind(), "source_file");
    assert_eq!(root.has_error(), false);
    assert_eq!(root.child(0).unwrap().kind(), "function_item");
}

#[test]
fn test_parsing_after_editing() {
    let mut parser = Parser::new();
    parser.set_language(rust()).unwrap();

    let mut input_bytes = "fn test(a: A, c: C) {}".as_bytes();
    let mut input_bytes_read = Vec::new();

    let mut tree = parser
        .parse_utf8(
            &mut |offset, _| {
                let offset = offset;
                if offset < input_bytes.len() {
                    let result = &input_bytes[offset..offset + 1];
                    input_bytes_read.extend(result.iter());
                    result
                } else {
                    &[]
                }
            },
            None,
        )
        .unwrap();

    let parameters_sexp = tree
        .root_node()
        .named_child(0)
        .unwrap()
        .named_child(1)
        .unwrap()
        .to_sexp();
    assert_eq!(
        parameters_sexp,
        "(parameters (parameter (identifier) (type_identifier)) (parameter (identifier) (type_identifier)))"
    );

    input_bytes_read.clear();
    input_bytes = "fn test(a: A, b: B, c: C) {}".as_bytes();
    tree.edit(&InputEdit {
        start_byte: 14,
        old_end_byte: 14,
        new_end_byte: 20,
        start_position: Point::new(0, 14),
        old_end_position: Point::new(0, 14),
        new_end_position: Point::new(0, 20),
    });

    let tree = parser
        .parse_utf8(
            &mut |offset, _| {
                let offset = offset;
                if offset < input_bytes.len() {
                    let result = &input_bytes[offset..offset + 1];
                    input_bytes_read.extend(result.iter());
                    result
                } else {
                    &[]
                }
            },
            Some(&tree),
        )
        .unwrap();

    let parameters_sexp = tree
        .root_node()
        .named_child(0)
        .unwrap()
        .named_child(1)
        .unwrap()
        .to_sexp();
    assert_eq!(
        parameters_sexp,
        "(parameters (parameter (identifier) (type_identifier)) (parameter (identifier) (type_identifier)) (parameter (identifier) (type_identifier)))"
    );

    let retokenized_content = String::from_utf8(input_bytes_read).unwrap();
    assert!(retokenized_content.contains("b: B"));
    assert!(!retokenized_content.contains("a: A"));
    assert!(!retokenized_content.contains("c: C"));
    assert!(!retokenized_content.contains("{}"));
}

#[test]
fn test_parsing_on_multiple_threads() {
    // Parse this source file so that each thread has a non-trivial amount of
    // work to do.
    let this_file_source = include_str!("parser_test.rs");

    let mut parser = Parser::new();
    parser.set_language(rust()).unwrap();
    let tree = parser.parse_str(this_file_source, None).unwrap();

    let mut parse_threads = Vec::new();
    for thread_id in 1..5 {
        let mut tree_clone = tree.clone();
        parse_threads.push(thread::spawn(move || {
            // For each thread, prepend a different number of declarations to the
            // source code.
            let mut prepend_line_count = 0;
            let mut prepended_source = String::new();
            for _ in 0..thread_id {
                prepend_line_count += 2;
                prepended_source += "struct X {}\n\n";
            }

            tree_clone.edit(&InputEdit {
                start_byte: 0,
                old_end_byte: 0,
                new_end_byte: prepended_source.len(),
                start_position: Point::new(0, 0),
                old_end_position: Point::new(0, 0),
                new_end_position: Point::new(prepend_line_count, 0),
            });
            prepended_source += this_file_source;

            // Reparse using the old tree as a starting point.
            let mut parser = Parser::new();
            parser.set_language(rust()).unwrap();
            parser
                .parse_str(&prepended_source, Some(&tree_clone))
                .unwrap()
        }));
    }

    // Check that the trees have the expected relationship to one another.
    let trees = parse_threads
        .into_iter()
        .map(|thread| thread.join().unwrap());
    let child_count_differences = trees
        .map(|t| t.root_node().child_count() - tree.root_node().child_count())
        .collect::<Vec<_>>();

    assert_eq!(child_count_differences, &[1, 2, 3, 4]);
}

// Included Ranges

#[test]
fn test_parsing_with_one_included_range() {
    let source_code = "<span>hi</span><script>console.log('sup');</script>";

    let mut parser = Parser::new();
    parser.set_language(get_language("html")).unwrap();
    let html_tree = parser.parse_str(source_code, None).unwrap();
    let script_content_node = html_tree.root_node().child(1).unwrap().child(1).unwrap();
    assert_eq!(script_content_node.kind(), "raw_text");

    parser.set_included_ranges(&[script_content_node.range()]);
    parser.set_language(get_language("javascript")).unwrap();
    let js_tree = parser.parse_str(source_code, None).unwrap();

    assert_eq!(
        js_tree.root_node().to_sexp(),
        concat!(
            "(program (expression_statement (call_expression",
            " (member_expression (identifier) (property_identifier))",
            " (arguments (string)))))",
        )
    );
    assert_eq!(
        js_tree.root_node().start_position(),
        Point::new(0, source_code.find("console").unwrap())
    );
}

#[test]
fn test_parsing_with_multiple_included_ranges() {
    let source_code = "html `<div>Hello, ${name.toUpperCase()}, it's <b>${now()}</b>.</div>`";

    let mut parser = Parser::new();
    parser.set_language(get_language("javascript")).unwrap();
    let js_tree = parser.parse_str(source_code, None).unwrap();
    let template_string_node = js_tree
        .root_node()
        .descendant_for_byte_range(
            source_code.find("<div>").unwrap(),
            source_code.find("Hello").unwrap(),
        )
        .unwrap();
    assert_eq!(template_string_node.kind(), "template_string");

    let open_quote_node = template_string_node.child(0).unwrap();
    let interpolation_node1 = template_string_node.child(1).unwrap();
    let interpolation_node2 = template_string_node.child(2).unwrap();
    let close_quote_node = template_string_node.child(3).unwrap();

    parser.set_language(get_language("html")).unwrap();
    parser.set_included_ranges(&[
        Range {
            start_byte: open_quote_node.end_byte(),
            start_point: open_quote_node.end_position(),
            end_byte: interpolation_node1.start_byte(),
            end_point: interpolation_node1.start_position(),
        },
        Range {
            start_byte: interpolation_node1.end_byte(),
            start_point: interpolation_node1.end_position(),
            end_byte: interpolation_node2.start_byte(),
            end_point: interpolation_node2.start_position(),
        },
        Range {
            start_byte: interpolation_node2.end_byte(),
            start_point: interpolation_node2.end_position(),
            end_byte: close_quote_node.start_byte(),
            end_point: close_quote_node.start_position(),
        },
    ]);
    let html_tree = parser.parse_str(source_code, None).unwrap();

    assert_eq!(
        html_tree.root_node().to_sexp(),
        concat!(
            "(fragment (element",
            " (start_tag (tag_name))",
            " (text)",
            " (element (start_tag (tag_name)) (end_tag (tag_name)))",
            " (text)",
            " (end_tag (tag_name))))",
        )
    );

    let div_element_node = html_tree.root_node().child(0).unwrap();
    let hello_text_node = div_element_node.child(1).unwrap();
    let b_element_node = div_element_node.child(2).unwrap();
    let b_start_tag_node = b_element_node.child(0).unwrap();
    let b_end_tag_node = b_element_node.child(1).unwrap();

    assert_eq!(hello_text_node.kind(), "text");
    assert_eq!(
        hello_text_node.start_byte(),
        source_code.find("Hello").unwrap()
    );
    assert_eq!(hello_text_node.end_byte(), source_code.find("<b>").unwrap());

    assert_eq!(b_start_tag_node.kind(), "start_tag");
    assert_eq!(
        b_start_tag_node.start_byte(),
        source_code.find("<b>").unwrap()
    );
    assert_eq!(
        b_start_tag_node.end_byte(),
        source_code.find("${now()}").unwrap()
    );

    assert_eq!(b_end_tag_node.kind(), "end_tag");
    assert_eq!(
        b_end_tag_node.start_byte(),
        source_code.find("</b>").unwrap()
    );
    assert_eq!(
        b_end_tag_node.end_byte(),
        source_code.find(".</div>").unwrap()
    );
}

#[test]
fn test_parsing_utf16_code_with_errors_at_the_end_of_an_included_range() {
    let source_code = "<script>a.</script>";
    let utf16_source_code: Vec<u16> = source_code.as_bytes().iter().map(|c| *c as u16).collect();

    let start_byte = 2 * source_code.find("a.").unwrap();
    let end_byte = 2 * source_code.find("</script>").unwrap();

    let mut parser = Parser::new();
    parser.set_language(get_language("javascript")).unwrap();
    parser.set_included_ranges(&[Range {
        start_byte,
        end_byte,
        start_point: Point::new(0, start_byte),
        end_point: Point::new(0, end_byte),
    }]);
    let tree = parser
        .parse_utf16(&mut |i, _| &utf16_source_code[i..], None)
        .unwrap();
    assert_eq!(tree.root_node().to_sexp(), "(program (ERROR (identifier)))");
}

fn rust() -> Language {
    get_language("rust")
}
