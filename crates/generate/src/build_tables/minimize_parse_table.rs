use std::{
    cmp::Ordering,
    hash::{Hash, Hasher},
    mem,
};

use rustc_hash::{FxHashMap, FxHashSet, FxHasher};

use log::debug;

use super::{SymbolIndexer, token_conflicts::TokenConflictMap};
use crate::{
    OptLevel,
    dedup::{SplitCriterion, split_state_id_groups},
    grammars::{LexicalGrammar, SyntaxGrammar, VariableType},
    rules::{AliasMap, Symbol, SymbolView, TokenSet},
    strpool::StrPool,
    tables::{
        ActionList, ActionListId, GotoAction, ParseAction, ParseState, ParseStateEntries,
        ParseStateId, ParseTable,
    },
};

/// Index into [`SyntaxGrammar::variables`]. All nonterminal [`Symbol`]s share
/// the same `kind`, so storing the index alone is sufficient for ordering.
type NonterminalIndex = u32;

/// A [`Symbol`]'s position from [`SymbolIndexer::index`]. Positions follow [`Symbol`]'s
/// order, so keys sort like their symbols.
#[derive(Clone, Copy, Debug, PartialEq, Eq, PartialOrd, Ord)]
struct SymbolKey(u32);

impl SymbolKey {
    #[inline]
    fn new(indexer: SymbolIndexer, symbol: Symbol) -> Self {
        Self(indexer.index(symbol) as u32)
    }

    /// The key's position, for indexing a table by [`SymbolIndexer::index`].
    #[inline]
    const fn index(self) -> usize {
        self.0 as usize
    }

    #[inline]
    const fn symbol(self, indexer: SymbolIndexer) -> Symbol {
        indexer.symbol(self.index())
    }
}

/// A sorted list for each parse state, all in one buffer.
struct StateLists<T> {
    items: Vec<T>,
    /// Where each state's list starts in `items`, by state id, then where the last one ends.
    /// State `i`'s list is `items[starts[i]..starts[i + 1]]`.
    starts: Vec<u32>,
}

impl<T> StateLists<T> {
    /// Collects one list per state, in state order, each sorted by `key`.
    fn collect<L, K>(lists: impl ExactSizeIterator<Item = L>, key: impl Fn(&T) -> K) -> Self
    where
        L: IntoIterator<Item = T>,
        K: Ord,
    {
        let mut starts = Vec::with_capacity(lists.len() + 1);
        starts.push(0);
        let mut items = Vec::new();
        for list in lists {
            let start = items.len();
            items.extend(list);
            items[start..].sort_unstable_by_key(&key);
            starts.push(items.len() as u32);
        }
        items.shrink_to_fit();
        Self { items, starts }
    }

    /// The list of `state`.
    #[inline]
    fn get(&self, state: &ParseState) -> &[T] {
        let id = state.id as usize;
        // INVARIANT: `collect` pushes one offset per state after the leading 0, so a state of
        // the table has its start at `starts[id]` and its end at `starts[id + 1]`.
        let offsets = self.starts.get(id..id + 2).unwrap();
        // SAFETY: the offsets only increase, and the last one is `items.len()`, so the range
        // is within `items`.
        unsafe {
            self.items
                .get_unchecked(offsets[0] as usize..offsets[1] as usize)
        }
    }
}

#[expect(
    clippy::too_many_arguments,
    reason = "all parameters are required for parse table minimization"
)]
pub fn minimize_parse_table(
    parse_table: &mut ParseTable,
    syntax_grammar: &SyntaxGrammar,
    lexical_grammar: &LexicalGrammar,
    simple_aliases: &AliasMap,
    token_conflict_map: &TokenConflictMap,
    keywords: &TokenSet,
    str_pool: &StrPool,
    optimizations: OptLevel,
) {
    let mut minimizer = Minimizer {
        parse_table,
        syntax_grammar,
        lexical_grammar,
        indexer: SymbolIndexer::new(syntax_grammar, lexical_grammar),
        token_conflict_map,
        keywords,
        simple_aliases,
        str_pool,
    };
    if optimizations.contains(OptLevel::MergeStates) {
        minimizer.merge_compatible_states();
    }
    minimizer.remove_unit_reductions();
    minimizer.remove_unused_states();
    minimizer.reorder_states_by_descending_size();
}

/// Word-aligned bitsets precomputed for `token_conflicts`, all indexed by terminal
/// index. `state_terminals` and `conflict_rows` are flattened two dimensional vectors:
/// row `i` spans `[i * row_words, (i + 1) * row_words)`.
struct ConflictBits {
    row_words: usize,
    /// Per state: which terminals have entries
    state_terminals: Vec<u64>,
    /// Per token: which terminals it lexically conflicts with
    conflict_rows: Vec<u64>,
    /// The keyword set.
    keywords: Vec<u64>,
    /// Tokens that are also external tokens.
    internal_external: Vec<u64>,
    /// The grammar's word token, as a key and as its bit in a row, if it's a terminal. An
    /// external word token has no keywords (see `identify_keywords`).
    word_token: Option<(SymbolKey, usize)>,
}

