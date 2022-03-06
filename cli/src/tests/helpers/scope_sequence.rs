use tree_sitter::{Point, Range, Tree};

#[derive(Debug)]
pub struct ScopeSequence(Vec<ScopeStack>);

type ScopeStack = Vec<&'static str>;

impl ScopeSequence {
    pub fn new(tree: &Tree) -> Self {
        let mut result = ScopeSequence(Vec::new());
        let mut scope_stack = Vec::new();

        let mut cursor = tree.walk();
        let mut visited_children = false;
        loop {
            let node = cursor.node();
            for _ in result.0.len()..node.start_byte() {
                result.0.push(scope_stack.clone());
            }
            if visited_children {
                for _ in result.0.len()..node.end_byte() {
                    result.0.push(scope_stack.clone());
                }
                scope_stack.pop();
                if cursor.goto_next_sibling() {
                    visited_children = false;
                } else if !cursor.goto_parent() {
                    break;
                }
            } else {
                scope_stack.push(cursor.node().kind());
                if !cursor.goto_first_child() {
                    visited_children = true;
                }
            }
        }

        result
    }

    pub fn check_changes(
        &self,
        other: &ScopeSequence,
        text: &Vec<u8>,
        known_changed_ranges: &Vec<Range>,
    ) -> Result<(), String> {
        if self.0.len() != text.len() {
            panic!(
                "Inconsistent scope sequence: {:?}",
                self.0
                    .iter()
                    .zip(text.iter().map(|c| *c as char))
                    .collect::<Vec<_>>()
            );
        }

        assert_eq!(self.0.len(), other.0.len());
        let mut position = Point { row: 0, column: 0 };
        for (i, stack) in self.0.iter().enumerate() {
            let other_stack = &other.0[i];
            if *stack != *other_stack {
                let containing_range = known_changed_ranges
                    .iter()
                    .find(|range| range.start_point <= position && position < range.end_point);
                if containing_range.is_none() {
                    let line = &text[(i - position.column)..]
                        .split(|c| *c == '\n' as u8)
                        .next()
                        .unwrap();
                    return Err(format!(
                        concat!(
                            "Position: {}\n",
                            "Byte offset: {}\n",
                            "Line: {}\n",
                            "{}^\n",
                            "Old scopes: {:?}\n",
                            "New scopes: {:?}\n",
                            "Invalidated ranges: {:?}",
                        ),
                        position,
                        i,
                        String::from_utf8_lossy(line),
                        String::from(" ").repeat(position.column + "Line: ".len()),
                        stack,
                        other_stack,
                        known_changed_ranges,
                    ));
                }
            }

            if text[i] == '\n' as u8 {
                position.row += 1;
                position.column = 0;
            } else {
                position.column += 1;
            }
        }
        Ok(())
    }
}
