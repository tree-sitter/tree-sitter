use super::helpers::edits::invert_edit;
use super::helpers::fixtures::get_language;
use crate::parse::{perform_edit, Edit};
use std::str;
use tree_sitter::{InputEdit, Parser, Point, Range, Tree};

#[test]
fn test_tree_edit() {
    let mut parser = Parser::new();
    parser.set_language(get_language("javascript")).unwrap();
    let tree = parser.parse("  abc  !==  def", None).unwrap();

    assert_eq!(
        tree.root_node().to_sexp(),
        "(program (expression_statement (binary_expression left: (identifier) right: (identifier))))"
    );

    // edit entirely within the tree's padding:
    // resize the padding of the tree and its leftmost descendants.
    {
        let mut tree = tree.clone();
        tree.edit(&InputEdit {
            start_byte: 1,
            old_end_byte: 1,
            new_end_byte: 2,
            start_position: Point::new(0, 1),
            old_end_position: Point::new(0, 1),
            new_end_position: Point::new(0, 2),
        });

        let expr = tree.root_node().child(0).unwrap().child(0).unwrap();
        let child1 = expr.child(0).unwrap();
        let child2 = expr.child(1).unwrap();

        assert!(expr.has_changes());
        assert_eq!(expr.start_byte(), 3);
        assert_eq!(expr.end_byte(), 16);
        assert!(child1.has_changes());
        assert_eq!(child1.start_byte(), 3);
        assert_eq!(child1.end_byte(), 6);
        assert!(!child2.has_changes());
        assert_eq!(child2.start_byte(), 8);
        assert_eq!(child2.end_byte(), 11);
    }

    // edit starting in the tree's padding but extending into its content:
    // shrink the content to compenstate for the expanded padding.
    {
        let mut tree = tree.clone();
        tree.edit(&InputEdit {
            start_byte: 1,
            old_end_byte: 4,
            new_end_byte: 5,
            start_position: Point::new(0, 1),
            old_end_position: Point::new(0, 5),
            new_end_position: Point::new(0, 5),
        });

        let expr = tree.root_node().child(0).unwrap().child(0).unwrap();
        let child1 = expr.child(0).unwrap();
        let child2 = expr.child(1).unwrap();

        assert!(expr.has_changes());
        assert_eq!(expr.start_byte(), 5);
        assert_eq!(expr.end_byte(), 16);
        assert!(child1.has_changes());
        assert_eq!(child1.start_byte(), 5);
        assert_eq!(child1.end_byte(), 6);
        assert!(!child2.has_changes());
        assert_eq!(child2.start_byte(), 8);
        assert_eq!(child2.end_byte(), 11);
    }

    // insertion at the edge of a tree's padding:
    // expand the tree's padding.
    {
        let mut tree = tree.clone();
        tree.edit(&InputEdit {
            start_byte: 2,
            old_end_byte: 2,
            new_end_byte: 4,
            start_position: Point::new(0, 2),
            old_end_position: Point::new(0, 2),
            new_end_position: Point::new(0, 4),
        });

        let expr = tree.root_node().child(0).unwrap().child(0).unwrap();
        let child1 = expr.child(0).unwrap();
        let child2 = expr.child(1).unwrap();

        assert!(expr.has_changes());
        assert_eq!(expr.start_byte(), 4);
        assert_eq!(expr.end_byte(), 17);
        assert!(child1.has_changes());
        assert_eq!(child1.start_byte(), 4);
        assert_eq!(child1.end_byte(), 7);
        assert!(!child2.has_changes());
        assert_eq!(child2.start_byte(), 9);
        assert_eq!(child2.end_byte(), 12);
    }

    // replacement starting at the edge of the tree's padding:
    // resize the content and not the padding.
    {
        let mut tree = tree.clone();
        tree.edit(&InputEdit {
            start_byte: 2,
            old_end_byte: 2,
            new_end_byte: 4,
            start_position: Point::new(0, 2),
            old_end_position: Point::new(0, 2),
            new_end_position: Point::new(0, 4),
        });

        let expr = tree.root_node().child(0).unwrap().child(0).unwrap();
        let child1 = expr.child(0).unwrap();
        let child2 = expr.child(1).unwrap();

        assert!(expr.has_changes());
        assert_eq!(expr.start_byte(), 4);
        assert_eq!(expr.end_byte(), 17);
        assert!(child1.has_changes());
        assert_eq!(child1.start_byte(), 4);
        assert_eq!(child1.end_byte(), 7);
        assert!(!child2.has_changes());
        assert_eq!(child2.start_byte(), 9);
        assert_eq!(child2.end_byte(), 12);
    }

    // deletion that spans more than one child node:
    // shrink subsequent child nodes.
    {
        let mut tree = tree.clone();
        tree.edit(&InputEdit {
            start_byte: 1,
            old_end_byte: 11,
            new_end_byte: 4,
            start_position: Point::new(0, 1),
            old_end_position: Point::new(0, 11),
            new_end_position: Point::new(0, 4),
        });

        let expr = tree.root_node().child(0).unwrap().child(0).unwrap();
        let child1 = expr.child(0).unwrap();
        let child2 = expr.child(1).unwrap();
        let child3 = expr.child(2).unwrap();

        assert!(expr.has_changes());
        assert_eq!(expr.start_byte(), 4);
        assert_eq!(expr.end_byte(), 8);
        assert!(child1.has_changes());
        assert_eq!(child1.start_byte(), 4);
        assert_eq!(child1.end_byte(), 4);
        assert!(child2.has_changes());
        assert_eq!(child2.start_byte(), 4);
        assert_eq!(child2.end_byte(), 4);
        assert!(child3.has_changes());
        assert_eq!(child3.start_byte(), 5);
        assert_eq!(child3.end_byte(), 8);
    }

    // insertion at the end of the tree:
    // extend the tree's content.
    {
        let mut tree = tree.clone();
        tree.edit(&InputEdit {
            start_byte: 15,
            old_end_byte: 15,
            new_end_byte: 16,
            start_position: Point::new(0, 15),
            old_end_position: Point::new(0, 15),
            new_end_position: Point::new(0, 16),
        });

        let expr = tree.root_node().child(0).unwrap().child(0).unwrap();
        let child1 = expr.child(0).unwrap();
        let child2 = expr.child(1).unwrap();
        let child3 = expr.child(2).unwrap();

        assert!(expr.has_changes());
        assert_eq!(expr.start_byte(), 2);
        assert_eq!(expr.end_byte(), 16);
        assert!(!child1.has_changes());
        assert_eq!(child1.end_byte(), 5);
        assert!(!child2.has_changes());
        assert_eq!(child2.end_byte(), 10);
        assert!(child3.has_changes());
        assert_eq!(child3.end_byte(), 16);
    }
}

