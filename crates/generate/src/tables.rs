use std::collections::BTreeMap;

use super::{
    nfa::CharacterSet,
    rules::Alias,
    rules::{Symbol, TokenSet},
    strpool::StrId,
};

pub type ProductionInfoId = u32;
pub type ParseStateId = u32;
pub type LexStateId = u32;

use std::hash::BuildHasherDefault;

use indexmap::IndexMap;
use rustc_hash::{FxHashMap, FxHasher};

#[derive(Clone, Copy, Debug, PartialEq, Eq, PartialOrd, Ord, Hash)]
pub enum ParseAction {
    Accept,
    Shift {
        state: ParseStateId,
        is_repetition: bool,
    },
    ShiftExtra,
    Recover,
    Reduce {
        symbol: Symbol,
        child_count: u16,
        dynamic_precedence: i32,
        production_id: u16,
    },
}

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum GotoAction {
    Goto(ParseStateId),
    ShiftExtra,
}

/// Action list for one parse table entry. Holds entries with <= 1 action inline.
#[derive(Clone, Debug, Default, Eq)]
pub enum ActionList {
    #[default]
    Empty,
    One(ParseAction),
    Many(Vec<ParseAction>),
}

impl ActionList {
    pub fn push(&mut self, action: ParseAction) {
        match self {
            Self::Empty => *self = Self::One(action),
            Self::One(first) => *self = Self::Many(vec![*first, action]),
            Self::Many(actions) => actions.push(action),
        }
    }

    pub fn pop(&mut self) -> Option<ParseAction> {
        match self {
            Self::Empty => None,
            Self::One(action) => {
                let action = *action;
                *self = Self::Empty;
                Some(action)
            }
            Self::Many(actions) => actions.pop(),
        }
    }

    pub fn clear(&mut self) {
        *self = Self::Empty;
    }

    pub fn keep_last(&mut self) {
        if let Self::Many(actions) = self
            && let Some(&last) = actions.last()
        {
            *self = Self::One(last);
        }
    }

    pub fn from_slice(actions: &[ParseAction]) -> Self {
        match actions {
            [] => Self::Empty,
            [action] => Self::One(*action),
            actions => Self::Many(actions.to_vec()),
        }
    }
}

impl std::ops::Deref for ActionList {
    type Target = [ParseAction];
    fn deref(&self) -> &[ParseAction] {
        match self {
            Self::Empty => &[],
            Self::One(action) => std::slice::from_ref(action),
            Self::Many(actions) => actions,
        }
    }
}

impl std::ops::DerefMut for ActionList {
    fn deref_mut(&mut self) -> &mut [ParseAction] {
        match self {
            Self::Empty => &mut [],
            Self::One(action) => std::slice::from_mut(action),
            Self::Many(actions) => actions,
        }
    }
}

impl PartialEq for ActionList {
    fn eq(&self, other: &Self) -> bool {
        self[..] == other[..]
    }
}

impl std::hash::Hash for ActionList {
    fn hash<H: std::hash::Hasher>(&self, state: &mut H) {
        self[..].hash(state);
    }
}

impl<'a> IntoIterator for &'a ActionList {
    type Item = &'a ParseAction;
    type IntoIter = std::slice::Iter<'a, ParseAction>;
    fn into_iter(self) -> Self::IntoIter {
        self.iter()
    }
}

/// Index into [`ActionListPool::ranges`], with the high bit indicating whether the
/// given [`ActionList`] is reusable.
#[derive(Clone, Copy, Debug, Default, PartialEq, Eq, Hash)]
pub struct ActionListId(u32);

impl ActionListId {
    /// [`ActionListPool`] holds one entry per unique action list. In practice, there
    /// are only a few thousand of these, and `render` caps the table count at `u16::MAX`.
    /// These ids never come close to 2^31, so the top bit is free to indicate `reusable`.
    const REUSABLE_BIT: u32 = 1 << 31;

    pub const fn new(index: u32, reusable: bool) -> Self {
        debug_assert!(index < Self::REUSABLE_BIT);
        Self(index | if reusable { Self::REUSABLE_BIT } else { 0 })
    }

    pub const fn index(self) -> usize {
        (self.0 & !Self::REUSABLE_BIT) as usize
    }

    pub const fn reusable(self) -> bool {
        self.0 & Self::REUSABLE_BIT != 0
    }

    pub const fn set_reusable(&mut self, reusable: bool) {
        self.0 = (self.0 & !Self::REUSABLE_BIT) | if reusable { Self::REUSABLE_BIT } else { 0 };
    }
}

#[derive(Clone, Copy, Debug, Default)]
struct ActionListRange {
    offset: u32,
    len: u32,
}