impl ConflictBits {
    fn new(minimizer: &Minimizer) -> Self {
        // Precompute word-aligned bitsets so `token_conflicts` can test a candidate
        // token against a whole state's terminals.
        //   - per state: which terminal indices have entries
        //   - per token: which terminal indices it lexically conflicts with
        //   - the keyword set as bits
        let n_terminals = minimizer.lexical_grammar.variables.len();
        let row_words = n_terminals.div_ceil(64);
        let set = |bits: &mut [u64], index: usize| bits[index / 64] |= 1 << (index % 64);

        let mut state_terminals = vec![0u64; minimizer.parse_table.states.len() * row_words];
        for (s, state) in minimizer.parse_table.states.iter().enumerate() {
            let base = s * row_words;
            let row = &mut state_terminals[base..base + row_words];
            for symbol in state.terminal_entries.keys() {
                if let Some(index) = symbol.terminal_index() {
                    set(row, usize::from(index));
                }
            }
        }

        let mut conflict_rows = vec![0u64; n_terminals * row_words];
        for i in 0..n_terminals {
            let base = i * row_words;
            let row = &mut conflict_rows[base..base + row_words];
            for j in 0..n_terminals {
                if minimizer.token_conflict_map.does_conflict(i, j) {
                    set(row, j);
                }
            }
        }

        let mut keywords = vec![0u64; row_words];
        for symbol in minimizer.keywords.iter() {
            if let Some(index) = symbol.terminal_index() {
                set(&mut keywords, usize::from(index));
            }
        }

        let mut internal_external = vec![0u64; row_words];
        for external in &minimizer.syntax_grammar.external_tokens {
            if let Some(index) = external
                .corresponding_internal_token
                .and_then(Symbol::terminal_index)
            {
                set(&mut internal_external, usize::from(index));
            }
        }

        Self {
            row_words,
            state_terminals,
            conflict_rows,
            keywords,
            internal_external,
            word_token: minimizer.syntax_grammar.word_token.and_then(|word| {
                let index = word.terminal_index()?;
                Some((SymbolKey::new(minimizer.indexer, word), usize::from(index)))
            }),
        }
    }

    #[inline]
    fn get_conflict_row(&self, token: usize) -> &[u64] {
        let base = token * self.row_words;
        &self.conflict_rows[base..base + self.row_words]
    }

    #[inline]
    fn get_state_row(&self, state: usize) -> &[u64] {
        let base = state * self.row_words;
        &self.state_terminals[base..base + self.row_words]
    }
}

/// The first pass of [`Minimizer::merge_compatible_states`]: splits states whose terminal
/// entries can't be merged.
struct ConflictPass<'min, 'a> {
    minimizer: &'min Minimizer<'a>,
    /// Each state's terminal entries, sorted by symbol.
    entry_maps: StateLists<(SymbolKey, ActionListId)>,
    bits: ConflictBits,
    /// A hash of each state's reserved words and terminal entries, apart from its shift
    /// targets, whose groups change as groups split.
    static_signatures: Vec<u64>,
    /// Each state's shift targets, sorted by symbol.
    shift_maps: &'min StateLists<(SymbolKey, ParseStateId)>,
    /// Scratch for [`SplitCriterion::compatible_with_all`].
    kept: KeptStates,
}

impl<'min, 'a> ConflictPass<'min, 'a> {
    fn new(
        minimizer: &'min Minimizer<'a>,
        shift_maps: &'min StateLists<(SymbolKey, ParseStateId)>,
    ) -> Self {
        // Precompute sorted terminal entry references for merge-join in states_conflict.
        // entry_maps.get(state)[i] = (symbol_key, action_list_id). Keys are symbol positions
        // for easy comparison.
        let entry_maps = StateLists::collect(
            minimizer.parse_table.states.iter().map(|state| {
                state
                    .terminal_entries
                    .iter()
                    .map(|(sym, id)| (SymbolKey::new(minimizer.indexer, *sym), *id))
            }),
            |&(key, _)| key,
        );

        // Hash each state's terminal entries once, apart from its shift targets, whose groups
        // change as groups split.
        let static_signatures = minimizer
            .parse_table
            .states
            .iter()
            .map(|state| {
                let mut hasher = FxHasher::default();
                state.reserved_words.hash(&mut hasher);
                for &(key, id) in entry_maps.get(state) {
                    key.0.hash(&mut hasher);
                    for action in minimizer.parse_table.action_lists.get(id) {
                        match *action {
                            ParseAction::Shift { is_repetition, .. } => {
                                is_repetition.hash(&mut hasher);
                            }
                            action => action.hash(&mut hasher),
                        }
                    }
                }
                hasher.finish()
            })
            .collect::<Vec<_>>();

        Self {
            minimizer,
            entry_maps,
            bits: ConflictBits::new(minimizer),
            static_signatures,
            shift_maps,
            kept: KeptStates::new(minimizer.indexer),
        }
    }

    /// Whether the state has an entry for `key`.
    fn has_token(&self, state: &ParseState, key: SymbolKey) -> bool {
        if let Some(index) = key.symbol(self.minimizer.indexer).terminal_index() {
            let row = self.bits.get_state_row(state.id as usize);
            let index = usize::from(index);
            row[index / 64] & (1 << (index % 64)) != 0
        } else {
            self.entry_maps
                .get(state)
                .binary_search_by_key(&key, |&(key, _)| key)
                .is_ok()
        }
    }

    /// Whether `key` can be added to `target`, or `target` already has it.
    fn can_take(&self, target: &ParseState, key: SymbolKey) -> bool {
        self.has_token(target, key)
            || self
                .minimizer
                .token_conflicts(target, &self.bits, key)
                .is_none()
    }

    /// [`SplitCriterion::compatible_with_all`], with the kept states merged into `kept_states`.
    fn compatible_with_merged(
        &self,
        kept_states: &mut KeptStates,
        state: &ParseState,
        kept: &[u32],
        group_ids_by_state_id: &[ParseStateId],
    ) -> bool {
        let states = &self.minimizer.parse_table.states;
        for &(key, action_list) in self.entry_maps.get(state) {
            let token = kept_states.tokens[key.index()];
            if let Some(kept_action_list) = token.action_list
                && self
                    .minimizer
                    .entries_conflict(kept_action_list, action_list, group_ids_by_state_id)
                    .is_some()
            {
                return false;
            }
            if (token.count as usize) < kept.len()
                && !kept_states.addable_to_all(key, kept, |kept_id| {
                    self.can_take(&states[kept_id as usize], key)
                })
            {
                return false;
            }
        }
        kept_states
            .merged_tokens
            .iter()
            .all(|&key| self.can_take(state, key))
    }
}

