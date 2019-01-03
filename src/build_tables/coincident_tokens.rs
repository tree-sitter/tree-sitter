use crate::grammars::LexicalGrammar;
use crate::rules::Symbol;
use crate::tables::{ParseStateId, ParseTable};
use std::collections::HashSet;

pub(crate) struct CoincidentTokenIndex {
    entries: Vec<HashSet<ParseStateId>>,
    n: usize,
}

impl CoincidentTokenIndex {
    pub fn new(table: &ParseTable, lexical_grammar: &LexicalGrammar) -> Self {
        let n = lexical_grammar.variables.len();
        let mut result = Self {
            n,
            entries: vec![HashSet::new(); n * n],
        };
        for (i, state) in table.states.iter().enumerate() {
            for symbol in state.terminal_entries.keys() {
                for other_symbol in state.terminal_entries.keys() {
                    let index = result.index(*symbol, *other_symbol);
                    result.entries[index].insert(i);
                }
            }
        }
        result
    }

    pub fn states_with(&self, a: Symbol, b: Symbol) -> &HashSet<ParseStateId> {
        &self.entries[self.index(a, b)]
    }

    pub fn contains(&self, a: Symbol, b: Symbol) -> bool {
        !self.entries[self.index(a, b)].is_empty()
    }

    fn index(&self, a: Symbol, b: Symbol) -> usize {
        if a.index < b.index {
            a.index * self.n + b.index
        } else {
            b.index * self.n + a.index
        }
    }
}
