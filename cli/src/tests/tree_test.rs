use super::helpers::fixtures::get_language;
use tree_sitter::{InputEdit, Language, Parser, Point};

#[test]
fn test_edit() {
    let mut parser = Parser::new();
    parser.set_language(javascript()).unwrap();
    let tree = parser.parse_str("  abc  !==  def", None).unwrap();

    assert_eq!(
        tree.root_node().to_sexp(),
        "(program (expression_statement (binary_expression (identifier) (identifier))))"
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

fn javascript() -> Language {
    get_language("javascript")
}