#[test]
fn test_tree_cursor() {
    let mut parser = Parser::new();
    parser.set_language(get_language("rust")).unwrap();

    let tree = parser
        .parse(
            "
                struct Stuff {
                    a: A;
                    b: Option<B>,
                }
            ",
            None,
        )
        .unwrap();

    let mut cursor = tree.walk();
    assert_eq!(cursor.node().kind(), "source_file");

    assert!(cursor.goto_first_child());
    assert_eq!(cursor.node().kind(), "struct_item");

    assert!(cursor.goto_first_child());
    assert_eq!(cursor.node().kind(), "struct");
    assert_eq!(cursor.node().is_named(), false);

    assert!(cursor.goto_next_sibling());
    assert_eq!(cursor.node().kind(), "type_identifier");
    assert_eq!(cursor.node().is_named(), true);

    assert!(cursor.goto_next_sibling());
    assert_eq!(cursor.node().kind(), "field_declaration_list");
    assert_eq!(cursor.node().is_named(), true);
}

#[test]
fn test_tree_cursor_fields() {
    let mut parser = Parser::new();
    parser.set_language(get_language("javascript")).unwrap();

    let tree = parser
        .parse("function /*1*/ bar /*2*/ () {}", None)
        .unwrap();

    let mut cursor = tree.walk();
    assert_eq!(cursor.node().kind(), "program");

    cursor.goto_first_child();
    assert_eq!(cursor.node().kind(), "function_declaration");
    assert_eq!(cursor.field_name(), None);

    cursor.goto_first_child();
    assert_eq!(cursor.node().kind(), "function");
    assert_eq!(cursor.field_name(), None);

    cursor.goto_next_sibling();
    assert_eq!(cursor.node().kind(), "comment");
    assert_eq!(cursor.field_name(), None);

    cursor.goto_next_sibling();
    assert_eq!(cursor.node().kind(), "identifier");
    assert_eq!(cursor.field_name(), Some("name"));

    cursor.goto_next_sibling();
    assert_eq!(cursor.node().kind(), "comment");
    assert_eq!(cursor.field_name(), None);

    cursor.goto_next_sibling();
    assert_eq!(cursor.node().kind(), "formal_parameters");
    assert_eq!(cursor.field_name(), Some("parameters"));
}

#[test]
fn test_tree_node_equality() {
    let mut parser = Parser::new();
    parser.set_language(get_language("rust")).unwrap();
    let tree = parser.parse("struct A {}", None).unwrap();
    let node1 = tree.root_node();
    let node2 = tree.root_node();
    assert_eq!(node1, node2);
    assert_eq!(node1.child(0).unwrap(), node2.child(0).unwrap());
    assert_ne!(node1.child(0).unwrap(), node2);
}

