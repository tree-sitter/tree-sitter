use crate::rules::Symbol;
use crate::tables::{ParseStateId, ParseTable};
use std::collections::{HashMap, HashSet};

pub(crate) struct CoincidentTokenIndex {
    entries: HashMap<(Symbol, Symbol), HashSet<ParseStateId>>,
    empty: HashSet<ParseStateId>,
}

impl CoincidentTokenIndex {
    pub fn new(table: &ParseTable) -> Self {
        let mut entries = HashMap::new();
        for (i, state) in table.states.iter().enumerate() {
            for symbol in state.terminal_entries.keys() {
                for other_symbol in state.terminal_entries.keys() {
                    entries
                        .entry((*symbol, *other_symbol))
                        .or_insert(HashSet::new())
                        .insert(i);
                }
            }
        }
        Self {
            entries,
            empty: HashSet::new(),
        }
    }

    pub fn states_with(&self, a: Symbol, b: Symbol) -> &HashSet<ParseStateId> {
        self.entries.get(&(a, b)).unwrap_or(&self.empty)
    }

    pub fn contains(&self, a: Symbol, b: Symbol) -> bool {
        self.entries.contains_key(&(a, b))
    }
}