/// De-duped storage for the parse table's terminal action lists.
///
/// Every `(state, terminal)` entry has an action list, but across a grammar typically
/// 98-99% of these lists are duplicates. Each entry holds an [`ActionListId`] pointing
/// into  [`Self::ranges`], which points to a representative slice into [`Self::actions`].
///
/// [`intern_table`] builds this pool immediately after the parse table is constructed
/// (every inline becomes an id). `minimize` then rewrites shift targets at the pool
/// level. `canonicalize` rebuilds the pool before `render` with each list stored exactly
/// once. Pool index 0 is always the empty list.
#[derive(Clone, Debug, Default)]
pub struct ActionListPool {
    actions: Vec<ParseAction>,
    ranges: Vec<ActionListRange>,
    remap_scratch: Vec<bool>,
}

impl ActionListPool {
    pub fn push(&mut self, list: &[ParseAction]) -> u32 {
        let index = self.ranges.len() as u32;
        let offset = self.actions.len() as u32;
        self.actions.extend_from_slice(list);
        self.ranges.push(ActionListRange {
            offset,
            len: list.len() as u32,
        });
        index
    }

    pub fn get(&self, id: ActionListId) -> &[ParseAction] {
        let range = self.ranges[id.index()];
        &self.actions[range.offset as usize..(range.offset + range.len) as usize]
    }

    pub const fn len(&self) -> usize {
        self.ranges.len()
    }

    pub fn intern(&mut self, dedup: &mut FxHashMap<ActionList, u32>, list: ActionList) -> u32 {
        if let Some(&index) = dedup.get(&list) {
            index
        } else {
            let index = self.push(&list);
            dedup.insert(list, index);
            index
        }
    }

    pub fn intern_table(table: ParseTable<ParseTableEntry>) -> ParseTable<ActionListId> {
        let mut pool = Self::default();
        let mut ids = FxHashMap::default();
        let states = table
            .states
            .into_iter()
            .map(|state| {
                let terminal_entries = state
                    .terminal_entries
                    .into_iter()
                    .map(|(symbol, entry)| {
                        let index = pool.intern(&mut ids, entry.actions);
                        (symbol, ActionListId::new(index, entry.reusable))
                    })
                    .collect();

                ParseState {
                    id: state.id,
                    terminal_entries,
                    nonterminal_entries: state.nonterminal_entries,
                    reserved_words: state.reserved_words,
                    lex_state_id: state.lex_state_id,
                    external_lex_state_id: state.external_lex_state_id,
                    core_id: state.core_id,
                    has_eof_gated_reduce: state.has_eof_gated_reduce,
                }
            })
            .collect();

        ParseTable {
            states,
            action_lists: pool,
            symbols: table.symbols,
            production_infos: table.production_infos,
            max_aliased_production_length: table.max_aliased_production_length,
            external_lex_states: table.external_lex_states,
        }
    }

    pub fn canonicalize(&mut self, states: &mut [ParseState]) {
        let old_actions = std::mem::take(&mut self.actions);
        let old_ranges = std::mem::take(&mut self.ranges);
        let mut ids = FxHashMap::default();
        // render's "no action" default
        self.intern(&mut ids, ActionList::Empty);
        let mut old_to_new = vec![u32::MAX; old_ranges.len()];
        for state in states {
            for id in state.terminal_entries.values_mut() {
                let old_index = id.index();
                let mut new_index = old_to_new[old_index];
                // INVARIANT: [`ParseTableEntry::index`] can never return `u32::MAX`
                if new_index == u32::MAX {
                    let range = old_ranges[old_index];
                    let list = ActionList::from_slice(
                        &old_actions[range.offset as usize..(range.offset + range.len) as usize],
                    );
                    new_index = self.intern(&mut ids, list);
                    old_to_new[old_index] = new_index;
                }
                *id = ActionListId::new(new_index, id.reusable());
            }
        }
    }
}

#[derive(Clone, Debug, PartialEq, Eq, Hash)]
pub struct ParseTableEntry {
    pub actions: ActionList,
    pub reusable: bool,
}

#[derive(Clone, Debug, Default)]
pub struct ParseState<T = ActionListId> {
    pub id: ParseStateId,
    pub terminal_entries: IndexMap<Symbol, T, BuildHasherDefault<FxHasher>>,
    pub nonterminal_entries: IndexMap<Symbol, GotoAction, BuildHasherDefault<FxHasher>>,
    pub reserved_words: TokenSet,
    pub lex_state_id: LexStateId,
    pub external_lex_state_id: LexStateId,
    pub core_id: u32,
    pub has_eof_gated_reduce: bool,
}

#[derive(Clone, Copy, Debug, Default, PartialEq, Eq)]
pub struct FieldLocation {
    pub index: u32,
    pub inherited: bool,
}