#[test]
fn test_get_changed_ranges() {
    let source_code = b"{a: null};\n".to_vec();

    let mut parser = Parser::new();
    parser.set_language(get_language("javascript")).unwrap();
    let tree = parser.parse(&source_code, None).unwrap();

    assert_eq!(
        tree.root_node().to_sexp(),
        "(program (expression_statement (object (pair key: (property_identifier) value: (null)))))"
    );

    // Updating one token
    {
        let mut tree = tree.clone();
        let mut source_code = source_code.clone();

        // Replace `null` with `nothing` - that token has changed syntax
        let edit = Edit {
            position: index_of(&source_code, "ull"),
            deleted_length: 3,
            inserted_text: b"othing".to_vec(),
        };
        let inverse_edit = invert_edit(&source_code, &edit);
        let ranges = get_changed_ranges(&mut parser, &mut tree, &mut source_code, edit);
        assert_eq!(ranges, vec![range_of(&source_code, "nothing")]);

        // Replace `nothing` with `null` - that token has changed syntax
        let ranges = get_changed_ranges(&mut parser, &mut tree, &mut source_code, inverse_edit);
        assert_eq!(ranges, vec![range_of(&source_code, "null")]);
    }

    // Changing only leading whitespace
    {
        let mut tree = tree.clone();
        let mut source_code = source_code.clone();

        // Insert leading newline - no changed ranges
        let edit = Edit {
            position: 0,
            deleted_length: 0,
            inserted_text: b"\n".to_vec(),
        };
        let inverse_edit = invert_edit(&source_code, &edit);
        let ranges = get_changed_ranges(&mut parser, &mut tree, &mut source_code, edit);
        assert_eq!(ranges, vec![]);

        // Remove leading newline - no changed ranges
        let ranges = get_changed_ranges(&mut parser, &mut tree, &mut source_code, inverse_edit);
        assert_eq!(ranges, vec![]);
    }

    // Inserting elements
    {
        let mut tree = tree.clone();
        let mut source_code = source_code.clone();

        // Insert a key-value pair before the `}` - those tokens are changed
        let edit1 = Edit {
            position: index_of(&source_code, "}"),
            deleted_length: 0,
            inserted_text: b", b: false".to_vec(),
        };
        let inverse_edit1 = invert_edit(&source_code, &edit1);
        let ranges = get_changed_ranges(&mut parser, &mut tree, &mut source_code, edit1);
        assert_eq!(ranges, vec![range_of(&source_code, ", b: false")]);

        let edit2 = Edit {
            position: index_of(&source_code, ", b"),
            deleted_length: 0,
            inserted_text: b", c: 1".to_vec(),
        };
        let inverse_edit2 = invert_edit(&source_code, &edit2);
        let ranges = get_changed_ranges(&mut parser, &mut tree, &mut source_code, edit2);
        assert_eq!(ranges, vec![range_of(&source_code, ", c: 1")]);

        // Remove the middle pair
        let ranges = get_changed_ranges(&mut parser, &mut tree, &mut source_code, inverse_edit2);
        assert_eq!(ranges, vec![]);

        // Remove the second pair
        let ranges = get_changed_ranges(&mut parser, &mut tree, &mut source_code, inverse_edit1);
        assert_eq!(ranges, vec![]);
    }

    // Wrapping elements in larger expressions
    {
        let mut tree = tree.clone();
        let mut source_code = source_code.clone();

        // Replace `null` with the binary expression `b === null`
        let edit1 = Edit {
            position: index_of(&source_code, "null"),
            deleted_length: 0,
            inserted_text: b"b === ".to_vec(),
        };
        let inverse_edit1 = invert_edit(&source_code, &edit1);
        let ranges = get_changed_ranges(&mut parser, &mut tree, &mut source_code, edit1);
        assert_eq!(ranges, vec![range_of(&source_code, "b === null")]);

        // Undo
        let ranges = get_changed_ranges(&mut parser, &mut tree, &mut source_code, inverse_edit1);
        assert_eq!(ranges, vec![range_of(&source_code, "null")]);
    }
}

fn index_of(text: &Vec<u8>, substring: &str) -> usize {
    str::from_utf8(text.as_slice())
        .unwrap()
        .find(substring)
        .unwrap()
}

fn range_of(text: &Vec<u8>, substring: &str) -> Range {
    let start_byte = index_of(text, substring);
    let end_byte = start_byte + substring.as_bytes().len();
    Range {
        start_byte,
        end_byte,
        start_point: Point::new(0, start_byte),
        end_point: Point::new(0, end_byte),
    }
}

fn get_changed_ranges(
    parser: &mut Parser,
    tree: &mut Tree,
    source_code: &mut Vec<u8>,
    edit: Edit,
) -> Vec<Range> {
    perform_edit(tree, source_code, &edit);
    let new_tree = parser.parse(&source_code, Some(tree)).unwrap();
    let result = tree.changed_ranges(&new_tree).collect();
    *tree = new_tree;
    result
}