/// What the states kept so far in a group of the conflict pass have in common, to check a state
/// against all of them at once. Kept states never need to be split from each other, so any two
/// agree on every token they share, and one entry per token stands for all of them.
#[derive(Default)]
struct KeptStates {
    /// What the merged states have for each token, by [`SymbolIndexer::index`].
    tokens: Vec<KeptToken>,
    /// How many of the kept states are merged into `tokens`.
    merged_count: usize,
    /// The tokens that some merged state has.
    merged_tokens: Vec<SymbolKey>,
    /// The tokens that have been checked against kept states lacking them.
    checked_tokens: Vec<SymbolKey>,
}

/// What the kept states have for a token. See [`KeptStates`].
#[derive(Clone, Copy, Default)]
struct KeptToken {
    /// The action list of the first merged state with this token.
    action_list: Option<ActionListId>,
    /// How many merged states have this token.
    count: u32,
    /// Whether this token can be added to the kept states that lack it.
    addable: Addable,
}

/// Whether a token can be added to the kept states that lack it, as far as they've been
/// checked, in order.
#[derive(Clone, Copy)]
enum Addable {
    /// To each of the first this many kept states.
    UpTo(u32),
    /// Not to one of them.
    Blocked,
}

impl Default for Addable {
    fn default() -> Self {
        Self::UpTo(0)
    }
}

impl KeptStates {
    fn new(indexer: SymbolIndexer) -> Self {
        Self {
            tokens: vec![KeptToken::default(); indexer.token_count() as usize],
            merged_count: 0,
            merged_tokens: Vec::new(),
            checked_tokens: Vec::new(),
        }
    }

    /// Forgets the kept states, for the next group.
    fn clear(&mut self) {
        for key in self
            .merged_tokens
            .drain(..)
            .chain(self.checked_tokens.drain(..))
        {
            self.tokens[key.index()] = KeptToken::default();
        }
        self.merged_count = 0;
    }

    /// Merges the entries of the kept states that aren't merged yet.
    fn merge(
        &mut self,
        kept: &[u32],
        states: &[ParseState],
        entry_maps: &StateLists<(SymbolKey, ActionListId)>,
    ) {
        for &state_id in &kept[self.merged_count..] {
            for &(key, action_list) in entry_maps.get(&states[state_id as usize]) {
                let token = &mut self.tokens[key.index()];
                if token.action_list.is_none() {
                    token.action_list = Some(action_list);
                    self.merged_tokens.push(key);
                }
                token.count += 1;
            }
        }
        self.merged_count = kept.len();
    }

    /// Whether `key` can be added to every kept state that lacks it, asking `can_take` about
    /// each kept state at most once per group: the answer doesn't depend on the state being
    /// checked.
    fn addable_to_all(
        &mut self,
        key: SymbolKey,
        kept: &[u32],
        mut can_take: impl FnMut(u32) -> bool,
    ) -> bool {
        let token = &mut self.tokens[key.index()];
        let Addable::UpTo(checked) = token.addable else {
            return false;
        };
        if checked == 0 {
            self.checked_tokens.push(key);
        }
        for &kept_id in &kept[checked as usize..] {
            if !can_take(kept_id) {
                token.addable = Addable::Blocked;
                return false;
            }
        }
        token.addable = Addable::UpTo(kept.len() as u32);
        true
    }
}

impl SplitCriterion<ParseState> for ConflictPass<'_, '_> {
    fn should_split(
        &mut self,
        left: &ParseState,
        right: &ParseState,
        group_ids_by_state_id: &[ParseStateId],
    ) -> bool {
        self.minimizer.states_conflict(
            left,
            right,
            group_ids_by_state_id,
            &self.entry_maps,
            &self.bits,
        )
    }

    fn signature(
        &mut self,
        state: &ParseState,
        group_ids_by_state_id: &[ParseStateId],
    ) -> Option<u64> {
        let mut hasher = FxHasher::default();
        self.static_signatures[state.id as usize].hash(&mut hasher);
        for &(_, successor) in self.shift_maps.get(state) {
            group_ids_by_state_id[successor as usize].hash(&mut hasher);
        }
        Some(hasher.finish())
    }

    /// Whether two states have the same reserved words and terminal entries, with shift
    /// targets compared by group. Then [`Minimizer::states_conflict`] never separates them,
    /// and separates either from exactly the same states.
    fn equivalent(
        &mut self,
        left: &ParseState,
        right: &ParseState,
        group_ids_by_state_id: &[ParseStateId],
    ) -> bool {
        let entries1 = self.entry_maps.get(left);
        let entries2 = self.entry_maps.get(right);
        let action_lists = &self.minimizer.parse_table.action_lists;
        left.reserved_words == right.reserved_words
            && entries1.len() == entries2.len()
            && entries1
                .iter()
                .zip(entries2)
                .all(|(&(key1, id1), &(key2, id2))| {
                    if key1 != key2 {
                        return false;
                    }
                    if id1.index() == id2.index() {
                        return true;
                    }
                    let actions1 = action_lists.get(id1);
                    let actions2 = action_lists.get(id2);
                    actions1.len() == actions2.len()
                        && actions1.iter().zip(actions2).all(|pair| match pair {
                            (
                                ParseAction::Shift {
                                    state: s1,
                                    is_repetition: is_repetition1,
                                },
                                ParseAction::Shift {
                                    state: s2,
                                    is_repetition: is_repetition2,
                                },
                            ) => {
                                group_ids_by_state_id[*s1 as usize]
                                    == group_ids_by_state_id[*s2 as usize]
                                    && is_repetition1 == is_repetition2
                            }
                            (action1, action2) => action1 == action2,
                        })
                })
    }

    fn start_group(&mut self) {
        self.kept.clear();
    }

