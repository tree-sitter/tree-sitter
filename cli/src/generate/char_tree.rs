use std::ops::Range;

/// A set of characters represented as a balanced binary tree of comparisons.
/// This is used as an intermediate step in generating efficient code for
/// matching a given character set.
#[derive(PartialEq, Eq)]
pub enum CharacterTree {
    Yes,
    Compare {
        value: char,
        operator: Comparator,
        consequence: Option<Box<CharacterTree>>,
        alternative: Option<Box<CharacterTree>>,
    },
}

#[derive(PartialEq, Eq)]
pub enum Comparator {
    Less,
    LessOrEqual,
    Equal,
    GreaterOrEqual,
}

impl CharacterTree {
    pub fn from_ranges(ranges: &[Range<char>]) -> Option<Self> {
        match ranges.len() {
            0 => None,
            1 => {
                let range = &ranges[0];
                if range.start == range.end {
                    Some(CharacterTree::Compare {
                        operator: Comparator::Equal,
                        value: range.start,
                        consequence: Some(Box::new(CharacterTree::Yes)),
                        alternative: None,
                    })
                } else {
                    Some(CharacterTree::Compare {
                        operator: Comparator::GreaterOrEqual,
                        value: range.start,
                        consequence: Some(Box::new(CharacterTree::Compare {
                            operator: Comparator::LessOrEqual,
                            value: range.end,
                            consequence: Some(Box::new(CharacterTree::Yes)),
                            alternative: None,
                        })),
                        alternative: None,
                    })
                }
            }
            len => {
                let mid = len / 2;
                let mid_range = &ranges[mid];
                Some(CharacterTree::Compare {
                    operator: Comparator::Less,
                    value: mid_range.start,
                    consequence: Self::from_ranges(&ranges[0..mid]).map(Box::new),
                    alternative: Some(Box::new(CharacterTree::Compare {
                        operator: Comparator::LessOrEqual,
                        value: mid_range.end,
                        consequence: Some(Box::new(CharacterTree::Yes)),
                        alternative: Self::from_ranges(&ranges[(mid + 1)..]).map(Box::new),
                    })),
                })
            }
        }
    }

    #[cfg(test)]
    fn contains(&self, c: char) -> bool {
        match self {
            CharacterTree::Yes => true,
            CharacterTree::Compare {
                value,
                operator,
                alternative,
                consequence,
            } => {
                let condition = match operator {
                    Comparator::Less => c < *value,
                    Comparator::LessOrEqual => c <= *value,
                    Comparator::Equal => c == *value,
                    Comparator::GreaterOrEqual => c >= *value,
                };
                if condition { consequence } else { alternative }
                    .as_ref()
                    .map_or(false, |a| a.contains(c))
            }
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_character_tree_simple() {
        let tree = CharacterTree::from_ranges(&['a'..'d', 'h'..'l', 'p'..'r', 'u'..'u', 'z'..'z'])
            .unwrap();

        assert!(tree.contains('a'));
        assert!(tree.contains('b'));
        assert!(tree.contains('c'));
        assert!(tree.contains('d'));

        assert!(!tree.contains('e'));
        assert!(!tree.contains('f'));
        assert!(!tree.contains('g'));

        assert!(tree.contains('h'));
        assert!(tree.contains('i'));
        assert!(tree.contains('j'));
        assert!(tree.contains('k'));
        assert!(tree.contains('l'));

        assert!(!tree.contains('m'));
        assert!(!tree.contains('n'));
        assert!(!tree.contains('o'));

        assert!(tree.contains('p'));
        assert!(tree.contains('q'));
        assert!(tree.contains('r'));

        assert!(!tree.contains('s'));
        assert!(!tree.contains('s'));

        assert!(tree.contains('u'));

        assert!(!tree.contains('v'));
    }
}