#[derive(Debug, Default, PartialEq, Eq)]
pub struct ProductionInfo {
    pub alias_sequence: Vec<Option<Alias>>,
    pub field_map: BTreeMap<StrId, Vec<FieldLocation>>,
}

#[derive(Debug, Default)]
pub struct ParseTable<T = ActionListId> {
    pub states: Vec<ParseState<T>>,
    pub action_lists: ActionListPool,
    pub symbols: Vec<Symbol>,
    pub production_infos: Vec<ProductionInfo>,
    pub max_aliased_production_length: usize,
    pub external_lex_states: Vec<TokenSet>,
}

#[derive(Clone, Debug, PartialEq, Eq, PartialOrd, Ord)]
pub struct AdvanceAction {
    pub state: LexStateId,
    pub in_main_token: bool,
}

#[derive(Clone, Debug, Default, PartialEq, Eq, PartialOrd, Ord)]
pub struct LexState {
    pub accept_action: Option<Symbol>,
    pub eof_action: Option<AdvanceAction>,
    pub advance_actions: Vec<(CharacterSet, AdvanceAction)>,
}

#[derive(Debug, PartialEq, Eq, Default)]
pub struct LexTable {
    pub states: Vec<LexState>,
}

impl ParseTableEntry {
    #[must_use]
    #[allow(clippy::new_without_default)]
    pub const fn new() -> Self {
        Self {
            reusable: true,
            actions: ActionList::Empty,
        }
    }
}

impl<T> ParseState<T> {
    #[must_use]
    pub fn is_end_of_non_terminal_extra(&self) -> bool {
        self.terminal_entries
            .contains_key(&Symbol::end_of_nonterminal_extra())
    }
}

impl ParseState<ActionListId> {
    pub fn referenced_states<'a>(
        &'a self,
        pool: &'a ActionListPool,
    ) -> impl Iterator<Item = ParseStateId> + 'a {
        self.terminal_entries
            .iter()
            .flat_map(|(_, id)| {
                pool.get(*id).iter().filter_map(|action| match action {
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

    pub fn update_nonterminal_references<F>(&mut self, mut f: F)
    where
        F: FnMut(ParseStateId, &Self) -> ParseStateId,
    {
        let mut updates = Vec::new();
        for (symbol, action) in &self.nonterminal_entries {
            if let GotoAction::Goto(other_state) = action {
                let result = f(*other_state, self);
                if result != *other_state {
                    updates.push((*symbol, result));
                }
            }
        }
        for (symbol, new_state) in updates {
            self.nonterminal_entries
                .insert(symbol, GotoAction::Goto(new_state));
        }
    }
}

impl ParseTable<ActionListId> {
    pub fn remap_terminal_references(&mut self, mut f: impl FnMut(ParseStateId) -> ParseStateId) {
        self.action_lists
            .remap_scratch
            .resize(self.action_lists.len(), false);
        self.action_lists.remap_scratch.fill(false);
        for state in &self.states {
            for id in state.terminal_entries.values() {
                self.action_lists.remap_scratch[id.index()] = true;
            }
        }
        for (index, range) in self.action_lists.ranges.iter().copied().enumerate() {
            if !self.action_lists.remap_scratch[index] {
                continue;
            }
            for action in &mut self.action_lists.actions
                [range.offset as usize..(range.offset + range.len) as usize]
            {
                if let ParseAction::Shift { state, .. } = action {
                    *state = f(*state);
                }
            }
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    // `remap_terminal_references` must remap only the pool slots some state references.
    // Dead slots (e.g. left by remove_unit_reductions' COW) can hold Shift targets
    // outside the remap's domain, so touching them would panic or corrupt. Here, slot 0
    // is live, slot 1 is dead, and the closure is defined only for state 0. A regressed
    // skip would call `f` on slot 1 and index out of bounds here.
    #[test]
    fn terminal_remap_skips_unreferenced_pool_entries() {
        let mut table = ParseTable::default();
        table
            .action_lists
            .push(&ActionList::One(ParseAction::Shift {
                state: 0,
                is_repetition: false,
            }));
        table
            .action_lists
            .push(&ActionList::One(ParseAction::Shift {
                state: 1,
                is_repetition: false,
            }));
        let mut state = ParseState::default();
        state
            .terminal_entries
            .insert(Symbol::end(), ActionListId::new(0, true));
        table.states.push(state);

        // Slot 1 is unreferenced, so `f` must never see state 1 (else this indexes out of bounds).
        let replacement = [7];
        table.remap_terminal_references(|state| replacement[state as usize]);

        assert!(matches!(
            table.action_lists.get(ActionListId::new(0, false))[0],
            ParseAction::Shift { state: 7, .. }
        ));
        assert!(matches!(
            table.action_lists.get(ActionListId::new(1, false))[0],
            ParseAction::Shift { state: 1, .. }
        ));
    }
}