    /// Checks `state` against what the kept states have in common, which covers everything
    /// [`Minimizer::states_conflict`] compares:
    /// - the tokens `state` shares with kept states, whose entries all agree.
    /// - `state`'s tokens that some kept state lacks, which must be addable to it.
    /// - the kept states' tokens that `state` lacks, which must be addable to `state`.
    fn compatible_with_all(
        &mut self,
        state: &ParseState,
        kept: &[u32],
        group_ids_by_state_id: &[ParseStateId],
    ) -> bool {
        self.kept
            .merge(kept, &self.minimizer.parse_table.states, &self.entry_maps);
        // The check reads the rest of `self` while it updates the scratch.
        let mut kept_states = mem::take(&mut self.kept);
        let compatible =
            self.compatible_with_merged(&mut kept_states, state, kept, group_ids_by_state_id);
        self.kept = kept_states;
        compatible
    }
}

/// The second pass of [`Minimizer::merge_compatible_states`], repeated until nothing splits:
/// splits states whose successors are in different groups.
struct SuccessorPass<'min, 'a> {
    minimizer: &'min Minimizer<'a>,
    /// Each state's shift targets, sorted by symbol.
    shift_maps: StateLists<(SymbolKey, ParseStateId)>,
    /// Each state's nonterminal entries, sorted by symbol.
    nonterminal_maps: StateLists<(NonterminalIndex, GotoAction)>,
}

impl<'min, 'a> SuccessorPass<'min, 'a> {
    fn new(
        minimizer: &'min Minimizer<'a>,
        shift_maps: StateLists<(SymbolKey, ParseStateId)>,
    ) -> Self {
        // Store only the symbol index: all nonterminal entries share the same kind,
        // so index alone is sufficient for sorting and comparison.
        let nonterminal_maps = StateLists::collect(
            minimizer.parse_table.states.iter().map(|state| {
                state.nonterminal_entries.iter().map(|(sym, action)| {
                    let Some(index) = sym.non_terminal_index() else {
                        unreachable!();
                    };
                    (u32::from(index), *action)
                })
            }),
            |&(index, _)| index,
        );

        Self {
            minimizer,
            shift_maps,
            nonterminal_maps,
        }
    }
}

impl SplitCriterion<ParseState> for SuccessorPass<'_, '_> {
    fn should_split(
        &mut self,
        left: &ParseState,
        right: &ParseState,
        group_ids_by_state_id: &[ParseStateId],
    ) -> bool {
        self.minimizer.state_successors_differ(
            left,
            right,
            group_ids_by_state_id,
            &self.shift_maps,
            &self.nonterminal_maps,
        )
    }

    fn signature(
        &mut self,
        state: &ParseState,
        group_ids_by_state_id: &[ParseStateId],
    ) -> Option<u64> {
        let mut hasher = FxHasher::default();
        for &(key, successor) in self.shift_maps.get(state) {
            (key.0, group_ids_by_state_id[successor as usize]).hash(&mut hasher);
        }
        for &(index, action) in self.nonterminal_maps.get(state) {
            let group = match action {
                GotoAction::Goto(successor) => Some(group_ids_by_state_id[successor as usize]),
                GotoAction::ShiftExtra => None,
            };
            (index, group).hash(&mut hasher);
        }
        Some(hasher.finish())
    }

    /// Whether two states shift and go to on the same symbols, with successors in the same
    /// groups. Then [`Minimizer::state_successors_differ`] never separates them, and separates
    /// either from exactly the same states.
    fn equivalent(
        &mut self,
        left: &ParseState,
        right: &ParseState,
        group_ids_by_state_id: &[ParseStateId],
    ) -> bool {
        let shifts1 = self.shift_maps.get(left);
        let shifts2 = self.shift_maps.get(right);
        let gotos1 = self.nonterminal_maps.get(left);
        let gotos2 = self.nonterminal_maps.get(right);
        shifts1.len() == shifts2.len()
            && gotos1.len() == gotos2.len()
            && shifts1
                .iter()
                .zip(shifts2)
                .all(|(&(key1, s1), &(key2, s2))| {
                    key1 == key2
                        && group_ids_by_state_id[s1 as usize] == group_ids_by_state_id[s2 as usize]
                })
            && gotos1
                .iter()
                .zip(gotos2)
                .all(|(&(index1, action1), &(index2, action2))| {
                    index1 == index2
                        && match (action1, action2) {
                            (GotoAction::Goto(s1), GotoAction::Goto(s2)) => {
                                group_ids_by_state_id[s1 as usize]
                                    == group_ids_by_state_id[s2 as usize]
                            }
                            (GotoAction::ShiftExtra, GotoAction::ShiftExtra) => true,
                            _ => false,
                        }
                })
    }
}

/// Why two states can't be merged: either their entries for a token differ, or a token that
/// only one of them has can't be added to the other.
#[derive(Clone, Copy)]
enum Conflict {
    /// Their entries have different numbers of actions.
    ActionCounts,
    /// Their entries shift to these states, which are in different groups.
    SplitSuccessors(ParseStateId, ParseStateId),
    /// Their entries have different actions.
    UnequalActions,
    /// The token ends a non-terminal extra.
    EndOfNonTerminalExtra,
    /// The token is external, so it could conflict lexically with any of the other state's.
    ExternalToken,
    /// The token is both internal and external.
    InternalExternalToken,
    /// The token conflicts lexically with this terminal, which the other state has.
    Lexical(usize),
}

struct Minimizer<'a> {
    parse_table: &'a mut ParseTable,
    syntax_grammar: &'a SyntaxGrammar,
    lexical_grammar: &'a LexicalGrammar,
    /// Gives each symbol its [`SymbolKey`].
    indexer: SymbolIndexer,
    token_conflict_map: &'a TokenConflictMap,
    keywords: &'a TokenSet,
    simple_aliases: &'a AliasMap,
    str_pool: &'a StrPool,
}

