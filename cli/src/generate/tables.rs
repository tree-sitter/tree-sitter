use super::nfa::CharacterSet;
use super::rules::{Alias, Associativity, Symbol, TokenSet};
use std::collections::{BTreeMap, HashMap};
pub(crate) type ProductionInfoId = usize;
pub(crate) type ParseStateId = usize;
pub(crate) type LexStateId = usize;

#[derive(Clone, Copy, Debug, PartialEq, Eq, PartialOrd, Ord)]
pub(crate) enum ParseAction {
    Accept,
    Shift {
        state: ParseStateId,
        is_repetition: bool,
    },
    ShiftExtra,
    Recover,
    Reduce {
        symbol: Symbol,
        child_count: usize,
        precedence: i32,
        dynamic_precedence: i32,
        associativity: Option<Associativity>,
        production_id: ProductionInfoId,
    },
}

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub(crate) enum GotoAction {
    Goto(ParseStateId),
    ShiftExtra,
}

#[derive(Clone, Debug, PartialEq, Eq)]
pub(crate) struct ParseTableEntry {
    pub actions: Vec<ParseAction>,
    pub reusable: bool,
}

#[derive(Clone, Debug, Default, PartialEq, Eq)]
pub(crate) struct ParseState {
    pub id: ParseStateId,
    pub terminal_entries: HashMap<Symbol, ParseTableEntry>,
    pub nonterminal_entries: HashMap<Symbol, GotoAction>,
    pub lex_state_id: usize,
    pub external_lex_state_id: usize,
    pub core_id: usize,
    pub is_non_terminal_extra: bool,
}

#[derive(Clone, Copy, Debug, Default, PartialEq, Eq)]
pub(crate) struct FieldLocation {
    pub index: usize,
    pub inherited: bool,
}

#[derive(Debug, Default, PartialEq, Eq)]
pub(crate) struct ProductionInfo {
    pub alias_sequence: Vec<Option<Alias>>,
    pub field_map: BTreeMap<String, Vec<FieldLocation>>,
}

#[derive(Debug, PartialEq, Eq)]
pub(crate) struct ParseTable {
    pub states: Vec<ParseState>,
    pub symbols: Vec<Symbol>,
    pub production_infos: Vec<ProductionInfo>,
    pub max_aliased_production_length: usize,
    pub external_lex_states: Vec<TokenSet>,
}

#[derive(Clone, Debug, PartialEq, Eq, PartialOrd, Ord)]
pub(crate) struct AdvanceAction {
    pub state: LexStateId,
    pub in_main_token: bool,
}

#[derive(Clone, Debug, Default, PartialEq, Eq, PartialOrd, Ord)]
pub(crate) struct LexState {
    pub accept_action: Option<Symbol>,
    pub eof_action: Option<AdvanceAction>,
    pub advance_actions: Vec<(CharacterSet, AdvanceAction)>,
}

#[derive(Debug, PartialEq, Eq)]
pub(crate) struct LexTable {
    pub states: Vec<LexState>,
}

impl ParseTableEntry {
    pub fn new() -> Self {
        Self {
            reusable: true,
            actions: Vec::new(),
        }
    }
}

impl Default for LexTable {
    fn default() -> Self {
        LexTable { states: Vec::new() }
    }
}

impl ParseState {
    pub fn referenced_states<'a>(&'a self) -> impl Iterator<Item = ParseStateId> + 'a {
        self.terminal_entries
            .iter()
            .flat_map(|(_, entry)| {
                entry.actions.iter().filter_map(|action| match action {
                    ParseAction::Shift { state, .. } => Some(*state),
                    _ => None,
                })
            })
            .chain(self.nonterminal_entries.iter().filter_map(|(_, action)| {
                if let GotoAction::Goto(state) = action {
                    Some(*state)
                } else {
                    None
                }
            }))
    }

    pub fn update_referenced_states<F>(&mut self, mut f: F)
    where
        F: FnMut(usize, &ParseState) -> usize,
    {
        let mut updates = Vec::new();
        for (symbol, entry) in &self.terminal_entries {
            for (i, action) in entry.actions.iter().enumerate() {
                if let ParseAction::Shift { state, .. } = action {
                    let result = f(*state, self);
                    if result != *state {
                        updates.push((*symbol, i, result));
                    }
                }
            }
        }
        for (symbol, action) in &self.nonterminal_entries {
            if let GotoAction::Goto(other_state) = action {
                let result = f(*other_state, self);
                if result != *other_state {
                    updates.push((*symbol, 0, result));
                }
            }
        }
        for (symbol, action_index, new_state) in updates {
            if symbol.is_non_terminal() {
                self.nonterminal_entries
                    .insert(symbol, GotoAction::Goto(new_state));
            } else {
                let entry = self.terminal_entries.get_mut(&symbol).unwrap();
                if let ParseAction::Shift { is_repetition, .. } = entry.actions[action_index] {
                    entry.actions[action_index] = ParseAction::Shift {
                        state: new_state,
                        is_repetition,
                    };
                }
            }
        }
    }
}

impl ParseAction {
    pub fn precedence(&self) -> i32 {
        if let ParseAction::Reduce { precedence, .. } = self {
            *precedence
        } else {
            0
        }
    }
}
