use crate::grammars::{LexicalGrammar, LexicalVariable};
use crate::nfa::{CharacterSet, NfaCursor};
use std::collections::HashSet;

#[derive(Default)]
struct TokenConflictStatus {
    matches_same_string: bool,
    matches_longer_string_with_valid_next_char: bool,
}

pub(crate) struct TokenConflictMap {
    starting_chars_by_index: Vec<CharacterSet>,
    status_matrix: Vec<TokenConflictStatus>,
}

impl TokenConflictMap {
    pub fn new(grammar: &LexicalGrammar) -> Self {
        let mut cursor = NfaCursor::new(&grammar.nfa, Vec::new());

        let mut starting_chars_by_index = Vec::with_capacity(grammar.variables.len());
        for variable in &grammar.variables {
            cursor.reset(vec![variable.start_state]);
            let mut all_chars = CharacterSet::empty();
            for (chars, _, _) in cursor.successors() {
                all_chars = all_chars.add(chars);
            }
            starting_chars_by_index.push(all_chars);
        }

        let status_matrix =
            Vec::with_capacity(grammar.variables.len() * grammar.variables.len());

        TokenConflictMap {
            starting_chars_by_index,
            status_matrix,
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::grammars::{Variable, VariableType};
    use crate::prepare_grammar::{expand_tokens, ExtractedLexicalGrammar};
    use crate::rules::Rule;

    #[test]
    fn test_starting_characters() {
        let grammar = expand_tokens(ExtractedLexicalGrammar {
            separators: Vec::new(),
            variables: vec![
                Variable {
                    name: "token_0".to_string(),
                    kind: VariableType::Named,
                    rule: Rule::pattern("[a-f]1|0x\\d"),
                },
                Variable {
                    name: "token_1".to_string(),
                    kind: VariableType::Named,
                    rule: Rule::pattern("d*ef"),
                },
            ],
        })
        .unwrap();

        let token_map = TokenConflictMap::new(&grammar);

        assert_eq!(
            token_map.starting_chars_by_index[0],
            CharacterSet::empty().add_range('a', 'f').add_char('0')
        );
        assert_eq!(
            token_map.starting_chars_by_index[1],
            CharacterSet::empty().add_range('d', 'e')
        );
    }
}