impl Minimizer<'_> {
    fn remove_unit_reductions(&mut self) {
        let mut aliased_symbols = FxHashSet::default();
        for i in 0..self.syntax_grammar.variables.len() {
            for prod_id in self.syntax_grammar.variable_prod_ids(i) {
                for step in self.syntax_grammar.production(prod_id).steps {
                    if step.alias().is_some() {
                        aliased_symbols.insert(step.symbol());
                    }
                }
            }
        }

        let mut unit_reduction_symbols_by_state = FxHashMap::default();
        for (i, state) in self.parse_table.states.iter().enumerate() {
            if state.has_eof_gated_reduce {
                continue;
            }
            let mut only_unit_reductions = true;
            let mut unit_reduction_symbol = None;
            for (_, id) in state.terminal_entries.iter() {
                for action in self.parse_table.action_lists.get(*id) {
                    match action {
                        ParseAction::ShiftExtra => continue,
                        ParseAction::Reduce {
                            child_count: 1,
                            production_id: 0,
                            symbol,
                            ..
                        } if !self.simple_aliases.contains_key(symbol)
                            && !self.syntax_grammar.supertype_symbols.contains(symbol)
                            && !self.syntax_grammar.extra_symbols.contains(symbol)
                            && !aliased_symbols.contains(symbol)
                            && matches!(symbol.non_terminal_index(), Some(index)
                                    if self.syntax_grammar.variables[usize::from(index)].kind
                                        != VariableType::Named
                            )
                            && (unit_reduction_symbol.is_none()
                                || unit_reduction_symbol == Some(symbol)) =>
                        {
                            unit_reduction_symbol = Some(symbol);
                            continue;
                        }
                        _ => {}
                    }
                    only_unit_reductions = false;
                    break;
                }

                if !only_unit_reductions {
                    break;
                }
            }

            if let Some(symbol) = unit_reduction_symbol
                && only_unit_reductions
            {
                unit_reduction_symbols_by_state.insert(i as u32, *symbol);
            }
        }

        if unit_reduction_symbols_by_state.is_empty() {
            return;
        }

        let mut action_list_ids = FxHashMap::default();
        for state_index in 0..self.parse_table.states.len() {
            let mut done = false;
            while !done {
                done = true;
                let ParseTable {
                    states,
                    action_lists,
                    ..
                } = self.parse_table;
                let state = &mut states[state_index];

                state.update_nonterminal_references(|other_state_id, state| {
                    unit_reduction_symbols_by_state.get(&other_state_id).map_or(
                        other_state_id,
                        |symbol| {
                            done = false;
                            match state.nonterminal_entries.get(*symbol) {
                                Some(GotoAction::Goto(state_id)) => *state_id,
                                _ => other_state_id,
                            }
                        },
                    )
                });

                for i in 0..state.terminal_entries.len() {
                    let old_id = state.terminal_entries.get_index(i).unwrap().1;
                    let mut actions = ActionList::from_slice(action_lists.get(*old_id));
                    let mut changed = false;
                    for action in &mut *actions {
                        // A Shift onto a unit-reduction state (one whose only action reduces a
                        // single `symbol`) can skip it. Shift then reduce then goto is equivalent
                        // to shifting straight to the the goto target for `symbol` in this case.
                        if let ParseAction::Shift { state: target, .. } = action
                            && let Some(symbol) = unit_reduction_symbols_by_state.get(target)
                            && let Some(GotoAction::Goto(new_target)) =
                                state.nonterminal_entries.get(*symbol)
                            && *new_target != *target
                        {
                            *target = *new_target;
                            changed = true;
                            done = false;
                        }
                    }
                    if changed {
                        let index = action_lists.intern(&mut action_list_ids, actions);
                        *state.terminal_entries.get_index_mut(i).unwrap().1 =
                            ActionListId::new(index, old_id.reusable());
                    }
                }
            }
        }
    }

    fn merge_compatible_states(&mut self) {
        let core_count = 1 + self
            .parse_table
            .states
            .iter()
            .map(|state| state.core_id)
            .max()
            .unwrap();

        // Initially group the states by their parse item set core.
        let mut group_ids_by_state_id = Vec::with_capacity(self.parse_table.states.len());
        // Pre-allocate for the maximum possible number of groups (one per state) to
        // avoid reallocs as split_state_id_groups pushes new groups.
        let mut state_ids_by_group_id = Vec::with_capacity(self.parse_table.states.len());
        state_ids_by_group_id.resize(core_count as usize, Vec::new());
        for (i, state) in self.parse_table.states.iter().enumerate() {
            state_ids_by_group_id[state.core_id as usize].push(i as u32);
            group_ids_by_state_id.push(state.core_id);
        }

        // Precompute per-state sorted shift actions, for both passes.
        // State actions are stable across loop iterations; only group assignments change.
        // Keys are symbol positions, for single-instruction comparison.
        let shift_maps = StateLists::collect(
            self.parse_table.states.iter().map(|state| {
                state.terminal_entries.iter().filter_map(|(sym, entry)| {
                    let action = self.parse_table.action_lists.get(*entry).last()?;
                    if let ParseAction::Shift { state: s, .. } = action {
                        Some((SymbolKey::new(self.indexer, *sym), *s))
                    } else {
                        None
                    }
                })
            }),
            |&(key, _)| key,
        );

        let mut conflict_pass = ConflictPass::new(self, &shift_maps);
        split_state_id_groups(
            &self.parse_table.states,
            &mut state_ids_by_group_id,
            &mut group_ids_by_state_id,
            0,
            &mut conflict_pass,
        );
        drop(conflict_pass); // The rest only looks at successors.

        let mut successor_pass = SuccessorPass::new(self, shift_maps);

        while split_state_id_groups(
            &self.parse_table.states,
            &mut state_ids_by_group_id,
            &mut group_ids_by_state_id,
            0,
            &mut successor_pass,
        ) {}
        drop(successor_pass);

        let error_group_index = state_ids_by_group_id
            .iter()
            .position(|g| g.contains(&0))
            .unwrap();
        let start_group_index = state_ids_by_group_id
            .iter()
            .position(|g| g.contains(&1))
            .unwrap();
        state_ids_by_group_id.swap(error_group_index, 0);
        state_ids_by_group_id.swap(start_group_index, 1);

        // Create a list of new parse states: one state for each group of old states.
        let mut new_states = Vec::with_capacity(state_ids_by_group_id.len());
        // Scratch for merging: the position of each symbol's entry in the new state, by
        // `SymbolIndexer::index`.
        let mut positions = vec![None; self.indexer.symbol_count() as usize];
        for state_ids in &state_ids_by_group_id {
            // Initialize the new state based on the first old state in the group.
            let mut parse_state = mem::take(&mut self.parse_table.states[state_ids[0] as usize]);
            set_positions(&parse_state.terminal_entries, &mut positions, self.indexer);
            set_positions(
                &parse_state.nonterminal_entries,
                &mut positions,
                self.indexer,
            );

            // Extend the new state with all of the actions from the other old states
            // in the group.
            for state_id in &state_ids[1..] {
                let other_parse_state = mem::take(&mut self.parse_table.states[*state_id as usize]);

                parse_state.has_eof_gated_reduce |= other_parse_state.has_eof_gated_reduce;
                merge_entries(
                    &mut parse_state.terminal_entries,
                    other_parse_state.terminal_entries,
                    &mut positions,
                    self.indexer,
                );
                merge_entries(
                    &mut parse_state.nonterminal_entries,
                    other_parse_state.nonterminal_entries,
                    &mut positions,
                    self.indexer,
                );
                parse_state
                    .reserved_words
                    .insert_all(&other_parse_state.reserved_words);
                for &symbol in parse_state.terminal_entries.keys() {
                    parse_state.reserved_words.remove(symbol);
                }
            }

            for symbol in parse_state
                .terminal_entries
                .keys()
                .chain(parse_state.nonterminal_entries.keys())
            {
                positions[self.indexer.index(*symbol)] = None;
            }

            // Update the new state's outgoing references using the new grouping.
            parse_state.update_nonterminal_references(|state_id, _| {
                group_ids_by_state_id[state_id as usize]
            });
            new_states.push(parse_state);
        }

        self.parse_table.states = new_states;
        self.parse_table
            .remap_terminal_references(|state_id| group_ids_by_state_id[state_id as usize]);
    }

    fn states_conflict(
        &self,
        state1: &ParseState,
        state2: &ParseState,
        group_ids_by_state_id: &[ParseStateId],
        entry_maps: &StateLists<(SymbolKey, ActionListId)>,
        bits: &ConflictBits,
    ) -> bool {
        let entries1 = entry_maps.get(state1);
        let entries2 = entry_maps.get(state2);
        let len1 = entries1.len();
        let len2 = entries2.len();
        let mut i = 0;
        let mut j = 0;
        while i < len1 || j < len2 {
            // SAFETY: each branch only accesses entries1[i] when i < len1
            // and entries2[j] when j < len2, both of which hold by construction.
            let ord = if i < len1 && j < len2 {
                unsafe { entries1.get_unchecked(i) }
                    .0
                    .cmp(&unsafe { entries2.get_unchecked(j) }.0)
            } else if i < len1 {
                Ordering::Less
            } else {
                Ordering::Greater
            };
            match ord {
                Ordering::Equal => {
                    // SAFETY: Equal is only reachable when i < len1 && j < len2.
                    let e1 = unsafe { entries1.get_unchecked(i) };
                    let e2 = unsafe { entries2.get_unchecked(j) };
                    if let Some(conflict) = self.entries_conflict(e1.1, e2.1, group_ids_by_state_id)
                    {
                        self.log_conflict(state1.id, state2.id, e1.0, conflict);
                        return true;
                    }
                    i += 1;
                    j += 1;
                }
                Ordering::Less => {
                    // SAFETY: Less is only reachable when i < len1.
                    let e1 = unsafe { entries1.get_unchecked(i) };
                    if let Some(conflict) = self.token_conflicts(state2, bits, e1.0) {
                        self.log_conflict(state1.id, state2.id, e1.0, conflict);
                        return true;
                    }
                    i += 1;
                }
                Ordering::Greater => {
                    // SAFETY: Greater is only reachable when j < len2.
                    let e2 = unsafe { entries2.get_unchecked(j) };
                    if let Some(conflict) = self.token_conflicts(state1, bits, e2.0) {
                        self.log_conflict(state1.id, state2.id, e2.0, conflict);
                        return true;
                    }
                    j += 1;
                }
            }
        }
        false
    }

    fn state_successors_differ(
        &self,
        state1: &ParseState,
        state2: &ParseState,
        group_ids_by_state_id: &[ParseStateId],
        shift_maps: &StateLists<(SymbolKey, ParseStateId)>,
        nonterminal_maps: &StateLists<(NonterminalIndex, GotoAction)>,
    ) -> bool {
        let shifts1 = shift_maps.get(state1);
        let shifts2 = shift_maps.get(state2);
        let mut i = 0;
        let mut j = 0;
        while i < shifts1.len() && j < shifts2.len() {
            // SAFETY: loop condition ensures i < shifts1.len() and j < shifts2.len().
            let (k1, s1) = *unsafe { shifts1.get_unchecked(i) };
            let (k2, s2) = *unsafe { shifts2.get_unchecked(j) };
            match k1.cmp(&k2) {
                Ordering::Less => i += 1,
                Ordering::Greater => j += 1,
                Ordering::Equal => {
                    let group1 = group_ids_by_state_id[s1 as usize];
                    let group2 = group_ids_by_state_id[s2 as usize];
                    if group1 != group2 {
                        debug!(
                            "split states {} {} - successors for {} are split: {s1} {s2}",
                            state1.id,
                            state2.id,
                            self.symbol_name(k1.symbol(self.indexer)),
                        );
                        return true;
                    }
                    i += 1;
                    j += 1;
                }
            }
        }

        let nonterms1 = nonterminal_maps.get(state1);
        let nonterms2 = nonterminal_maps.get(state2);
        let mut i = 0;
        let mut j = 0;
        while i < nonterms1.len() && j < nonterms2.len() {
            // SAFETY: loop condition ensures i < nonterms1.len() and j < nonterms2.len().
            let (idx1, s1) = *unsafe { nonterms1.get_unchecked(i) };
            let (idx2, s2) = *unsafe { nonterms2.get_unchecked(j) };
            match idx1.cmp(&idx2) {
                Ordering::Less => i += 1,
                Ordering::Greater => j += 1,
                Ordering::Equal => {
                    match (s1, s2) {
                        (GotoAction::ShiftExtra, GotoAction::ShiftExtra) => {}
                        (GotoAction::Goto(s1), GotoAction::Goto(s2)) => {
                            let group1 = group_ids_by_state_id[s1 as usize];
                            let group2 = group_ids_by_state_id[s2 as usize];
                            if group1 != group2 {
                                debug!(
                                    "split states {} {} - successors for {} are split: {s1} {s2}",
                                    state1.id,
                                    state2.id,
                                    self.str_pool
                                        .resolve(self.syntax_grammar.variables[idx1 as usize].name),
                                );
                                return true;
                            }
                        }
                        _ => return true,
                    }
                    i += 1;
                    j += 1;
                }
            }
        }

        false
    }

    /// Why two entries for the same token can't be merged.
    #[inline]
    fn entries_conflict(
        &self,
        id1: ActionListId,
        id2: ActionListId,
        group_ids_by_state_id: &[ParseStateId],
    ) -> Option<Conflict> {
        // To be compatible, entries need to have the same actions.
        if id1.index() == id2.index() {
            None
        } else {
            self.action_lists_conflict(id1, id2, group_ids_by_state_id)
        }
    }

    /// [`Self::entries_conflict`] for entries with different action lists.
    fn action_lists_conflict(
        &self,
        id1: ActionListId,
        id2: ActionListId,
        group_ids_by_state_id: &[ParseStateId],
    ) -> Option<Conflict> {
        let actions1 = self.parse_table.action_lists.get(id1);
        let actions2 = self.parse_table.action_lists.get(id2);
        if actions1.len() != actions2.len() {
            return Some(Conflict::ActionCounts);
        }

        for (action1, action2) in actions1.iter().zip(actions2.iter()) {
            // Two shift actions are equivalent if their destinations are in the same group.
            if let (
                ParseAction::Shift {
                    state: s1,
                    is_repetition: is_repetition1,
                },
                ParseAction::Shift {
                    state: s2,
                    is_repetition: is_repetition2,
                },
            ) = (action1, action2)
            {
                let group1 = group_ids_by_state_id[*s1 as usize];
                let group2 = group_ids_by_state_id[*s2 as usize];
                if group1 == group2 && is_repetition1 == is_repetition2 {
                    continue;
                }
                return Some(Conflict::SplitSuccessors(*s1, *s2));
            } else if action1 != action2 {
                return Some(Conflict::UnequalActions);
            }
        }

        None
    }

    /// Why `new_token` can't be added to `right_state`, if it can't.
    #[inline]
    fn token_conflicts(
        &self,
        right_state: &ParseState,
        bits: &ConflictBits,
        new_token: SymbolKey,
    ) -> Option<Conflict> {
        let (new_token_index, new_token_is_terminal) = match new_token.symbol(self.indexer).view() {
            SymbolView::EndOfNonTerminalExtra => return Some(Conflict::EndOfNonTerminalExtra),
            // Do not add external tokens, as they could conflict lexically with
            // any of the state's existing lookahead tokens.
            SymbolView::External(_) => return Some(Conflict::ExternalToken),
            SymbolView::End => (0, false),
            SymbolView::Terminal(index) => (usize::from(index), true),
            SymbolView::NonTerminal(_) => unreachable!(),
        };

        let is_reserved = if new_token_is_terminal {
            right_state
                .reserved_words
                .contains_terminal(new_token_index)
        } else {
            right_state.reserved_words.contains(Symbol::End)
        };
        if is_reserved {
            return None;
        }

        // Do not add tokens which are both internal and external. Their validity could
        // influence the behavior of the external scanner. `bits.internal_external` is
        // indexed by terminal index only.
        if new_token_is_terminal
            && bits.internal_external[new_token_index / 64] & (1 << (new_token_index % 64)) != 0
        {
            return Some(Conflict::InternalExternalToken);
        }

        let new_token_is_word = bits.word_token.is_some_and(|(word, _)| word == new_token);
        let new_token_is_keyword = bits.word_token.is_some()
            && if new_token_is_terminal {
                bits.keywords[new_token_index / 64] & (1 << (new_token_index % 64)) != 0
            } else {
                self.keywords.contains(Symbol::End)
            };
        // Do not add a token if it conflicts with an existing token. Test the candidate's
        // conflict row against the state's terminal bits, masking out the word/keyword
        // exemptions.
        let row = bits.get_conflict_row(new_token_index);
        let right_terminal_bits = bits.get_state_row(right_state.id as usize);
        for (w, &row_word) in row.iter().enumerate() {
            let mut candidates = right_terminal_bits[w] & row_word;
            if new_token_is_keyword
                && let Some((_, word)) = bits.word_token
                && word / 64 == w
            {
                candidates &= !(1u64 << (word % 64));
            }
            if new_token_is_word {
                candidates &= !bits.keywords[w];
            }
            if candidates != 0 {
                return Some(Conflict::Lexical(
                    w * 64 + candidates.trailing_zeros() as usize,
                ));
            }
        }

        None
    }

    /// Logs that the states `id1` and `id2` are split because of `conflict`, over `token`.
    fn log_conflict(
        &self,
        id1: ParseStateId,
        id2: ParseStateId,
        token: SymbolKey,
        conflict: Conflict,
    ) {
        match conflict {
            Conflict::ActionCounts => debug!(
                "split states {id1} {id2} - differing action counts for token {}",
                self.symbol_name(token.symbol(self.indexer))
            ),
            Conflict::SplitSuccessors(s1, s2) => debug!(
                "split states {id1} {id2} - successors for {} are split: {s1} {s2}",
                self.symbol_name(token.symbol(self.indexer)),
            ),
            Conflict::UnequalActions => debug!(
                "split states {id1} {id2} - unequal actions for {}",
                self.symbol_name(token.symbol(self.indexer)),
            ),
            Conflict::EndOfNonTerminalExtra => {
                debug!("split states {id1} {id2} - end of non-terminal extra");
            }
            Conflict::ExternalToken => debug!(
                "split states {id1} {id2} - external token {}",
                self.symbol_name(token.symbol(self.indexer)),
            ),
            Conflict::InternalExternalToken => debug!(
                "split states {id1} {id2} - internal/external token {}",
                self.symbol_name(token.symbol(self.indexer)),
            ),
            Conflict::Lexical(terminal) => debug!(
                "split states {id1} {id2} - token {} conflicts with {}",
                self.symbol_name(token.symbol(self.indexer)),
                self.symbol_name(Symbol::terminal(terminal)),
            ),
        }
    }

    fn symbol_name(&self, symbol: Symbol) -> &str {
        match symbol.view() {
            SymbolView::NonTerminal(index) => self
                .str_pool
                .resolve(self.syntax_grammar.variables[usize::from(index)].name),
            SymbolView::External(index) => self
                .str_pool
                .resolve(self.syntax_grammar.external_tokens[usize::from(index)].name),
            SymbolView::Terminal(index) => self
                .str_pool
                .resolve(self.lexical_grammar.variables[usize::from(index)].name),
            SymbolView::End => "<EOF>",
            SymbolView::EndOfNonTerminalExtra => "<END_OF_NONTERMINAL_EXTRA>",
        }
    }

    fn remove_unused_states(&mut self) {
        let mut state_usage_map = vec![false; self.parse_table.states.len()];

        state_usage_map[0] = true;
        state_usage_map[1] = true;

        for state in &self.parse_table.states {
            for referenced_state in state.referenced_states(&self.parse_table.action_lists) {
                state_usage_map[referenced_state as usize] = true;
            }
        }
        let mut removed_predecessor_count = 0;
        let mut state_replacement_map = vec![0; self.parse_table.states.len()];
        for state_id in 0..self.parse_table.states.len() {
            state_replacement_map[state_id] = (state_id - removed_predecessor_count) as u32;
            if !state_usage_map[state_id] {
                removed_predecessor_count += 1;
            }
        }
        let mut state_id = 0;
        let mut original_state_id = 0;
        while state_id < self.parse_table.states.len() {
            if state_usage_map[original_state_id] {
                self.parse_table.states[state_id].update_nonterminal_references(
                    |other_state_id, _| state_replacement_map[other_state_id as usize],
                );
                state_id += 1;
            } else {
                self.parse_table.states.remove(state_id);
            }
            original_state_id += 1;
        }
        self.parse_table
            .remap_terminal_references(|state_id| state_replacement_map[state_id as usize]);
    }

    fn reorder_states_by_descending_size(&mut self) {
        // Get a mapping of old state index -> new_state_index
        let mut old_ids_by_new_id = (0..self.parse_table.states.len()).collect::<Vec<_>>();
        old_ids_by_new_id.sort_unstable_by_key(|i| {
            // Don't change states 0 (the error state) or 1 (the start state).
            if *i <= 1 {
                return *i as i64 - 1_000_000;
            }

            // Reorder all the other states by descending symbol count.
            let state = &self.parse_table.states[*i];
            -((state.terminal_entries.len() + state.nonterminal_entries.len()) as i64)
        });

        // Get the inverse mapping
        let mut new_ids_by_old_id = vec![0; old_ids_by_new_id.len()];
        for (id, old_id) in old_ids_by_new_id.iter().enumerate() {
            new_ids_by_old_id[*old_id] = id as u32;
        }

        // Reorder the parse states and update their references to reflect
        // the new ordering.
        self.parse_table.states = old_ids_by_new_id
            .iter()
            .map(|old_id| {
                let mut state = ParseState::default();
                mem::swap(&mut state, &mut self.parse_table.states[*old_id]);
                state.update_nonterminal_references(|id, _| new_ids_by_old_id[id as usize]);
                state
            })
            .collect();
        self.parse_table
            .remap_terminal_references(|id| new_ids_by_old_id[id as usize]);
    }
}

/// Records the position of each of `entries`' symbols in `positions`, by
/// [`SymbolIndexer::index`].
fn set_positions<V>(
    entries: &ParseStateEntries<V>,
    positions: &mut [Option<usize>],
    indexer: SymbolIndexer,
) {
    for (position, symbol) in entries.keys().enumerate() {
        positions[indexer.index(*symbol)] = Some(position);
    }
}

/// Merges `other` into `entries` like `IndexMap::extend`: a symbol that `entries` already has
/// keeps its place and takes `other`'s value, and the rest are added in order. `positions` holds
/// the position of each of `entries`' symbols, by [`SymbolIndexer::index`].
fn merge_entries<V>(
    entries: &mut ParseStateEntries<V>,
    other: ParseStateEntries<V>,
    positions: &mut [Option<usize>],
    indexer: SymbolIndexer,
) {
    for (symbol, value) in other {
        let position = &mut positions[indexer.index(symbol)];
        if let Some(position) = *position {
            // INVARIANT: `positions` only holds positions of `entries`' entries.
            *entries.get_index_mut(position).unwrap().1 = value;
        } else {
            *position = Some(entries.len());
            entries.push(symbol, value);
        }
    }
}
